#include <jni.h>
#include <string>
#include <vector>
#include <pthread.h>
#include <unistd.h>
#include <atomic>
#include <android/log.h>
#include "Includes/Utils.h"
#include "KittyMemory/MemoryPatch.h"
#include "Hook.h"

#define LOG_TAG "9b_bloodie"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,  LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

// ============================================================
//  Estado del mod — atomic para acceso seguro entre hilos
// ============================================================
static std::atomic<bool> isGameLibLoaded(false);

// ============================================================
//  Estados de features — se leen en Changes() y en el loop
// ============================================================
static std::atomic<bool> featureNoRecoil(false);
static std::atomic<bool> featureAimbot(false);
static std::atomic<bool> featureESP(false);

// ============================================================
//  HACK THREAD
//  Espera que libil2cpp.so esté en memoria, luego inicializa.
// ============================================================
static void* hack_thread(void*) {
    LOGI(">>> HACK THREAD STARTING <<<");

    const int MAX_RETRIES = 60;
    for (int i = 0; i < MAX_RETRIES && libBase == 0; i++) {
        libBase = get_libBase(libName);
        if (libBase == 0) {
            LOGI("Waiting for %s... (%d/%d)", libName, i + 1, MAX_RETRIES);
            sleep(2);
        }
    }

    if (libBase == 0) {
        LOGE("ERROR: Timeout — game library not found after %d retries.", MAX_RETRIES);
        return nullptr;
    }

    LOGI("SUCCESS: %s found at base 0x%lx", libName, libBase);

    // setupHooks() ya crea el MemoryPatch de noRecoil internamente.
    // No volver a crearlo en Changes().
    setupHooks();

    isGameLibLoaded.store(true);
    LOGI("Hooks initialized. Mod ready.");

    return nullptr;
}

// ============================================================
//  JNI_OnLoad
// ============================================================
extern "C" jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    LOGI("JNI_OnLoad — 9b bloodie starting...");

    pthread_t t;
    if (pthread_create(&t, nullptr, hack_thread, nullptr) != 0) {
        LOGE("Failed to create hack thread!");
    } else {
        // Detach para que el SO limpie el thread al terminar sin necesidad de join
        pthread_detach(t);
    }

    return JNI_VERSION_1_6;
}

// ============================================================
//  JNI EXPORTS
// ============================================================
extern "C" {

JNIEXPORT jboolean JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_EnableSounds(JNIEnv* env, jobject obj) {
    return JNI_TRUE;
}

JNIEXPORT jstring JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_Title(JNIEnv* env, jobject obj) {
    return env->NewStringUTF("𝟡𝕓 𝕓𝕝𝕠𝕠𝕕𝕚𝕖 𝕍𝕀ℙ");
}

JNIEXPORT jstring JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_Heading(JNIEnv* env, jobject obj) {
    if (isGameLibLoaded.load())
        return env->NewStringUTF("Status: Online | Game Hooked ✅");
    return env->NewStringUTF("Status: Waiting | Finding Game... 🔍");
}

// ============================================================
//  LISTA DE FEATURES
//  Formato: "ID_Tipo_Nombre"
//  Tipos: Toggle, Seekbar, Button
//  IMPORTANTE: el nombre del método debe coincidir EXACTAMENTE
//  con el nombre declarado en FloatingModMenuService.java
// ============================================================
JNIEXPORT jobjectArray JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_getFeatureList(JNIEnv* env, jobject obj) {
    const char* features[] = {
        "0_Toggle_No Recoil",
        "1_Toggle_Aimbot",
        "2_Toggle_ESP Lines"
    };
    const int count = 3;

    jobjectArray arr = env->NewObjectArray(
        count,
        env->FindClass("java/lang/String"),
        env->NewStringUTF("")
    );
    for (int i = 0; i < count; i++)
        env->SetObjectArrayElement(arr, i, env->NewStringUTF(features[i]));

    return arr;
}

// ============================================================
//  CHANGES — Se llama cuando el usuario toca un toggle/seekbar
//  feature : ID del feature (primer número en getFeatureList)
//  value   : 1 = activar, 0 = desactivar
// ============================================================
JNIEXPORT void JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_Changes(JNIEnv* env, jobject obj, jint feature, jint value) {
    LOGI("Feature change: id=%d value=%d", feature, value);

    if (!isGameLibLoaded.load()) {
        LOGW("Changes() ignorado — game no hookeado aún.");
        return;
    }

    const bool enable = (value == 1);

    switch (feature) {

        // ---- NO RECOIL (ID 0) ----
        case 0: {
            featureNoRecoil.store(enable);
            if (Global.noRecoil <= 0x1000) {
                LOGE("No Recoil: offset inválido, actualizar Global.noRecoil.");
                break;
            }
            // El parche ya fue creado en setupHooks(), solo Modify/Restore
            if (enable) {
                if (hexlibPatches.recargaRapida.Modify())
                    LOGI("No Recoil: activado.");
                else
                    LOGE("No Recoil: Modify() falló.");
            } else {
                hexlibPatches.recargaRapida.Restore();
                LOGI("No Recoil: restaurado.");
            }
            break;
        }

        // ---- AIMBOT (ID 1) ----
        case 1: {
            featureAimbot.store(enable);
            // TODO: implementar lógica de aimbot aquí
            // Ejemplo: usar Global.AimRotation para escribir rotación al jugador local
            LOGI("Aimbot: %s (pendiente implementación)", enable ? "ON" : "OFF");
            break;
        }

        // ---- ESP LINES (ID 2) ----
        case 2: {
            featureESP.store(enable);
            // TODO: implementar lógica de ESP aquí
            // Ejemplo: usar Global.WorldToScreenPoint + overlay para dibujar líneas
            LOGI("ESP Lines: %s (pendiente implementación)", enable ? "ON" : "OFF");
            break;
        }

        default:
            LOGW("Changes(): feature ID %d desconocido.", feature);
            break;
    }
}

} // extern "C"