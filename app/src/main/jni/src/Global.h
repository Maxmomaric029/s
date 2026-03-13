#ifndef ANDROID_MOD_MENU_GLOBAL_H
#define ANDROID_MOD_MENU_GLOBAL_H

#include <stdint.h>

// ============================================================
//  GLOBAL OFFSETS
//  Juego : (nombre del APK aquí)
//  Versión: (versión del APK aquí)
//  Arch  : ARM64
//  Fecha : (fecha de extracción aquí)
//  NOTA  : Actualizar todos los offsets al cambiar de versión.
// ============================================================

struct {

    // --- OFFSETS DE CLASE (posición relativa dentro del objeto) ---
    uintptr_t MainCameraTransform  = 0x5A8;
    uintptr_t Dictionary           = 0x44;
    uintptr_t HeadTF               = 0x5B8;
    uintptr_t HipTF                = 0x5C0;
    uintptr_t HandTF               = 0x630;
    uintptr_t EyeTF                = 0x5B8;   // mismo que HeadTF, verificar si es correcto
    uintptr_t ToeTF                = 0x608;
    uintptr_t RightShoulder        = 0x628;
    uintptr_t LeftShoulder         = 0x620;
    uintptr_t IsClientBot          = 0xC4;

    // --- OFFSETS DE MIEMBROS DE JUGADOR ---
    uintptr_t CurrentMatch         = 0x90;
    uintptr_t LocalPlayer          = 0xB0;
    uintptr_t Player_IsDead        = 0x74;
    uintptr_t Player_Name          = 0x3C0;
    uintptr_t AimRotation          = 0x53C;
    uintptr_t Weapon               = 0x528;
    uintptr_t WeaponData           = 0x88;
    uintptr_t WeaponRecoil         = 0x18;
    uintptr_t GetPhysXPose         = 0x80;
    uintptr_t get_isVisible        = 0x650;

    // --- OFFSETS DE FUNCIÓN (direcciones absolutas en libil2cpp.so) ---
    uintptr_t U3DStr                          = 0x228396C;
    uintptr_t U3DStrConcat                    = 0x228210C;
    uintptr_t Component_GetTransform          = 0x2729DC4;
    uintptr_t Transform_INTERNAL_GetPosition  = 0x2D3638C;
    uintptr_t Transform_INTERNAL_SetPosition  = 0x2D3644C;
    uintptr_t GetForward                      = 0x2D36A70;
    uintptr_t WorldToScreenPoint              = 0x2724AA0;
    uintptr_t Camera_main                     = 0x2725090;

    // Parche de no-retroceso: dirección absoluta de la función en libil2cpp.so
    // IMPORTANTE: este valor debe ser una dirección válida (> 0x1000), NO un offset de campo
    uintptr_t noRecoil                        = 0x0; // <-- COMPLETAR con dirección real

    // --- FUNCIONES ADICIONALES ---
    uintptr_t IsSameTeam                = 0x21E49E8;
    uintptr_t Player_Index              = 0x1597968;
    uintptr_t AttackableEntity_GetIsDead= 0x1D57DA4;
    uintptr_t AttackableEntity_IsVisible= 0x1D57E9C;
    uintptr_t get_MyFollowCamera        = 0xA516E8;
    uintptr_t IsFiring                  = 0xA6DBFC;
    uintptr_t spof_nick                 = 0xA50E58;
    uintptr_t CurrentUIScene            = 0x1FAAFDC;
    uintptr_t AddTeammateHud            = 0x135E088;
    uintptr_t set_esp                   = 0xF482E0;
    uintptr_t get_IsSighting            = 0xAA1964;
    uintptr_t get_IsCrouching           = 0xA5B85C;
    uintptr_t GetLocalPlayerOrObServer  = 0x1FC03F0;
    uintptr_t get_isLocalTeam           = 0xA59E10;
    uintptr_t GetAttackableCenterWS     = 0xA50948;
    uintptr_t ShowDynamicPopupMessage   = 0x134BBA0;
    uintptr_t ShowPopupMessage          = 0x134BD28;

    // --- SILENT AIM OFFSETS ---
    uintptr_t sAim1 = 0x750;
    uintptr_t sAim2 = 0xD18;
    uintptr_t sAim3 = 0x4C;
    uintptr_t sAim4 = 0x40;

} Global;

#endif // ANDROID_MOD_MENU_GLOBAL_H