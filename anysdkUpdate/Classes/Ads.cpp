#include "Ads.h"

Ads::Ads () {

};

Ads::~Ads () {

};

Ads* Ads::_pInstance = NULL;

Ads* Ads::getInstance () {

	if (_pInstance == NULL) {
		_pInstance = new Ads ();
		_pInstance->_adsPlugin = AgentManager::getInstance ()->getAdsPlugin ();
		_pInstance->setListener ();
	}
};

void Ads::purge () {

	if (_pInstance) {
		delete _pInstance;
		_pInstance = NULL;
	}
};

//广告系统
void Ads::setListener () {

	if (_adsPlugin) {
		_adsPlugin->setAdsListener (this);
	}
};

//广告系统加载 
void Ads::preloadAds (AdsType type, int idx) {

	//通过传递要显示的广告类型，显示相应的广告
	//Banner 广告使用屏幕的一小部分空间来吸引用户通过点击获得更丰富的全屏体验
	if (_adsPlugin) {
		if (_adsPlugin->isAdTypeSupported (type)) {
			_adsPlugin->preloadAds (type, idx);
		}
	}
};

//广告系统展示
void Ads::showAds (AdsType type, int idx) {

	if (_adsPlugin) {
		if (_adsPlugin->isAdTypeSupported (type)) {
			_adsPlugin->showAds (type, idx);
		}
	}
};

//广告系统隐藏
void Ads::hideAds (AdsType type, int idx) {

	if (_adsPlugin) {
		if (_adsPlugin->isAdTypeSupported (type)) {
			_adsPlugin->hideAds (type, idx);
		}
	}
};

//广告回调函数
void Ads::onAdsResult (AdsResultCode ret, const char* msg) {

	switch (ret) {
		case kAdsReceived:			//广告接受成功回调
			break;
		case kAdsShown:				//广告展示回调	
			break;
		case kAdsDismissed:			//广告消失回调	
			break;
		case kPointsSpendSucceed:	//积分设置成功回调	 
			break;
		case kPointsSpendFailed:	//积分设置失败回调 
			break;
		case kNetworkError:			//网络错误回调	  
			break;
		case kUnknownError:			//未知错误回调	  
			break;
		case kOfferWallOnPointsChanged://积分改变回调
			break;
		default:
			break;
	}

};

//查询积分
float Ads::queryPoints () {

	if (_adsPlugin) {
		return _adsPlugin->queryPoints ();
	}
	return 0.0f;
};

//消费积分
void Ads::spendPoints (float points) {

	if (_adsPlugin) {
		_adsPlugin->spendPoints (points);
	}
};
