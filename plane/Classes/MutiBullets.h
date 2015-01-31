#ifndef __MUTIBULLETS_H__
#define __MUTIBULLETS_H__	
#include"cocos2d.h"
using namespace cocos2d;
class MutiBullets:public Layer
{
private:
	SpriteBatchNode * bulletBatchNode;
public:
	__Array * m_pAllBullet;
public:
	MutiBullets();
	~MutiBullets();

	virtual bool init();
	CREATE_FUNC(MutiBullets);
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