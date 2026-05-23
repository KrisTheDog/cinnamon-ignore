#include "../data_win.h"
#include "../runner.h"
#include "../runner_keyboard.h"
#include "../utils.h"
#include "../vm.h"

#include "n3ds_audio_system.h"
#include "n3ds_file_system.h"
#include "n3ds_renderer.h"

#include <3ds.h>
#include <citro2d.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define N3DS_ENABLE_CONSOLE 1
#define N3DS_LOADING_TEXT_SCALE 0.42f

typedef struct {
    bool useCitro2D;
    C3D_RenderTarget* target;
    C2D_TextBuf textBuf;
    PrintConsole console;
    char statusLine[128];
    int chunkIndex;
    int totalChunks;
} N3DSLoadingScreen;

static PrintConsole gN3DSLogConsole;
static bool gN3DSHasLogConsole = false;

static bool fileExists(const char* path) {
    struct stat st;
    return stat(path, &st) == 0;
}

static char* chooseDataWinPath(void) {
    if (fileExists("sdmc:/3ds/cinnamon/data.win")) return safeStrdup("sdmc:/3ds/cinnamon/data.win");
    return safeStrdup("romfs:/data.win");
}

static void syncKey(RunnerKeyboardState* keyboard, bool* state, int32_t key, bool held) {
    if (held && !*state) RunnerKeyboard_onKeyDown(keyboard, key);
    if (!held && *state) RunnerKeyboard_onKeyUp(keyboard, key);
    *state = held;
}

static void N3DSLoadingScreen_free(N3DSLoadingScreen* screen) {
    if (screen == NULL) return;
    if (screen->textBuf != NULL) {
        C2D_TextBufDelete(screen->textBuf);
        screen->textBuf = NULL;
    }
    if (screen->target != NULL) {
        C3D_RenderTargetDelete(screen->target);
        screen->target = NULL;
    }
}

void Runner_platformBootLog(const char* message) {
    if (N3DS_ENABLE_CONSOLE && message != NULL) {
        printf("%s\n", message);
    }
}

static void N3DS_activateLogConsole(void) {
    if (N3DS_ENABLE_CONSOLE && gN3DSHasLogConsole) {
        consoleSelect(&gN3DSLogConsole);
    }
}

static void N3DSLoadingScreen_draw(N3DSLoadingScreen* screen) {
    if (screen == NULL) return;

    float progress = 0.0f;
    if (screen->totalChunks > 0) {
        progress = (float) screen->chunkIndex / (float) screen->totalChunks;
        if (progress < 0.0f) progress = 0.0f;
        if (progress > 1.0f) progress = 1.0f;
    }

    if (screen->useCitro2D && screen->target != NULL && screen->textBuf != NULL) {
        const float barX = 36.0f;
        const float barY = 146.0f;
        const float barW = 328.0f;
        const float barH = 18.0f;
        const float fillW = (barW - 4.0f) * progress;

        C2D_Text title;
        C2D_Text status;
        C2D_Text detail;
        char detailLine[64];
        snprintf(detailLine, sizeof(detailLine), "%d / %d chunks", screen->chunkIndex, screen->totalChunks);

        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        C2D_TargetClear(screen->target, C2D_Color32(8, 10, 14, 255));
        C2D_SceneBegin(screen->target);

        C2D_DrawRectSolid(0.0f, 0.0f, 0.5f, 400.0f, 240.0f, C2D_Color32(8, 10, 14, 255));
        C2D_DrawRectSolid(barX, barY, 0.5f, barW, barH, C2D_Color32(42, 48, 60, 255));
        C2D_DrawRectSolid(barX + 2.0f, barY + 2.0f, 0.5f, fillW, barH - 4.0f, C2D_Color32(110, 224, 160, 255));

        C2D_TextBufClear(screen->textBuf);
        C2D_TextParse(&title, screen->textBuf, "Loading Game Data");
        C2D_TextParse(&status, screen->textBuf, screen->statusLine);
        C2D_TextParse(&detail, screen->textBuf, detailLine);
        C2D_TextOptimize(&title);
        C2D_TextOptimize(&status);
        C2D_TextOptimize(&detail);

        C2D_DrawText(&title, C2D_WithColor, 36.0f, 74.0f, 0.5f, 0.60f, 0.60f, C2D_Color32(255, 255, 255, 255));
        C2D_DrawText(&status, C2D_WithColor, 36.0f, 104.0f, 0.5f, N3DS_LOADING_TEXT_SCALE, N3DS_LOADING_TEXT_SCALE, C2D_Color32(210, 214, 224, 255));
        C2D_DrawText(&detail, C2D_WithColor, 36.0f, 172.0f, 0.5f, 0.34f, 0.34f, C2D_Color32(146, 153, 168, 255));

        C3D_FrameEnd(0);
        gspWaitForVBlank();
        return;
    }

    int filled = (int) lroundf(progress * 24.0f);
    if (filled < 0) filled = 0;
    if (filled > 24) filled = 24;

    char bar[25];
    repeat(24, i) {
        bar[i] = (int) i < filled ? '#' : '-';
    }
    bar[24] = '\0';

    consoleSelect(&screen->console);
    printf("\x1b[2J");
    printf("\x1b[4;8HLoading Game Data");
    printf("\x1b[7;8H%s", screen->statusLine);
    printf("\x1b[10;8H[%s]", bar);
    printf("\x1b[12;8H%d / %d chunks", screen->chunkIndex, screen->totalChunks);
    printf("\x1b[15;8HPlease wait...");

    gfxFlushBuffers();
    gfxSwapBuffers();
    gspWaitForVBlank();
}

