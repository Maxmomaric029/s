#ifndef ANDROID_MOD_MENU_HOOK_H
#define ANDROID_MOD_MENU_HOOK_H

#include "Unity/Unity.h"
#include "Unity/Vector3.hpp"
#include "Global.h"
#include "Includes/Utils.h"
#include "Logger.h"

// ============================================================
//  PARCHES DE MEMORIA
//  Agregar aquí todos los MemoryPatch que se usen en main.cpp
// ============================================================
struct My_Patches {
    MemoryPatch recargaRapida;
    // Agregar más parches aquí según se necesiten:
    // MemoryPatch speed;
    // MemoryPatch aimbot;
} hexlibPatches;

// ============================================================
//  PUNTEROS DE FUNCIÓN
//  Se inicializan en nullptr. Solo se asignan si la dirección
//  es válida (> 0x1000). Verificar siempre antes de llamar.
// ============================================================
bool (*IsSameTeam)(void* _this, void* p1, void* p2)    = nullptr;
void* (*getPlayerByIndex)(void* match, uint8_t index)  = nullptr;

// ============================================================
//  setupHooks()
//  Llama UNA sola vez desde hack_thread, después de confirmar
//  que libil2cpp.so está cargada (libBase != 0).
// ============================================================
void setupHooks() {
    uintptr_t addr = 0;

    // --- IsSameTeam ---
    if (Global.IsSameTeam > 0x1000) {
        addr = getRealOffset(Global.IsSameTeam);
        if (addr != 0) {
            IsSameTeam = reinterpret_cast<bool(*)(void*, void*, void*)>(addr);
            LOGI("[Hook] IsSameTeam OK @ 0x%lx", addr);
        } else {
            LOGE("[Hook] IsSameTeam: getRealOffset retornó 0, hook omitido.");
        }
    }

    // --- getPlayerByIndex ---
    if (Global.Player_Index > 0x1000) {
        addr = getRealOffset(Global.Player_Index);
        if (addr != 0) {
            getPlayerByIndex = reinterpret_cast<void*(*)(void*, uint8_t)>(addr);
            LOGI("[Hook] getPlayerByIndex OK @ 0x%lx", addr);
        } else {
            LOGE("[Hook] getPlayerByIndex: getRealOffset retornó 0, hook omitido.");
        }
    }

    // --- Pre-crear parche de noRecoil si la dirección es válida ---
    // De esta forma no se recrea en cada toggle desde Changes()
    if (Global.noRecoil > 0x1000) {
        hexlibPatches.recargaRapida = MemoryPatch::createWithHex(
            libName, Global.noRecoil, "00 00 A0 E3 1E FF 2F E1"
        );
        LOGI("[Hook] noRecoil patch creado @ 0x%lx", Global.noRecoil);
    } else {
        LOGW("[Hook] noRecoil: offset inválido (0x%lx). Actualizar Global.noRecoil.", Global.noRecoil);
    }
}

#endif // ANDROID_MOD_MENU_HOOK_H