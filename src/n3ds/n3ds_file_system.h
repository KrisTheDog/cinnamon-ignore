#pragma once

#include "../file_system.h"

typedef struct {
    FileSystem base;
    char* romfsBasePath;
    char* saveBasePath;
} N3DSFileSystem;

N3DSFileSystem* N3DSFileSystem_create(const char* romfsBasePath, const char* saveBasePath);
void N3DSFileSystem_destroy(N3DSFileSystem* fs);