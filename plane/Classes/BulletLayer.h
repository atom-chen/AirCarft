#ifndef __BULLETLAYER_H__
#define __BULLETLAYER_H__	
#include"cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;//很多人少了这一步导致找不到SimpleAudioEngine
using namespace cocos2d;
class BulletLayer:public Layer
{
private:
	SpriteBatchNode * bulletBatchNode;
	int m_bulletSoundId;
public:
	__Array * m_pAllBullet;
public:
	BulletLayer();
	~BulletLayer();

	virtual bool init();
	CREATE_FUNC(BulletLayer);
	//添加子弹
	void  AddBullet(float dt);
	//开始子弹
	void StartShoot(float delay=1.0);
	//停止发射
	void StopShoot();//卸载任务执行器
	//子弹飞出屏幕后销毁
	void bulletMoveFinished(Node *pSender);
	//删除某个子弹
	void RemoveBullet(Sprite * bullet);

};
#endif