#include "Rec.h"

Rec::Rec () {

	setListener ();
};

Rec::~Rec () {

};

Rec* Rec::_pInstance = NULL;

Rec* Rec::getInstance () {

	if (_pInstance==NULL) {
		_pInstance = new Rec ();
		_pInstance->_recPlugin = AgentManager::getInstance ()->getRECPlugin ();
		_pInstance->setListener ();
	}
};

void Rec::purge () {

	if (_pInstance) {
		delete _pInstance;
		_pInstance = NULL;
	}
};

void Rec::setListener () {

	if (_recPlugin) {
		_recPlugin->setResultListener (this);
	}
};

//录制是否可用
bool Rec::isAvailable () {

	if (_recPlugin) {
		if (isFunctionSupported("isAvailable")) {
			return  _recPlugin->callBoolFuncWithParam ("isAvailable", NULL);
		}
	}
};


bool Rec::isFunctionSupported (string strClassName) {
	
	if (_recPlugin) {
		return _recPlugin->isFunctionSupported (strClassName.c_str ());
	}
	return NULL;
};

//录制状态
bool Rec::isRecording () {

	if (_recPlugin) {
		if (isFunctionSupported("isRecording")) {
			return _recPlugin->callBoolFuncWithParam ("isRecording", NULL);
		}
	}
};

//开始录制
void Rec::startRecording () {

	if (_recPlugin) {
		_recPlugin->startRecording ();
	}
};

//结束录制
void Rec::stopRecording () {
	
	if (_recPlugin) {
		_recPlugin->stopRecording ();
	}
};

//暂停录制
void Rec::pauseRecording () {

	if (_recPlugin) {
		if (isFunctionSupported ("pauseRecording")) {
			_recPlugin->callFuncWithParam ("pauseRecording", NULL);
		}
	}
};

//恢复录制
void Rec::resumeRecording () {

	if (_recPlugin) {
		if (isFunctionSupported ("resumeRecording")) {
			_recPlugin->callFuncWithParam ("resumeRecording", NULL);
		}
	}
};

//显示工具条
void Rec::showToolBar () {

	if (_recPlugin) {
		if (isFunctionSupported ("showToolBar")) {
			_recPlugin->callFuncWithParam ("showToolBar", NULL);
		}
	}
};

//隐藏工具条
void Rec::hideToolBar () {

	if (_recPlugin) {
		if (isFunctionSupported ("hideToolBar")) {
			_recPlugin->callFuncWithParam ("hideToolBar", NULL);
		}
	}
};

//显示视频中心
void Rec::showVideoCenter () {

	if (_recPlugin) {
		if (isFunctionSupported ("showVideoCenter")) {
			_recPlugin->callFuncWithParam ("showVideoCenter", NULL);
		}
	}
};

//隐藏视频中心
void Rec::enterPlatform () {

	if (_recPlugin) {
		if (isFunctionSupported ("hideVideoCenter")) {
			_recPlugin->callFuncWithParam ("hideVideoCenter", NULL);
		}
	}
};

//设置
void Rec::setMetaData () {

	if (_recPlugin) {
		if (isFunctionSupported ("setMetaData")) {
			map<string, string> info;
			info ["title"] = "RECSDK";
			PluginParam data (info);
			_recPlugin->callFuncWithParam ("setMetaData", NULL);
		}
	}
};

void Rec::onRECResult (RECResultCode ret, const char* msg) {

	switch (ret) {
		case kRECInitSuccess://初始化成功
			printf ("kRECInitSuccess\n");
			break;
		case kRECInitFail://初始化失败
			printf ("kRECInitFail\n");
			break;
		case kRECStartRecording://开始录制
			printf ("kRECStartRecording \n");
			break;
		case kRECStopRecording://结束录制
			printf ("kRECStopRecording \n");
			break;
		case kRECPauseRecording://暂停录制
			printf ("kRECPauseRecording \n");
			break;
		case kRECResumeRecording://恢复录制
			printf ("kRECResumeRecording \n");
			break;
		case kRECEnterSDKPage://进入SDK页面
			printf ("kRECEnterSDKPage \n");
			break;
		case kRECQuitSDKPage://退出SDK页面
			printf ("kRECQuitSDKPage \n");
			break;
		case kRECShareSuccess://视频分享成功
			printf ("kRECShareSuccess \n");
			//cocos2d::Application::getInstance ()->applicationDidEnterBackground ();
			break;
		case kRECShareFail://视频分享失败
			printf ("kRECShareFail \n");
			//cocos2d::Application::getInstance ()->applicationWillEnterForeground ();
			break;
		default:
			break;
	}
};

//分享录制 
void Rec::share () {

	if (_recPlugin) {
		map<string, string> info;
		info["Video_Desc"] = "REC分享";
		info ["Video_Title"] = "RECSDK";
		_recPlugin->share (info);
	}
};