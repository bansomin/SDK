LOCAL_PATH := $(call my-dir)

#1、将AnySDK提供的 Framework 库链接到游戏工程的库中
$(call import-add-path,$(LOCAL_PATH)/../)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2djs_shared

LOCAL_MODULE_FILENAME := libcocos2djs

#2、新增 JS 绑定的 cpp 文件
LOCAL_SRC_FILES := hellojavascript/main.cpp \
                   ../../../Classes/AppDelegate.cpp \
                   ../../../Classes/jsb_anysdk_basic_conversions.cpp \
                   ../../../Classes/jsb_anysdk_protocols_auto.cpp \
                   ../../../Classes/manualanysdkbindings.cpp

#3、头文件的引用
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes \
                 ../protocols_gnustl_static/include \
                 ../protocols_gnustl_static/android

LOCAL_STATIC_LIBRARIES := cocos2d_js_static

#4、添加 AnySDK Framework 静态库声明
LOCAL_WHOLE_STATIC_LIBRARIES ：= PluginProtocolStatic

LOCAL_EXPORT_CFLAGS := -DCOCOS2D_DEBUG=2 -DCOCOS2D_JAVASCRIPT

include $(BUILD_SHARED_LIBRARY)


$(call import-module, scripting/js-bindings/proj.android)
#5、添加库路径声明代码
$(call import-module,protocols_gnustl_static/android)