/*
录屏功能的实现
*/

#ifndef __REC_H__
#define __REC_H__

#include "../proj.android-studio/app/protocols_gnustl_static/include/AgentManager.h"
using namespace anysdk::framework;

//分享系统存在回调信息，需要设置监听
class Rec : public RECResultListener {

private:
	Rec ();
	~Rec ();
	static Rec* _pInstance;
	ProtocolREC * _recPlugin;

public:
	static Rec* getInstance ();
	void purge ();
	void setListener ();

	//录制是否可用
	bool isAvailable (); 
	//录制状态
	bool isRecording ();
	//开始录制
	void startRecording ();
	//结束录制
	void stopRecording ();
	//分享录制 
	void share (); 
	//暂停录制
	void pauseRecording ();
	//恢复录制
	void resumeRecording ();
	//显示工具条
	void showToolBar ();
	//隐藏工具条
	void hideToolBar (); 
	//显示视频中心
	void showVideoCenter ();
	//隐藏视频中心
	void enterPlatform ();
	//设置
	void setMetaData ();

	bool isFunctionSupported (string strClassName);
	virtual void onRECResult (RECResultCode ret, const char* msg);

};

#endif

