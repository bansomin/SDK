/*************************BEGIN**************************************************** 
    			Created by HAO on 2017/1/23
    BRIEF	: 	
    VERSION	: 
    HISTORY	:
***************************END****************************************************/

#pragma once

#ifndef __PLUGINCHANNEL_HHH
#define __PLUGINCHANNEL_HHH

#include "../../../../proj.android/protocols/include/AgentManager.h"
using namespace anysdk::framework;
using namespace std;

#define APPSTORE_PLUGIN_ID "92"

class PluginChannel :public PayResultListener, public UserActionListener {

	public:
	static PluginChannel* getInstance();
	static void purge();

	//��������ͬʱ���в���ĳ�ʼ��
	void loadPlugins();

	//ж�ز��
	void unloadPlugins();

	//�û�ϵͳ����
	//��ǰ���id
	std::string getPluginId();

	//�÷����Ƿ�֧��:(login��getUserIdΪĬ�ϣ��������ж�)
	bool isFunctionSupported(string strClassName);

	//��½
	void login();

	//�ǳ�
	void logout();


	//��ȡ�û�Ψһ��ʶ����������Ϸ�˵�½
	std::string getUserId();


	//���������û�����
	void enterPlatform();

	//��ʾ������ť
	void showToolBar(ToolBarPlace place);

	//����������ť
	void hideToolBar();

	//�����˳��������
	void Exit();

	//sdk�˳�
	void destroy();

	//������ͣ�������
	void pause();

	//�л��˺�
	void accountSwitch();

	//�û�ʵ��ע��(360���к���)
	void realNameRegister();

	//������(360���к���)
	void antiAddictionQuery();
	//UC�ύ��ɫ��Ϣ(UC���к���)
	void submitLoginGameRole();

	//֧��ϵͳ����
	void pay();
	void requestProducts();
	void resetPayState();

	//֧���ص�����
	virtual void onPayResult(PayResultCode ret, const char* msg, TProductInfo info);

	//֧������Ʒ����ص�����
	virtual void onRequestResult(RequestResultCode ret, const char* msg, AllProductsInfo info);

	//��½�ص�����
	virtual void onActionResult(ProtocolUser* pPlugin, UserActionResultCode code, const char* msg);

	void payMode(std::string id);

	//��ȡ����id
	std::string getChannelId();

	//
	const char* getResourceId(std::string name);
	void ChoosePayMode(std::vector<std::string>& pluginId);

	private:
	PluginChannel();
	virtual ~PluginChannel();

	static PluginChannel* _pInstance;
	std::map<std::string, std::string> productInfo;
	std::map<std::string, ProtocolIAP*>* _pluginsIAPMap;

	ProtocolIAP* getIAPAppstore();
	ProtocolIAP* _iapAppstore;

};

#endif	//__PLUGINCHANNEL_HHH