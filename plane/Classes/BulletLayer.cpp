#include "BulletLayer.h"
#include "PlaneLayer.h"
#include "GameData.h"
BulletLayer::BulletLayer()
{
	m_pAllBullet = __Array::create();
	m_pAllBullet->retain();
	//
}
BulletLayer::~BulletLayer()
{
	m_pAllBullet->release();
	m_pAllBullet = NULL;
}
bool BulletLayer::init()
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
void BulletLayer::AddBullet(float dt)
{
	

	Sprite *bullet = Sprite::createWithSpriteFrameName("zidan1.png");
	bulletBatchNode->addChild(bullet);

	//m_bulletSoundId = SimpleAudioEngine::getInstance()->playEffect("sound/bullet.wav",false);//开始播放背景音效，false表示不循环 

	//设置子弹位置
	Vec2 planePosition = PlaneLayer::sharedPlane->getChildByTag(1)->getPosition();
	Vec2 bulletPositon = Vec2(planePosition.x,planePosition.y+PlaneLayer::sharedPlane->getChildByTag(1)->getContentSize().height/2);
	bullet->setPosition(bulletPositon);
	//设置子弹飞行效果
	float length = Director::getInstance()->getWinSize().height+bullet->getContentSize().height/2-bulletPositon.y;//飞行距离 超过屏幕结束
	float velocity = 2500/1;//飞行速度
	float realMoveDuration = length/velocity;//飞行时间
	//调用MoveTo动画 子弹运行到屏幕结束 FiniteTimeAction有限次动作执行类 分为瞬时动作和延时动作
	FiniteTimeAction * actionMove = MoveTo::create(realMoveDuration,Vec2(bulletPositon.x,Director::getInstance()->getWinSize().height+bullet->getContentSize().height/2));
	FiniteTimeAction * actionDone = CallFuncN::create(this,callfuncN_selector(BulletLayer::bulletMoveFinished));
	Sequence *sequence = Sequence::create(actionMove,actionDone,NULL);//Sequence按照顺序执行动作
	bullet->runAction(sequence);
	
	this->m_pAllBullet->addObject(bullet);
	
}
void BulletLayer::bulletMoveFinished(Node *pSender)
{
	Sprite *bullet = (Sprite*)pSender;
	this->m_pAllBullet->removeObject(bullet);//移除__Array
	this->bulletBatchNode->removeChild(bullet,true);//移除屏幕
}
void BulletLayer::StartShoot(float delay)
{
	//SimpleAudioEngine::getInstance()->
	if (GameData::Inst()->isEffectOpen) {
        m_bulletSoundId = SimpleAudioEngine::getInstance()->playEffect("sound/bullet.wav",true);
    }
	//this->schedule(schedule_selector(BulletLayer::AddBullet),0.08f,kCCRepeatForever,delay);
    schedule(SEL_SCHEDULE(&BulletLayer::AddBullet), 0.08f,kRepeatForever, delay);
}
void BulletLayer::StopShoot()
{
	//SimpleAudioEngine::getInstance()->pauseAllEffects();//暂停全部音效
	SimpleAudioEngine::getInstance()->stopEffect(m_bulletSoundId);//停止音效，可以选择单独停掉一个音效，这个值是由playEffect返回的
	//卸载任务执行器
	this->unschedule(schedule_selector(BulletLayer::AddBullet));
}
//删除子弹 子弹和敌机碰撞的时候调用
void BulletLayer::RemoveBullet(Sprite *bullet)
{
	if(bullet != NULL)
	{
		this->m_pAllBullet->removeObject(bullet);
		this->bulletBatchNode->removeChild(bullet,true);
	}
}