/*************************BEGIN**************************************************** 
    			Created by HAO on 2017/1/24
    BRIEF	: 	�������
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
	static Share* _instance;	//����ģʽ

	public:
	static Share*getInstance();
	
	//���
	void purge();
	//����ϵͳ����
	void share();
	void setListener();
	//����ص�����
	virtual void onShareResult(ShareResultCode ret, const char* msg);

};


#endif // !__SHARE__
