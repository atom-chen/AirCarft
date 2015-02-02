#include"GameSpeed.h"
#include "GameData.h"
bool GameSpeed::playEffect = true;
bool GameSpeed::playbgtmusic = true;
bool GameSpeed::init()
{
	if(!Layer::init())
	{
		return false;
	}
	buttetFlag = true;
	bigBoomCount = 0;
    playerScore  = 0;
    curtime      = 0;
    distance     = 0;
    miniDistance =10;
    flySpeed     =1;
    
    GameData::Inst()->gameMode = GameMode::SPEED;
    GameData::Inst()->resetSpeed();
	GameScene * gameLayer = GameScene::create();
	this->addChild(gameLayer);

	controlLayer = ControlLayer::create();
	this->addChild(controlLayer);

	planeLayer = PlaneLayer::create();
	this->addChild(planeLayer);

	bulletLayer = BulletLayer::create();
	this->addChild(bulletLayer);

	enemyLayer = EnemyLayer::create();
	this->addChild(enemyLayer);

	mutibullets=MutiBullets::create();
	this->addChild(mutibullets);

	ufoLayer = UFOLayer::create();
	this->addChild(ufoLayer);

	this->GameStart();
	this->scheduleUpdate();

    //设置触摸事件监听
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(GameSpeed::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameSpeed::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameSpeed::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    //记录时间
    schedule(schedule_selector(GameSpeed::GameTime),1.0);
    return true;
}
Scene* GameSpeed::scene()
{
    Scene* scene = NULL;

    scene  = Scene::create();

    GameSpeed* layer = GameSpeed::create();
    scene->addChild(layer);
    return scene;
}
void GameSpeed::GameTime(float dt)
{
    curtime = curtime+1;
    if (curtime>10 && curtime<=20) {
        miniDistance = 12;
        GameData::Inst()->minSpeed=4;
        GameData::Inst()->maxSpeed=9;
        GameData::Inst()->min3Speed=14;
        GameData::Inst()->max3Speed=24;
        GameData::Inst()->bgSpeed = 2;
    }else if (curtime>20 && curtime<=30)
    {
         miniDistance = 14;
        GameData::Inst()->minSpeed=3;
        GameData::Inst()->maxSpeed=8;
        GameData::Inst()->min3Speed=13;
        GameData::Inst()->max3Speed=23;
        GameData::Inst()->bgSpeed = 3;
    }else if (curtime>30 && curtime<=40)
    {
        miniDistance = 16;
        GameData::Inst()->minSpeed=3;
        GameData::Inst()->maxSpeed=7;
        GameData::Inst()->min3Speed=12;
        GameData::Inst()->max3Speed=22;
        GameData::Inst()->bgSpeed = 4;
    }else if (curtime>40 && curtime<=50)
    {
        miniDistance = 18;
        GameData::Inst()->minSpeed=3;
        GameData::Inst()->maxSpeed=6;
        GameData::Inst()->min3Speed=11;
        GameData::Inst()->max3Speed=21;
        GameData::Inst()->bgSpeed = 4;
    }else if (curtime>50 && curtime<=60)
    {
        miniDistance = 20;
        GameData::Inst()->minSpeed=2;
        GameData::Inst()->maxSpeed=5;
        GameData::Inst()->min3Speed=10;
        GameData::Inst()->max3Speed=20;
        GameData::Inst()->bgSpeed = 5;
    }else if (curtime>60 && curtime<=70)
    {
        miniDistance = 22;
        GameData::Inst()->minSpeed=2;
        GameData::Inst()->maxSpeed=4;
        GameData::Inst()->min3Speed=9;
        GameData::Inst()->max3Speed=19;
        GameData::Inst()->bgSpeed = 6;
    }else if (curtime>70 && curtime<=80)
    {
        miniDistance = 22;
        GameData::Inst()->minSpeed=1;
        GameData::Inst()->maxSpeed=4;
        GameData::Inst()->min3Speed=8;
        GameData::Inst()->max3Speed=18;
        GameData::Inst()->bgSpeed = 7;
    }else if (curtime>80 && curtime<=90)
    {
        miniDistance = 24;
        GameData::Inst()->minSpeed=1;
        GameData::Inst()->maxSpeed=3;
        GameData::Inst()->min3Speed=8;
        GameData::Inst()->max3Speed=18;
        GameData::Inst()->bgSpeed = 8;
    }else if (curtime>100 && curtime<=110)
    {
        miniDistance = 24;
        GameData::Inst()->minSpeed=1;
        GameData::Inst()->maxSpeed=3;
        GameData::Inst()->min3Speed=8;
        GameData::Inst()->max3Speed=17;
        GameData::Inst()->bgSpeed = 9;
    }else if (curtime>110 && curtime<=120)
    {
        miniDistance = 26;
        GameData::Inst()->minSpeed=1;
        GameData::Inst()->maxSpeed=3;
        GameData::Inst()->min3Speed=8;
        GameData::Inst()->max3Speed=16;
        GameData::Inst()->bgSpeed = 10;
    }else if (curtime>120)
    {
        miniDistance = 28;
        GameData::Inst()->minSpeed=1;
        GameData::Inst()->maxSpeed=3;
        GameData::Inst()->min3Speed=6;
        GameData::Inst()->max3Speed=12;
        GameData::Inst()->bgSpeed = 11;
    }
    if (this->planeLayer->isAlive) {
        distance = distance + miniDistance;
        this->controlLayer->updateScore((int)distance);
    }
    
}


bool GameSpeed::onTouchBegan(Touch *pTouch,Event *pEvent)
{
    return true;
}
void GameSpeed::GameStart()
{
    bulletLayer->StartShoot(0.1f);
	this->schedule(schedule_selector(GameSpeed::produceGameItem),0.5f);
	this->schedule(schedule_selector(GameSpeed::isGameOver),8.0f);
	this->schedule(schedule_selector(GameSpeed::produceGameItem2),10.0f);
}
void GameSpeed::GameStop()
{
    unscheduleUpdate();
    
	bulletLayer->StopShoot();
    unschedule(SEL_SCHEDULE(&GameSpeed::GameTime));
	this->unschedule(schedule_selector(GameSpeed::produceGameItem));
	this->unschedule(schedule_selector(GameSpeed::produceGameItem2));
	this->unschedule(schedule_selector(GameSpeed::isGameOver));

}
void GameSpeed::isGameOver(float dt)
{
	if(this->planeLayer->isAlive && !Director::getInstance()->isPaused())
	{
		enemyLayer->addEnemy1(1);
	}
	else
	{
		GameOver();
	}
}
void GameSpeed::produceGameItem(float dt)
{
	if(this->planeLayer->isAlive && !Director::getInstance()->isPaused())
	{
		int max=1000,min=1;
		int flag = rand()%(max+1-min)+min;
		if (flag>0 && flag <=700)
		{
			enemyLayer->addEnemy1(1);
		}
		else if (flag>700 && flag <=900)
		{
			enemyLayer->addEnemy1(1);
		}
		else if (flag>900 && flag <=950)
		{
			enemyLayer->addEnemy1(1);
		}
		else
		{
			enemyLayer->addEnemy1(1);
		}
	}
}
void GameSpeed::produceGameItem2(float dt)
{
	if(this->planeLayer->isAlive && !Director::getInstance()->isPaused())
	{
		int max=100,min=1;
		int flag = rand()%(max+1-min)+min;
		if (flag>0 && flag <=50)
		{
			enemyLayer->addEnemy3(1);
		}
		else if (flag>60 && flag <=80)
		{
			ufoLayer->AddBigBoomItem(0.1f);
		
		}
		else
		{
			ufoLayer->AddMutiBullets(0.1f);
		}
	}
}
void GameSpeed::onTouchMoved(Touch *pTouch,Event *pEvent)
{
	if(this->planeLayer->isAlive && !Director::getInstance()->isPaused())
	{

		Point beginPoint = pTouch->getLocationInView();
		beginPoint = Director::getInstance()->convertToGL(beginPoint);

		Rect planeRect = this->planeLayer->getChildByTag(1)->boundingBox();
		planeRect.origin.x-=15;
		planeRect.origin.y-=15;
		planeRect.size.width+=30;
		planeRect.size.height+=30;
		if(planeRect.containsPoint(beginPoint))
		{
			Point endPoint = pTouch->getPreviousLocationInView();
			endPoint = Director::getInstance()->convertToGL(endPoint);
            Point offset = beginPoint-endPoint;//ccpSub(beginPoint,endPoint);
            Point toPoint = this->planeLayer->getChildByTag(1)->getPosition()+offset;//ccpAdd(this->planeLayer->getChildByTag(1)->getPosition(),offset);
			this->planeLayer->MoveTo(toPoint);
		}

	}
}
void GameSpeed::update(float dt)
{
	//playerAndEnemy();
	if (this->planeLayer->isAlive)
	{
		if (this->bulletLayer->m_pAllBullet != NULL)
		{
			 SingleBulletCrash();
		}
		
		if (this->mutibullets->m_pAllBullet != NULL)
		{
			
			MutiBulletCrash();
		}

		planeAndUFOCrash();
		planeAndUFOBoomCrash();
		playerAndEnemy();
		playerAndEnemy3();
	}
	
}
void GameSpeed::SingleBulletCrash()
{
	isBullet2AndEnemy();
	isBulletAndEnemy();
	isBullet3AndEnemy();
}
void GameSpeed::MutiBulletCrash()
{
	MutibulletAndEnemy();
	Mutibullet2AndEnemy();
	Mutibullet3AndEnemy();
}
void GameSpeed::playerAndEnemy()
{
	auto enemy1ToDelete = __Array::create();
	enemy1ToDelete->retain();
	Ref* et;

	CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy1,et)
	{
		Enemy* enemy1 = (Enemy*)et;
		if (enemy1->getBoundingBox().intersectsRect(this->planeLayer->getBoundingBox()))
		{
			enemy1ToDelete->addObject(enemy1);
			this->planeLayer->isAlive=false;
			this->bulletLayer->StopShoot();
			this->mutibullets->StopShoot();
			this->planeLayer->PlayerBlowup(PlaneLayer::sharedPlane->getPlayerPlane());
			//CCLOG("plane is bad");
			
			break;
		}
	}
	CCARRAY_FOREACH(enemy1ToDelete,et)
	{
		Enemy* enemy1=(Enemy*)et;
		this->enemyLayer->enemy1Blowup(enemy1);
	}
	enemy1ToDelete->release();
	

}
void GameSpeed::playerAndEnemy3()
{
	__Array* enemy1ToDelete = __Array::create();
	enemy1ToDelete->retain();
	Ref* et;
	CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy3,et)
	{
		Enemy* enemy1 = (Enemy*)et;

		if (enemy1->getBoundingBox().intersectsRect(this->planeLayer->getBoundingBox()))
		{
		
			enemy1ToDelete->addObject(enemy1);
			this->planeLayer->isAlive=false;
			this->bulletLayer->StopShoot();
			this->mutibullets->StopShoot();
			this->planeLayer->PlayerBlowup(PlaneLayer::sharedPlane->getPlayerPlane());
			//CCLOG("plane is bad");
			break;
			//this->removeChild(this->planeLayer);
		}
	}

	CCARRAY_FOREACH(enemy1ToDelete,et)
	{
		Enemy* enemy1=(Enemy*)et;
		this->enemyLayer->enemy3Blowup(enemy1);
	}
	enemy1ToDelete->release();


}
void GameSpeed::GameOver()
{
    if (GameData::Inst()->isEffectOpen) {
        SimpleAudioEngine::getInstance()->playEffect("sound/game_over.mp3",false);
    }

    GameStop();
    GameoverLayer* m_gameover=GameoverLayer::create((int)distance);
    m_gameover->setScale(0.1);
    auto scaleOne=ScaleTo::create(0.1f, 0.3f);
    auto scaleTwo=ScaleTo::create(0.1f, 0.6f);
    auto scaleThr=ScaleTo::create(0.1f, 0.8f);
    auto scaleFor=ScaleTo::create(0.1f, 1.0f);
    m_gameover->runAction(Sequence::create(scaleOne,scaleTwo,scaleThr,scaleFor, NULL));
    addChild(m_gameover,100);

}
void GameSpeed::isBulletAndEnemy()
{

	__Array* bulletToDelete=__Array::create();
	bulletToDelete->retain();
	Ref *bt,*et;

	CCARRAY_FOREACH(this->bulletLayer->m_pAllBullet,bt)
	{
		Sprite *bullte =(Sprite*)bt;
		__Array* enemy1ToDelete = __Array::create();
		enemy1ToDelete->retain();


		CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy1,et)
		{
			Enemy* enemy1 = (Enemy*)et;
	
			if (bullte->boundingBox().intersectsRect(enemy1->getBoundingBox()))
			{
				if (enemy1->getLife()>1)
				{
					enemy1->lostLife();
					bulletToDelete->addObject(bullte);
				}
				else if (enemy1->getLife()==1)
				{
                    if (GameData::Inst()->isEffectOpen) {
                        SimpleAudioEngine::getInstance()->playEffect("sound/enemy1_down.mp3",false);
                    }
					enemy1->lostLife();
					bulletToDelete->addObject(bullte);
					enemy1ToDelete->addObject(enemy1);

				}
				else;
				break;
			}
		}
		CCARRAY_FOREACH(enemy1ToDelete,et)
		{
			Enemy* enemy1=(Enemy*)et;
			this->enemyLayer->enemy1Blowup(enemy1);
		}
		enemy1ToDelete->release();

	}
	CCARRAY_FOREACH(bulletToDelete,bt)
	{
		Sprite* bullet =(Sprite*)bt;
		this->bulletLayer->RemoveBullet(bullet);
	}
	bulletToDelete->removeAllObjects();
	bulletToDelete->release();
}
void GameSpeed::isBullet2AndEnemy()
{

	__Array* bulletToDelete2=__Array::create();
	bulletToDelete2->retain();
	Ref *bt,*et;
	CCARRAY_FOREACH(this->bulletLayer->m_pAllBullet,bt)
	{
		Sprite *bullte =(Sprite*)bt;
		__Array* enemy2ToDelete = __Array::create();
		enemy2ToDelete->retain();

		CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy2,et)
		{
			Enemy* enemy2 = (Enemy*)et;
		
			if (bullte->boundingBox().intersectsRect(enemy2->getBoundingBox()))
			{
				if (enemy2->getLife()>1)
				{
					enemy2->lostLife();
					bulletToDelete2->addObject(bullte);
				}
				else if (enemy2->getLife()==1)
				{
					enemy2->lostLife();
					bulletToDelete2->addObject(bullte);
					enemy2ToDelete->addObject(enemy2);
					
					//playerScore += DIJI2_SCORE2;
					//this->controlLayer->updateScore(playerScore);
				}
				else;
				break;
			}
		}

		CCARRAY_FOREACH(enemy2ToDelete,et)
		{
			Enemy* enemy2=(Enemy*)et;
			this->enemyLayer->enemy2Blowup(enemy2);
		}
		enemy2ToDelete->release();
	}
	CCARRAY_FOREACH(bulletToDelete2,bt)
	{
		Sprite* bullet =(Sprite*)bt;
		this->bulletLayer->RemoveBullet(bullet);
	}
	bulletToDelete2->removeAllObjects();
	bulletToDelete2->release();
}
void GameSpeed::isBullet3AndEnemy()
{
	__Array* bulletToDelete=__Array::create();
	bulletToDelete->retain();
	Ref *bt,*et;
	CCARRAY_FOREACH(this->bulletLayer->m_pAllBullet,bt)
	{
		Sprite *bullte =(Sprite*)bt;
		__Array* enemy2ToDelete = __Array::create();
		enemy2ToDelete->retain();
		CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy3,et)
		{
			Enemy* enemy2 = (Enemy*)et;
			if (bullte->boundingBox().intersectsRect(enemy2->getBoundingBox()))
			{
				if (enemy2->getLife()>1)
				{
					enemy2->lostLife();
					bulletToDelete->addObject(bullte);
				}
				else if (enemy2->getLife()==1)
				{
                    if (GameData::Inst()->isEffectOpen) {
                        SimpleAudioEngine::getInstance()->playEffect("sound/enemy3_down.mp3",false);
                    }
					enemy2->lostLife();
					bulletToDelete->addObject(bullte);
					enemy2ToDelete->addObject(enemy2);
					//playerScore += DIJI3_SCORE2;
					//this->controlLayer->updateScore(playerScore);
				}
				else;
				break;
			}
		}
		CCARRAY_FOREACH(enemy2ToDelete,et)
		{
			Enemy* enemy2=(Enemy*)et;
			this->enemyLayer->enemy3Blowup(enemy2);
		}
		enemy2ToDelete->release();

	}
	CCARRAY_FOREACH(bulletToDelete,bt)
	{
		Sprite* bullet =(Sprite*)bt;
		this->bulletLayer->RemoveBullet(bullet);
	}
	bulletToDelete->removeAllObjects();
	bulletToDelete->release();
}

