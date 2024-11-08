namespace ProjectVenium {
    float x, y;

    void Reset() {
        jclass v_Class = env->FindClass("android/view/View");
        jmethodID i_ID = env->GetMethodID(v_Class, "postInvalidateDelayed", "(J)V");
        env->CallVoidMethod(OverlayView, i_ID, (jlong)(1000 / FRAME_RATE));
    }

    bool IconSelected(float x, float y) {
        return x >= iconX - (float)(screenWidth / 42) && x <= iconX + (float)(screenWidth / 42)
               && y >= iconY - (float)(screenWidth / 42) && y <= iconY + (float)(screenWidth / 42);
    }

    ///Trial & Error Lazy Value Findings, Not Perfect Per Device
    int GetSelectedLine(float x, float y) {
        int _y = screenHeight / 3.43;
        int _x = screenWidth / 3;
        int x_ = screenWidth / 3 * 2;
        int count = curMenu != 0 ? menus[curMenu - 1].mods.size() : menus.size();
        for (int i = 0; i < count; i++) {
            int y_ = _y + lineHeight;
            if ((y >= _y && y <= y_) && x >= _x && x <= x_) return i;
            _y = y_;
        } if (y >= screenWidth / 85 && y <= screenWidth / 85 * 5 &&  x >= _x && x <= x_) return -1;
        return -2;
    }

    void AddMenus() {
        for (int i = 0; i < menus.size(); i++) {
            int y = screenHeight / 2.85 + i * lineHeight;
            if (i == curLine) {
                jclass klass = env->FindClass("android/graphics/Paint");
                jmethodID method = env->GetMethodID(klass, "setColor", "(I)V");
                env->CallVoidMethod(paint, method, -1); ///Cyan -16711681, Red -65536

                method = env->GetMethodID(klass, "setTextSize", "(F)V");
                env->CallVoidMethod(paint, method, (float)(screenWidth / 62));

                klass = env->FindClass("android/graphics/Canvas");
                method = env->GetMethodID(klass, "drawRect", "(FFFFLandroid/graphics/Paint;)V");
                env->CallVoidMethod(canvas, method, (float)menuWidth, (float)(y - lineHeight / 2), (float)(menuWidth * 2), (float)(y + lineHeight / 4), paint);

                klass = env->FindClass("android/graphics/Paint");
                method = env->GetMethodID(klass, "setColor", "(I)V");
                env->CallVoidMethod(paint, method, -16777216); ///Black

                klass = env->FindClass("android/graphics/Paint");
                method = env->GetMethodID(klass, "setTextAlign", "(Landroid/graphics/Paint$Align;)V");
                klass = env->FindClass("android/graphics/Paint$Align");
                jfieldID field = env->GetStaticFieldID(klass, "CENTER", "Landroid/graphics/Paint$Align;");
                env->CallVoidMethod(paint, method, env->GetStaticObjectField(klass, field));

                klass = env->FindClass("android/graphics/Canvas");
                method = env->GetMethodID(klass, "drawText", "(Ljava/lang/String;FFLandroid/graphics/Paint;)V");
                env->CallVoidMethod(canvas, method, env->NewStringUTF(menus[i].text.c_str()), (float)(screenWidth / 2), (float)y, paint);
                menus[i].go = true;
            } else {
                if (menus[i].go) {
                    menus[i].go = false;
                    curMenu = i + 1;
                    Reset();
                    return;
                } jclass klass = env->FindClass("android/graphics/Paint");
                jmethodID method = env->GetMethodID(klass, "setColor", "(I)V");
                env->CallVoidMethod(paint, method, -1); ///White

                method = env->GetMethodID(klass, "setTextSize", "(F)V");
                env->CallVoidMethod(paint, method, (float)(screenWidth / 62));

                klass = env->FindClass("android/graphics/Paint");
                method = env->GetMethodID(klass, "setTextAlign", "(Landroid/graphics/Paint$Align;)V");
                klass = env->FindClass("android/graphics/Paint$Align");
                jfieldID field = env->GetStaticFieldID(klass, "CENTER", "Landroid/graphics/Paint$Align;");
                env->CallVoidMethod(paint, method, env->GetStaticObjectField(klass, field));

                klass = env->FindClass("android/graphics/Canvas");
                method = env->GetMethodID(klass, "drawText", "(Ljava/lang/String;FFLandroid/graphics/Paint;)V");
                env->CallVoidMethod(canvas, method, env->NewStringUTF(menus[i].text.c_str()), (float)(screenWidth / 2), (float)y, paint);
            }
        }
    }

    void AddMods() {
        for (int i = 0; i < menus[curMenu - 1].mods.size(); i++) {
            int y = screenHeight / 2.85 + i * lineHeight;
            if (i == curLine) {
                jclass klass = env->FindClass("android/graphics/Paint");
                jmethodID method = env->GetMethodID(klass, "setColor", "(I)V");
                env->CallVoidMethod(paint, method, -1); ///Cyan -16711681, Red -65536

                method = env->GetMethodID(klass, "setTextSize", "(F)V");
                env->CallVoidMethod(paint, method, (float)(screenWidth / 62));

                klass = env->FindClass("android/graphics/Canvas");
                method = env->GetMethodID(klass, "drawRect", "(FFFFLandroid/graphics/Paint;)V");
                env->CallVoidMethod(canvas, method, (float)menuWidth, (float)(y - lineHeight / 2), (float)(menuWidth * 2), (float)(y + lineHeight / 4), paint);

                klass = env->FindClass("android/graphics/Paint");
                method = env->GetMethodID(klass, "setColor", "(I)V");
                env->CallVoidMethod(paint, method, -16777216); ///Black

                klass = env->FindClass("android/graphics/Paint");
                method = env->GetMethodID(klass, "setTextAlign", "(Landroid/graphics/Paint$Align;)V");
                klass = env->FindClass("android/graphics/Paint$Align");
                jfieldID field = env->GetStaticFieldID(klass, "CENTER", "Landroid/graphics/Paint$Align;");
                env->CallVoidMethod(paint, method, env->GetStaticObjectField(klass, field));

                klass = env->FindClass("android/graphics/Canvas");
                method = env->GetMethodID(klass, "drawText", "(Ljava/lang/String;FFLandroid/graphics/Paint;)V");
                env->CallVoidMethod(canvas, method, env->NewStringUTF(menus[curMenu - 1].mods[i].text.c_str()), (float)(screenWidth / 2), (float)y, paint);

                menus[curMenu - 1].mods[i].next = true;
                if ((curMenu - 1 == 0 && i == 56)
                    || (curMenu - 1 == 1 && i == 4)
                    || (curMenu - 1 == 2 && i == 5)
                    || (curMenu - 1 == 3 && i == 1)
                    || (curMenu - 1 == 4 && i == 1)) return;

                klass = env->FindClass("android/graphics/Paint");
                method = env->GetMethodID(klass, "setTextSize", "(F)V");
                env->CallVoidMethod(paint, method, (float)(screenWidth / 42));

                klass = env->FindClass("android/graphics/Paint");
                method = env->GetMethodID(klass, "setTextAlign", "(Landroid/graphics/Paint$Align;)V");
                klass = env->FindClass("android/graphics/Paint$Align");
                field = env->GetStaticFieldID(klass, "LEFT", "Landroid/graphics/Paint$Align;");
                env->CallVoidMethod(paint, method, env->GetStaticObjectField(klass, field));

                if (!menus[curMenu - 1].mods[i].is) {
                    jclass klass = env->FindClass("android/graphics/Paint");
                    jmethodID method = env->GetMethodID(klass, "setColor", "(I)V");
                    env->CallVoidMethod(paint, method,  -16711936); ///Green

                    klass = env->FindClass("android/graphics/Canvas");
                    method = env->GetMethodID(klass, "drawText", "(Ljava/lang/String;FFLandroid/graphics/Paint;)V");
                    std::string text =  menus[curMenu - 1].mods[i].text + " ENABLED";
                    env->CallVoidMethod(canvas, method, env->NewStringUTF(text.c_str()), 0.0f, (float)(screenHeight / 1.01), paint);
                } else {
                    jclass klass = env->FindClass("android/graphics/Paint");
                    jmethodID method = env->GetMethodID(klass, "setColor", "(I)V");
                    env->CallVoidMethod(paint, method,  -65536); //Red

                    klass = env->FindClass("android/graphics/Canvas");
                    method = env->GetMethodID(klass, "drawText", "(Ljava/lang/String;FFLandroid/graphics/Paint;)V");
                    std::string text =  menus[curMenu - 1].mods[i].text + " DISABLED";
                    env->CallVoidMethod(canvas, method, env->NewStringUTF(text.c_str()), 0.0f, (float)(screenHeight / 1.01), paint);
                }

            } else {
                if (menus[curMenu - 1].mods[i].next) {
                    menus[curMenu - 1].mods[i].is = !menus[curMenu - 1].mods[i].is;
                    menus[curMenu - 1].mods[i].next = false;
                } if (menus[curMenu - 1].mods[i].back && menus[curMenu - 1].mods[i].is) {
                    menus[curMenu - 1].mods[i].is = false;
                    curMenu = 0;
                    Reset();
                    return;
                } jclass klass = env->FindClass("android/graphics/Paint");
                jmethodID method = env->GetMethodID(klass, "setColor", "(I)V");
                env->CallVoidMethod(paint, method, -1); ///White

                method = env->GetMethodID(klass, "setTextSize", "(F)V");
                env->CallVoidMethod(paint, method, (float)(screenWidth / 62));

                klass = env->FindClass("android/graphics/Paint");
                method = env->GetMethodID(klass, "setTextAlign", "(Landroid/graphics/Paint$Align;)V");
                klass = env->FindClass("android/graphics/Paint$Align");
                jfieldID field = env->GetStaticFieldID(klass, "CENTER", "Landroid/graphics/Paint$Align;");
                env->CallVoidMethod(paint, method, env->GetStaticObjectField(klass, field));

                klass = env->FindClass("android/graphics/Canvas");
                method = env->GetMethodID(klass, "drawText", "(Ljava/lang/String;FFLandroid/graphics/Paint;)V");
                env->CallVoidMethod(canvas, method, env->NewStringUTF(menus[curMenu - 1].mods[i].text.c_str()), (float)(screenWidth / 2), (float)y, paint);
            }
        }
    }

    void DrawMenu() {
        jclass klass = env->FindClass("android/view/View");
        jmethodID method = env->GetMethodID(klass, "getWidth", "()I");
        screenWidth = env->CallIntMethod(OverlayView, method);

        method = env->GetMethodID(klass, "getHeight", "()I");
        screenHeight = env->CallIntMethod(OverlayView, method);

        menuWidth = screenWidth / 3;
        borderSize = menuWidth / 69;
        iconY = screenWidth / 15;
        iconX = screenHeight / 10;
        lineHeight = screenWidth / 37;

        if (icon) {
            klass = env->FindClass("android/graphics/Color");
            method = env->GetStaticMethodID(klass, "parseColor", "(Ljava/lang/String;)I");
            jint color = env->CallStaticIntMethod(klass, method, env->NewStringUTF("#44880000"));

            klass = env->FindClass("android/graphics/Paint");
            method = env->GetMethodID(klass, "setColor", "(I)V");
            env->CallVoidMethod(paint, method, color);

            klass = env->FindClass("android/graphics/Canvas");
            method = env->GetMethodID(klass, "drawCircle", "(FFFLandroid/graphics/Paint;)V");
            env->CallVoidMethod(canvas, method, (float)iconX, (float)iconY, (float)(screenWidth / 42), paint);

            klass = env->FindClass("android/graphics/Paint");
            method = env->GetMethodID(klass, "setColor", "(I)V");
            env->CallVoidMethod(paint, method, -1); ///White

            method = env->GetMethodID(klass, "setTextSize", "(F)V");
            env->CallVoidMethod(paint, method, (float)(screenWidth / 49));

            klass = env->FindClass("android/graphics/Canvas");
            method = env->GetMethodID(klass, "drawText", "(Ljava/lang/String;FFLandroid/graphics/Paint;)V");
            env->CallVoidMethod(canvas, method, env->NewStringUTF("P"), (float)iconX, (float)(iconY * 1.11), paint);
        } else {
            klass = env->FindClass("android/graphics/Paint");
            method = env->GetMethodID(klass, "setColor", "(I)V");
            env->CallVoidMethod(paint, method, -16777216); ///Black

            klass = env->FindClass("android/graphics/Canvas");
            method = env->GetMethodID(klass, "drawRect", "(FFFFLandroid/graphics/Paint;)V");
            env->CallVoidMethod(canvas, method, (float)(menuWidth - borderSize), 0.0f, (float)menuWidth, (float)screenHeight, paint);
            env->CallVoidMethod(canvas, method, (float)(menuWidth * 2), 0.0f, (float)(menuWidth * 2 + borderSize), (float)screenHeight, paint);

            klass = env->FindClass("android/graphics/Color");
            method = env->GetStaticMethodID(klass, "parseColor", "(Ljava/lang/String;)I");
            jint color = env->CallStaticIntMethod(klass, method, env->NewStringUTF("#66440000"));

            klass = env->FindClass("android/graphics/Paint");
            method = env->GetMethodID(klass, "setColor", "(I)V");
            env->CallVoidMethod(paint, method, color);

            klass = env->FindClass("android/graphics/Canvas");
            method = env->GetMethodID(klass, "drawRect", "(FFFFLandroid/graphics/Paint;)V");
            env->CallVoidMethod(canvas, method, (float)menuWidth, 0.0f, (float)(menuWidth * 2), (float)screenHeight, paint);

            klass = env->FindClass("android/graphics/Paint");
            method = env->GetMethodID(klass, "setColor", "(I)V");
            env->CallVoidMethod(paint, method, -16777216); ///Black

            klass = env->FindClass("android/graphics/Canvas");
            method = env->GetMethodID(klass, "drawRect", "(FFFFLandroid/graphics/Paint;)V");
            env->CallVoidMethod(canvas, method, (float)menuWidth, 0.0f, (float)(menuWidth * 2), (float)(screenHeight / 5.6), paint);

            klass = env->FindClass("android/graphics/Paint");
            method = env->GetMethodID(klass, "setColor", "(I)V");
            env->CallVoidMethod(paint, method, -1); ///White

            method = env->GetMethodID(klass, "setTextSize", "(F)V");
            env->CallVoidMethod(paint, method, (float)(screenWidth / 33));

            method = env->GetMethodID(klass, "setStyle", "(Landroid/graphics/Paint$Style;)V");
            klass = env->FindClass("android/graphics/Paint$Style");
            jfieldID field = env->GetStaticFieldID(klass, "STROKE", "Landroid/graphics/Paint$Style;");
            env->CallVoidMethod(paint, method, env->GetStaticObjectField(klass, field));

            klass = env->FindClass("android/graphics/Paint");
            method = env->GetMethodID(klass, "setTextAlign", "(Landroid/graphics/Paint$Align;)V");
            klass = env->FindClass("android/graphics/Paint$Align");
            field = env->GetStaticFieldID(klass, "CENTER", "Landroid/graphics/Paint$Align;");
            env->CallVoidMethod(paint, method, env->GetStaticObjectField(klass, field));

            klass = env->FindClass("android/graphics/Canvas");
            method = env->GetMethodID(klass, "drawText", "(Ljava/lang/String;FFLandroid/graphics/Paint;)V");
            env->CallVoidMethod(canvas, method, env->NewStringUTF("Project Venium v2"), (float)(screenWidth / 2), (float)(screenHeight / 12.34), paint);

            klass = env->FindClass("android/graphics/Paint");
            method = env->GetMethodID(klass, "setStyle", "(Landroid/graphics/Paint$Style;)V");
            klass = env->FindClass("android/graphics/Paint$Style");
            field = env->GetStaticFieldID(klass, "FILL", "Landroid/graphics/Paint$Style;");
            env->CallVoidMethod(paint, method, env->GetStaticObjectField(klass, field));

            klass = env->FindClass("android/graphics/Paint");
            method = env->GetMethodID(klass, "setTextSize", "(F)V");
            env->CallVoidMethod(paint, method, (float)(screenWidth / 49));

            switch (curMenu) {
                case 0:
                    klass = env->FindClass("android/graphics/Canvas");
                    method = env->GetMethodID(klass, "drawText", "(Ljava/lang/String;FFLandroid/graphics/Paint;)V");
                    env->CallVoidMethod(canvas, method, env->NewStringUTF("Main Menu"), (float)(screenWidth / 2), (float)(screenHeight / 7.11), paint);
                    AddMenus();
                    break;
                case 1:
                    klass = env->FindClass("android/graphics/Canvas");
                    method = env->GetMethodID(klass, "drawText", "(Ljava/lang/String;FFLandroid/graphics/Paint;)V");
                    env->CallVoidMethod(canvas, method, env->NewStringUTF("Player Menu"), (float)(screenWidth / 2), (float)(screenHeight / 7.11), paint);
                    AddMods();
                    break;
                case 2:
                    klass = env->FindClass("android/graphics/Canvas");
                    method = env->GetMethodID(klass, "drawText", "(Ljava/lang/String;FFLandroid/graphics/Paint;)V");
                    env->CallVoidMethod(canvas, method, env->NewStringUTF("Weapon Menu"), (float)(screenWidth / 2), (float)(screenHeight / 7.11), paint);
                    AddMods();
                    break;
                case 3:
                    klass = env->FindClass("android/graphics/Canvas");
                    method = env->GetMethodID(klass, "drawText", "(Ljava/lang/String;FFLandroid/graphics/Paint;)V");
                    env->CallVoidMethod(canvas, method, env->NewStringUTF("Visions Menu"), (float)(screenWidth / 2), (float)(screenHeight / 7.11), paint);
                    AddMods();
                    break;
                case 4:
                    klass = env->FindClass("android/graphics/Canvas");
                    method = env->GetMethodID(klass, "drawText", "(Ljava/lang/String;FFLandroid/graphics/Paint;)V");
                    env->CallVoidMethod(canvas, method, env->NewStringUTF("Killstreak Menu"), (float)(screenWidth / 2), (float)(screenHeight / 7.11), paint);
                    AddMods();
                    break;
                case 5:
                    klass = env->FindClass("android/graphics/Canvas");
                    method = env->GetMethodID(klass, "drawText", "(Ljava/lang/String;FFLandroid/graphics/Paint;)V");
                    env->CallVoidMethod(canvas, method, env->NewStringUTF("Profile Menu"), (float)(screenWidth / 2), (float)(screenHeight / 7.11), paint);
                    AddMods();
                    break;
            }

            klass = env->FindClass("android/graphics/Paint");
            method = env->GetMethodID(klass, "setColor", "(I)V");
            env->CallVoidMethod(paint, method, -1); ///White

            method = env->GetMethodID(klass, "setTextSize", "(F)V");
            env->CallVoidMethod(paint, method, (float)(screenWidth / 61));

            method = env->GetMethodID(klass, "setTextAlign", "(Landroid/graphics/Paint$Align;)V");
            klass = env->FindClass("android/graphics/Paint$Align");
            field = env->GetStaticFieldID(klass, "CENTER", "Landroid/graphics/Paint$Align;");
            env->CallVoidMethod(paint, method, env->GetStaticObjectField(klass, field));

            klass = env->FindClass("android/graphics/Canvas");
            method = env->GetMethodID(klass, "drawText", "(Ljava/lang/String;FFLandroid/graphics/Paint;)V");
            env->CallVoidMethod(canvas, method, env->NewStringUTF("Credits: Platinmods Team"), (float)(screenWidth / 2), (float)(screenHeight - (screenHeight / 77.11)), paint);
        }
    }

    void onDraw(JNIEnv *env, jobject thiz, jobject canvaz) {
        jclass o_Class = env->GetObjectClass(thiz);
        jclass s_Class = env->GetSuperclass(o_Class);
        jmethodID od_ID = env->GetMethodID(s_Class, "onDraw", "(Landroid/graphics/Canvas;)V");
        env->CallNonvirtualVoidMethod(thiz, o_Class, od_ID, canvaz);

        canvas = env->NewGlobalRef(canvaz);
        DrawMenu();
    }

    bool onTouchEvent(JNIEnv *env, jobject thiz, jobject event) {
        jclass klass = env->FindClass("android/view/MotionEvent");
        jmethodID method = env->GetMethodID(klass, "getAction", "()I");
        int value = env->CallIntMethod(event, method);

        switch (value) {
            case 0:
                method = env->GetMethodID(klass, "getRawX", "()F");
                x = env->CallFloatMethod(event, method);
                method = env->GetMethodID(klass, "getRawY", "()F");
                y = env->CallFloatMethod(event, method);

                if (!icon) {
                    curLine = GetSelectedLine(x, y);
                    if (curLine == -1) icon = true;
                    if (x >= screenWidth / 3 && x <= screenWidth / 3 * 2) {
                        Reset();
                        return true;
                    }
                } else if (IconSelected(x, y)) {
                    Reset();
                    return true;
                } Reset();
                return false;
            case 1:
                method = env->GetMethodID(klass, "getRawX", "()F");
                int rawX = env->CallFloatMethod(event, method);
                method = env->GetMethodID(klass, "getRawY", "()F");
                int rawY = env->CallFloatMethod(event, method);

                if (rawX - x < 8 && rawY - y < 8 && icon && IconSelected(rawX, rawY)) {
                    icon = false;
                    Reset();
                    return true;
                } else if (!icon) {
                    curLine = -2;
                    if (x >= screenWidth / 3 && x <= screenWidth / 3 * 2) {
                        Reset();
                        return true;
                    }
                }
        } Reset();
        return false;
    }
}