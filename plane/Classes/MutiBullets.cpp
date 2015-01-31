#include"MutiBullets.h"
#include"PlaneLayer.h"
//构造函数
MutiBullets::MutiBullets()
{
	m_pAllBullet = __Array::create();
	m_pAllBullet->retain();
	//
}
MutiBullets::~MutiBullets()
{
	m_pAllBullet->release();
	m_pAllBullet = NULL;
}
bool MutiBullets::init()
{
	if(!Layer::init())
	{
		return false;
	}
	Texture2D *texture = Director::getInstance()->getTextureCache()->getTextureForKey("shoot.png");
	bulletBatchNode = SpriteBatchNode::createWithTexture(texture);
	this->addChild(bulletBatchNode);

	return true;
}
void MutiBullets::AddBullet(float dt)
{
	Sprite *bullet = Sprite::createWithSpriteFrameName("zidan2.png");
	Sprite *bullet2 = Sprite::createWithSpriteFrameName("zidan2.png");
	bulletBatchNode->addChild(bullet);
	bulletBatchNode->addChild(bullet2);
	//设置子弹位置 子弹位置为双排
	Vec2 planePosition = PlaneLayer::sharedPlane->getChildByTag(1)->getPosition();
	//位置设置在飞机两侧
	Vec2 bulletPositon = Vec2(planePosition.x-46,planePosition.y+PlaneLayer::sharedPlane->getChildByTag(1)->getContentSize().height/2-14);
	Vec2 bulletPositon2 = Vec2(planePosition.x+46,planePosition.y+PlaneLayer::sharedPlane->getChildByTag(1)->getContentSize().height/2-14);
	bullet->setPosition(bulletPositon);
	bullet2->setPosition(bulletPositon2);
	//设置子弹飞行效果
	float length = Director::getInstance()->getWinSize().height+bullet->getContentSize().height/2-bulletPositon.y;//飞行距离 超过屏幕结束
	float velocity = 2200/1;//飞行速度 比单排子弹2000加快
	float realMoveDuration = length/velocity;//飞行时间
	//调用MoveTo动画 子弹运行到屏幕结束 FiniteTimeAction有限次动作执行类 分为瞬时动作和延时动作
	FiniteTimeAction * actionMove = MoveTo::create(realMoveDuration,Vec2(bulletPositon.x,Director::getInstance()->getWinSize().height+bullet->getContentSize().height/2));
	FiniteTimeAction * actionDone = CallFuncN::create(this,callfuncN_selector(MutiBullets::bulletMoveFinished));
	Sequence *sequence = Sequence::create(actionMove,actionDone,NULL);//Sequence按照顺序执行动作
	//调用MoveTo动画 子弹运行到屏幕结束 FiniteTimeAction有限次动作执行类 分为瞬时动作和延时动作
	FiniteTimeAction * actionMove2 = MoveTo::create(realMoveDuration,Vec2(bulletPositon2.x,Director::getInstance()->getWinSize().height+bullet2->getContentSize().height/2));
	FiniteTimeAction * actionDone2 = CallFuncN::create(this,callfuncN_selector(MutiBullets::bulletMoveFinished));
	Sequence *sequence2 = Sequence::create(actionMove2,actionDone2,NULL);//Sequence按照顺序执行动作

	//双排子弹执行相同动作
	bullet->runAction(sequence);
	bullet2->runAction(sequence2);
	this->m_pAllBullet->addObject(bullet);
	this->m_pAllBullet->addObject(bullet2);
}
void MutiBullets::bulletMoveFinished(Node *pSender)
{
	Sprite *bullet = (Sprite*)pSender;
	this->m_pAllBullet->removeObject(bullet);//移除__Array
	this->bulletBatchNode->removeChild(bullet,true);//移除屏幕
}
void MutiBullets::StartShoot(float delay)
{
	//双排子弹不能使用kCCRepeatForever 加上时间限制
	this->schedule(schedule_selector(MutiBullets::AddBullet),0.06f,100,delay);
}
void MutiBullets::StopShoot()
{
	//卸载任务执行器
	this->unschedule(schedule_selector(MutiBullets::AddBullet));
}
//删除子弹 子弹和敌机碰撞的时候调用
void MutiBullets::RemoveBullet(Sprite *bullet)
{
	if(bullet != NULL)
	{
		this->m_pAllBullet->removeObject(bullet);
		this->bulletBatchNode->removeChild(bullet,true);
	}
}