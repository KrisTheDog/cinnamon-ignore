#include "n3ds_file_system.h"

#include "../utils.h"

#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define N3DS_ENABLE_LOGGING 0

static FILE* gN3DSSdIoLogFile = NULL;

static double N3DSFileSystem_ticksToMs(u64 ticks) {
    return (double) ticks * 1000.0 / (double) SYSCLOCK_ARM11;
}

static bool N3DSFileSystem_isSdmcPath(const char* path) {
    return path != NULL && strncmp(path, "sdmc:/", 6) == 0;
}

static void N3DSFileSystem_openSdIoLog(void) {
#if !N3DS_ENABLE_LOGGING
    return;
#else
    if (gN3DSSdIoLogFile != NULL) return;
    gN3DSSdIoLogFile = fopen("sdmc:/3ds/cinnamon/sd_io.log", "a");
    if (gN3DSSdIoLogFile != NULL) {
        setvbuf(gN3DSSdIoLogFile, NULL, _IOLBF, 0);
    }
#endif
}

static void N3DSFileSystem_logSdIo(
    const char* op,
    const char* path,
    double elapsedMs,
    long sizeBytes,
    bool ok
) {
#if !N3DS_ENABLE_LOGGING
    (void) op;
    (void) path;
    (void) elapsedMs;
    (void) sizeBytes;
    (void) ok;
    return;
#else
    if (path == NULL || !N3DSFileSystem_isSdmcPath(path)) return;
    if (elapsedMs < 0.25 && ok) return;

    N3DSFileSystem_openSdIoLog();
    fprintf(
        stderr,
        "N3DS SDIO: %-10s %7.2f ms %s size=%ld ok=%d\n",
        op != NULL ? op : "<null>",
        elapsedMs,
        path,
        sizeBytes,
        ok ? 1 : 0
    );
    if (gN3DSSdIoLogFile != NULL) {
        fprintf(
            gN3DSSdIoLogFile,
            "N3DS SDIO: %-10s %7.2f ms %s size=%ld ok=%d\n",
            op != NULL ? op : "<null>",
            elapsedMs,
            path,
            sizeBytes,
            ok ? 1 : 0
        );
        fflush(gN3DSSdIoLogFile);
    }
#endif
}

static bool N3DSFileSystem_hasScheme(const char* path) {
    return path != NULL && strstr(path, ":/") != NULL;
}

static bool N3DSFileSystem_pathExists(const char* path) {
    u64 startTick = svcGetSystemTick();
    struct stat st;
    bool ok = path != NULL && stat(path, &st) == 0;
    N3DSFileSystem_logSdIo("stat", path, N3DSFileSystem_ticksToMs(svcGetSystemTick() - startTick), 0, ok);
    return ok;
}

static char* N3DSFileSystem_join(const char* base, const char* relativePath) {
    if (relativePath == NULL) return NULL;
    if (N3DSFileSystem_hasScheme(relativePath)) return safeStrdup(relativePath);

    size_t baseLen = strlen(base);
    size_t relLen = strlen(relativePath);
    bool needSlash = baseLen > 0 && base[baseLen - 1] != '/' && relLen > 0 && relativePath[0] != '/';
    char* result = safeMalloc(baseLen + relLen + (needSlash ? 2 : 1));
    memcpy(result, base, baseLen);
    size_t cursor = baseLen;
    if (needSlash) result[cursor++] = '/';
    memcpy(result + cursor, relativePath, relLen);
    result[cursor + relLen] = '\0';
    return result;
}

static char* N3DSFileSystem_resolvePath(FileSystem* fs, const char* relativePath) {
    N3DSFileSystem* n3ds = (N3DSFileSystem*) fs;
    if (relativePath == NULL) return NULL;
    if (N3DSFileSystem_hasScheme(relativePath)) return safeStrdup(relativePath);

    char* savePath = N3DSFileSystem_join(n3ds->saveBasePath, relativePath);
    if (N3DSFileSystem_pathExists(savePath)) return savePath;
    free(savePath);

    return N3DSFileSystem_join(n3ds->romfsBasePath, relativePath);
}

static bool N3DSFileSystem_fileExists(FileSystem* fs, const char* relativePath) {
    u64 startTick = svcGetSystemTick();
    char* path = N3DSFileSystem_resolvePath(fs, relativePath);
    struct stat st;
    bool ok = path != NULL && stat(path, &st) == 0;
    N3DSFileSystem_logSdIo("exists", path, N3DSFileSystem_ticksToMs(svcGetSystemTick() - startTick), 0, ok);
    free(path);
    return ok;
}

