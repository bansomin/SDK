#include "AppDelegate.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace cocos2d;

//初始化 JavaVM
//导入头文件并声明命名空间
//#include "../../../../proj.android/protocols/android/PluginJniHelper.h"
//using namespace anysdk::framework;

void cocos_android_app_init (JNIEnv* env) {
    LOGD("cocos_android_app_init");
    AppDelegate *pAppDelegate = new AppDelegate();

	//JavaVM* vm;
	//env->GetJavaVM(vm);
	//PluginJniHelper::setJavaVM(vm);
}
