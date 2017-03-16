#include "AppDelegate.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

/*
要在游戏工程加载 jni 的时候为 AnySDK framework 设置 JavaVM 引用
因为 setJavaVM 需要在 onCreate 之前，所以写在 JNI_OnLoad 里肯定没错。3.3rc0 及其以上版本的 cocos_android_app_init 是在 onCreate 之前的，所以也可以写在这里。3.x 版本头文件需要写全路径，
例如 3.2 版本 #include "../../../../proj.android/protocols/android/PluginJniHelper.h"
*/

#include "../../../../proj.android-studio/app/protocols_gnustl_static/android/PluginJniHelper.h"
using namespace anysdk::framework;

using namespace cocos2d;

void cocos_android_app_init (JNIEnv* env) {
    LOGD("cocos_android_app_init");
    AppDelegate *pAppDelegate = new AppDelegate();

	JavaVM* vm;
	env->GetJavaVM(&vm);
	PluginJniHelper::setJavaVM(vm);
}
