#include "ShareScene.h"

#include "HelloWorldScene.h"

//测试分享
//点击QQ分享进行测试
#include "Share.h"

//录屏相关分享
#include "Rec.h"

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

	//汉字乱码解决方案
	//创建字典类实例，将xml加载到字典中
	auto* chnString = Dictionary::createWithContentsOfFile ("fonts/myString.xml");
	//通过xml文件中的key获取value
	const char* back = ((String*) chnString->objectForKey ("back"))->getCString ();
	const char* exit = ((String*) chnString->objectForKey ("exit"))->getCString ();

	const char* share = ((String*) chnString->objectForKey ("share"))->getCString ();

	const char* recCheck = ((String*) chnString->objectForKey ("recCheck"))->getCString ();
	const char* recStatus = ((String*) chnString->objectForKey ("recStatus"))->getCString ();
	const char* recStart = ((String*) chnString->objectForKey ("recStart"))->getCString ();
	const char* recEnd = ((String*) chnString->objectForKey ("recEnd"))->getCString ();
	const char* recPause = ((String*) chnString->objectForKey ("recPause"))->getCString ();
	const char* recResume = ((String*) chnString->objectForKey ("recResume"))->getCString ();
	const char* recShowBar = ((String*) chnString->objectForKey ("recShowBar"))->getCString ();
	const char* recHideBar = ((String*) chnString->objectForKey ("recHideBar"))->getCString ();
	const char* recShowCenter = ((String*) chnString->objectForKey ("recShowCenter"))->getCString ();
	const char* recHideCenter = ((String*) chnString->objectForKey ("recHideCenter"))->getCString ();
	const char* recSet = ((String*) chnString->objectForKey ("recSet"))->getCString ();

	//返回
	auto itemBack = MenuItemFont::create(back, CC_CALLBACK_1(ShareScene::backFunc, this));
	itemBack->setPosition(Wsize.width - 100, 100);
	itemBack->setScale(1.5);

	//退出
	auto exitItem = MenuItemFont::create (exit, CC_CALLBACK_1 (ShareScene::menuCloseCallback, this));
	exitItem->setPosition (100, 100);
	exitItem->setScale (1.5, 1.6);
	auto dis = 120;

	//QQ分享
	//auto qqItem = MenuItemImage::create("shareQQ.png", "shareQQ.png", CC_CALLBACK_1(ShareScene::Share_QQ, this));
	auto qqItem = MenuItemFont::create (share, CC_CALLBACK_1 (ShareScene::Share_QQ, this));
	//qqItem->setPosition(Wsize.width/2, Wsize.height-200);
	qqItem->setScale(1.5, 1.6);

	//微信分享
	//auto wcItem = MenuItemImage::create("shareWC.png", "shareWC.png", CC_CALLBACK_1(ShareScene::Share_WC, this));
	auto wcItem = MenuItemFont::create (recCheck, CC_CALLBACK_1 (ShareScene::Share_WC, this));
	//wcItem->setPosition(qqItem->getPositionX(), qqItem->getPositionY() - dis);
	wcItem->setScale(1.5, 1.6);

	//facebook
	//auto facebookItem = MenuItemImage::create("authface.png", "authface.png", CC_CALLBACK_1(ShareScene::Share_FACEBOOK, this));
	auto facebookItem = MenuItemFont::create (recStatus, CC_CALLBACK_1 (ShareScene::Share_FACEBOOK, this));
	//facebookItem->setPosition(wcItem->getPositionX(), wcItem->getPositionY()-dis);
	facebookItem->setScale(1.5, 1.6);

	//新浪分享
	//auto sinaItem = MenuItemImage::create("shareSina.png", "shareSina.png", CC_CALLBACK_1(ShareScene::Share_SINA, this));
	auto sinaItem = MenuItemFont::create (recStart, CC_CALLBACK_1 (ShareScene::Share_SINA, this));
	//sinaItem->setPosition(facebookItem->getPositionX(), facebookItem->getPositionY() - dis);
	sinaItem->setScale(1.5, 1.6);

	//QQ空间分享
	//auto qqzItem = MenuItemImage::create("shareQQZ.png", "shareQQZ.png", CC_CALLBACK_1(ShareScene::Share_QQZ, this));
	auto qqzItem = MenuItemFont::create (recEnd, CC_CALLBACK_1 (ShareScene::Share_QQZ, this));
	//qqzItem->setPosition(sinaItem->getPositionX(), sinaItem->getPositionY()-dis);
	qqzItem->setScale(1.5, 1.6);

	//Twitter
	//auto twitterItem = MenuItemImage::create("authTwitter.png", "authTwitter.png", CC_CALLBACK_1(ShareScene::Share_TWITTER, this));
	auto twitterItem = MenuItemFont::create (recPause, CC_CALLBACK_1 (ShareScene::Share_TWITTER, this));
	//twitterItem->setPosition(qqzItem->getPositionX(), qqzItem->getPositionY()-dis);
	twitterItem->setScale(1.5, 1.6);

	//MulPlatform
	//auto mulItem = MenuItemImage::create("socialshare.png", "socialshare.png", CC_CALLBACK_1(ShareScene::Share_MulPlatform, this));
	auto mulItem = MenuItemFont::create (recResume, CC_CALLBACK_1 (ShareScene::Share_MulPlatform, this));
	//mulItem->setPosition(twitterItem->getPositionX(), twitterItem->getPositionY()-dis);
	mulItem->setScale(1.5, 1.6);

	//WeChatC
	//auto wccItem = MenuItemImage::create("shareWCC.png", "shareWCC.png", CC_CALLBACK_1(ShareScene::Share_WCC, this));
	auto wccItem = MenuItemFont::create (recShowBar, CC_CALLBACK_1 (ShareScene::Share_WCC, this));
	//wccItem->setPosition(mulItem->getPositionX(), mulItem->getPositionY()-dis);
	wccItem->setScale(1.5, 1.6);

	auto recHideBarItem = MenuItemFont::create (recHideBar, CC_CALLBACK_1 (ShareScene::Share_recHideBar, this));
	recHideBarItem->setScale (1.5, 1.6);

	auto recShowCenterItem = MenuItemFont::create (recShowCenter, CC_CALLBACK_1 (ShareScene::Share_recShowCenter, this));
	recShowCenterItem->setScale (1.5, 1.6);

	auto recHideCenterItem = MenuItemFont::create (recHideCenter, CC_CALLBACK_1 (ShareScene::Share_recHideCenter, this));
	recHideCenterItem->setScale (1.5, 1.6);

	auto recSetItem = MenuItemFont::create (recSet, CC_CALLBACK_1 (ShareScene::Share_recSet, this));
	recSetItem->setScale (1.5, 1.6);

	auto menu = Menu::create(itemBack, exitItem, qqItem, wcItem, sinaItem, facebookItem, qqzItem, 
							 twitterItem, mulItem, wccItem, recHideBarItem, recShowCenterItem, recHideCenterItem, recSetItem, NULL);
	menu->setPosition(Wsize.width/2, Wsize.height/2);
	menu->alignItemsVerticallyWithPadding (30);
	this->addChild(menu);

	return true;
};

