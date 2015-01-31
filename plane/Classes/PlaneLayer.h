#ifndef __PLANELAYER_H__
#define __PLANELAYER_H__
#include"cocos2d.h"
using namespace cocos2d;
class PlaneLayer:public Layer
{
private:
	Sprite* plane;
public:
	PlaneLayer();
	~PlaneLayer();
	virtual bool init();
	static PlaneLayer * create();//创建函数
	static PlaneLayer * sharedPlane;//提高静态全局指针
	bool isAlive;
	//飞机触摸移动
	void MoveTo(Vec2 location);
	void PlayerBlowup(Sprite* plane);
	void PlayerAnimation();
	void removePlane(Node* pTarget,void* data);
	Sprite* getPlayerPlane();
	Rect getBoundingBox();//获取飞机大小
	//添加跳字
	void addJumpWord1(Vec2 point);
	void word1Finished(Node *pSender);
	void addJumpWord2(Vec2 point);
	void word2Finished(Node *pSender);
};
#endif