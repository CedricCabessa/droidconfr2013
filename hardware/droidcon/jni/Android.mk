LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE_TAGS := optional
LOCAL_SRC_FILES := android_droidcon_LibDroidcon.c
LOCAL_C_INCLUDES += $(JNI_H_INCLUDE) $(LOCAL_PATH)/../lib/
LOCAL_SHARED_LIBRARIES := libdroidcon
LOCAL_MODULE := libdroidcon_jni
LOCAL_PRELINK_MODULE := false
include $(BUILD_SHARED_LIBRARY)
