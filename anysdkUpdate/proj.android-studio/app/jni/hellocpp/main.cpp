#include "AppDelegate.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

/*
Ҫ����Ϸ���̼��� jni ��ʱ��Ϊ AnySDK framework ���� JavaVM ����
��Ϊ setJavaVM ��Ҫ�� onCreate ֮ǰ������д�� JNI_OnLoad ��϶�û��3.3rc0 �������ϰ汾�� cocos_android_app_init ���� onCreate ֮ǰ�ģ�����Ҳ����д�����3.x �汾ͷ�ļ���Ҫдȫ·����
���� 3.2 �汾 #include "../../../../proj.android/protocols/android/PluginJniHelper.h"
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
