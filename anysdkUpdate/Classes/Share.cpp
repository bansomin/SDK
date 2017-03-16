
#include "Share.h"

Share::Share () {

	setListener ();
};

Share::~Share () {

};

Share* Share::_pInstance = NULL;

Share* Share::getInstance () {

	if (_pInstance==NULL) {
		_pInstance = new Share ();
		_pInstance->setListener ();
	}
	printf ("获取单例成功");

	return _pInstance;
};

void Share::purge () { 
	
	if (_pInstance) {
		delete _pInstance;
		_pInstance = NULL;
	}
};

//分享系统
void Share::setListener () {

	if (AgentManager::getInstance()->getSharePlugin()) {
		AgentManager::getInstance ()->getSharePlugin ()->setResultListener (this);
	}
};

	//分享系统功能
void Share::share () {
	printf ("Share::share");

	if (AgentManager::getInstance()->getSharePlugin()) {
		
		map<string, string> info;

		//title标题  印象笔记、邮箱、信息、微信、人人网和QQ空间使用
		info ["title"] = "title";
		// titleUrl是标题的网络链接，仅在人人网和QQ空间使用
		info ["titleUrl"] = "http://pre.im/pghJ";
		// site是分享此内容的网站名称，仅在QQ空间使用
		info ["site"] = "site";
		// siteUrl是分享此内容的网站地址，仅在QQ空间使用
		info ["sitUrl"] = "http://pre.im/pghJ";		   
		//imagePath是图片的本地路径，Linked-In以外的平台都支持此参数
		info ["imagePath"] = "/20170309021213296.jpg";
		// url仅在微信（包括好友和朋友圈）中使用
		info ["url"] = "http://pre.im/pghJ";
		//text分享文本，所有平台都需要这个
		info ["text"] = "文本内容文本内容文本内容文本内容文本内容文本内容";
		//comment是我对这条分享的评论，仅在人人网和QQ空间使用
		info ["comment"] = "该用户对这条分享没评论";

		AgentManager::getInstance ()->getSharePlugin ()->share (info);
	}
};

//分享回调函数（）
void Share::onShareResult (ShareResultCode ret, const char* msg) {

	printf ("onShareResult : %d", ret);
	
	switch (ret) {
		case kShareSuccess:
			printf ("kShareSuccess");
			break;
		case kShareFail:
			printf ("kShareFail");
			break;
		case kShareCancel:
			printf ("kShareCancel");
			break;
		case kShareNetworkError:	//网络问题分享失败
			printf ("kShareNetworkError");
			break;
		default:
			printf ("未知错误");
			break;
	}
};
