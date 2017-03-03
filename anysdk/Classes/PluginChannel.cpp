#include "PluginChannel.h"

#define  LOG_TAG    "PluginChannel"


PluginChannel::PluginChannel() {

	_pluginsIAPMap = NULL;
};

PluginChannel::~PluginChannel() {

};

static AllProductsInfo _myProducts;
PluginChannel* PluginChannel::_pInstance = NULL;
PluginChannel* PluginChannel::getInstance() {

	if (_pInstance==NULL){
		_pInstance = new PluginChannel();
	}
	return _pInstance;
};

void PluginChannel::purge() {

	if (_pInstance){
		delete _pInstance;
		_pInstance = NULL;
	}
};

//载入插件，同时进行插件的初始化
void PluginChannel::loadPlugins() {

	/*
	oauthLoginServer 参数是游戏服务提供的用来做登陆验证转发的接口地址，
	在此处配置的接口地址仅用于 SIM SDK 测试模式下（即直接运行母包时）
	做登录时框架请求的地址，而在正式打出渠道包的时候会被替换成相应渠道在打包工具中配置的地址参数。
	*/

	//获取AgentManager
	AgentManager* agent = AgentManager::getInstance();
	string appKey = "29B94BAF-75C2-D3AE-5312-855745BF875F";
	string appSecret = "775c733fd4b5081730261764f81c1279";
	string privateKey = "60EC380452AF707B706704BDD1E4551C";
	string oauthLoginServer = "http://pre.im/pghJ";
	agent->init(appKey, appSecret, privateKey, oauthLoginServer);

#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
	//使用框架中代理类进行插件初始化
	//Android建议在onCreate里调用PluginWrapper.loadAllPlugins();来进行插件初始化
	agent->loadALLPlugin();
#endif
	//对用户系统设置监听类
	if (agent->getUserPlugin()) {
		agent->getUserPlugin()->setActionListener(this);
	}

	//对支付系统设置监听类
	printf("Load plugins invoked\n");
	_pluginsIAPMap = AgentManager::getInstance()->getIAPPlugin();
	std::map<std::string, ProtocolIAP*>::iterator iter;
	for(iter = _pluginsIAPMap->begin(); iter!=_pluginsIAPMap->end(); iter++) {
		(iter->second)->setResultListener(this);
	}

	_iapAppstore = getIAPAppstore();
};

ProtocolIAP* PluginChannel::getIAPAppstore() {
	if(_pluginsIAPMap) {
		std::map<std::string, ProtocolIAP*>::iterator it = _pluginsIAPMap->begin();
		for(; it!=_pluginsIAPMap->end(); it++) {
			printf("it->first: %s----\n", it->first.c_str());
			if(it->first==APPSTORE_PLUGIN_ID) {
				return it->second;
			}
		}
	}
	return NULL;
}

//卸载插件
void PluginChannel::unloadPlugins() {

	printf("Unload plugins invoked\n");
	AgentManager::getInstance()->unloadAllPlugins();
};

//用户系统功能
//当前插件id
std::string PluginChannel::getPluginId() {

	if(AgentManager::getInstance()->getUserPlugin()) {
		return AgentManager::getInstance()->getUserPlugin()->getPluginId();
	}
	return "";
};

//登陆
void PluginChannel::login() {

	if(AgentManager::getInstance()->getUserPlugin()) {
		AgentManager::getInstance()->getUserPlugin()->login();
	}
};

//登出
void PluginChannel::logout() {

	if(AgentManager::getInstance()->getUserPlugin()) {
		if(isFunctionSupported("logout")) {
			AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("logout", NULL);
		}
	}
};

//该方法是否支持:(login、getUserId为默认，可无需判断)
bool PluginChannel::isFunctionSupported(string strClassName) {

	if(AgentManager::getInstance()->getUserPlugin()) {
		return AgentManager::getInstance()->getUserPlugin()->isFunctionSupported(strClassName);
	}
	return false;
};

//获取用户唯一标识符，进行游戏端登陆
std::string PluginChannel::getUserId() {

	if(AgentManager::getInstance()->getUserPlugin()) {
		return AgentManager::getInstance()->getUserPlugin()->getUserID();
	}
	return "";
};

//进入渠道用户中心
void PluginChannel::enterPlatform() {

	//使用isFunctionSupported可先判断该插件是否支持该功能
	if(AgentManager::getInstance()->getUserPlugin()) {
		if(isFunctionSupported("enterPlatform")) {
			AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("enterPlatform", NULL);
		}
	}
};

//显示悬浮按钮
void PluginChannel::showToolBar(ToolBarPlace place) {

	//使用isFunctionSupported可先判断该插件是否支持该功能
	if(AgentManager::getInstance()->getUserPlugin()) {
		if(isFunctionSupported("showToolBar")) {
			AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("showToolBar", NULL);
		}
	}
};

