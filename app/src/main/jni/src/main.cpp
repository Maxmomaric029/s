#include <jni.h>
#include <string>
#include <vector>
#include <pthread.h>
#include <unistd.h>
#include <android/log.h>
#include "Includes/Utils.h"
#include "KittyMemory/MemoryPatch.h"
#include "Hook.h"

#define LOG_TAG "9b_bloodie"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

bool isGameLibLoaded = false;

// Función de monitoreo de hilos
void* hack_thread(void*) {
    LOGI(">>> HACK THREAD STARTING... <<<");
    
    int retries = 0;
    while (libBase == 0 && retries < 60) {
        libBase = get_libBase(libName);
        if (libBase == 0) {
            LOGI("Waiting for %s... (Attempt %d)", libName, retries++);
            sleep(2); // Esperar 2 segundos entre intentos
        }
    }

    if (libBase != 0) {
        LOGI("SUCCESS: libil2cpp.so found at %lx", libBase);
        isGameLibLoaded = true;
        
        // Inicializar hooks de forma directa (las protecciones están en setupHooks)
        setupHooks();
        LOGI("Hooks initialized successfully!");
    } else {
        LOGE("ERROR: Timeout waiting for game library!");
    }
    
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
    if (isGameLibLoaded) return env->NewStringUTF("Status: Online | Game Hooked ✅");
    return env->NewStringUTF("Status: Waiting | Finding Game... 🔍");
}

JNIEXPORT void JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_Changes(JNIEnv *env, jobject activityObject, jint feature, jint value) {
    LOGI("Feature Change: ID %d, Value %d", feature, value);
    
    if (!isGameLibLoaded) {
        LOGE("Warning: Change ignored, game not hooked yet.");
        return;
    }

    // Lógica de parches (Solo si la librería está cargada)
    if (feature == 6 && Global.noRecoil > 0x1000) {
        if (value == 1) {
            hexlibPatches.recargaRapida = MemoryPatch::createWithHex(libName, Global.noRecoil, "00 00 A0 E3 1E FF 2F E1");
            if (hexlibPatches.recargaRapida.Modify()) {
                LOGI("No Recoil: Modified!");
            } else {
                LOGE("No Recoil: Modification Failed!");
            }
        } else {
            hexlibPatches.recargaRapida.Restore();
            LOGI("No Recoil: Restored!");
        }
    }
}

// JNI_OnLoad: Se ejecuta al cargar la librería
jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    LOGI("JNI_OnLoad called - Initializing 9b bloodie...");
    
    pthread_t t;
    if (pthread_create(&t, NULL, hack_thread, NULL) != 0) {
        LOGE("Failed to create hack thread!");
    }
    
    return JNI_VERSION_1_6;
}

JNIEXPORT jobjectArray JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_getFeatureListttttttttt(JNIEnv *env, jobject activityObject) {
    const char *features[] = {"6_Toggle_No Recoil", "0_Toggle_Aimbot", "2_Toggle_ESP Lines"};
    jobjectArray ret = (jobjectArray) env->NewObjectArray(3, env->FindClass("java/lang/String"), env->NewStringUTF(""));
    for (int i = 0; i < 3; i++) env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));
    return ret;
}

}
