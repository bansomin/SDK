/*
��湦�ܵ�ʵ��
*/

#ifndef __ADS_H__
#define __ADS_H__

#include "../proj.android-studio/app/protocols_gnustl_static/include/AgentManager.h"
using namespace anysdk::framework;

//����ϵͳ���ڻص���Ϣ����Ҫ���ü���
class Ads : public AdsListener{

private:
	Ads ();
	~Ads ();
	static Ads* _pInstance;
	ProtocolAds* _adsPlugin;

public:
	static Ads* getInstance ();
	void purge ();
	//���ϵͳ
	void setListener ();
	//���ϵͳ���� 
	void preloadAds (AdsType type, int idx=1);
	//���ϵͳչʾ
	void showAds (AdsType type, int idx=1);
	//���ϵͳ����
	void hideAds (AdsType type, int idx=1);
	//���ص�����
	virtual void onAdsResult (AdsResultCode ret, const char* msg);
	
	//��ѯ����
	float queryPoints ();
	//���ѻ���
	void spendPoints (float points);
};

#endif
