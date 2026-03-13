#ifndef UTILS_H
#define UTILS_H

#include <pthread.h>
#include "src/KittyMemory/MemoryPatch.h"
#include <android/log.h>
#include <jni.h>
#include <unistd.h>
#include "../KittyMemory/KittyMemory.h"

typedef unsigned long DWORD;

DWORD libBase = 0;
const char* libName = "libil2cpp.so";

DWORD getRealOffset(DWORD address);

DWORD getRealOffset(DWORD address) {
    if (libBase == 0) {
        // Usar KittyMemory para encontrar la base de la librería de forma segura
        KittyMemory::ProcMap map;
        if (KittyMemory::getMemoryBaseMap(libName, map)) {
            libBase = map.startAddress;
            __android_log_print(ANDROID_LOG_INFO, "9b_bloodie", "libil2cpp found at: %lx", libBase);
        } else {
            __android_log_print(ANDROID_LOG_ERROR, "9b_bloodie", "libil2cpp NOT FOUND!");
        }
    }
    return (libBase + address);
}

#endif