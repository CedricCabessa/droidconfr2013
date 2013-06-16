LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= droidcon.c
LOCAL_MODULE_TAGS := optional
LOCAL_SHARED_LIBRARIES += libdroidcon
LOCAL_MODULE := droidcontestbin

include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)
LOCAL_SRC_FILES:= libdroidcon.c
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := libdroidcon
include $(BUILD_SHARED_LIBRARY)
