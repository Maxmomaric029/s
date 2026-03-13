#include <jni.h>
#include <string>
#include <vector>
#include <pthread.h>
#include <unistd.h>
#include "Includes/Utils.h"
#include "KittyMemory/MemoryPatch.h"
#include "Includes/Esp.h"
#include "Hook.h"

// Flags de control
bool isGameLibLoaded = false;

// Hilo principal de los trucos
void* hack_thread(void*) {
    __android_log_print(ANDROID_LOG_INFO, "9b_bloodie", "Hack Thread Started. Waiting for Game...");
    
    // Esperar hasta que la librería del juego esté cargada
    while (get_libBase(libName) == 0) {
        sleep(1);
    }
    
    isGameLibLoaded = true;
    libBase = get_libBase(libName);
    __android_log_print(ANDROID_LOG_INFO, "9b_bloodie", "Game Lib Loaded! Base: %lx", libBase);
    
    // Aquí puedes inicializar hooks de funciones reales si tienes los offsets largos
    // Ejemplo: if (Global.U3DStr > 0x1000) { ... setup hooks ... }
    
    return NULL;
}

extern "C" {
JNIEXPORT jboolean JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_EnableSounds(JNIEnv *env, jobject activityObject) {
    return true;
}

JNIEXPORT jstring JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_Title(JNIEnv *env, jobject activityObject) {
    return env->NewStringUTF("𝟡𝕓 𝕓𝕝𝕠𝕠𝕕𝕚𝕖 𝕍𝕀ℙ");
}

JNIEXPORT jstring JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_Heading(JNIEnv *env, jobject activityObject) {
    return env->NewStringUTF("Status: Online | Waiting for Game...");
}

JNIEXPORT jstring JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_Toast(JNIEnv *env, jclass clazz) {
    return env->NewStringUTF("Modded by 9b bloodie");
}

JNIEXPORT void JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_Changes(JNIEnv *env, jobject activityObject, jint feature, jint value) {
    if (!isGameLibLoaded) return; // No hacer nada si el juego no ha cargado

    switch (feature) {
        case 6: // No Recoil
            if (value == 1) {
                // Solo aplicar si el offset es una función real, no un campo de clase
                if (Global.noRecoil > 0x1000) {
                    hexlibPatches.recargaRapida = MemoryPatch::createWithHex(libName, Global.noRecoil, "00 00 A0 E3 1E FF 2F E1");
                    hexlibPatches.recargaRapida.Modify();
                }
            } else {
                hexlibPatches.recargaRapida.Restore();
            }
            break;
    }
}

// Inicializador de la librería
jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    pthread_t t;
    pthread_create(&t, NULL, hack_thread, NULL);
    return JNI_VERSION_1_6;
}

JNIEXPORT jobjectArray JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_getFeatureListttttttttt(JNIEnv *env, jobject activityObject) {
    const char *features[] = {"6_Toggle_No Recoil", "0_Toggle_Aimbot (Safe)", "2_Toggle_ESP Lines"};
    jobjectArray ret = (jobjectArray) env->NewObjectArray(3, env->FindClass("java/lang/String"), env->NewStringUTF(""));
    for (int i = 0; i < 3; i++) env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));
    return ret;
}

}
