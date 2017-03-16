#include "AuthorizeScene.h"

#include <map>
#include <vector>

#include "HelloWorldScene.h"

#include "../proj.android-studio/app/protocols_gnustl_static/include/AgentManager.h"
//测试社交
#include "Social.h"
//测试登陆、登出
#include "PluginChannel.h"

using namespace anysdk::framework;

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

	//汉字乱码解决方案
	//创建字典类实例，将xml加载到字典中
	auto* chnString = Dictionary::createWithContentsOfFile ("fonts/myString.xml");
	//通过xml文件中的key获取value
	const char* back = ((String*) chnString->objectForKey ("back"))->getCString ();
	const char* exit = ((String*) chnString->objectForKey ("exit"))->getCString ();

	const char* submit = ((String*) chnString->objectForKey ("submit"))->getCString ();
	const char* rank = ((String*) chnString->objectForKey ("rank"))->getCString ();

	const char* unlock = ((String*) chnString->objectForKey ("unlock"))->getCString ();
	const char* ach = ((String*) chnString->objectForKey ("ach"))->getCString ();

	const char* login = ((String*) chnString->objectForKey ("login"))->getCString ();
	const char* logout = ((String*) chnString->objectForKey ("logout"))->getCString ();

	const char* switchb = ((String*) chnString->objectForKey ("switch"))->getCString ();
	const char* platform = ((String*) chnString->objectForKey ("platform"))->getCString ();

	const char* ppause = ((String*) chnString->objectForKey ("ppause"))->getCString ();
	const char* pexit = ((String*) chnString->objectForKey ("pexit"))->getCString ();

	const char* showBar = ((String*) chnString->objectForKey ("showBar"))->getCString ();
	const char* hideBar = ((String*) chnString->objectForKey ("hideBar"))->getCString ();

	auto dis = 150;

	//返回
	auto itemBack = MenuItemFont::create(back, CC_CALLBACK_1(AuthorizeScene::backFunc, this));
	itemBack->setPosition(Wsize.width - 100, 100);
	itemBack->setScale(1.5);

	//退出
	auto exitItem = MenuItemFont::create (exit, CC_CALLBACK_1 (AuthorizeScene::menuCloseCallback, this));
	exitItem->setPosition (100, 100);
	exitItem->setScale (1.5, 1.6);

	//QQ授权
	//auto qqItem = MenuItemImage::create("authQQ.png", "authQQ.png", CC_CALLBACK_1(AuthorizeScene::Auth_QQ, this));
	auto qqItem = MenuItemFont::create (submit, CC_CALLBACK_1 (AuthorizeScene::Auth_QQ, this));
	qqItem->setPosition(Wsize.width/2 - 150, Wsize.height - 200);
	qqItem->setScale(1.5, 1.6);

	//取消QQ授权
	//auto qqCanItem = MenuItemImage::create("authCan.png", "authCan.png", CC_CALLBACK_1(AuthorizeScene::Auth_QQCancel, this));
	auto qqCanItem = MenuItemFont::create (rank, CC_CALLBACK_1 (AuthorizeScene::Auth_QQCancel, this));
	qqCanItem->setPosition(Wsize.width/2 + 150, qqItem->getPositionY());
	qqCanItem->setScale(1.5, 1.6);

	//微信授权
	//auto wcItem = MenuItemImage::create("authWC.png", "authWC.png", CC_CALLBACK_1(AuthorizeScene::Auth_WC, this));
	auto wcItem = MenuItemFont::create (unlock, CC_CALLBACK_1 (AuthorizeScene::Auth_WC, this));
	wcItem->setPosition(qqItem->getPositionX(), qqItem->getPositionY() - dis);
	wcItem->setScale(1.5, 1.6);

	//取消微信授权
	//auto wcCanItem = MenuItemImage::create("authCan.png", "authCan.png", CC_CALLBACK_1(AuthorizeScene::Auth_WCCancel, this));
	auto wcCanItem = MenuItemFont::create (ach, CC_CALLBACK_1 (AuthorizeScene::Auth_WCCancel, this));
	wcCanItem->setPosition(Wsize.width/2 + 150, wcItem->getPositionY());
	wcCanItem->setScale(1.5, 1.6);

	//新浪授权
	//auto sinaItem = MenuItemImage::create("authSina.png", "authSina.png", CC_CALLBACK_1(AuthorizeScene::Auth_SINA, this));
	auto sinaItem = MenuItemFont::create (login, CC_CALLBACK_1 (AuthorizeScene::Auth_SINA, this));
	sinaItem->setPosition(wcItem->getPositionX(), wcItem->getPositionY()-dis);
	sinaItem->setScale(1.5, 1.6);

	//取消新浪授权
	//auto sinaCanItem = MenuItemImage::create("authCan.png", "authCan.png", CC_CALLBACK_1(AuthorizeScene::Auth_SINACancel, this));
	auto sinaCanItem = MenuItemFont::create (logout, CC_CALLBACK_1 (AuthorizeScene::Auth_SINACancel, this));
	sinaCanItem->setPosition(Wsize.width/2 + 150, sinaItem->getPositionY());
	sinaCanItem->setScale(1.5, 1.6);

	//facebook授权
	//auto facebookItem = MenuItemImage::create("authface.png", "authface.png", CC_CALLBACK_1(AuthorizeScene::Auth_FACEBOOK, this));
	auto facebookItem = MenuItemFont::create (switchb, CC_CALLBACK_1 (AuthorizeScene::Auth_FACEBOOK, this));
	facebookItem->setPosition(sinaItem->getPositionX(), sinaItem->getPositionY()-dis);
	facebookItem->setScale(1.5, 1.6);
	
	//取消facebook授权
	//auto facebookCanItem = MenuItemImage::create("authCan.png", "authCan.png", CC_CALLBACK_1(AuthorizeScene::Auth_FACEBOOKCancel, this));
	auto facebookCanItem = MenuItemFont::create (platform, CC_CALLBACK_1 (AuthorizeScene::Auth_FACEBOOKCancel, this));
	facebookCanItem->setPosition(Wsize.width/2+150, facebookItem->getPositionY());
	facebookCanItem->setScale(1.5, 1.6);

	//twitter授权
	//auto twitterItem = MenuItemImage::create("authTwitter.png", "authTwitter.png", CC_CALLBACK_1(AuthorizeScene::Auth_Twitter, this));
	auto twitterItem = MenuItemFont::create (ppause, CC_CALLBACK_1 (AuthorizeScene::Auth_Twitter, this));
	twitterItem->setPosition(facebookItem->getPositionX(), facebookItem->getPositionY()-dis);
	twitterItem->setScale(1.5, 1.6);
	
	//取消twitter授权
	//auto twitterCanItem = MenuItemImage::create("authCan.png", "authCan.png", CC_CALLBACK_1(AuthorizeScene::Auth_TwitterCancel, this));
	auto twitterCanItem = MenuItemFont::create (pexit, CC_CALLBACK_1 (AuthorizeScene::Auth_TwitterCancel, this));
	twitterCanItem->setPosition(Wsize.width/2+150, twitterItem->getPositionY());
	twitterCanItem->setScale(1.5, 1.6);

	//显示按钮
	auto showBarItem = MenuItemFont::create (showBar, CC_CALLBACK_1 (AuthorizeScene::Auth_ShowBar, this));
	showBarItem->setPosition (twitterItem->getPositionX (), twitterItem->getPositionY () - dis);
	showBarItem->setScale (1.5, 1.6);

	//隐藏按钮
	auto hideBarItem = MenuItemFont::create (hideBar, CC_CALLBACK_1 (AuthorizeScene::Auth_HideBar, this));
	hideBarItem->setPosition (Wsize.width / 2 + 150, showBarItem->getPositionY ());
	hideBarItem->setScale (1.5, 1.6);

	auto menu = Menu::create(itemBack, exitItem, qqItem, qqCanItem, wcItem, wcCanItem, sinaItem, sinaCanItem, facebookItem, facebookCanItem, twitterItem, twitterCanItem, showBarItem, hideBarItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	return true;
};

