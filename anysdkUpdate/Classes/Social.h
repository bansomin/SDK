#pragma once

/*
社交系统 
*/

#ifndef __SOCIAL_H__
#define __SOCIAL_H__

#include "../proj.android-studio/app/protocols_gnustl_static/include/AgentManager.h"
using namespace anysdk::framework;

class Social :public SocialListener {

private:
	Social ();
	~Social ();
	static Social* _pInstance;

public:
	static Social* getInstance ();
	void purge ();

	//社交系统
	void setListener ();

	//提交分数（排行榜 ID，score 为分数值）
	void submitScore (const char* leaderboardID, long score);
	//获取排行榜(leaderboardID 为排行榜 ID)
	void showLeaderboard (const char* leaderboardID);
	//解锁成就榜(achInfo 为相关信息，TAchievementInfo 为 std::map 类型)
	void unlockAchievement (TAchievementInfo achInfo);
	//显示成就榜
	void showAchievements ();

	//社交回调函数
	virtual void onSocialResult (SocialRetCode ret, const char* msg);
};

#endif // !__SOCIAL_H__


