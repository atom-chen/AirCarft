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
	//��Ӷ��ӵ�����
	void AddMutiBullets(float dt);
	//��Ӵ�ը��
	void AddBigBoomItem(float dt);
	//�����Ƴ���Ļ����
	void mutiBulletsMoveFinished(Node *pSender);
	void bigBoomItemMoveFinished(Node *pSender);
	//�����Ƴ��ӿ� ��ҳԵ�����ʹ��
	void RemoveMutiBullets(Sprite * mutiBullets);
	void RemoveBigBoomItem(Sprite * bigBoomItems);
	void createUFOZidanAnimation();//����ӵ�����������
	void createUFOAnheiAnimation();//��Ӱ��ڶ���������
};
#endif