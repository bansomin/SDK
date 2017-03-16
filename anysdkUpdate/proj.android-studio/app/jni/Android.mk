LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
#1.将AnySDK提供的 Framework 库链接到游戏工程的库中
$(call import-add-path,$(LOCAL_PATH)/../)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../../Classes/AppDelegate.cpp \
                   ../../../Classes/ShareScene.cpp \
				   ../../../Classes/InformationScene.cpp \
				   ../../../Classes/AuthorizeScene.cpp \
				   ../../../Classes/PluginChannel.cpp \
				   ../../../Classes/Share.cpp \
				   ../../../Classes/Social.cpp \
				   ../../../Classes/Ads.cpp \
				   ../../../Classes/Rec.cpp \
                   ../../../Classes/HelloWorldScene.cpp

#头文件的引用
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes \
					../protocols_gnustl_static/include \
                    ../protocols_gnustl_static/android

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

#2.添加 AnySDK Framework 静态库声明
LOCAL_WHOLE_STATIC_LIBRARIES := PluginProtocolStatic		#添加静态块

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
#3.添加库路径声明代码
$(call import-module,protocols_gnustl_static/android)	#添加module

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