static void N3DSLoadingScreen_set(N3DSLoadingScreen* screen, const char* statusLine, int chunkIndex, int totalChunks) {
    if (screen == NULL) return;
    snprintf(screen->statusLine, sizeof(screen->statusLine), "%s", statusLine != NULL ? statusLine : "");
    screen->chunkIndex = chunkIndex;
    screen->totalChunks = totalChunks;
    N3DSLoadingScreen_draw(screen);
}

static s64 N3DS_ticksToNs(u64 ticks) {
    return (s64) ((ticks * 1000000000ULL) / SYSCLOCK_ARM11);
}

static void N3DSDataWinProgressCallback(const char* chunkName, int chunkIndex, int totalChunks, MAYBE_UNUSED DataWin* dataWin, void* userData) {
    N3DSLoadingScreen* screen = (N3DSLoadingScreen*) userData;
    if (screen == NULL) return;

    char status[128];
    snprintf(status, sizeof(status), "Parsing chunk %.4s", chunkName != NULL ? chunkName : "----");
    N3DSLoadingScreen_set(screen, status, chunkIndex + 1, totalChunks);
}

int main(int argc, char** argv) {
    (void) argc;
    (void) argv;

    gfxInitDefault();
    romfsInit();
    osSetSpeedupEnable(true);

    bool citroReady = false;

    if (C3D_Init(0x80000) && C2D_Init(C2D_DEFAULT_MAX_OBJECTS)) {
        C2D_Prepare();
        citroReady = true;
    } else {
        C2D_Fini();
        C3D_Fini();
    }

    mkdir("sdmc:/3ds", 0777);
    mkdir("sdmc:/3ds/cinnamon", 0777);

    char* dataWinPath = chooseDataWinPath();

    N3DSLoadingScreen loadingScreen = {0};
    if (citroReady) {
        loadingScreen.useCitro2D = true;
        loadingScreen.target = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
        loadingScreen.textBuf = C2D_TextBufNew(512);
        if (loadingScreen.target == NULL || loadingScreen.textBuf == NULL) {
            N3DSLoadingScreen_free(&loadingScreen);
            loadingScreen.useCitro2D = false;
        }
    } else {
        consoleInit(GFX_TOP, &loadingScreen.console);
    }

    if (N3DS_ENABLE_CONSOLE) {
        consoleInit(GFX_BOTTOM, &gN3DSLogConsole);
        gN3DSHasLogConsole = true;
        consoleClear();
        N3DS_activateLogConsole();
        printf("N3DS: bottom-screen logging enabled\n");
    }

    N3DSLoadingScreen_set(&loadingScreen, "Scanning data.win", 0, 1);

    DataWin* dataWin = DataWin_parse(
        dataWinPath,
        (DataWinParserOptions) {
            .parseGen8 = true,
            .parseOptn = true,
            .parseLang = true,
            .parseExtn = false,
            .parseSond = true,
            .parseAgrp = true,
            .parseSprt = true,
            .parseBgnd = true,
            .parsePath = true,
            .parseScpt = true,
            .parseGlob = true,
            .parseShdr = true,
            .parseFont = true,
            .parseTmln = true,
            .parseObjt = true,
            .parseRoom = true,
            .parseTpag = true,
            .parseCode = true,
            .parseVari = true,
            .parseFunc = true,
            .parseStrg = true,
            .parseTxtr = false,
            .parseAudo = false,
            .skipLoadingPreciseMasksForNonPreciseSprites = true,
            .progressCallback = N3DSDataWinProgressCallback,
            .progressCallbackUserData = &loadingScreen,
        }
    );

    free(dataWinPath);

    if (dataWin == NULL) {
        while (aptMainLoop()) {
            hidScanInput();
            if (hidKeysDown() & KEY_START) break;
            gspWaitForVBlank();
        }
        return 1;
    }

    N3DSLoadingScreen_free(&loadingScreen);
    VMContext* vm = VM_create(dataWin);
    Renderer* renderer = N3DSRenderer_create();
    FileSystem* fileSystem = (FileSystem*) N3DSFileSystem_create("romfs:/", "sdmc:/3ds/cinnamon/");
    AudioSystem* audioSystem = (AudioSystem*) N3DSAudioSystem_create();
    Runner* runner = Runner_create(dataWin, vm, renderer, fileSystem, audioSystem);

    runner->osType = OS_3DS;
    Runner_initFirstRoom(runner);

    C2D_Sprite roomBorder;
    C2D_SpriteFromSheet(&roomBorder, borderSheet, 0);
    C2D_SpriteSetPos(&roomBorder, 0.0f, 0.0f);

    bool leftHeld = false, rightHeld = false, upHeld = false, downHeld = false;
    bool aHeld = false, bHeld = false, yHeld = false, startHeld = false;
    bool selectHeld = false, lHeld = false, rHeld = false;

    Gen8* gen8 = &dataWin->gen8;
    int32_t gameW = (int32_t) gen8->defaultWindowWidth;
    int32_t gameH = (int32_t) gen8->defaultWindowHeight;

    const u64 frameTicks = (SYSCLOCK_ARM11 + 15u) / 30u;
    u64 nextFrameTick = svcGetSystemTick() + frameTicks;
    while (aptMainLoop() && !runner->shouldExit) {
        hidScanInput();
        u32 held = hidKeysHeld();
        u32 down = hidKeysDown();

        if (down & KEY_START) break;

        circlePosition circle;
        hidCircleRead(&circle);

        syncKey(runner->keyboard, &leftHeld, VK_LEFT, (held & KEY_LEFT) || circle.dx < -80);
        syncKey(runner->keyboard, &rightHeld, VK_RIGHT, (held & KEY_RIGHT) || circle.dx > 80);
        syncKey(runner->keyboard, &upHeld, VK_UP, (held & KEY_UP) || circle.dy > 80);
        syncKey(runner->keyboard, &downHeld, VK_DOWN, (held & KEY_DOWN) || circle.dy < -80);

        syncKey(runner->keyboard, &aHeld, 'Z', (held & KEY_A));
        syncKey(runner->keyboard, &bHeld, 'X', (held & KEY_B));
        syncKey(runner->keyboard, &yHeld, 'C', (held & KEY_Y) || (held & KEY_X));

        Runner_step(runner);
        runner->audioSystem->vtable->update(runner->audioSystem, 1.0f / 30.0f);

        float displayScaleX = 1.0f;
        float displayScaleY = 1.0f;
        Runner_computeViewDisplayScale(runner, gameW, gameH, &displayScaleX, &displayScaleY);
        C3D_FrameBegin(0);
        renderer->vtable->beginFrame(renderer, gameW, gameH, 400, 240);
        Runner_drawViews(runner, gameW, gameH, displayScaleX, displayScaleY, false);
        renderer->vtable->endFrame(renderer);
        C2D_DrawSprite(&roomBorder);
        C3D_FrameEnd(0);

        RunnerKeyboard_beginFrame(runner->keyboard);

        u64 now = svcGetSystemTick();
        if (now < nextFrameTick) {
            svcSleepThread(N3DS_ticksToNs(nextFrameTick - now));
            nextFrameTick += frameTicks;
        } else {
            nextFrameTick = now + frameTicks;
        }
    }

    audioSystem->vtable->destroy(audioSystem);
    renderer->vtable->destroy(renderer);
    Runner_free(runner);
    N3DSFileSystem_destroy((N3DSFileSystem*) fileSystem);
    VM_free(vm);
    DataWin_free(dataWin);

    C2D_SpriteSheetFree(borderSheet);

    if (citroReady) {
        C2D_Fini();
        C3D_Fini();
    }

    romfsExit();
    gfxExit();
    return 0;
}