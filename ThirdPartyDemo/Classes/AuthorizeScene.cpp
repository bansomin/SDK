#include "AuthorizeScene.h"

#include <map>
#include <vector>

#include "HelloWorldScene.h"
#include "Cocos2dx/Common/CCUMSocialSDK.h"
USING_NS_UM_SOCIAL;

AuthorizeScene::AuthorizeScene() {

};

AuthorizeScene::~AuthorizeScene() {

};

Scene* AuthorizeScene::createScene() {

	auto scene = Scene::create();
	auto layer = AuthorizeScene::create();
	scene->addChild(layer);

	return scene;
};

bool AuthorizeScene::init() {

	if (!Layer::init()){
		return false;
	}

	auto Wsize = Director::getInstance()->getWinSize();

	auto bg = Sprite::create("bg.png");
	bg->setPosition(Wsize.width/2, Wsize.height/2);
	this->addChild(bg);

	//����
	auto itemBack = MenuItemFont::create("Back", CC_CALLBACK_1(AuthorizeScene::backFunc, this));
	itemBack->setPosition(100, (Wsize.height - 50));
	itemBack->setScale(1.5);

	auto dis = 200;

	//QQ��Ȩ
	auto qqItem = MenuItemImage::create("authQQ.png", "authQQ.png", CC_CALLBACK_1(AuthorizeScene::Auth_QQ, this));
	qqItem->setPosition(Wsize.width/2 - 150, Wsize.height - 200);
	qqItem->setScale(1.5, 1.6);
	//ȡ��QQ��Ȩ
	auto qqCanItem = MenuItemImage::create("authCan.png", "authCan.png", CC_CALLBACK_1(AuthorizeScene::Auth_QQCancel, this));
	qqCanItem->setPosition(Wsize.width/2 + 150, qqItem->getPositionY());
	qqCanItem->setScale(1.5, 1.6);

	//΢����Ȩ
	auto wcItem = MenuItemImage::create("authWC.png", "authWC.png", CC_CALLBACK_1(AuthorizeScene::Auth_WC, this));
	wcItem->setPosition(qqItem->getPositionX(), qqItem->getPositionY() - dis);
	wcItem->setScale(1.5, 1.6);
	//ȡ��΢����Ȩ
	auto wcCanItem = MenuItemImage::create("authCan.png", "authCan.png", CC_CALLBACK_1(AuthorizeScene::Auth_WCCancel, this));
	wcCanItem->setPosition(Wsize.width/2 + 150, wcItem->getPositionY());
	wcCanItem->setScale(1.5, 1.6);

	//������Ȩ
	auto sinaItem = MenuItemImage::create("authSina.png", "authSina.png", CC_CALLBACK_1(AuthorizeScene::Auth_SINA, this));
	sinaItem->setPosition(wcItem->getPositionX(), wcItem->getPositionY()-dis);
	sinaItem->setScale(1.5, 1.6);
	//ȡ��������Ȩ
	auto sinaCanItem = MenuItemImage::create("authCan.png", "authCan.png", CC_CALLBACK_1(AuthorizeScene::Auth_SINACancel, this));
	sinaCanItem->setPosition(Wsize.width/2 + 150, sinaItem->getPositionY());
	sinaCanItem->setScale(1.5, 1.6);

	//facebook��Ȩ
	auto facebookItem = MenuItemImage::create("authface.png", "authface.png", CC_CALLBACK_1(AuthorizeScene::Auth_FACEBOOK, this));
	facebookItem->setPosition(sinaItem->getPositionX(), sinaItem->getPositionY()-dis);
	facebookItem->setScale(1.5, 1.6);
	//ȡ��facebook��Ȩ
	auto facebookCanItem = MenuItemImage::create("authCan.png", "authCan.png", CC_CALLBACK_1(AuthorizeScene::Auth_FACEBOOKCancel, this));
	facebookCanItem->setPosition(Wsize.width/2+150, facebookItem->getPositionY());
	facebookCanItem->setScale(1.5, 1.6);

	//twitter��Ȩ
	auto twitterItem = MenuItemImage::create("authTwitter.png", "authTwitter.png", CC_CALLBACK_1(AuthorizeScene::Auth_Twitter, this));
	twitterItem->setPosition(facebookItem->getPositionX(), facebookItem->getPositionY()-dis);
	twitterItem->setScale(1.5, 1.6);
	//ȡ��twitter��Ȩ
	auto twitterCanItem = MenuItemImage::create("authCan.png", "authCan.png", CC_CALLBACK_1(AuthorizeScene::Auth_TwitterCancel, this));
	twitterCanItem->setPosition(Wsize.width/2+150, twitterItem->getPositionY());
	twitterCanItem->setScale(1.5, 1.6);

	auto menu = Menu::create(itemBack, qqItem, qqCanItem, wcItem, wcCanItem, sinaItem, sinaCanItem, facebookItem, facebookCanItem, twitterItem, twitterCanItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	return true;
};

void AuthorizeScene::backFunc(Ref* pSender) {
	log("backFunc");

	Director::getInstance()->replaceScene(TransitionFade::create(1, HelloWorld::createScene()));
};
/*
*��Ȩ�ص�
* @param platform Ҫ��Ȩ��ƽ̨
* @param stCode ������, 200������Ȩ�ɹ�, 100����ʼ��Ȩ, 0������Ȩ����, -1����ȡ����Ȩ
* @param data ��Ȩʱ���ص�����
*/
void authCallback(int platform, int stCode, map<string, string>& data) {
	log("authCallback");

	log("********************************** Code : %d", stCode);
	if(stCode==100) {
		log("Authorization begin.");
	}
	else if(stCode==200) {
		log("Authorization success.");

		map<string, string>::iterator it = data.begin();
		for(; it!=data.end(); ++it) {
			log("#### DATA  %s -> %s.", it->first.c_str(), it->second.c_str());
		}
	}
	else if(stCode==0) {
		log("Authorization error.");
	}
	else if(stCode==-1) {
		log("Authorization to cancel.");
	}
	else {
		log("An unknown error.");
	}

};

/*
*QQ��Ȩ����ȡ��
*/
void AuthorizeScene::Auth_QQ(Ref* pSender) {
	log("Auth_QQ");

	CCUMSocialSDK* sdk = CCUMSocialSDK::create();
	sdk->authorize(QQ, auth_selector(authCallback));
};
void AuthorizeScene::Auth_QQCancel(Ref* pSender) {
	log("Auth_QQCancel");
	
	CCUMSocialSDK* sdk = CCUMSocialSDK::create();
	sdk->deleteAuthorization(QQ, auth_selector(authCallback));
};

/*
*΢����Ȩ����ȡ��
*/
void AuthorizeScene::Auth_WC(Ref* pSender) {
	log("Auth_WC");

	CCUMSocialSDK* sdk = CCUMSocialSDK::create();
	sdk->authorize(WEIXIN, auth_selector(authCallback));
};
void AuthorizeScene::Auth_WCCancel(Ref* pSender) {
	log("Auth_WCCancel");

	CCUMSocialSDK* sdk = CCUMSocialSDK::create();
	sdk->deleteAuthorization(WEIXIN, auth_selector(authCallback));
};

/*
*������Ȩ����ȡ��
*/
void AuthorizeScene::Auth_SINA(Ref* pSender) {
	log("Auth_SINA");

	CCUMSocialSDK* sdk = CCUMSocialSDK::create();
	sdk->authorize(SINA, auth_selector(authCallback));
};

void AuthorizeScene::Auth_SINACancel(Ref* pSender) {
	log("Auth_SINACancel");

	CCUMSocialSDK* sdk = CCUMSocialSDK::create();
	sdk->deleteAuthorization(SINA, auth_selector(authCallback));
};

/*
*facebook��Ȩ����ȡ��
*/
void AuthorizeScene::Auth_FACEBOOK(Ref* pSender) {
	log("Auth_FACEBOOK");

	CCUMSocialSDK* sdk = CCUMSocialSDK::create();
	sdk->authorize(FACEBOOK, auth_selector(authCallback));
};

void AuthorizeScene::Auth_FACEBOOKCancel(Ref* pSender) {
	log("Auth_FACEBOOKCancel");

	CCUMSocialSDK* sdk = CCUMSocialSDK::create();
	sdk->deleteAuthorization(FACEBOOK, auth_selector(authCallback));
};

/*
*Twitter��Ȩ����ȡ��
*/
void AuthorizeScene::Auth_Twitter(Ref* pSender) {
	log("Auth_Twitter");

	CCUMSocialSDK* sdk = CCUMSocialSDK::create();
	sdk->authorize(TWITTER, auth_selector(authCallback));
};

void AuthorizeScene::Auth_TwitterCancel(Ref* pSender) {
	log("Auth_TwitterCancel");

	CCUMSocialSDK* sdk = CCUMSocialSDK::create();
	sdk->deleteAuthorization(TWITTER, auth_selector(authCallback));
};

