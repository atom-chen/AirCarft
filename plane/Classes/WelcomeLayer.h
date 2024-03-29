#ifndef _WELCOMELAYER_H_
#define _WELCOMELAYER_H_	
#include "MainScene.h"
#include "GameSpeed.h"
#include "GameoverLayer.h"
#include "DBUtil.h"
#include "setLayer.h"
#include "SimpleAudioEngine.h"
#include"cocos2d.h"

using namespace cocos2d;

class WelcomeLayer:public Layer
{
private:
	Sprite *plane;
	Sprite *plane1;
	Sprite *plane2;
	UserVO *userVo;
public:
	virtual bool init();
	static Scene *scene();
	CREATE_FUNC(WelcomeLayer);
	bool isHaveSaveFile();
	void  getHighestHistorySorce();
	void copyLoading();
	void playGame(Ref *obj);
	void playGame2(Ref *obj);
	void changeScene(Node *pSender);
	void menuSetCallback(Ref* pSender);
	void menuExitCallback(Ref* pSender);
	void menuShareCallback(Ref* pSender);
};
#endif