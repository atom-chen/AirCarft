#include "NumberScroll.h"
bool NumberScroll::init()
{
	if (!Node::init() )
	{
		return false;
	}
	visibleNode=Node::create();
	//    ����0-9������
	for(int i=0;i<10;i++){
		char str[2];
		str[0] = '0' + i;
		str[1] = '\0';

		//        char buf[100];
		Sprite* spTmp = Sprite::create("number.png");

		Size sz = spTmp->getContentSize();
		auto single = LabelAtlas::create(str, "number.png", sz.width/10, sz.height, '1');
		//CCLabelTTF* single = CCLabelTTF::create(str, "", 27);
		single->setTag(i);
		single->setAnchorPoint(Vec2(0, 0));
		single->setPosition(Vec2(0, 27 * i));
		//     �����ּ���visibleNode�ڵ���
		visibleNode->addChild(single);
	}
	this->addChild(visibleNode);
	return true;    
}
void NumberScroll::onEnter() {
	//    ��������Ч��
	glEnable(GL_SCISSOR_TEST);
	Vec2 pos = Vec2::ZERO;
	//    ��ȡvisibleNode�ڵ���Ļ����λ��
	pos = visibleNode->getParent()->convertToWorldSpace(pos);
	Rect rect = Rect(pos.x, pos.y, 27, 27);
	//    ��������Ч��
	glScissor(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
	Node::visit();
	//    �ر�����Ч��
	glDisable(GL_SCISSOR_TEST);
}
void NumberScroll::setNumber(int var)
{
	//    ֹͣ���ڵ�����ж���
	this->stopAllActions();
	//    �ƶ������ڵ�����
	Vec2 moveToPosition = Vec2(visibleNode->getPosition().x,-var*27);
	//    ���������ƶ����ýڵ�
	MoveTo* moveAction = MoveTo::create(var *1.0, moveToPosition);
	//    ���иö���
	visibleNode->runAction(moveAction);  
}