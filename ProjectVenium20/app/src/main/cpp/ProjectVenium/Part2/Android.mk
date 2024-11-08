LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CFLAGS := -Wno-error=format-security -fpermissive -fvisibility=hidden -fvisibility-inlines-hidden -w -s -Werror -fms-extensions -Wno-narrowing -fno-rtti -fno-exceptions -g0 -fomit-frame-pointer -ffunction-sections -fdata-sections
LOCAL_CPPFLAGS := $(LOCAL_CFLAGS)
LOCAL_CPP_FEATURES := exceptions
LOCAL_LDFLAGS := -Wl,--strip-all
LOCAL_DISABLE_FORMAT_STRING_CHECKS := true
LOCAL_LDLIBS := -llog -landroid -lz -lGLESv2
LOCAL_MODULE := Platinmods
LOCAL_SRC_FILES := $(LOCAL_PATH)/native-lib.cpp

ifeq ($(TARGET_ARCH_ABI), armeabi-v7a)
endif

ifeq ($(TARGET_ARCH_ABI), arm64-v8a)
endif

ifeq ($(TARGET_ARCH_ABI), x86)
    LOCAL_CFLAGS += -ffast-math -mtune=atom -mssse3 -mfpmath=sse
endif

include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)