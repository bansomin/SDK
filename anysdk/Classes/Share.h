/*************************BEGIN**************************************************** 
    			Created by HAO on 2017/1/24
    BRIEF	: 	分享界面
    VERSION	: 
    HISTORY	:
***************************END****************************************************/
#pragma once

#ifndef __SHARE__
#define __SHARE__

#include "cocos2d.h"
USING_NS_CC;

#include "../../../../proj.android/protocols/include/AgentManager.h"
using namespace anysdk::framework;

class Share : public ShareResultListener {

	private:
	Share();
	virtual ~Share();
	static Share* _instance;	//单例模式

	public:
	static Share*getInstance();
	
	//清除
	void purge();
	//分享系统功能
	void share();
	void setListener();
	//分享回调函数
	virtual void onShareResult(ShareResultCode ret, const char* msg);

};


#endif // !__SHARE__
