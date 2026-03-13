#ifndef UTILS_H
#define UTILS_H

#include <pthread.h>
#include <android/log.h>
#include <jni.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

// Usar uintptr_t para compatibilidad total con 64 bits (ARM64)
typedef uintptr_t addr_t;

addr_t libBase = 0;
const char* libName = "libil2cpp.so";

addr_t getRealOffset(addr_t address);

// Función optimizada para encontrar la base de la librería
addr_t get_libBase(const char* libraryName) {
    FILE *fp;
    addr_t addr = 0;
    char buffer[1024];
    
    // Abrir los mapas del proceso actual
    fp = fopen("/proc/self/maps", "rt");
    if (fp != NULL) {
        while (fgets(buffer, sizeof(buffer), fp)) {
            if (strstr(buffer, libraryName)) {
                addr = (addr_t) strtoul(buffer, NULL, 16);
                break;
            }
        }
        fclose(fp);
    }
    return addr;
}

addr_t getRealOffset(addr_t address) {
    if (libBase == 0) {
        libBase = get_libBase(libName);
        if (libBase == 0) {
             __android_log_print(ANDROID_LOG_ERROR, "9b_bloodie", "CRITICAL: %s not found in memory!", libName);
        } else {
             __android_log_print(ANDROID_LOG_INFO, "9b_bloodie", "SUCCESS: %s found at %p", libName, (void*)libBase);
        }
    }
    return (libBase + address);
}

#endif
