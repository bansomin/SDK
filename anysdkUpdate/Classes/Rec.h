/*
¼�����ܵ�ʵ��
*/

#ifndef __REC_H__
#define __REC_H__

#include "../proj.android-studio/app/protocols_gnustl_static/include/AgentManager.h"
using namespace anysdk::framework;

//����ϵͳ���ڻص���Ϣ����Ҫ���ü���
class Rec : public RECResultListener {

private:
	Rec ();
	~Rec ();
	static Rec* _pInstance;
	ProtocolREC * _recPlugin;

public:
	static Rec* getInstance ();
	void purge ();
	void setListener ();

	//¼���Ƿ����
	bool isAvailable (); 
	//¼��״̬
	bool isRecording ();
	//��ʼ¼��
	void startRecording ();
	//����¼��
	void stopRecording ();
	//����¼�� 
	void share (); 
	//��ͣ¼��
	void pauseRecording ();
	//�ָ�¼��
	void resumeRecording ();
	//��ʾ������
	void showToolBar ();
	//���ع�����
	void hideToolBar (); 
	//��ʾ��Ƶ����
	void showVideoCenter ();
	//������Ƶ����
	void enterPlatform ();
	//����
	void setMetaData ();

	bool isFunctionSupported (string strClassName);
	virtual void onRECResult (RECResultCode ret, const char* msg);

};

#endif

