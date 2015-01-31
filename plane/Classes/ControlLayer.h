#ifndef __CONTROLLAYER_H__
#define __CONTROLLAYER_H__	
#include"cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;//很多人少了这一步导致找不到SimpleAudioEngine
using namespace cocos2d;
static 	int	SCORE_LAYER_ITEM=5;
class ControlLayer:public Layer
{
private:
    MenuItemToggle *pPauseItem;
    MenuItem *m_btnPauseOpen;
    MenuItem *m_btnPauseClose;
	LabelAtlas   *lableScore;

public:
	virtual bool init();
	CREATE_FUNC(ControlLayer);
	void menuPauseCallback(Ref* pSender);//暂定按钮回调
	void updateScore(int score); //更新分数显示
};
#endif