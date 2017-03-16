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

//社交系统
void Social::setListener () {
	
	if (AgentManager::getInstance()->getSocialPlugin()) {
		AgentManager::getInstance ()->getSocialPlugin ()->setListener (this);
	}
};

//提交分数（排行榜 ID，score 为分数值）
void Social::submitScore (const char* leaderboardID, long score) {

	if (AgentManager::getInstance ()->getSocialPlugin ()) {
		AgentManager::getInstance ()->getSocialPlugin ()->submitScore (leaderboardID, score);
	}
};

//获取排行榜(leaderboardID 为排行榜 ID)
void Social::showLeaderboard (const char* leaderboardID) {

	if (AgentManager::getInstance ()->getSocialPlugin ()) {
		AgentManager::getInstance ()->getSocialPlugin ()->showLeaderboard (leaderboardID);
	}
};

//解锁成就榜(achInfo 为相关信息，TAchievementInfo 为 std::map 类型)
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

//社交回调函数
void Social::onSocialResult (SocialRetCode ret, const char* msg) {

	switch (ret) {
		case kScoreSubmitSucceed:		//提交分数成功
			break;
		case kScoreSubmitfail:			//提交分数失败
			break;
		case kAchUnlockSucceed:			//解锁成功
			break;
		case kAchUnlockFail:			//解锁失败
			break;
		default:
			break;
	}
};