void ShareScene::backFunc(Ref* pSender) {
	log("backFunc");

	Director::getInstance()->replaceScene(TransitionFade::create(1, HelloWorld::createScene()));
};

void ShareScene::Share_QQ(Ref* pSender) {
	log("Share_QQ");
	
	//进行分享测试						  
	Share::getInstance ()->share ();
};

void ShareScene::Share_WC(Ref* pSender) {
	log("Share_WC");

	//检测录屏是否可用
	Rec::getInstance ()->isAvailable ();
};

void ShareScene::Share_WCC(Ref* pSender) {
	log("Share_WCC");

	//检测状态
	Rec::getInstance ()->isRecording ();
};

void ShareScene::Share_SINA(Ref* pSender) {
	log("Share_SINA");

	//开始录屏
	Rec::getInstance ()->startRecording ();
};

void ShareScene::Share_FACEBOOK(Ref* pSender) {
	log("Share_FACEBOOK");

	//结束录屏
	Rec::getInstance ()->stopRecording();
};

void ShareScene::Share_QQZ(Ref* pSender) {
	log("Share_QQZ");

	//暂停录屏
	Rec::getInstance ()->pauseRecording ();
};

void ShareScene::Share_TWITTER(Ref* pSender) {
	log("Share_TWITTER");

	//恢复录屏
	Rec::getInstance ()->resumeRecording ();
};

void ShareScene::Share_MulPlatform(Ref* pSender) {
	log("Share_MulPlatform");
										   
	//显示工具条
	Rec::getInstance ()->showToolBar ();
};

void ShareScene::Share_recHideBar (Ref* pSender) {
	log ("Share_recHideBar");

	//隐藏工具条
	Rec::getInstance ()->hideToolBar ();
};

void ShareScene::Share_recShowCenter (Ref* pSender) {
	log ("Share_recShowCenter");

	//显示视频中心
	Rec::getInstance ()->showVideoCenter ();
};

void ShareScene::Share_recHideCenter (Ref* pSender) {
	log ("Share_recHideCenter");

	//隐藏视频中心
	Rec::getInstance ()->enterPlatform();
};

void ShareScene::Share_recSet (Ref* pSender) {
	log ("Share_recSet");

	//设置
	Rec::getInstance ()->setMetaData ();
};

void ShareScene::menuCloseCallback (Ref* pSender) {
	Director::getInstance ()->end ();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit (0);
#endif
}