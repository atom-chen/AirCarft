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

	//m_bulletSoundId = SimpleAudioEngine::getInstance()->playEffect("sound/bullet.wav",false);//��ʼ���ű�����Ч��false��ʾ��ѭ�� 

	//�����ӵ�λ��
	Vec2 planePosition = PlaneLayer::sharedPlane->getChildByTag(1)->getPosition();
	Vec2 bulletPositon = Vec2(planePosition.x,planePosition.y+PlaneLayer::sharedPlane->getChildByTag(1)->getContentSize().height/2);
	bullet->setPosition(bulletPositon);
	//�����ӵ�����Ч��
	float length = Director::getInstance()->getWinSize().height+bullet->getContentSize().height/2-bulletPositon.y;//���о��� ������Ļ����
	float velocity = 2500/1;//�����ٶ�
	float realMoveDuration = length/velocity;//����ʱ��
	//����MoveTo���� �ӵ����е���Ļ���� FiniteTimeAction���޴ζ���ִ���� ��Ϊ˲ʱ��������ʱ����
	FiniteTimeAction * actionMove = MoveTo::create(realMoveDuration,Vec2(bulletPositon.x,Director::getInstance()->getWinSize().height+bullet->getContentSize().height/2));
	FiniteTimeAction * actionDone = CallFuncN::create(this,callfuncN_selector(BulletLayer::bulletMoveFinished));
	Sequence *sequence = Sequence::create(actionMove,actionDone,NULL);//Sequence����˳��ִ�ж���
	bullet->runAction(sequence);
	
	this->m_pAllBullet->addObject(bullet);
	
}
void BulletLayer::bulletMoveFinished(Node *pSender)
{
	Sprite *bullet = (Sprite*)pSender;
	this->m_pAllBullet->removeObject(bullet);//�Ƴ�__Array
	this->bulletBatchNode->removeChild(bullet,true);//�Ƴ���Ļ
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
	//SimpleAudioEngine::getInstance()->pauseAllEffects();//��ͣȫ����Ч
	SimpleAudioEngine::getInstance()->stopEffect(m_bulletSoundId);//ֹͣ��Ч������ѡ�񵥶�ͣ��һ����Ч�����ֵ����playEffect���ص�
	//ж������ִ����
	this->unschedule(schedule_selector(BulletLayer::AddBullet));
}
//ɾ���ӵ� �ӵ��͵л���ײ��ʱ�����
void BulletLayer::RemoveBullet(Sprite *bullet)
{
	if(bullet != NULL)
	{
		this->m_pAllBullet->removeObject(bullet);
		this->bulletBatchNode->removeChild(bullet,true);
	}
}