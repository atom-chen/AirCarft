#ifndef __UFOLAYER_H__
#define __UFOLAYER_H__	
#include"cocos2d.h"
using namespace cocos2d;
class UFOLayer:public Layer
{
public:
	__Array * m_pAllMutiBullets;
	__Array * m_pAllBigBoomItem;
public:
	UFOLayer();
	~UFOLayer();
	virtual bool init();
	CREATE_FUNC(UFOLayer);
	//添加多子弹道具
	void AddMutiBullets(float dt);
	//添加大炸弹
	void AddBigBoomItem(float dt);
	//道具移除屏幕回收
	void mutiBulletsMoveFinished(Node *pSender);
	void bigBoomItemMoveFinished(Node *pSender);
	//道具移除接口 玩家吃到道具使用
	void RemoveMutiBullets(Sprite * mutiBullets);
	void RemoveBigBoomItem(Sprite * bigBoomItems);
	void createUFOZidanAnimation();//添加子弹动画到缓存
	void createUFOAnheiAnimation();//添加暗黑动画到缓存
};
#endif