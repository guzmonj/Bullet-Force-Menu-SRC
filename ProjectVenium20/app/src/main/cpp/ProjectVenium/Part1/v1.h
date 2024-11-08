///*** Replace Run1 function's local variable, field, with the static activity of your choice for other apps. ***///

namespace v1 {
    void onCreate(JNIEnv *env, jobject thiz, jobject bundle) {
        jclass o_Class = env->GetObjectClass(thiz);
        jclass s_Class = env->GetSuperclass(o_Class);
        jmethodID od_ID = env->GetMethodID(s_Class, "onCreate", "(Landroid/os/Bundle;)V");
        env->CallNonvirtualVoidMethod(thiz, o_Class, od_ID, bundle);

        appContext = env->NewGlobalRef(thiz);
        StartActivity("com.unity3d.player.UnityPlayerActivity", env, thiz);

        jclass klass = env->FindClass("com/platinmods/projectvenium/v1/MainActivity");
        jmethodID method = env->GetMethodID(klass, "Check", "()V");
        env->CallVoidMethod(thiz, method);
    }

    void Run1(JNIEnv *env, jobject thiz) {
        jclass klass = env->FindClass("com/unity3d/player/UnityPlayer");
        jfieldID field = env->GetStaticFieldID(klass, "currentActivity", "Landroid/app/Activity;");
        jobject object = env->GetStaticObjectField(klass, field);
        klass  = env->FindClass("com/platinmods/projectvenium/v1/MainActivity");
        jmethodID method = env->GetMethodID(klass, "Check", "()V");
        if (object) {
            gameContext = env->NewGlobalRef(object);
            field = env->GetFieldID(klass, "layer", "I");
            env->SetIntField(thiz, field, 1);
        } env->CallVoidMethod(thiz, method);
    }

    void Run2(JNIEnv *env, jobject thiz) {
        if (sideloaded) Sideload(gameContext);
        else {
            jclass klass = env->FindClass("com/platinmods/projectvenium/MainActivity");
            jmethodID init = env->GetMethodID(klass, "<init>", "(Landroid/content/Context;)V");
            jobject mainActivity = env->NewObject(klass, init, gameContext);
        }
    }
}