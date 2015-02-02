#include "NumberScroll.h"
bool NumberScroll::init()
{
	if (!Node::init() )
	{
		return false;
	}
	visibleNode=Node::create();
	//    创建0-9的数字
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
		//     将数字加入visibleNode节点中
		visibleNode->addChild(single);
	}
	this->addChild(visibleNode);
	return true;    
}
void NumberScroll::onEnter() {
	//    启动遮罩效果
	glEnable(GL_SCISSOR_TEST);
	Vec2 pos = Vec2::ZERO;
	//    获取visibleNode节点屏幕绝对位置
	pos = visibleNode->getParent()->convertToWorldSpace(pos);
	Rect rect = Rect(pos.x, pos.y, 27, 27);
	//    设置遮罩效果
	glScissor(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
	Node::visit();
	//    关闭遮罩效果
	glDisable(GL_SCISSOR_TEST);
}
void NumberScroll::setNumber(int var)
{
	//    停止本节点的所有动作
	this->stopAllActions();
	//    移动到到节点坐标
	Vec2 moveToPosition = Vec2(visibleNode->getPosition().x,-var*27);
	//    创建动作移动到该节点
	MoveTo* moveAction = MoveTo::create(var *1.0, moveToPosition);
	//    运行该动作
	visibleNode->runAction(moveAction);  
}