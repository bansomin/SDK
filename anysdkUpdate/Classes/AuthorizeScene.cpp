#include "AuthorizeScene.h"

#include <map>
#include <vector>

#include "HelloWorldScene.h"

#include "../proj.android-studio/app/protocols_gnustl_static/include/AgentManager.h"
//�����罻
#include "Social.h"
//���Ե�½���ǳ�
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

	//��������������
	//�����ֵ���ʵ������xml���ص��ֵ���
	auto* chnString = Dictionary::createWithContentsOfFile ("fonts/myString.xml");
	//ͨ��xml�ļ��е�key��ȡvalue
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

	//����
	auto itemBack = MenuItemFont::create(back, CC_CALLBACK_1(AuthorizeScene::backFunc, this));
	itemBack->setPosition(Wsize.width - 100, 100);
	itemBack->setScale(1.5);

	//�˳�
	auto exitItem = MenuItemFont::create (exit, CC_CALLBACK_1 (AuthorizeScene::menuCloseCallback, this));
	exitItem->setPosition (100, 100);
	exitItem->setScale (1.5, 1.6);

	//QQ��Ȩ
	//auto qqItem = MenuItemImage::create("authQQ.png", "authQQ.png", CC_CALLBACK_1(AuthorizeScene::Auth_QQ, this));
	auto qqItem = MenuItemFont::create (submit, CC_CALLBACK_1 (AuthorizeScene::Auth_QQ, this));
	qqItem->setPosition(Wsize.width/2 - 150, Wsize.height - 200);
	qqItem->setScale(1.5, 1.6);

	//ȡ��QQ��Ȩ
	//auto qqCanItem = MenuItemImage::create("authCan.png", "authCan.png", CC_CALLBACK_1(AuthorizeScene::Auth_QQCancel, this));
	auto qqCanItem = MenuItemFont::create (rank, CC_CALLBACK_1 (AuthorizeScene::Auth_QQCancel, this));
	qqCanItem->setPosition(Wsize.width/2 + 150, qqItem->getPositionY());
	qqCanItem->setScale(1.5, 1.6);

	//΢����Ȩ
	//auto wcItem = MenuItemImage::create("authWC.png", "authWC.png", CC_CALLBACK_1(AuthorizeScene::Auth_WC, this));
	auto wcItem = MenuItemFont::create (unlock, CC_CALLBACK_1 (AuthorizeScene::Auth_WC, this));
	wcItem->setPosition(qqItem->getPositionX(), qqItem->getPositionY() - dis);
	wcItem->setScale(1.5, 1.6);

	//ȡ��΢����Ȩ
	//auto wcCanItem = MenuItemImage::create("authCan.png", "authCan.png", CC_CALLBACK_1(AuthorizeScene::Auth_WCCancel, this));
	auto wcCanItem = MenuItemFont::create (ach, CC_CALLBACK_1 (AuthorizeScene::Auth_WCCancel, this));
	wcCanItem->setPosition(Wsize.width/2 + 150, wcItem->getPositionY());
	wcCanItem->setScale(1.5, 1.6);

	//������Ȩ
	//auto sinaItem = MenuItemImage::create("authSina.png", "authSina.png", CC_CALLBACK_1(AuthorizeScene::Auth_SINA, this));
	auto sinaItem = MenuItemFont::create (login, CC_CALLBACK_1 (AuthorizeScene::Auth_SINA, this));
	sinaItem->setPosition(wcItem->getPositionX(), wcItem->getPositionY()-dis);
	sinaItem->setScale(1.5, 1.6);

	//ȡ��������Ȩ
	//auto sinaCanItem = MenuItemImage::create("authCan.png", "authCan.png", CC_CALLBACK_1(AuthorizeScene::Auth_SINACancel, this));
	auto sinaCanItem = MenuItemFont::create (logout, CC_CALLBACK_1 (AuthorizeScene::Auth_SINACancel, this));
	sinaCanItem->setPosition(Wsize.width/2 + 150, sinaItem->getPositionY());
	sinaCanItem->setScale(1.5, 1.6);

	//facebook��Ȩ
	//auto facebookItem = MenuItemImage::create("authface.png", "authface.png", CC_CALLBACK_1(AuthorizeScene::Auth_FACEBOOK, this));
	auto facebookItem = MenuItemFont::create (switchb, CC_CALLBACK_1 (AuthorizeScene::Auth_FACEBOOK, this));
	facebookItem->setPosition(sinaItem->getPositionX(), sinaItem->getPositionY()-dis);
	facebookItem->setScale(1.5, 1.6);
	
	//ȡ��facebook��Ȩ
	//auto facebookCanItem = MenuItemImage::create("authCan.png", "authCan.png", CC_CALLBACK_1(AuthorizeScene::Auth_FACEBOOKCancel, this));
	auto facebookCanItem = MenuItemFont::create (platform, CC_CALLBACK_1 (AuthorizeScene::Auth_FACEBOOKCancel, this));
	facebookCanItem->setPosition(Wsize.width/2+150, facebookItem->getPositionY());
	facebookCanItem->setScale(1.5, 1.6);

	//twitter��Ȩ
	//auto twitterItem = MenuItemImage::create("authTwitter.png", "authTwitter.png", CC_CALLBACK_1(AuthorizeScene::Auth_Twitter, this));
	auto twitterItem = MenuItemFont::create (ppause, CC_CALLBACK_1 (AuthorizeScene::Auth_Twitter, this));
	twitterItem->setPosition(facebookItem->getPositionX(), facebookItem->getPositionY()-dis);
	twitterItem->setScale(1.5, 1.6);
	
	//ȡ��twitter��Ȩ
	//auto twitterCanItem = MenuItemImage::create("authCan.png", "authCan.png", CC_CALLBACK_1(AuthorizeScene::Auth_TwitterCancel, this));
	auto twitterCanItem = MenuItemFont::create (pexit, CC_CALLBACK_1 (AuthorizeScene::Auth_TwitterCancel, this));
	twitterCanItem->setPosition(Wsize.width/2+150, twitterItem->getPositionY());
	twitterCanItem->setScale(1.5, 1.6);

	//��ʾ��ť
	auto showBarItem = MenuItemFont::create (showBar, CC_CALLBACK_1 (AuthorizeScene::Auth_ShowBar, this));
	showBarItem->setPosition (twitterItem->getPositionX (), twitterItem->getPositionY () - dis);
	showBarItem->setScale (1.5, 1.6);

	//���ذ�ť
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
*QQ��Ȩ����ȡ��
*/
void AuthorizeScene::Auth_QQ(Ref* pSender) {
	log("Auth_QQ");

	//����-//�ύ���������а� ID��score Ϊ����ֵ��
	Social::getInstance ()->submitScore ("my", 100);
};
void AuthorizeScene::Auth_QQCancel(Ref* pSender) {
	log("Auth_QQCancel");
	
	//����-//��ȡ���а�(leaderboardID Ϊ���а� ID)
	Social::getInstance ()->showLeaderboard ("my");
};

