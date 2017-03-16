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

//¼���Ƿ����
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

//¼��״̬
bool Rec::isRecording () {

	if (_recPlugin) {
		if (isFunctionSupported("isRecording")) {
			return _recPlugin->callBoolFuncWithParam ("isRecording", NULL);
		}
	}
};

//��ʼ¼��
void Rec::startRecording () {

	if (_recPlugin) {
		_recPlugin->startRecording ();
	}
};

//����¼��
void Rec::stopRecording () {
	
	if (_recPlugin) {
		_recPlugin->stopRecording ();
	}
};

//��ͣ¼��
void Rec::pauseRecording () {

	if (_recPlugin) {
		if (isFunctionSupported ("pauseRecording")) {
			_recPlugin->callFuncWithParam ("pauseRecording", NULL);
		}
	}
};

//�ָ�¼��
void Rec::resumeRecording () {

	if (_recPlugin) {
		if (isFunctionSupported ("resumeRecording")) {
			_recPlugin->callFuncWithParam ("resumeRecording", NULL);
		}
	}
};

//��ʾ������
void Rec::showToolBar () {

	if (_recPlugin) {
		if (isFunctionSupported ("showToolBar")) {
			_recPlugin->callFuncWithParam ("showToolBar", NULL);
		}
	}
};

//���ع�����
void Rec::hideToolBar () {

	if (_recPlugin) {
		if (isFunctionSupported ("hideToolBar")) {
			_recPlugin->callFuncWithParam ("hideToolBar", NULL);
		}
	}
};

//��ʾ��Ƶ����
void Rec::showVideoCenter () {

	if (_recPlugin) {
		if (isFunctionSupported ("showVideoCenter")) {
			_recPlugin->callFuncWithParam ("showVideoCenter", NULL);
		}
	}
};

//������Ƶ����
void Rec::enterPlatform () {

	if (_recPlugin) {
		if (isFunctionSupported ("hideVideoCenter")) {
			_recPlugin->callFuncWithParam ("hideVideoCenter", NULL);
		}
	}
};

//����
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
		case kRECInitSuccess://��ʼ���ɹ�
			printf ("kRECInitSuccess\n");
			break;
		case kRECInitFail://��ʼ��ʧ��
			printf ("kRECInitFail\n");
			break;
		case kRECStartRecording://��ʼ¼��
			printf ("kRECStartRecording \n");
			break;
		case kRECStopRecording://����¼��
			printf ("kRECStopRecording \n");
			break;
		case kRECPauseRecording://��ͣ¼��
			printf ("kRECPauseRecording \n");
			break;
		case kRECResumeRecording://�ָ�¼��
			printf ("kRECResumeRecording \n");
			break;
		case kRECEnterSDKPage://����SDKҳ��
			printf ("kRECEnterSDKPage \n");
			break;
		case kRECQuitSDKPage://�˳�SDKҳ��
			printf ("kRECQuitSDKPage \n");
			break;
		case kRECShareSuccess://��Ƶ����ɹ�
			printf ("kRECShareSuccess \n");
			//cocos2d::Application::getInstance ()->applicationDidEnterBackground ();
			break;
		case kRECShareFail://��Ƶ����ʧ��
			printf ("kRECShareFail \n");
			//cocos2d::Application::getInstance ()->applicationWillEnterForeground ();
			break;
		default:
			break;
	}
};

//����¼�� 
void Rec::share () {

	if (_recPlugin) {
		map<string, string> info;
		info["Video_Desc"] = "REC����";
		info ["Video_Title"] = "RECSDK";
		_recPlugin->share (info);
	}
};