LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CFLAGS := -Wno-error=format-security -fpermissive -fvisibility=hidden -fvisibility-inlines-hidden -w -s -Werror -fms-extensions -Wno-narrowing -fno-rtti -fno-exceptions -g0 -fomit-frame-pointer -ffunction-sections -fdata-sections
LOCAL_CPPFLAGS := $(LOCAL_CFLAGS)
LOCAL_CPP_FEATURES := exceptions
LOCAL_LDFLAGS := -Wl,--strip-all
LOCAL_DISABLE_FORMAT_STRING_CHECKS := true
LOCAL_LDLIBS := -llog -landroid -lz -lGLESv2
LOCAL_MODULE := ProjectVenium
LOCAL_SRC_FILES := $(LOCAL_PATH)/native-lib.cpp

include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)