/*
*΢����Ȩ����ȡ��
*/
void AuthorizeScene::Auth_WC(Ref* pSender) {
	log("Auth_WC");

	//����-	//�����ɾͰ�(achInfo Ϊ�����Ϣ��TAchievementInfo Ϊ std::map ����)
	TAchievementInfo info;
	info ["rank"] = "my";
	Social::getInstance ()->unlockAchievement (info);
}

void AuthorizeScene::Auth_WCCancel(Ref* pSender) {
	log("Auth_WCCancel");

	//����-//��ʾ�ɾͰ�
	Social::getInstance ()->showAchievements ();
};

/*
*������Ȩ����ȡ��
*/
void AuthorizeScene::Auth_SINA(Ref* pSender) {
	log("Auth_SINA");

	//���Ե�½
	PluginChannel::getInstance ()->login ();
};

void AuthorizeScene::Auth_SINACancel(Ref* pSender) {
	log("Auth_SINACancel");

	//���Եǳ�
	PluginChannel::getInstance ()->logout ();
};

/*
*facebook��Ȩ����ȡ��
*/
void AuthorizeScene::Auth_FACEBOOK(Ref* pSender) {
	log("Auth_FACEBOOK");

	//�����л��˺�
	PluginChannel::getInstance ()->accountSwitch ();
};

void AuthorizeScene::Auth_FACEBOOKCancel(Ref* pSender) {
	log("Auth_FACEBOOKCancel");

	//������������
	PluginChannel::getInstance ()->enterPlatform ();
};

/*
*Twitter��Ȩ����ȡ��
*/
void AuthorizeScene::Auth_Twitter(Ref* pSender) {
	log("Auth_Twitter");

	//������ͣ�������
	PluginChannel::getInstance ()->pause ();
};

void AuthorizeScene::Auth_TwitterCancel(Ref* pSender) {
	log("Auth_TwitterCancel");

	//�����˳��������
	PluginChannel::getInstance ()->Exit ();
};

/*
*��ť��ʾ������
*/
void AuthorizeScene::Auth_ShowBar (Ref* pSender) {
	log ("Auth_ShowBar");

	//��ʾ����������
	//PluginChannel::getInstance ()->showToolBar ();
};

void AuthorizeScene::Auth_HideBar (Ref* pSender) {
	log ("Auth_HideBar");

	//��������������
	//PluginChannel::getInstance ()->hideToolBar ();
};

void AuthorizeScene::menuCloseCallback (Ref* pSender) {
	Director::getInstance ()->end ();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit (0);
#endif
}

