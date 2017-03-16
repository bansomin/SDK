#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	//��Ȩ
	void authorizeFunc(Ref* pSender);
	//����
	void shareFunc(Ref* pSender);
	//��ȡ��Ϣ
	void informationFunc(Ref* pSender);
	//¼��ϵͳ
	void recFunc (Ref* pSender);

};

#endif // __HELLOWORLD_SCENE_H__
