#pragma once

/*
�罻ϵͳ 
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

	//�罻ϵͳ
	void setListener ();

	//�ύ���������а� ID��score Ϊ����ֵ��
	void submitScore (const char* leaderboardID, long score);
	//��ȡ���а�(leaderboardID Ϊ���а� ID)
	void showLeaderboard (const char* leaderboardID);
	//�����ɾͰ�(achInfo Ϊ�����Ϣ��TAchievementInfo Ϊ std::map ����)
	void unlockAchievement (TAchievementInfo achInfo);
	//��ʾ�ɾͰ�
	void showAchievements ();

	//�罻�ص�����
	virtual void onSocialResult (SocialRetCode ret, const char* msg);
};

#endif // !__SOCIAL_H__


