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

//清除
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

//分享系统功能
void Share::share() {
	log("share");

	if(AgentManager::getInstance()->getPushPlugin()) {
		std::map<std::string, std::string> info;
		// title标题，印象笔记、邮箱、信息、微信、人人网和QQ空间使用
		info["title"] = "ShareSDK是一个神奇的SDK";
		// titleUrl是标题的网络链接，仅在人人网和QQ空间使用
		info["titleUrl"] = "http://sharesdk.cn";
		// site是分享此内容的网站名称，仅在QQ空间使用
		info["site"] = "ShareSDK";
		// siteUrl是分享此内容的网站地址，仅在QQ空间使用
		info["siteUrl"] = "http://sharesdk.cn";

		// imagePath是图片的本地路径，Linked-In以外的平台都支持此参数
		info["imagePath"] = "/sdcard/test.png";
		// imageUrl是图片的网络路径，新浪微博，人人网，QQ空间支持此字段
		info["imageUrl"] = "http://www.baidu.com/img/bdlogo.png?tn=63090008_1_hao_pg";

		// url仅在微信（包括好友和朋友圈）中使用
		info["url"] = "http://sharesdk.cn";

		// text是分享文本，所有平台都需要这个字段
		info["text"] = "ShareSDK支持如微信、新浪微博、腾讯微博等社交平台";
		// comment是我对这条分享的评论，仅在人人网和QQ空间使用
		info["comment"] = "无";


		AgentManager::getInstance()->getSharePlugin()->share(info);
	}
};

//分享回调函数
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
