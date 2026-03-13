#ifndef UTILS_H
#define UTILS_H

#include <pthread.h>
#include <android/log.h>
#include <jni.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned long DWORD;

DWORD libBase = 0;
const char* libName = "libil2cpp.so";

DWORD getRealOffset(DWORD address);

// Función manual para encontrar la base de la librería (Compatible con versiones antiguas)
DWORD get_libBase(const char* libName) {
    FILE *fp;
    DWORD addr = 0;
    char filename[32], buffer[1024];
    snprintf(filename, sizeof(filename), "/proc/self/maps");
    fp = fopen(filename, "rt");
    if (fp != NULL) {
        while (fgets(buffer, sizeof(buffer), fp)) {
            if (strstr(buffer, libName)) {
                addr = (uintptr_t) strtoul(buffer, NULL, 16);
                break;
            }
        }
        fclose(fp);
    }
    return addr;
}

DWORD getRealOffset(DWORD address) {
    if (libBase == 0) {
        libBase = get_libBase(libName);
        if (libBase == 0) {
             __android_log_print(ANDROID_LOG_ERROR, "9b_bloodie", "libil2cpp NOT FOUND! Retrying...");
             // Intento secundario si la primera lectura falla (común en algunos dispositivos)
             libBase = get_libBase("libil2cpp.so");
        } else {
             __android_log_print(ANDROID_LOG_INFO, "9b_bloodie", "libil2cpp found at: %lx", libBase);
        }
    }
    return (libBase + address);
}

#endif