#include "../data_win.h"
#include "../vm.h"

#include <citro2d.h>
#include <3ds.h>

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <malloc.h>

#include "runner_keyboard.h"
#include "runner.h"
#include "input_recording.h"

#include "n3ds_renderer.h"

#include "n3ds_file_system.h"
#include "n3ds_audio_system.h"
#include "stb_ds.h"
#include "stb_image_write.h"
#include "profiler.h"

#include "utils.h"

#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
