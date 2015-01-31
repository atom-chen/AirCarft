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
	//����ӵ�
	void  AddBullet(float dt);
	//��ʼ�ӵ�
	void StartShoot(float delay=1.0);
	//ֹͣ����
	void StopShoot();//ж������ִ����
	//�ӵ��ɳ���Ļ������
	void bulletMoveFinished(Node *pSender);
	//ɾ��ĳ���ӵ�
	void RemoveBullet(Sprite * bullet);

};
#endif