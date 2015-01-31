#include"MutiBullets.h"
#include"PlaneLayer.h"
//���캯��
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
	//�����ӵ�λ�� �ӵ�λ��Ϊ˫��
	Vec2 planePosition = PlaneLayer::sharedPlane->getChildByTag(1)->getPosition();
	//λ�������ڷɻ�����
	Vec2 bulletPositon = Vec2(planePosition.x-46,planePosition.y+PlaneLayer::sharedPlane->getChildByTag(1)->getContentSize().height/2-14);
	Vec2 bulletPositon2 = Vec2(planePosition.x+46,planePosition.y+PlaneLayer::sharedPlane->getChildByTag(1)->getContentSize().height/2-14);
	bullet->setPosition(bulletPositon);
	bullet2->setPosition(bulletPositon2);
	//�����ӵ�����Ч��
	float length = Director::getInstance()->getWinSize().height+bullet->getContentSize().height/2-bulletPositon.y;//���о��� ������Ļ����
	float velocity = 2200/1;//�����ٶ� �ȵ����ӵ�2000�ӿ�
	float realMoveDuration = length/velocity;//����ʱ��
	//����MoveTo���� �ӵ����е���Ļ���� FiniteTimeAction���޴ζ���ִ���� ��Ϊ˲ʱ��������ʱ����
	FiniteTimeAction * actionMove = MoveTo::create(realMoveDuration,Vec2(bulletPositon.x,Director::getInstance()->getWinSize().height+bullet->getContentSize().height/2));
	FiniteTimeAction * actionDone = CallFuncN::create(this,callfuncN_selector(MutiBullets::bulletMoveFinished));
	Sequence *sequence = Sequence::create(actionMove,actionDone,NULL);//Sequence����˳��ִ�ж���
	//����MoveTo���� �ӵ����е���Ļ���� FiniteTimeAction���޴ζ���ִ���� ��Ϊ˲ʱ��������ʱ����
	FiniteTimeAction * actionMove2 = MoveTo::create(realMoveDuration,Vec2(bulletPositon2.x,Director::getInstance()->getWinSize().height+bullet2->getContentSize().height/2));
	FiniteTimeAction * actionDone2 = CallFuncN::create(this,callfuncN_selector(MutiBullets::bulletMoveFinished));
	Sequence *sequence2 = Sequence::create(actionMove2,actionDone2,NULL);//Sequence����˳��ִ�ж���

	//˫���ӵ�ִ����ͬ����
	bullet->runAction(sequence);
	bullet2->runAction(sequence2);
	this->m_pAllBullet->addObject(bullet);
	this->m_pAllBullet->addObject(bullet2);
}
void MutiBullets::bulletMoveFinished(Node *pSender)
{
	Sprite *bullet = (Sprite*)pSender;
	this->m_pAllBullet->removeObject(bullet);//�Ƴ�__Array
	this->bulletBatchNode->removeChild(bullet,true);//�Ƴ���Ļ
}
void MutiBullets::StartShoot(float delay)
{
	//˫���ӵ�����ʹ��kCCRepeatForever ����ʱ������
	this->schedule(schedule_selector(MutiBullets::AddBullet),0.06f,100,delay);
}
void MutiBullets::StopShoot()
{
	//ж������ִ����
	this->unschedule(schedule_selector(MutiBullets::AddBullet));
}
//ɾ���ӵ� �ӵ��͵л���ײ��ʱ�����
void MutiBullets::RemoveBullet(Sprite *bullet)
{
	if(bullet != NULL)
	{
		this->m_pAllBullet->removeObject(bullet);
		this->bulletBatchNode->removeChild(bullet,true);
	}
}