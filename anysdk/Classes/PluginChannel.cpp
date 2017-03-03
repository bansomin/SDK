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

//��������ͬʱ���в���ĳ�ʼ��
void PluginChannel::loadPlugins() {

	/*
	oauthLoginServer ��������Ϸ�����ṩ����������½��֤ת���Ľӿڵ�ַ��
	�ڴ˴����õĽӿڵ�ַ������ SIM SDK ����ģʽ�£���ֱ������ĸ��ʱ��
	����¼ʱ�������ĵ�ַ��������ʽ�����������ʱ��ᱻ�滻����Ӧ�����ڴ�����������õĵ�ַ������
	*/

	//��ȡAgentManager
	AgentManager* agent = AgentManager::getInstance();
	string appKey = "29B94BAF-75C2-D3AE-5312-855745BF875F";
	string appSecret = "775c733fd4b5081730261764f81c1279";
	string privateKey = "60EC380452AF707B706704BDD1E4551C";
	string oauthLoginServer = "http://pre.im/pghJ";
	agent->init(appKey, appSecret, privateKey, oauthLoginServer);

#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
	//ʹ�ÿ���д�������в����ʼ��
	//Android������onCreate�����PluginWrapper.loadAllPlugins();�����в����ʼ��
	agent->loadALLPlugin();
#endif
	//���û�ϵͳ���ü�����
	if (agent->getUserPlugin()) {
		agent->getUserPlugin()->setActionListener(this);
	}

	//��֧��ϵͳ���ü�����
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

//ж�ز��
void PluginChannel::unloadPlugins() {

	printf("Unload plugins invoked\n");
	AgentManager::getInstance()->unloadAllPlugins();
};

//�û�ϵͳ����
//��ǰ���id
std::string PluginChannel::getPluginId() {

	if(AgentManager::getInstance()->getUserPlugin()) {
		return AgentManager::getInstance()->getUserPlugin()->getPluginId();
	}
	return "";
};

//��½
void PluginChannel::login() {

	if(AgentManager::getInstance()->getUserPlugin()) {
		AgentManager::getInstance()->getUserPlugin()->login();
	}
};

//�ǳ�
void PluginChannel::logout() {

	if(AgentManager::getInstance()->getUserPlugin()) {
		if(isFunctionSupported("logout")) {
			AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("logout", NULL);
		}
	}
};

//�÷����Ƿ�֧��:(login��getUserIdΪĬ�ϣ��������ж�)
bool PluginChannel::isFunctionSupported(string strClassName) {

	if(AgentManager::getInstance()->getUserPlugin()) {
		return AgentManager::getInstance()->getUserPlugin()->isFunctionSupported(strClassName);
	}
	return false;
};

//��ȡ�û�Ψһ��ʶ����������Ϸ�˵�½
std::string PluginChannel::getUserId() {

	if(AgentManager::getInstance()->getUserPlugin()) {
		return AgentManager::getInstance()->getUserPlugin()->getUserID();
	}
	return "";
};

//���������û�����
void PluginChannel::enterPlatform() {

	//ʹ��isFunctionSupported�����жϸò���Ƿ�֧�ָù���
	if(AgentManager::getInstance()->getUserPlugin()) {
		if(isFunctionSupported("enterPlatform")) {
			AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("enterPlatform", NULL);
		}
	}
};

//��ʾ������ť
void PluginChannel::showToolBar(ToolBarPlace place) {

	//ʹ��isFunctionSupported�����жϸò���Ƿ�֧�ָù���
	if(AgentManager::getInstance()->getUserPlugin()) {
		if(isFunctionSupported("showToolBar")) {
			AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("showToolBar", NULL);
		}
	}
};

//����������ť
void PluginChannel::hideToolBar() {

	//ʹ��isFunctionSupported�����жϸò���Ƿ�֧�ָù���
	if(AgentManager::getInstance()->getUserPlugin()) {
		if(isFunctionSupported("hideToolBar")) {
			AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("hideToolBar", NULL);
		}
	}
};

//�����˳��������
void PluginChannel::Exit() {

	//ʹ��isFunctionSupported�����жϸò���Ƿ�֧�ָù���
	if(AgentManager::getInstance()->getUserPlugin()) {
		if(isFunctionSupported("exit")) {
			AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("exit", NULL);
		}
	}
};

//sdk�˳�
void PluginChannel::destroy() {

	//ʹ��isFunctionSupported�����жϸò���Ƿ�֧�ָù���
	if(AgentManager::getInstance()->getUserPlugin()) {
		if(isFunctionSupported("destroy")) {
			AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("destroy", NULL);
		}
	}
};

//������ͣ�������
void PluginChannel::pause() {

	//ʹ��isFunctionSupported�����жϸò���Ƿ�֧�ָù���
	if(AgentManager::getInstance()->getUserPlugin()) {
		if(isFunctionSupported("pause")) {
			AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("pause", NULL);
		}
	}
};

//�л��˺�
void PluginChannel::accountSwitch() {

	if(AgentManager::getInstance()->getUserPlugin()) {
		if(isFunctionSupported("accountSwitch")) {
			AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("accountSwitch", NULL);
		}
	}
};

//�û�ʵ��ע��(360���к���)
void PluginChannel::realNameRegister() {

	if(AgentManager::getInstance()->getUserPlugin()) {
		if(isFunctionSupported("realNameRegister")) {
			AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("realNameRegister", NULL);
		}
	}
};

//������(360���к���)
void PluginChannel::antiAddictionQuery() {

	//ʹ��isFunctionSupported�����жϸò���Ƿ�֧�ָù���
	if(AgentManager::getInstance()->getUserPlugin()) {
		if(isFunctionSupported("antiAddictionQuery")) {
			AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("antiAddictionQuery", NULL);
		}
	}
};

//UC�ύ��ɫ��Ϣ(UC���к���)
void PluginChannel::submitLoginGameRole() {

};

//֧��ϵͳ����
void PluginChannel::pay() {

};

void PluginChannel::requestProducts() {

	// AppStroe���еĽӿڣ�Ҳ���Բ�����requestProductsֱ�ӵ���payForProduct 
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

//֧���ص�����
void PluginChannel::onPayResult(PayResultCode ret, const char* msg, TProductInfo info) {

	string temp = "fail";
	switch(ret) {
		case kPaySuccess://֧���ɹ��ص�
			temp = "Success";
			//CCMessageBox(temp.c_str(), temp.c_str());
			break;
		case kPayFail://֧��ʧ�ܻص�
			//CCMessageBox(temp.c_str(), temp.c_str());
			break;
		case kPayCancel://֧��ȡ���ص�
			//CCMessageBox(temp.c_str(), "Cancel");
			break;
		case kPayNetworkError://֧����ʱ�ص�
			//CCMessageBox(temp.c_str(), "NetworkError");
			break;
		case kPayProductionInforIncomplete://֧����ʱ�ص�
			//CCMessageBox(temp.c_str(), "ProductionInforIncomplete");
			break;
			/**
			* ������:���ڽ����лص�
			* ֧����������SDKû�лص����������Ϊ֧�����ڽ�����
			* ��Ϸ�����̿������ȥ�ж��Ƿ���Ҫ�ȴ��������ȴ��������һ�ε�֧��
			*/
		case kPayNowPaying:
			//ShowTipDialog();
			break;
		default:
			break;
	}
};

//֧������Ʒ����ص�����
void PluginChannel::onRequestResult(RequestResultCode ret, const char* msg, AllProductsInfo info) {

	_myProducts = info;
};

//��½�ص�����
void PluginChannel::onActionResult(ProtocolUser* pPlugin, UserActionResultCode code, const char* msg) {

};

void PluginChannel::payMode(std::string id) {

};

//��ȡ����id
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