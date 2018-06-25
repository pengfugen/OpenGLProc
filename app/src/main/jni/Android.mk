LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := opengl_proc
LOCAL_SRC_FILES := opengl_proc.c


LOCAL_SHARED_LIBRARIES := libEGL
LOCAL_LDLIBS := -llog -landroid -lEGL -lGLESv2 -ljnigraphics
include $(BUILD_SHARED_LIBRARY)
