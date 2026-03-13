#include <jni.h>
#include <string>
#include <vector>
#include "Includes/Utils.h"
#include "KittyMemory/MemoryPatch.h"
#include "Includes/Esp.h"
#include "Hook.h"
#include "Includes/Logger.h"
#include "Includes/obfuscator.hpp"

#define HOOK(offset, ptr, orig) MSHookFunction((void *)getRealOffset(offset), (void *)ptr, (void **)&orig)

extern "C" {
JNIEXPORT jboolean JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_EnableSounds(
        JNIEnv *env,
        jobject activityObject) {
    return true;
}

JNIEXPORT jstring JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_Title(
        JNIEnv *env,
        jobject activityObject) {
        	
    jstring str = env->NewStringUTF("𝟡𝕓 𝕓𝕝𝕠𝕠𝕕𝕚𝕖 𝕍𝕀ℙ");
    return str;
}

JNIEXPORT jstring JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_Heading(
        JNIEnv *env,
        jobject activityObject) {
        	
    return env->NewStringUTF("Welcome to 9b bloodie Panel | Status: Online");
}


JNIEXPORT jstring JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_Icon(
        JNIEnv *env,
        jobject activityObject) {

    // Icon code...
    return env->NewStringUTF(""); // Icon base64 would go here
}

JNIEXPORT jstring JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_Toast(
        JNIEnv *env,
        jclass clazz) {
    return env->NewStringUTF("<b><font color=WHITE> Modded by </font></b><font color=RED><b>9b bloodie</b></font>");
}

// Struct to store memory patches
struct My_Patches {
	MemoryPatch FreeKills;
	MemoryPatch speedx20;
	MemoryPatch Speed6;
	MemoryPatch Speed7;
	MemoryPatch Speed9;
	MemoryPatch HEADSHOT1;
	MemoryPatch Para;
	MemoryPatch IsFemale1;
	MemoryPatch Speed200x;
	MemoryPatch Speedcarro1;
	MemoryPatch Speedcarro2;
	MemoryPatch Speedcarro3;
	MemoryPatch Speedcarro4;
	MemoryPatch Speedcarro5;
	MemoryPatch Underground1;
	MemoryPatch Underground2;
	MemoryPatch recargaRapida;
	MemoryPatch Speed1;
	MemoryPatch Speed2;
	MemoryPatch Speed3;
	MemoryPatch Speed4;
	MemoryPatch Speed5;
	MemoryPatch speedhack;
	MemoryPatch IMEIdesbanido;
	MemoryPatch WallCarro;
	MemoryPatch FlyCarro;
} hexlibPatches;

// Boolean flags for hacks
bool KMHack1 = false;
bool KMHack2 = false;
bool KMHack3 = false;
bool KMHack4 = false;
bool KMHack5 = false;
bool KMHack6 = false;
bool KMHack7 = false;
bool KMHack8 = false;
bool KMHack9 = false;
bool KMHack10 = false;
bool KMHack11 = false;
bool KMHack12 = false;
bool KMHack13 = false;
bool KMHack14 = false;
bool KMHack15 = false;
bool KMHack16 = false;
bool KMHack17 = false;
bool KMHack18 = false;
bool KMHack19 = false;
bool KMHack20 = false;
bool KMHack21 = false;
bool KMHack22 = false;
bool KMHack23 = false;
bool KMHack24 = false;
bool KMHack25 = false;
bool KMHack26 = false;
bool KMHack27 = false;
bool KMHack28 = false;
bool KMHack29 = false;
bool KMHack30 = false;

// Feature list for the menu
JNIEXPORT jobjectArray JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_getFeatureListttttttttt(
        JNIEnv *env,
        jobject activityObject) {
    jobjectArray ret;
    const char *features[] = {
            "0_Toggle_Aimbot",
            "1_SeekBar_Aimbot FOV_0_360",
            "2_Toggle_ESP Lines",
            "3_Toggle_ESP Box",
            "4_Toggle_ESP Name",
            "5_Toggle_ESP Distance",
            "6_Toggle_No Recoil",
            "7_Toggle_Speed Hack x50",
            "8_Toggle_Fly Hack",
            "9_Toggle_Antenna",
            "10_Toggle_Medkit Running",
            "11_Toggle_Ghost Mode",
            "12_Toggle_Wallhack Car",
            "13_Toggle_Fly Car",
            "14_Toggle_Telekill",
            "15_Toggle_Rain Bullets",
            "16_Toggle_Rapid Reload",
            "17_Toggle_No Grass",
            "18_Toggle_Night Mode",
            "19_Toggle_Unlimited Diamonds (Visual)"
    };

    int totalFeatures = sizeof(features) / sizeof(features[0]);
    ret = (jobjectArray) env->NewObjectArray(totalFeatures, env->FindClass("java/lang/String"),
                                           env->NewStringUTF(""));

    for (int i = 0; i < totalFeatures; i++) {
        env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));
    }

    return (ret);
}

// Function to handle feature changes
JNIEXPORT void JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_Changes(
        JNIEnv *env,
        jobject activityObject,
        jint feature,
        jint value) {

    switch (feature) {
        case 0:
            KMHack1 = !KMHack1;
            break;
        case 6:
            KMHack2 = !KMHack2;
            if (KMHack2) {
                hexlibPatches.recargaRapida = MemoryPatch::createWithHex(libName, Global.noRecoil, "00 00 A0 E3 1E FF 2F E1");
                hexlibPatches.recargaRapida.Modify();
            } else {
                hexlibPatches.recargaRapida.Restore();
            }
            break;
        // Add more cases here for other features
    }
}

// End of C++ code
}
