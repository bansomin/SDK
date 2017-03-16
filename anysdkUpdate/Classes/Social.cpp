#include "Social.h"

Social::Social () {

	setListener ();
};

Social::~Social () {

};

Social* Social::_pInstance = NULL;	 
Social* Social::getInstance () {

	if (_pInstance == NULL) {	 		
		_pInstance = new Social ();
		_pInstance->setListener ();
	}
	return _pInstance;
};

void Social::purge () {

	if (_pInstance) {
		delete _pInstance;
		_pInstance = NULL;
	}
};

//�罻ϵͳ
void Social::setListener () {
	
	if (AgentManager::getInstance()->getSocialPlugin()) {
		AgentManager::getInstance ()->getSocialPlugin ()->setListener (this);
	}
};

//�ύ���������а� ID��score Ϊ����ֵ��
void Social::submitScore (const char* leaderboardID, long score) {

	if (AgentManager::getInstance ()->getSocialPlugin ()) {
		AgentManager::getInstance ()->getSocialPlugin ()->submitScore (leaderboardID, score);
	}
};

//��ȡ���а�(leaderboardID Ϊ���а� ID)
void Social::showLeaderboard (const char* leaderboardID) {

	if (AgentManager::getInstance ()->getSocialPlugin ()) {
		AgentManager::getInstance ()->getSocialPlugin ()->showLeaderboard (leaderboardID);
	}
};

//�����ɾͰ�(achInfo Ϊ�����Ϣ��TAchievementInfo Ϊ std::map ����)
void Social::unlockAchievement (TAchievementInfo achInfo) {

	if (AgentManager::getInstance ()->getSocialPlugin ()) {

		/*TAchievementInfo info;
		info ["rank"] = "friend";*/
		AgentManager::getInstance ()->getSocialPlugin ()->unlockAchievement (achInfo);
	}
};

void Social::showAchievements (){

	if (AgentManager::getInstance ()->getSocialPlugin ()) {
		AgentManager::getInstance ()->getSocialPlugin ()->showAchievements ();
	}
};

//�罻�ص�����
void Social::onSocialResult (SocialRetCode ret, const char* msg) {

	switch (ret) {
		case kScoreSubmitSucceed:		//�ύ�����ɹ�
			break;
		case kScoreSubmitfail:			//�ύ����ʧ��
			break;
		case kAchUnlockSucceed:			//�����ɹ�
			break;
		case kAchUnlockFail:			//����ʧ��
			break;
		default:
			break;
	}
};