void AuthorizeScene::backFunc(Ref* pSender) {
	log("backFunc");

	Director::getInstance()->replaceScene(TransitionFade::create(1, HelloWorld::createScene()));
};

/*
*QQ授权及其取消
*/
void AuthorizeScene::Auth_QQ(Ref* pSender) {
	log("Auth_QQ");

	//测试-//提交分数（排行榜 ID，score 为分数值）
	Social::getInstance ()->submitScore ("my", 100);
};
void AuthorizeScene::Auth_QQCancel(Ref* pSender) {
	log("Auth_QQCancel");
	
	//测试-//获取排行榜(leaderboardID 为排行榜 ID)
	Social::getInstance ()->showLeaderboard ("my");
};

/*
*微信授权及其取消
*/
void AuthorizeScene::Auth_WC(Ref* pSender) {
	log("Auth_WC");

	//测试-	//解锁成就榜(achInfo 为相关信息，TAchievementInfo 为 std::map 类型)
	TAchievementInfo info;
	info ["rank"] = "my";
	Social::getInstance ()->unlockAchievement (info);
}

void AuthorizeScene::Auth_WCCancel(Ref* pSender) {
	log("Auth_WCCancel");

	//测试-//显示成就榜
	Social::getInstance ()->showAchievements ();
};

/*
*新浪授权及其取消
*/
void AuthorizeScene::Auth_SINA(Ref* pSender) {
	log("Auth_SINA");

	//测试登陆
	PluginChannel::getInstance ()->login ();
};

void AuthorizeScene::Auth_SINACancel(Ref* pSender) {
	log("Auth_SINACancel");

	//测试登出
	PluginChannel::getInstance ()->logout ();
};

/*
*facebook授权及其取消
*/
void AuthorizeScene::Auth_FACEBOOK(Ref* pSender) {
	log("Auth_FACEBOOK");

	//测试切换账号
	PluginChannel::getInstance ()->accountSwitch ();
};

void AuthorizeScene::Auth_FACEBOOKCancel(Ref* pSender) {
	log("Auth_FACEBOOKCancel");

	//进入渠道中心
	PluginChannel::getInstance ()->enterPlatform ();
};

/*
*Twitter授权及其取消
*/
void AuthorizeScene::Auth_Twitter(Ref* pSender) {
	log("Auth_Twitter");

	//渠道暂停界面调用
	PluginChannel::getInstance ()->pause ();
};

void AuthorizeScene::Auth_TwitterCancel(Ref* pSender) {
	log("Auth_TwitterCancel");

	//渠道退出界面调用
	PluginChannel::getInstance ()->Exit ();
};

/*
*按钮显示及隐藏
*/
void AuthorizeScene::Auth_ShowBar (Ref* pSender) {
	log ("Auth_ShowBar");

	//显示悬浮工具栏
	//PluginChannel::getInstance ()->showToolBar ();
};

void AuthorizeScene::Auth_HideBar (Ref* pSender) {
	log ("Auth_HideBar");

	//隐藏悬浮工具栏
	//PluginChannel::getInstance ()->hideToolBar ();
};

void AuthorizeScene::menuCloseCallback (Ref* pSender) {
	Director::getInstance ()->end ();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit (0);
#endif
}

