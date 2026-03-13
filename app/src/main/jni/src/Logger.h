//
//  Logger.h
//  Created by MJ (Ruit) on 1/1/19.
//

#ifndef ANDROID_MOD_MENU_LOGGER_H
#define ANDROID_MOD_MENU_LOGGER_H

#include <android/log.h>

// Cambiar el TAG al nombre de tu mod para filtrar fácil en logcat:
//   adb logcat -s 9b_bloodie
#define TAG "9b_bloodie"

#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG,   TAG, __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR,   TAG, __VA_ARGS__))
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO,    TAG, __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN,    TAG, __VA_ARGS__))

#endif // ANDROID_MOD_MENU_LOGGER_H