//隐藏悬浮按钮
void PluginChannel::hideToolBar() {

	//使用isFunctionSupported可先判断该插件是否支持该功能
	if(AgentManager::getInstance()->getUserPlugin()) {
		if(isFunctionSupported("hideToolBar")) {
			AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("hideToolBar", NULL);
		}
	}
};

//渠道退出界面调用
void PluginChannel::Exit() {

	//使用isFunctionSupported可先判断该插件是否支持该功能
	if(AgentManager::getInstance()->getUserPlugin()) {
		if(isFunctionSupported("exit")) {
			AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("exit", NULL);
		}
	}
};

//sdk退出
void PluginChannel::destroy() {

	//使用isFunctionSupported可先判断该插件是否支持该功能
	if(AgentManager::getInstance()->getUserPlugin()) {
		if(isFunctionSupported("destroy")) {
			AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("destroy", NULL);
		}
	}
};

//渠道暂停界面调用
void PluginChannel::pause() {

	//使用isFunctionSupported可先判断该插件是否支持该功能
	if(AgentManager::getInstance()->getUserPlugin()) {
		if(isFunctionSupported("pause")) {
			AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("pause", NULL);
		}
	}
};

//切换账号
void PluginChannel::accountSwitch() {

	if(AgentManager::getInstance()->getUserPlugin()) {
		if(isFunctionSupported("accountSwitch")) {
			AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("accountSwitch", NULL);
		}
	}
};

//用户实名注册(360特有函数)
void PluginChannel::realNameRegister() {

	if(AgentManager::getInstance()->getUserPlugin()) {
		if(isFunctionSupported("realNameRegister")) {
			AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("realNameRegister", NULL);
		}
	}
};

//防沉迷(360特有函数)
void PluginChannel::antiAddictionQuery() {

	//使用isFunctionSupported可先判断该插件是否支持该功能
	if(AgentManager::getInstance()->getUserPlugin()) {
		if(isFunctionSupported("antiAddictionQuery")) {
			AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("antiAddictionQuery", NULL);
		}
	}
};

//UC提交角色信息(UC特有函数)
void PluginChannel::submitLoginGameRole() {

};

//支付系统功能
void PluginChannel::pay() {

};

void PluginChannel::requestProducts() {

	// AppStroe才有的接口，也可以不调用requestProducts直接调用payForProduct 
	if(NULL != _iapAppstore) {
		PluginParam param1("PD_10005");
		PluginParam param2("PD_10004");
		PluginParam param3("PD_10003");
		_iapAppstore->callFuncWithParam("", &param1, &param2, &param3, NULL);
	}
	else {
		printf("iap iphone isn't find!\n");
	}
};

void PluginChannel::resetPayState() {
	ProtocolIAP::resetPayState();
	pay();
};

//支付回调函数
void PluginChannel::onPayResult(PayResultCode ret, const char* msg, TProductInfo info) {

	string temp = "fail";
	switch(ret) {
		case kPaySuccess://支付成功回调
			temp = "Success";
			//CCMessageBox(temp.c_str(), temp.c_str());
			break;
		case kPayFail://支付失败回调
			//CCMessageBox(temp.c_str(), temp.c_str());
			break;
		case kPayCancel://支付取消回调
			//CCMessageBox(temp.c_str(), "Cancel");
			break;
		case kPayNetworkError://支付超时回调
			//CCMessageBox(temp.c_str(), "NetworkError");
			break;
		case kPayProductionInforIncomplete://支付超时回调
			//CCMessageBox(temp.c_str(), "ProductionInforIncomplete");
			break;
			/**
			* 新增加:正在进行中回调
			* 支付过程中若SDK没有回调结果，就认为支付正在进行中
			* 游戏开发商可让玩家去判断是否需要等待，若不等待则进行下一次的支付
			*/
		case kPayNowPaying:
			//ShowTipDialog();
			break;
		default:
			break;
	}
};

//支付，商品请求回调函数
void PluginChannel::onRequestResult(RequestResultCode ret, const char* msg, AllProductsInfo info) {

	_myProducts = info;
};

//登陆回调函数
void PluginChannel::onActionResult(ProtocolUser* pPlugin, UserActionResultCode code, const char* msg) {

};

void PluginChannel::payMode(std::string id) {

};

//获取渠道id
std::string PluginChannel::getChannelId() {

	return AgentManager::getInstance()->getChannelId();
};

//
const char* PluginChannel::getResourceId(std::string name) {

	return "3";
};

void PluginChannel::ChoosePayMode(std::vector<std::string>& pluginId) {

};

//void CCMessageBox(const char* content, const char* title) {
//
//}