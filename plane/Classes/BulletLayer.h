#ifndef __BULLETLAYER_H__
#define __BULLETLAYER_H__	
#include"cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;//�ܶ���������һ�������Ҳ���SimpleAudioEngine
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