#ifndef ANDROID_MOD_MENU_GLOBAL_H
#define ANDROID_MOD_MENU_GLOBAL_H

// OFFSETS ACTUALIZADOS - VERSIÓN OB44 / ACTUALIZACIÓN RECIENTE
// Mapeo realizado desde los datos proporcionados por el usuario

struct {
    // --- OFFSETS DE CLASE (VARIABLES) ---
    uintptr_t MainCameraTransform = 0x5a8;  // FollowCamera: 0x5a8
	uintptr_t Dictionary = 0x44;            // Diccionario de jugadores (estándar)
	uintptr_t HeadTF = 0x5b8;               // Head Bone: 0x5b8
	uintptr_t HipTF = 0x5c0;                // Hip Bone: 0x5c0
	uintptr_t HandTF = 0x630;               // RightHand: 0x630
	uintptr_t EyeTF = 0x5b8;                // Usando Head como referencia para Eye
	uintptr_t ToeTF = 0x608;                // RightToe: 0x608
	uintptr_t RightShoulder = 0x628;        // RightShoulder: 0x628
	uintptr_t LeftShoulder = 0x620;         // LeftShoulder: 0x620
    uintptr_t IsClientBot = 0xC4;           // Offset estándar para bots
    
    // --- OFFSETS DE CLASE GENERALES ---
    uintptr_t CurrentMatch = 0x90;          // CurrentMatch: 0x90
    uintptr_t LocalPlayer = 0xb0;           // LocalPlayer: 0xb0
    uintptr_t Player_IsDead = 0x74;         // Player_IsDead: 0x74
    uintptr_t Player_Name = 0x3c0;          // Player_Name: 0x3c0
    uintptr_t AimRotation = 0x53c;          // AimRotation: 0x53c
    uintptr_t Weapon = 0x528;               // Weapon: 0x528
    uintptr_t WeaponData = 0x88;            // WeaponData: 0x88
    uintptr_t WeaponRecoil = 0x18;          // WeaponRecoil: 0x18
    
    // --- OFFSETS DE FUNCIÓN (REQUIEREN DUMP DE LIBIL2CPP.SO ACTUAL) ---
    // NOTA: Estos valores son de la versión 1.54.2 y podrían causar CRASH si no se actualizan
	uintptr_t U3DStr = 0x228396C; 
    uintptr_t U3DStrConcat = 0x228210C; 
    uintptr_t Component_GetTransform = 0x2729DC4; 
    uintptr_t Transform_INTERNAL_GetPosition = 0x2D3638C; 
    uintptr_t Transform_INTERNAL_SetPosition = 0x2D3644C; 
    uintptr_t GetForward = 0x2D36A70; 
    uintptr_t WorldToScreenPoint = 0x2724AA0; 
    uintptr_t Camera_main = 0x2725090; 
    uintptr_t noRecoil = 0x18;              // Usando WeaponRecoil (0x18) directamente
    
    // --- VARIABLES DE CONTROL ---
    uintptr_t Curent_Match = 0x90;          // Match actual (repetido para compatibilidad)
    uintptr_t Current_Local_Player = 0xb0;  // Jugador local (repetido para compatibilidad)
    uintptr_t get_NickName = 0x3c0;         // Nombre del jugador
    uintptr_t set_aim = 0x53c;              // Rotación de la mira
    uintptr_t get_isAlive = 0x74;           // Estado de vida
    uintptr_t get_isLocalPlayer = 0xb0;     // Verificación de local player
    uintptr_t get_isVisible = 0x650;        // AimbotVisible: 0x650
    uintptr_t GetPhysXPose = 0x80;          // XPose: 0x80
    uintptr_t get_imo = 0x528;              // Arma activa (Weapon)

    // --- SILENT AIM OFFSETS (NUEVOS) ---
    uintptr_t sAim1 = 0x750;
    uintptr_t sAim2 = 0xd18;
    uintptr_t sAim3 = 0x4c;
    uintptr_t sAim4 = 0x40;

} Global;

#endif
