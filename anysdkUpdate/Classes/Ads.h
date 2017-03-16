/*
广告功能的实现
*/

#ifndef __ADS_H__
#define __ADS_H__

#include "../proj.android-studio/app/protocols_gnustl_static/include/AgentManager.h"
using namespace anysdk::framework;

//分享系统存在回调信息，需要设置监听
class Ads : public AdsListener{

private:
	Ads ();
	~Ads ();
	static Ads* _pInstance;
	ProtocolAds* _adsPlugin;

public:
	static Ads* getInstance ();
	void purge ();
	//广告系统
	void setListener ();
	//广告系统加载 
	void preloadAds (AdsType type, int idx=1);
	//广告系统展示
	void showAds (AdsType type, int idx=1);
	//广告系统隐藏
	void hideAds (AdsType type, int idx=1);
	//广告回调函数
	virtual void onAdsResult (AdsResultCode ret, const char* msg);
	
	//查询积分
	float queryPoints ();
	//消费积分
	void spendPoints (float points);
};

#endif
