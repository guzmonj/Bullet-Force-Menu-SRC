namespace ESP {
    void Line(float startX, float startY, float endX, float endY, float thickness, int alpha, int red, int green, int blue) {
        jclass p_Class = env->FindClass("android/graphics/Paint");
        jmethodID i_ID = env->GetMethodID(p_Class, "<init>", "()V");
        jobject n_Object = env->NewObject(p_Class, i_ID);
        jobject p_Object = env->NewGlobalRef(n_Object);

        env->DeleteLocalRef(n_Object);
        env->DeleteLocalRef(p_Class);

        jclass c_Class = env->FindClass("android/graphics/Canvas");
        jmethodID sargb_ID = env->GetMethodID(p_Class, "setARGB", "(IIII)V");
        env->CallVoidMethod(p_Object, sargb_ID, alpha, red, green, blue);
        jmethodID ssw_ID = env->GetMethodID(p_Class,"setStrokeWidth", "(F)V");
        env->CallVoidMethod(p_Object, ssw_ID, thickness);
        jmethodID dl_ID = env->GetMethodID(c_Class, "drawLine", "(FFFFLandroid/graphics/Paint;)V");
        env->CallVoidMethod(espCanvas, dl_ID, startX, startY, endX, endY, p_Object);

        env->DeleteGlobalRef(p_Object);
        env->DeleteGlobalRef(c_Class);
    }

    Vector3 WorldToScreen(void *camera, Vector3 position, int eye) {
        Vector3 s_position;
        s_position = Pointers::Camera::WorldToViewportPoint(camera, position, eye);
        s_position.Y = (float)screenHeight * (1 - s_position.Y);
        s_position.X = s_position.X * (float)screenWidth;
        return s_position;
    }

    void DrawESP() {
        int lineBoxThickness = 2.0f;
        for (int i = 0; i < 100; i++) {
            if (!playerInfo[i]) break;
            playerInfo[i]->screenPosition.Y = playerInfo[i]->leftKneeScreenPosition.Y;
            Vector3 enemyPos = playerInfo[i]->screenPosition, enemyHeadPos = playerInfo[i]->headScreenPosition;
            enemyHeadPos.Y -= (enemyPos.Y - enemyHeadPos.Y) / 1.0f;
            enemyPos.Y += (enemyPos.Y - enemyHeadPos.Y) / 2.5f;
            float oS = (enemyPos.Y - enemyHeadPos.Y) / 3.1f;
            if (playerInfo[i]->player && !playerInfo[i]->isMine && playerInfo[i]->health > 0.01f && !playerInfo[i]->isTeammate) {
                if (enemyPos.Z > 1.0f && menus[2].mods[3].is) {
                    Line(enemyPos.X - lineBoxThickness - oS, enemyPos.Y + lineBoxThickness,
                         enemyPos.X + lineBoxThickness + oS, enemyPos.Y + lineBoxThickness,
                         lineBoxThickness, 255, 255, 0, 0);

                    Line(enemyPos.X + lineBoxThickness + oS,enemyHeadPos.Y - lineBoxThickness,
                         enemyPos.X + lineBoxThickness + oS,enemyPos.Y + lineBoxThickness,
                         lineBoxThickness, 255, 255, 0, 0);

                    Line(enemyPos.X - lineBoxThickness - oS, enemyPos.Y + lineBoxThickness,
                         enemyPos.X - lineBoxThickness - oS, enemyHeadPos.Y - lineBoxThickness,
                         lineBoxThickness, 255, 255, 0, 0);

                    Line(enemyPos.X - lineBoxThickness - oS, enemyHeadPos.Y - lineBoxThickness,
                         enemyPos.X + lineBoxThickness + oS, enemyHeadPos.Y - lineBoxThickness,
                         lineBoxThickness, 255, 255, 0, 0);
                }
            }
        }
    }

    void Reset() {
        jclass v_Class = env->FindClass("android/view/View");
        jmethodID i_ID = env->GetMethodID(v_Class, "postInvalidateDelayed", "(J)V");
        env->CallVoidMethod(espView, i_ID, (jlong)(1000 / FRAME_RATE));
    }

    void onDraw(JNIEnv *env, jobject thiz, jobject canvaz) {
        jclass o_Class = env->GetObjectClass(thiz);
        jclass s_Class = env->GetSuperclass(o_Class);
        jmethodID od_ID = env->GetMethodID(s_Class, "onDraw", "(Landroid/graphics/Canvas;)V");
        env->CallNonvirtualVoidMethod(thiz, o_Class, od_ID, canvaz);

        espCanvas = canvaz;
        DrawESP();
        Reset();
    }

    void RegisterNatives(JNIEnv *env) {
        std::string method = "onDraw";
        std::string parameter = "(Landroid/graphics/Canvas;)V";
        std::string klass = "com/platinmods/projectvenium/ESPView";
        JNINativeMethod native2[] = {{method.c_str(), parameter.c_str(), (void*)onDraw}};
        env->RegisterNatives(env->FindClass(klass.c_str()), native2, 1);
    }
}