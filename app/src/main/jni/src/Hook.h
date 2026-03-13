#ifndef ANDROID_MOD_MENU_HOOK_H
#define ANDROID_MOD_MENU_HOOK_H

#include "Unity/Unity.h"
#include "Unity/Vector3.hpp"
#include "Global.h"
#include "Includes/Utils.h"

// Estructura para parches de memoria
struct My_Patches {
    MemoryPatch recargaRapida;
    MemoryPatch speed;
} hexlibPatches;

// Punteros de función (se inicializan en NULL para evitar crash)
bool (*IsSameTeam)(void* _this, void* p1, void* p2) = nullptr;
void* (*getPlayerByIndex)(void* match, uint8_t index) = nullptr;

// Función para inicializar los punteros cuando el juego cargue
void setupHooks() {
    if (Global.IsSameTeam > 0x1000)
        IsSameTeam = (bool(*)(void*, void*, void*))getRealOffset(Global.IsSameTeam);
    
    if (Global.Player_Index > 0x1000)
        getPlayerByIndex = (void*(*)(void*, uint8_t))getRealOffset(Global.Player_Index);
}

#endif
