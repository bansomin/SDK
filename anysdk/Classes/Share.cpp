#include "Share.h"

Share::Share() {

	log("Share");

	setListener();
};

Share::~Share() {

};

Share* Share::_instance = NULL;
Share* Share::getInstance() {
	log("getInstance");

	if(_instance==NULL) {
		_instance = new Share();
		_instance->setListener();
	}
	return _instance;
};

//���
void Share::purge() {
	log("purge");

	if(_instance) {
		delete _instance;
		_instance = NULL;
	}
};

void Share::setListener(){
		log("setListener");

	if(AgentManager::getInstance()->getSharePlugin()) {
		AgentManager::getInstance()->getSharePlugin()->setResultListener(this);
	}
};

//����ϵͳ����
void Share::share() {
	log("share");

	if(AgentManager::getInstance()->getPushPlugin()) {
		std::map<std::string, std::string> info;
		// title���⣬ӡ��ʼǡ����䡢��Ϣ��΢�š���������QQ�ռ�ʹ��
		info["title"] = "ShareSDK��һ�������SDK";
		// titleUrl�Ǳ�����������ӣ�������������QQ�ռ�ʹ��
		info["titleUrl"] = "http://sharesdk.cn";
		// site�Ƿ�������ݵ���վ���ƣ�����QQ�ռ�ʹ��
		info["site"] = "ShareSDK";
		// siteUrl�Ƿ�������ݵ���վ��ַ������QQ�ռ�ʹ��
		info["siteUrl"] = "http://sharesdk.cn";

		// imagePath��ͼƬ�ı���·����Linked-In�����ƽ̨��֧�ִ˲���
		info["imagePath"] = "/sdcard/test.png";
		// imageUrl��ͼƬ������·��������΢������������QQ�ռ�֧�ִ��ֶ�
		info["imageUrl"] = "http://www.baidu.com/img/bdlogo.png?tn=63090008_1_hao_pg";

		// url����΢�ţ��������Ѻ�����Ȧ����ʹ��
		info["url"] = "http://sharesdk.cn";

		// text�Ƿ����ı�������ƽ̨����Ҫ����ֶ�
		info["text"] = "ShareSDK֧����΢�š�����΢������Ѷ΢�����罻ƽ̨";
		// comment���Ҷ�������������ۣ�������������QQ�ռ�ʹ��
		info["comment"] = "��";


		AgentManager::getInstance()->getSharePlugin()->share(info);
	}
};

//����ص�����
void Share::onShareResult(ShareResultCode ret, const char* msg) {
	printf("onShareResult");

	switch(ret) {

		case kShareSuccess :
			printf("kShareSuccess");
		case kShareFail:
			printf("kShareFail");
		case kShareCancel:
			printf("kShareCancel");
		case kShareNetworkError:
			printf("kShareNetworkError");
		default:
			break;
	}
};
