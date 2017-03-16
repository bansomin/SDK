#include "HelloWorldScene.h"

#include "ShareScene.h"
#include "AuthorizeScene.h"
#include "InformationScene.h"

#include "PluginChannel.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	Size Wsize = Director::getInstance ()->getWinSize ();

	auto bg = Sprite::create("bg.png");
	bg->setPosition(Wsize.width/2, Wsize.height/2);
	this->addChild(bg);

	//汉字乱码解决方案
	//创建字典类实例，将xml加载到字典中
	auto* chnString = Dictionary::createWithContentsOfFile ("fonts/myString.xml");
	//通过xml文件中的key获取value
	const char* user = ((String*) chnString->objectForKey("user"))->getCString();
	const char* shareSys = ((String*) chnString->objectForKey ("shareSys"))->getCString ();
	const char* adsSys = ((String*) chnString->objectForKey ("adsSys"))->getCString ();
	const char* recSys = ((String*) chnString->objectForKey ("recSys"))->getCString ();
	const char* exit = ((String*) chnString->objectForKey ("exit"))->getCString ();

	//退出
	auto exitItem = MenuItemFont::create (exit, CC_CALLBACK_1 (HelloWorld::menuCloseCallback, this));
	exitItem->setPosition (100, 100);
	exitItem->setScale (1.5, 1.6);

	//授权
	//auto authorizeItem = MenuItemImage::create("auth.png", "auth.png", CC_CALLBACK_1(HelloWorld::authorizeFunc, this));
	auto authorizeItem = MenuItemFont::create (user, CC_CALLBACK_1(HelloWorld::authorizeFunc, this));
	authorizeItem->setPosition(Wsize.width/2, Wsize.height - 200);
	authorizeItem->setScale(1.5, 1.6);

	//分享
	//auto shareItem = MenuItemImage::create("share.png", "share.png", CC_CALLBACK_1(HelloWorld::shareFunc, this));
	auto shareItem = MenuItemFont::create (shareSys, CC_CALLBACK_1 (HelloWorld::shareFunc, this));
	shareItem->setPosition(authorizeItem->getPositionX(), authorizeItem->getPositionY() - 300);
	shareItem->setScale(1.5, 1.6);

	//获取信息
	//auto infoItem = MenuItemImage::create("info.png", "info.png", CC_CALLBACK_1(HelloWorld::informationFunc, this));
	auto infoItem = MenuItemFont::create (adsSys, CC_CALLBACK_1 (HelloWorld::informationFunc, this));
	infoItem->setPosition(shareItem->getPositionX(), shareItem->getPositionY()-300);
	infoItem->setScale(1.5, 1.6);
	 
	//新增
	//录屏系统
	auto recItem = MenuItemFont::create (recSys, CC_CALLBACK_1 (HelloWorld::recFunc, this));
	recItem->setPosition (infoItem->getPositionX (), infoItem->getPositionY () - 300);
	recItem->setScale (1.5, 1.6);

    auto menu = Menu::create(exitItem, authorizeItem, shareItem, infoItem, recItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

	//初始化sdk
	PluginChannel::getInstance ()->loadPlugins ();

    return true;
}

void HelloWorld::authorizeFunc(Ref* pSender) {
	log("authorizeFunc");

	Director::getInstance()->replaceScene(TransitionFade::create(1, AuthorizeScene::createScene()));
}

void HelloWorld::shareFunc(Ref* pSender) {
	log("shareFunc");

	Director::getInstance()->replaceScene(TransitionFade::create(1, ShareScene::createScene()));
}

void HelloWorld::informationFunc(Ref* pSender) {
	log("information");

	Director::getInstance()->replaceScene(TransitionFade::create(1, InformationScene::createScene()));
}

void HelloWorld::recFunc (Ref* pSender) {
	log ("recfunc");

	Director::getInstance ()->replaceScene (TransitionFade::create (1, ShareScene::createScene ()));
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
