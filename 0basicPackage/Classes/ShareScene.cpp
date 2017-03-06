#include "ShareScene.h"

#include "HelloWorldScene.h"

ShareScene::ShareScene() {

};

ShareScene::~ShareScene() {

};

Scene* ShareScene::createScene() {

	auto scene = Scene::create();
	auto layer = ShareScene::create();
	scene->addChild(layer);

	return scene;
};

bool ShareScene::init() {

	if (!Layer::init()){
		return false;
	}

	auto Wsize = Director::getInstance()->getWinSize();

	auto bg = Sprite::create("bg.png");
	bg->setPosition(Wsize.width/2, Wsize.height/2);
	this->addChild(bg);

	//返回
	auto itemBack = MenuItemFont::create("Back", CC_CALLBACK_1(ShareScene::backFunc, this));
	itemBack->setPosition(100, (Wsize.height-50));
	itemBack->setScale(1.5);

	auto dis = 120;

	//QQ分享
	auto qqItem = MenuItemImage::create("shareQQ.png", "shareQQ.png", CC_CALLBACK_1(ShareScene::Share_QQ, this));
	qqItem->setPosition(Wsize.width/2, Wsize.height-200);
	qqItem->setScale(1.5, 1.6);

	//微信分享
	auto wcItem = MenuItemImage::create("shareWC.png", "shareWC.png", CC_CALLBACK_1(ShareScene::Share_WC, this));
	wcItem->setPosition(qqItem->getPositionX(), qqItem->getPositionY() - dis);
	wcItem->setScale(1.5, 1.6);

	//facebook
	auto facebookItem = MenuItemImage::create("authface.png", "authface.png", CC_CALLBACK_1(ShareScene::Share_FACEBOOK, this));
	facebookItem->setPosition(wcItem->getPositionX(), wcItem->getPositionY()-dis);
	facebookItem->setScale(1.5, 1.6);

	//新浪分享
	auto sinaItem = MenuItemImage::create("shareSina.png", "shareSina.png", CC_CALLBACK_1(ShareScene::Share_SINA, this));
	sinaItem->setPosition(facebookItem->getPositionX(), facebookItem->getPositionY() - dis);
	sinaItem->setScale(1.5, 1.6);

	//QQ空间分享
	auto qqzItem = MenuItemImage::create("shareQQZ.png", "shareQQZ.png", CC_CALLBACK_1(ShareScene::Share_QQZ, this));
	qqzItem->setPosition(sinaItem->getPositionX(), sinaItem->getPositionY()-dis);
	qqzItem->setScale(1.5, 1.6);

	//Twitter
	auto twitterItem = MenuItemImage::create("authTwitter.png", "authTwitter.png", CC_CALLBACK_1(ShareScene::Share_TWITTER, this));
	twitterItem->setPosition(qqzItem->getPositionX(), qqzItem->getPositionY()-dis);
	twitterItem->setScale(1.5, 1.6);

	//MulPlatform
	auto mulItem = MenuItemImage::create("socialshare.png", "socialshare.png", CC_CALLBACK_1(ShareScene::Share_MulPlatform, this));
	mulItem->setPosition(twitterItem->getPositionX(), twitterItem->getPositionY()-dis);
	mulItem->setScale(1.5, 1.6);

	//WeChatC
	auto wccItem = MenuItemImage::create("shareWCC.png", "shareWCC.png", CC_CALLBACK_1(ShareScene::Share_WCC, this));
	wccItem->setPosition(mulItem->getPositionX(), mulItem->getPositionY()-dis);
	wccItem->setScale(1.5, 1.6);

	auto menu = Menu::create(itemBack, qqItem, wcItem, sinaItem, facebookItem, qqzItem, twitterItem, mulItem, wccItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	return true;
};

void ShareScene::backFunc(Ref* pSender) {
	log("backFunc");

	Director::getInstance()->replaceScene(TransitionFade::create(1, HelloWorld::createScene()));
};

void ShareScene::Share_QQ(Ref* pSender) {
	log("Share_QQ");

};

void ShareScene::Share_WC(Ref* pSender) {
	log("Share_WC");

};

void ShareScene::Share_WCC(Ref* pSender) {
	log("Share_WCC");

};

void ShareScene::Share_SINA(Ref* pSender) {
	log("Share_SINA");

};

void ShareScene::Share_FACEBOOK(Ref* pSender) {
	log("Share_FACEBOOK");

};

void ShareScene::Share_QQZ(Ref* pSender) {
	log("Share_QQZ");

};

void ShareScene::Share_TWITTER(Ref* pSender) {
	log("Share_TWITTER");

};

void ShareScene::Share_MulPlatform(Ref* pSender) {
	log("Share_MulPlatform");

};
