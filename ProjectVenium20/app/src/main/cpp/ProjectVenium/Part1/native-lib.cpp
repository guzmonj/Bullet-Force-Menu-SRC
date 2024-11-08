#pragma once
using namespace std;

#include "../../DEXLoader.h"
#include "../Part2/ActivityStuff.h"
#include "../../Unity Structs/Unity.h"
#include "../Part2/Structs.h"
#include "../Variables.h"
#include <jni.h>
#include <string>
#include <thread>

///*** To further clarify, use v2 if you aren't trying to run this project as the main activity. ***///
int version = 1;
bool sideloaded = true;

void Sideload(jobject context) {
    SetPolicy(env, appContext);
    DEX(env, appContext, "pmt.png", "com.platinmods.projectvenium.MainActivity", context);
}

#include "v1.h"
#include "v2.h"

void RegisterNatives() {
    std::string klass;
    if (version == 1) {
        klass = "com/platinmods/projectvenium/v1/MainActivity";
        JNINativeMethod native0[] = {
                {
                        "onCreate",
                        "(Landroid/os/Bundle;)V",
                        (void *)v1::onCreate
                }
        }; env->RegisterNatives( env->FindClass(klass.c_str()), native0, 1);

        klass = "com/platinmods/projectvenium/v1/MainActivity$1";
        JNINativeMethod native1[] = {
                {
                        "run",
                        "()V",
                        (void *)v1::Run1
                }
        }; env->RegisterNatives( env->FindClass(klass.c_str()), native1, 1);

        klass = "com/platinmods/projectvenium/v1/MainActivity$2";
        JNINativeMethod native2[] = {
                {
                        "run",
                        "()V",
                        (void *)v1::Run2
                }
        }; env->RegisterNatives( env->FindClass(klass.c_str()), native2, 1);
    } else {
        klass = "com/unity3d/player/UnityPlayerActivity";
        JNINativeMethod native0[] = {
                {
                        "Init",
                        "(Landroid/content/Context;)V",
                        (void *)v2::Init
                }
        }; env->RegisterNatives( env->FindClass(klass.c_str()), native0, 1);
    }
}

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    if (vm->GetEnv((void **)&env, JNI_VERSION_1_6) != JNI_OK) return -1;
    RegisterNatives();
    return JNI_VERSION_1_6;
}