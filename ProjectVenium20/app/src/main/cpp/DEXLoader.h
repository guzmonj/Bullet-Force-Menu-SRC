#pragma once
using namespace std;

#include <android/asset_manager_jni.h>
#include <android/native_activity.h>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <cerrno>
#include <cstring>

void SetPolicy(JNIEnv *env, jobject thiz) {
    jclass klass = env->FindClass("android/os/StrictMode$ThreadPolicy$Builder");
    jmethodID method = env->GetMethodID(klass, "<init>", "()V");
    jobject o1 = env->NewObject(klass, method);

    method = env->GetMethodID(klass, "permitAll", "()Landroid/os/StrictMode$ThreadPolicy$Builder;");
    jobject o2 = env->CallObjectMethod(o1, method);

    method = env->GetMethodID(klass, "build", "()Landroid/os/StrictMode$ThreadPolicy;");
    jobject o3 = env->CallObjectMethod(o2, method);

    klass = env->FindClass("android/os/StrictMode");
    method = env->GetStaticMethodID(klass, "setThreadPolicy","(Landroid/os/StrictMode$ThreadPolicy;)V");
    env->CallStaticVoidMethod(klass, method, o3);

    env->DeleteLocalRef(klass);
    env->DeleteLocalRef(o1);
    env->DeleteLocalRef(o2);
    env->DeleteLocalRef(o3);
}

void WriteTMP(off_t length, const void *data, uint64_t offset) {
    char tmpFile[] = "/data/data/com.blayzegames.iosfps/pmt.png";
    int fd = open(tmpFile, O_CREAT | O_WRONLY, S_IRWXU);
    const void *_data = static_cast<const char *>(data) + offset;
    off_t _length = length - offset;
    write(fd, _data, _length);
    close(fd);
}

void DEX(JNIEnv *env, jobject appActivity, const char *fileName, const char *javaClass, jobject gameActivity) {
    jclass activityClass = env->GetObjectClass(appActivity);
    jclass cwClass = env->FindClass("android/content/ContextWrapper");
    jclass dclClass = env->FindClass("dalvik/system/DexClassLoader");

    jmethodID getAssetsMethod = env->GetMethodID(activityClass, "getAssets", "()Landroid/content/res/AssetManager;");
    jmethodID gclMethod = env->GetMethodID(cwClass, "getClassLoader", "()Ljava/lang/ClassLoader;");
    jmethodID initMethod = env->GetMethodID(dclClass, "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/ClassLoader;)V");
    jmethodID lcMethod = env->GetMethodID(dclClass, "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;");

    jobject assetManager = env->CallObjectMethod(appActivity, getAssetsMethod);
    jobject loader = env->CallObjectMethod(appActivity, gclMethod);

    AAssetManager *mgr = AAssetManager_fromJava(env, assetManager);
    AAsset *asset = AAssetManager_open(mgr, fileName, AASSET_MODE_STREAMING);

    off_t length = AAsset_getLength(asset);
    const void *data = AAsset_getBuffer(asset);
    char tmpFile[] = "/data/data/com.blayzegames.iosfps/pmt.png";

    ///*** Basic hidden file trick. DEX is merged with LIB and founded at this offset in my example. ***///
    WriteTMP(length, data, 0x5E1C0);

    jobject newLoader = env->NewObject(dclClass, initMethod, env->NewStringUTF(tmpFile), env->NewStringUTF(""), env->NewStringUTF(""), loader);

    jclass loadedClass = (jclass)env->CallObjectMethod(newLoader, lcMethod, env->NewStringUTF(javaClass));
    jmethodID init = env->GetMethodID(loadedClass, "<init>", "(Landroid/content/Context;)V");
    jobject mainActivity = env->NewObject(loadedClass, init, gameActivity);

    unlink(tmpFile);
    AAsset_close(asset);

    env->DeleteLocalRef(activityClass);
    env->DeleteLocalRef(cwClass);
    env->DeleteLocalRef(dclClass);
    env->DeleteLocalRef(assetManager);
    env->DeleteLocalRef(loader);
    env->DeleteLocalRef(newLoader);
    env->DeleteLocalRef(loadedClass);
    env->DeleteLocalRef(mainActivity);
}