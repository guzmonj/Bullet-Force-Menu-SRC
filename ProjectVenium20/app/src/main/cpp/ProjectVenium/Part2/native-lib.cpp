#pragma once
using namespace std;

#include <GLES3/gl3.h>
#include <jni.h>
#include <string>
#include <unistd.h>
#include <fstream>
#include <dirent.h>
#include "../../Unity Structs/Unity.h"
#include "Structs.h"
#include "../Variables.h"
#include "ProjectVenium.h"
#include "ActivityStuff.h"
#include "Pointers.h"
#include "ESP.h"
#include "Hooks.h"

namespace HookThread {
    pthread_t thread;
    void *Start(void *) {
        for (auto & pi : playerInfo) pi = new PlayerInfo();

        #ifdef __arm__
        #elif __aarch64__
        #endif

        return nullptr;
    }
}

void SetupMenu() {
    jclass klass = env->FindClass("android/graphics/Paint");
    jmethodID method = env->GetMethodID(klass, "<init>", "()V");
    paint = env->NewGlobalRef(env->NewObject(klass, method));

    menuWidth = screenWidth / 3;
    borderSize = menuWidth / 69;
    iconY = screenWidth / 15;
    iconX = screenHeight / 10;
    lineHeight = screenWidth / 37;

    menus.resize(5);

    menus[0].text = "Player Menu";
    menus[1].text = "Weapons Menu";
    menus[2].text = "Visions Menu";
    menus[3].text = "Killstreaks Menu";
    menus[4].text = "Profile Menu";

    menus[0].mods.resize(7);
    menus[0].mods[0].text = "Increase Jump";
    menus[0].mods[1].text = "Crouch Under (5s)";
    menus[0].mods[2].text = "REMOVED";
    menus[0].mods[3].text = "Increase Speed";
    menus[0].mods[4].text = "Give All Perks";
    menus[0].mods[5].text = "REMOVED";
    menus[0].mods[6].text = "Back...";
    menus[0].mods[6].back = true;

    menus[1].mods.resize(5);
    menus[1].mods[0].text = "Infinite Ammo";
    menus[1].mods[1].text = "Low Spread";
    menus[1].mods[2].text = "REMOVED";
    menus[1].mods[3].text = "Increase Gun X";
    menus[1].mods[4].text = "Back...";
    menus[1].mods[4].back = true;

    menus[2].mods.resize(6);
    menus[2].mods[0].text = "Player Wallhack";
    menus[2].mods[1].text = "Player Chams";
    menus[2].mods[2].text = "No Flash";
    menus[2].mods[3].text = "Red Box";
    menus[2].mods[4].text = "Near Wallhack";
    menus[2].mods[5].text = "Back...";
    menus[2].mods[5].back = true;

    menus[3].mods.resize(2);
    menus[3].mods[0].text = "+1 Killstreak";
    menus[3].mods[1].text = "Back...";
    menus[3].mods[1].back = true;

    menus[4].mods.resize(2);
    menus[4].mods[0].text = "REMOVED";
    menus[4].mods[1].text = "Back...";
    menus[4].mods[1].back = true;
}

void Init(JNIEnv *env, jobject thiz, jobject _context) {
    ///*** Project Venium Init ***/
    appContext = env->NewGlobalRef(_context);
    SetupMenu();

    jclass klass = env->FindClass("com/platinmods/projectvenium/OverlayView");
    jmethodID method = env->GetMethodID(klass, "<init>", "(Landroid/content/Context;)V");
    OverlayView = env->NewGlobalRef(env->NewObject(klass, method, appContext));

    klass = env->FindClass("android/view/View");
    method = env->GetMethodID(klass, "getWidth", "()I");
    screenWidth = env->CallIntMethod(OverlayView, method);

    method = env->GetMethodID(klass, "getHeight", "()I");
    screenHeight = env->CallIntMethod(OverlayView, method);

    klass = env->FindClass("android/widget/FrameLayout$LayoutParams");
    method = env->GetMethodID(klass, "<init>", "(II)V");
    jobject params = env->NewGlobalRef(env->NewObject(klass, method, -2, -2));

    klass = env->FindClass("android/app/Activity");
    method = env->GetMethodID(klass, "addContentView","(Landroid/view/View;Landroid/view/ViewGroup$LayoutParams;)V");
    env->CallVoidMethod(appContext, method, OverlayView, params);

    ///*** ESP Init ***///
    ESP::RegisterNatives(env);
    klass = env->FindClass("com/platinmods/projectvenium/ESPView");
    method = env->GetMethodID(klass, "<init>", "(Landroid/content/Context;)V");
    espView = env->NewGlobalRef(env->NewObject(klass, method, appContext));

    klass = env->FindClass("android/widget/FrameLayout$LayoutParams");
    method = env->GetMethodID(klass, "<init>", "(II)V");
    jobject params2 = env->NewGlobalRef(env->NewObject(klass, method, -2, -2));

    klass = env->FindClass("android/app/Activity");
    method = env->GetMethodID(klass, "addContentView","(Landroid/view/View;Landroid/view/ViewGroup$LayoutParams;)V");
    env->CallVoidMethod(appContext, method, espView, params2);
}

void RegisterNatives() {
    std::string method = "I";
    std::string parameter = "(Landroid/content/Context;)V";
    std::string klass = "com/platinmods/projectvenium/MainActivity";
    JNINativeMethod native[] = {{method.c_str(), parameter.c_str(), (void*)Init}};
    env->RegisterNatives(env->FindClass(klass.c_str()), native, 1);

    method = "onTouchEvent";
    parameter = "(Landroid/view/MotionEvent;)Z";
    klass = "com/platinmods/projectvenium/OverlayView";
    JNINativeMethod native1[] = {{method.c_str(), parameter.c_str(), (void*)ProjectVenium::onTouchEvent}};
    env->RegisterNatives(env->FindClass(klass.c_str()), native1, 1);

    method = "onDraw";
    parameter = "(Landroid/graphics/Canvas;)V";
    klass = "com/platinmods/projectvenium/OverlayView";
    JNINativeMethod native2[] = {{method.c_str(), parameter.c_str(), (void*)ProjectVenium::onDraw}};
    env->RegisterNatives(env->FindClass(klass.c_str()), native2, 1);
}

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    if (vm->GetEnv((void **)&env, JNI_VERSION_1_6) != JNI_OK) return -1;
    RegisterNatives();
    pthread_create(&HookThread::thread, nullptr, HookThread::Start, nullptr);
    return JNI_VERSION_1_6;
}