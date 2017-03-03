#include "InformationScene.h"

#include <map>
#include <vector>

#include "HelloWorldScene.h"

InformationScene::InformationScene(){

};

InformationScene::~InformationScene() {

};

Scene* InformationScene::createScene() {

	auto scene = Scene::create();
	auto layer = InformationScene::create();
	scene->addChild(layer);

	return scene;
};

bool InformationScene::init() {

	if (!Layer::init()){
		return false;
	}

	auto Wsize = Director::getInstance()->getWinSize();

	auto bg = Sprite::create("bg.png");
	bg->setPosition(Wsize.width/2, Wsize.height/2);
	this->addChild(bg);

	//返回
	auto itemBack = MenuItemFont::create("Back", CC_CALLBACK_1(InformationScene::backFunc, this));
	itemBack->setPosition(100, (Wsize.height - 50));
	itemBack->setScale(1.5);

	auto dis = 200;

	//获取QQ信息
	auto qqItem = MenuItemImage::create("QQ.png", "QQ.png", CC_CALLBACK_1(InformationScene::GetInfo_QQ, this));
	qqItem->setPosition(Wsize.width/2, Wsize.height - 200);
	qqItem->setScale(1.5, 1.6);

	//微信
	auto wcItem = MenuItemImage::create("WC.png", "WC.png", CC_CALLBACK_1(InformationScene::GetInfo_WC, this));
	wcItem->setPosition(qqItem->getPositionX(), qqItem->getPositionY()-dis);
	wcItem->setScale(1.5, 1.6);

	//新浪
	auto sinaItem = MenuItemImage::create("Sina.png", "Sina.png", CC_CALLBACK_1(InformationScene::GetInfo_SINA, this));
	sinaItem->setPosition(wcItem->getPositionX(), wcItem->getPositionY()-dis);
	sinaItem->setScale(1.5, 1.6);

	auto menu = Menu::create(itemBack, qqItem, wcItem, sinaItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	return true;
};

void InformationScene::backFunc(Ref* pSender) {
	log("backFunc");

	Director::getInstance()->replaceScene(TransitionFade::create(1, HelloWorld::createScene()));
};

void InformationScene::GetInfo_QQ(Ref* pSender) {
	log("GetInfo_QQ");

};

void InformationScene::GetInfo_WC(Ref* pSender) {
	log("GetInfo_WC");

};

void InformationScene::GetInfo_SINA(Ref* pSender) {
	log("GetInfo_SINA");

};
