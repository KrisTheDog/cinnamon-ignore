#pragma once

#include "file_system.h"

typedef struct {
    FileSystem base;
    char* basePath; // the directory containing data.win, with trailing separator
} N3DSFileSystem;

// filesytem to the data.win path blah blah
N3DSFileSystem* N3DSFileSystem_create(const char* dataWinPath);
void N3DSFileSystem_destroy(N3DSFileSystem* fs);
