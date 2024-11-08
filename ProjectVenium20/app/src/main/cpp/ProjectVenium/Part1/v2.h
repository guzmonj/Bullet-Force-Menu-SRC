namespace v2 {
    void Init(JNIEnv *env, jobject thiz, jobject context) {
        appContext = env->NewGlobalRef(context);
        if (sideloaded) Sideload(appContext);
        else {
            jclass klass = env->FindClass("com/platinmods/projectvenium/MainActivity");
            jmethodID init = env->GetMethodID(klass, "<init>", "(Landroid/content/Context;)V");
            jobject mainActivity = env->NewObject(klass, init, appContext);
        }
    }
}