void GameSpeed::MutibulletAndEnemy()
{
	__Array* bulletToDelete=__Array::create();
	bulletToDelete->retain();
	Ref *bt,*et;
	CCARRAY_FOREACH(this->mutibullets->m_pAllBullet,bt)
	{
		Sprite *bullte =(Sprite*)bt;
		__Array* enemy1ToDelete = __Array::create();
		enemy1ToDelete->retain();

		CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy1,et)
		{
			Enemy* enemy1 = (Enemy*)et;
			if (bullte->boundingBox().intersectsRect(enemy1->getBoundingBox()))
			{
				if (enemy1->getLife()>1)
				{
					enemy1->lostLife();
					bulletToDelete->addObject(bullte);
				}
				else if (enemy1->getLife()==1)
				{
					enemy1->lostLife();
					bulletToDelete->addObject(bullte);
					enemy1ToDelete->addObject(enemy1);
					//playerScore += DIJI1_SCORE2;
					//this->controlLayer->updateScore(playerScore);
				}
				else;
				break;
			}
		}
		CCARRAY_FOREACH(enemy1ToDelete,et)
		{
			Enemy* enemy1=(Enemy*)et;
			this->enemyLayer->enemy1Blowup(enemy1);
		}
		enemy1ToDelete->release();

	}
	CCARRAY_FOREACH(bulletToDelete,bt)
	{
		Sprite* bullet =(Sprite*)bt;
		this->mutibullets->RemoveBullet(bullet);
	}
	bulletToDelete->removeAllObjects();
	bulletToDelete->release();
}
void GameSpeed::Mutibullet2AndEnemy()
{
	__Array* bulletToDelete=__Array::create();
	bulletToDelete->retain();
	Ref *bt,*et;
	CCARRAY_FOREACH(this->mutibullets->m_pAllBullet,bt)
	{
		Sprite *bullte =(Sprite*)bt;
		__Array* enemy2ToDelete = __Array::create();
		enemy2ToDelete->retain();
		CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy2,et)
		{
			Enemy* enemy2 = (Enemy*)et;
			if (bullte->boundingBox().intersectsRect(enemy2->getBoundingBox()))
			{
				if (enemy2->getLife()>1)
				{
					enemy2->lostLife();
					bulletToDelete->addObject(bullte);
				}
				else if (enemy2->getLife()==1)
				{
					enemy2->lostLife();
					bulletToDelete->addObject(bullte);
					enemy2ToDelete->addObject(enemy2);
					//playerScore += DIJI2_SCORE2;
					//this->controlLayer->updateScore(playerScore);
				}
				else;
				break;
			}
		}
		CCARRAY_FOREACH(enemy2ToDelete,et)
		{
			Enemy* enemy2=(Enemy*)et;
			this->enemyLayer->enemy2Blowup(enemy2);
		}
		enemy2ToDelete->release();

	}
	CCARRAY_FOREACH(bulletToDelete,bt)
	{
		Sprite* bullet =(Sprite*)bt;
		this->mutibullets->RemoveBullet(bullet);
	}
	bulletToDelete->removeAllObjects();
	bulletToDelete->release();
}
void GameSpeed::Mutibullet3AndEnemy()
{
	__Array* bulletToDelete=__Array::create();
	bulletToDelete->retain();
	Ref *bt,*et;
	CCARRAY_FOREACH(this->mutibullets->m_pAllBullet,bt)
	{
		Sprite *bullte =(Sprite*)bt;
		__Array* enemy2ToDelete = __Array::create();
		enemy2ToDelete->retain();
		CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy3,et)
		{
			Enemy* enemy2 = (Enemy*)et;
		
			if (bullte->boundingBox().intersectsRect(enemy2->getBoundingBox()))
			{
				if (enemy2->getLife()>1)
				{
					enemy2->lostLife();
					bulletToDelete->addObject(bullte);
				}
				else if (enemy2->getLife()==1)
				{
					enemy2->lostLife();
					bulletToDelete->addObject(bullte);
					enemy2ToDelete->addObject(enemy2);
				
					//playerScore += DIJI3_SCORE2;
					//this->controlLayer->updateScore(playerScore);
				}
				else;
				break;
			}
		}
	
		CCARRAY_FOREACH(enemy2ToDelete,et)
		{
			Enemy* enemy2=(Enemy*)et;
			this->enemyLayer->enemy3Blowup(enemy2);
		}
		enemy2ToDelete->release();

	}
	CCARRAY_FOREACH(bulletToDelete,bt)
	{
		Sprite* bullet =(Sprite*)bt;
		this->mutibullets->RemoveBullet(bullet);
	}
	bulletToDelete->removeAllObjects();
	bulletToDelete->release();
}
void GameSpeed::planeAndUFOCrash()
{


	Ref *ut;
	CCARRAY_FOREACH(this->ufoLayer->m_pAllMutiBullets,ut)
	{
		Sprite *mutiBulltes = (Sprite*)ut;
		if (mutiBulltes->boundingBox().intersectsRect(this->planeLayer->getBoundingBox()))
		{
			//this->bulletLayer->StopShoot();
            if (GameData::Inst()->isEffectOpen) {
                SimpleAudioEngine::getInstance()->playEffect("sound/get_bomb.mp3",false);
            }

			this->mutibullets->StartShoot(0.1f);
		    Point point =mutiBulltes->getPosition();
			
			this->planeLayer->addJumpWord1(point);
			
			this->ufoLayer->RemoveMutiBullets(mutiBulltes);
			//this->bulletLayer->StartShoot(10.0f);
			break;
		}

	}
}
void GameSpeed::planeAndUFOBoomCrash()
{
	
	Ref *ut;
	CCARRAY_FOREACH(this->ufoLayer->m_pAllBigBoomItem,ut)
	{
		Sprite *mutiBulltes = (Sprite*)ut;
		if (mutiBulltes->boundingBox().intersectsRect(this->planeLayer->getBoundingBox()))
		{
			if (GameData::Inst()->isEffectOpen) {
                SimpleAudioEngine::getInstance()->playEffect("sound/get_bomb.mp3",false);
            }

			Point point = mutiBulltes->getPosition();
			this->planeLayer->addJumpWord2(point);
			
			this->ufoLayer->RemoveBigBoomItem(mutiBulltes);
			bigBoomCount++;
			updateBigBoomItem(bigBoomCount);
			break;
		}

	}
}

