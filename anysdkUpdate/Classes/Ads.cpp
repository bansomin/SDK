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

//���ϵͳ
void Ads::setListener () {

	if (_adsPlugin) {
		_adsPlugin->setAdsListener (this);
	}
};

//���ϵͳ���� 
void Ads::preloadAds (AdsType type, int idx) {

	//ͨ������Ҫ��ʾ�Ĺ�����ͣ���ʾ��Ӧ�Ĺ��
	//Banner ���ʹ����Ļ��һС���ֿռ��������û�ͨ�������ø��ḻ��ȫ������
	if (_adsPlugin) {
		if (_adsPlugin->isAdTypeSupported (type)) {
			_adsPlugin->preloadAds (type, idx);
		}
	}
};

//���ϵͳչʾ
void Ads::showAds (AdsType type, int idx) {

	if (_adsPlugin) {
		if (_adsPlugin->isAdTypeSupported (type)) {
			_adsPlugin->showAds (type, idx);
		}
	}
};

//���ϵͳ����
void Ads::hideAds (AdsType type, int idx) {

	if (_adsPlugin) {
		if (_adsPlugin->isAdTypeSupported (type)) {
			_adsPlugin->hideAds (type, idx);
		}
	}
};

//���ص�����
void Ads::onAdsResult (AdsResultCode ret, const char* msg) {

	switch (ret) {
		case kAdsReceived:			//�����ܳɹ��ص�
			break;
		case kAdsShown:				//���չʾ�ص�	
			break;
		case kAdsDismissed:			//�����ʧ�ص�	
			break;
		case kPointsSpendSucceed:	//�������óɹ��ص�	 
			break;
		case kPointsSpendFailed:	//��������ʧ�ܻص� 
			break;
		case kNetworkError:			//�������ص�	  
			break;
		case kUnknownError:			//δ֪����ص�	  
			break;
		case kOfferWallOnPointsChanged://���ָı�ص�
			break;
		default:
			break;
	}

};

//��ѯ����
float Ads::queryPoints () {

	if (_adsPlugin) {
		return _adsPlugin->queryPoints ();
	}
	return 0.0f;
};

//���ѻ���
void Ads::spendPoints (float points) {

	if (_adsPlugin) {
		_adsPlugin->spendPoints (points);
	}
};
