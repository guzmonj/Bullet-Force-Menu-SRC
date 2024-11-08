namespace Intent {
    jobject get_intent(JNIEnv *env, jobject classObject, jobject klass) {
        jclass i_Class = env->FindClass("android/content/Intent");
        jmethodID i_ID = env->GetMethodID(i_Class, "<init>", "(Landroid/content/Context;Ljava/lang/Class;)V");
        jobject n_Object = env->NewObject(i_Class, i_ID, classObject, klass);
        env->DeleteLocalRef(i_Class);
        return n_Object;
    }
};

jobject locateClass(JNIEnv *env, const char *className) {
    jclass c_Class = env->FindClass("java/lang/Class");
    jmethodID fn_ID = env->GetStaticMethodID(c_Class, "forName", "(Ljava/lang/String;)Ljava/lang/Class;");
    jobject n_Object = env->CallStaticObjectMethod(c_Class, fn_ID, env->NewStringUTF(className));
    env->DeleteLocalRef(c_Class);
    return n_Object;
}

void startActivity(JNIEnv* env, jobject classObject, jobject intent) {
    jclass a_Class = env->FindClass("android/app/Activity");
    jmethodID sa_ID = env->GetMethodID(a_Class, "startActivity", "(Landroid/content/Intent;)V");
    env->CallVoidMethod(classObject, sa_ID, intent);
    env->DeleteLocalRef(a_Class);
}

void StartActivity(std::string name, JNIEnv *env, jobject obj) {
    jobject c_Object = locateClass(env, name.c_str());
    jobject intent = Intent::get_intent(env, obj, c_Object);
    startActivity(env, obj, intent);
    env->DeleteLocalRef(c_Object);
    env->DeleteLocalRef(intent);
}