/*
	分享功能的实现
*/

#ifndef __SHARE_H__
#define __SHARE_H__

#include "../proj.android-studio/app/protocols_gnustl_static/include/AgentManager.h"
using namespace anysdk::framework;

//分享系统存在回调信息，需要设置监听
class Share : public ShareResultListener {

private:
	Share ();
	~Share ();
	static Share* _pInstance;

public:
	static Share* getInstance ();
	void purge ();
	//分享系统
	void setListener ();
	//分享系统功能
	void share ();								   
	//分享回调函数
	virtual void onShareResult (ShareResultCode ret, const char* msg);	
};

#endif