static char* N3DSFileSystem_readFileText(FileSystem* fs, const char* relativePath) {
    u64 startTick = svcGetSystemTick();
    char* path = N3DSFileSystem_resolvePath(fs, relativePath);
    if (path == NULL) return NULL;

    FILE* file = fopen(path, "rb");
    if (file == NULL) {
        N3DSFileSystem_logSdIo("readText", path, N3DSFileSystem_ticksToMs(svcGetSystemTick() - startTick), 0, false);
        free(path);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    if (size < 0) {
        fclose(file);
        return NULL;
    }

    char* text = safeMalloc((size_t) size + 1);
    size_t bytesRead = fread(text, 1, (size_t) size, file);
    fclose(file);
    text[bytesRead] = '\0';
    N3DSFileSystem_logSdIo("readText", path, N3DSFileSystem_ticksToMs(svcGetSystemTick() - startTick), (long) bytesRead, true);
    free(path);
    return text;
}

static bool N3DSFileSystem_writeFileText(FileSystem* fs, const char* relativePath, const char* contents) {
    N3DSFileSystem* n3ds = (N3DSFileSystem*) fs;
    u64 startTick = svcGetSystemTick();
    char* path = N3DSFileSystem_join(n3ds->saveBasePath, relativePath);
    if (path == NULL) return false;

    FILE* file = fopen(path, "wb");
    if (file == NULL) {
        N3DSFileSystem_logSdIo("writeText", path, N3DSFileSystem_ticksToMs(svcGetSystemTick() - startTick), 0, false);
        free(path);
        return false;
    }

    size_t length = strlen(contents);
    bool ok = fwrite(contents, 1, length, file) == length;
    fclose(file);
    N3DSFileSystem_logSdIo("writeText", path, N3DSFileSystem_ticksToMs(svcGetSystemTick() - startTick), (long) length, ok);
    free(path);
    return ok;
}

static bool N3DSFileSystem_deleteFile(FileSystem* fs, const char* relativePath) {
    N3DSFileSystem* n3ds = (N3DSFileSystem*) fs;
    u64 startTick = svcGetSystemTick();
    char* path = N3DSFileSystem_join(n3ds->saveBasePath, relativePath);
    if (path == NULL) return false;
    int rc = remove(path);
    N3DSFileSystem_logSdIo("delete", path, N3DSFileSystem_ticksToMs(svcGetSystemTick() - startTick), 0, rc == 0);
    free(path);
    return rc == 0;
}

static bool N3DSFileSystem_readFileBinary(FileSystem* fs, const char* relativePath, uint8_t** outData, int32_t* outSize) {
    u64 startTick = svcGetSystemTick();
    char* path = N3DSFileSystem_resolvePath(fs, relativePath);
    if (path == NULL) return false;

    FILE* file = fopen(path, "rb");
    if (file == NULL) {
        N3DSFileSystem_logSdIo("readBin", path, N3DSFileSystem_ticksToMs(svcGetSystemTick() - startTick), 0, false);
        free(path);
        return false;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    if (size < 0) {
        fclose(file);
        return false;
    }

    uint8_t* data = safeMalloc((size_t) size);
    size_t bytesRead = fread(data, 1, (size_t) size, file);
    fclose(file);

    *outData = data;
    *outSize = (int32_t) bytesRead;
    N3DSFileSystem_logSdIo("readBin", path, N3DSFileSystem_ticksToMs(svcGetSystemTick() - startTick), (long) bytesRead, true);
    free(path);
    return true;
}

static bool N3DSFileSystem_writeFileBinary(FileSystem* fs, const char* relativePath, const uint8_t* data, int32_t size) {
    N3DSFileSystem* n3ds = (N3DSFileSystem*) fs;
    u64 startTick = svcGetSystemTick();
    char* path = N3DSFileSystem_join(n3ds->saveBasePath, relativePath);
    if (path == NULL) return false;

    FILE* file = fopen(path, "wb");
    if (file == NULL) {
        N3DSFileSystem_logSdIo("writeBin", path, N3DSFileSystem_ticksToMs(svcGetSystemTick() - startTick), size, false);
        free(path);
        return false;
    }

    bool ok = fwrite(data, 1, (size_t) size, file) == (size_t) size;
    fclose(file);
    N3DSFileSystem_logSdIo("writeBin", path, N3DSFileSystem_ticksToMs(svcGetSystemTick() - startTick), size, ok);
    free(path);
    return ok;
}

static FileSystemVtable N3DSFileSystem_vtable = {
    .resolvePath = N3DSFileSystem_resolvePath,
    .fileExists = N3DSFileSystem_fileExists,
    .readFileText = N3DSFileSystem_readFileText,
    .writeFileText = N3DSFileSystem_writeFileText,
    .deleteFile = N3DSFileSystem_deleteFile,
    .readFileBinary = N3DSFileSystem_readFileBinary,
    .writeFileBinary = N3DSFileSystem_writeFileBinary,
};

N3DSFileSystem* N3DSFileSystem_create(const char* romfsBasePath, const char* saveBasePath) {
    N3DSFileSystem* fs = safeCalloc(1, sizeof(N3DSFileSystem));
    fs->base.vtable = &N3DSFileSystem_vtable;
    fs->romfsBasePath = safeStrdup(romfsBasePath != NULL ? romfsBasePath : "romfs:/");
    fs->saveBasePath = safeStrdup(saveBasePath != NULL ? saveBasePath : "sdmc:/3ds/cinnamon/");
    return fs;
}

void N3DSFileSystem_destroy(N3DSFileSystem* fs) {
    if (fs == NULL) return;
#if N3DS_ENABLE_LOGGING
    if (gN3DSSdIoLogFile != NULL) {
        fclose(gN3DSSdIoLogFile);
        gN3DSSdIoLogFile = NULL;
    }
#endif
    free(fs->romfsBasePath);
    free(fs->saveBasePath);
    free(fs);
}