void GameSpeed::updateBigBoomItem(int bigBoomCount)
{
		Sprite* normalBomb=Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("boom.png"));
		Sprite* pressedBomb=Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("boom.png"));
		if (bigBoomCount<0)
		{
			return;
		}
		else if (bigBoomCount==0)
		{
			if(this->getChildByTag(TAG_BIGBOOM_MENUITEM2))
			{
				this->removeChildByTag(TAG_BIGBOOM_MENUITEM2,true);
				
			}
			if (this->getChildByTag(TAG_BIGBOOMCOUNT_LABEL2))
			{
				this->removeChildByTag(TAG_BIGBOOMCOUNT_LABEL2,true);
			}
		}
		else if (bigBoomCount==1)
		{
			if (!this->getChildByTag(TAG_BIGBOOM_MENUITEM2))
			{
				

                //auto pBigBoomItem = MenuItemImage::create("boom.png", "boom.png", CC_CALLBACK_1(GameSpeed::menuBigBoomCallback,this));
                
                auto pBigBoomItem = MenuItemSprite::create(normalBomb, pressedBomb,CC_CALLBACK_1(GameSpeed::menuBigBoomCallback,this));
                
				pBigBoomItem->setPosition(Point(normalBomb->getContentSize().width/2+10,normalBomb->getContentSize().height/2+10));
				menuBigBoom=CCMenu::create(pBigBoomItem,NULL);
                menuBigBoom->setPosition(Point::ZERO);
				this->addChild(menuBigBoom,0,TAG_BIGBOOM_MENUITEM2);

			}
			if (this->getChildByTag(TAG_BIGBOOMCOUNT_LABEL2))
			{
				this->removeChildByTag(TAG_BIGBOOMCOUNT_LABEL2,true);
			}
		}
		
		else//
		{
			if (!this->getChildByTag(TAG_BIGBOOM_MENUITEM2))
			{
				//CCMenuItemImage* pBigBoomItem=CCMenuItemImage::create();
				//pBigBoomItem->initWithNormalSprite(normalBomb,pressedBomb,NULL,this,menu_selector(GameSpeed::menuBigBoomCallback));
                auto pBigBoomItem = MenuItemImage::create("boom.png", "boom.png", CC_CALLBACK_1(GameSpeed::menuBigBoomCallback,this));
				pBigBoomItem->setPosition(Point(normalBomb->getContentSize().width/2+10,normalBomb->getContentSize().height/2+10));
				menuBigBoom=CCMenu::create(pBigBoomItem,NULL);
				menuBigBoom->setPosition(Point::ZERO);
				this->addChild(menuBigBoom,0,TAG_BIGBOOM_MENUITEM2);
			}
			if (this->getChildByTag(TAG_BIGBOOMCOUNT_LABEL2))
			{
				this->removeChildByTag(TAG_BIGBOOMCOUNT_LABEL2,true);
			}
			if (bigBoomCount>=0 && bigBoomCount<=MAX_BIGBOOM_COUNT2)
			{
				//CCString* strScore=CCString::createWithFormat("X %d",bigBoomCount);
                char strScore[100];
                sprintf(strScore, "%d",bigBoomCount);
                
                
				//CCLOG("strScore = %c",strScore);
				//bigBoomCountItem=CCLabelBMFont::create(strScore->m_sString.c_str(),"font/font.fnt");
                //bigBoomCountItem=CCLabelTTF::create(strScore->m_sString.c_str(),"",12);
               // bigBoomCountItem=Label::createWithBMFont("font/font.fnt", strScore);
                bigBoomCountItem = Label::createWithSystemFont(strScore, "", 24);
                
                
				bigBoomCountItem->setColor(Color3B(143,146,147));
				bigBoomCountItem->setAnchorPoint(Point(0,0.5));
				
				bigBoomCountItem->setPosition(Point(normalBomb->getContentSize().width+15,normalBomb->getContentSize().height/2+5));
				this->addChild(bigBoomCountItem,0,TAG_BIGBOOMCOUNT_LABEL2);
			}
		}
}
void GameSpeed::menuBigBoomCallback(Ref* pSender)
{
	if(bigBoomCount>0 && !Director::getInstance()->isPaused())
	{
		bigBoomCount--;

		Ref *et;
	
		CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy1,et)
		{
			playerScore+=DIJI1_SCORE2;
		}
		CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy2,et)
		{
			playerScore+=DIJI2_SCORE2;
		}
		CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy3,et)
		{
			playerScore+=DIJI3_SCORE2;
		}
		//this->controlLayer->updateScore(playerScore);
		this->enemyLayer->removeAllEnemy();
		updateBigBoomItem(bigBoomCount);
		
	}
}