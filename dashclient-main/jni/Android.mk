LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := libdashjni

LOCAL_SRC_FILES := dash_manager.c

include $(BUILD_SHARED_LIBRARY)
