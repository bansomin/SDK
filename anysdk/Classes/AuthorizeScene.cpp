#include "AuthorizeScene.h"

#include <map>
#include <vector>

#include "HelloWorldScene.h"

//using namespace anysdk::framework;

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
*QQ��Ȩ����ȡ��
*/
void AuthorizeScene::Auth_QQ(Ref* pSender) {
	log("Auth_QQ");

};
void AuthorizeScene::Auth_QQCancel(Ref* pSender) {
	log("Auth_QQCancel");
	
};

/*
*΢����Ȩ����ȡ��
*/
void AuthorizeScene::Auth_WC(Ref* pSender) {
	log("Auth_WC");

}

void AuthorizeScene::Auth_WCCancel(Ref* pSender) {
	log("Auth_WCCancel");

};

/*
*������Ȩ����ȡ��
*/
void AuthorizeScene::Auth_SINA(Ref* pSender) {
	log("Auth_SINA");

};

void AuthorizeScene::Auth_SINACancel(Ref* pSender) {
	log("Auth_SINACancel");

};

/*
*facebook��Ȩ����ȡ��
*/
void AuthorizeScene::Auth_FACEBOOK(Ref* pSender) {
	log("Auth_FACEBOOK");

};

void AuthorizeScene::Auth_FACEBOOKCancel(Ref* pSender) {
	log("Auth_FACEBOOKCancel");

};

/*
*Twitter��Ȩ����ȡ��
*/
void AuthorizeScene::Auth_Twitter(Ref* pSender) {
	log("Auth_Twitter");

};

void AuthorizeScene::Auth_TwitterCancel(Ref* pSender) {
	log("Auth_TwitterCancel");

};

