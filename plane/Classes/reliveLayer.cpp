#include "reliveLayer.h"
#include "GameData.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
reliveLayer::reliveLayer(Ref* target,SEL_CallFuncO selector)
{
    m_pListener = target;
    m_pfnSelector = selector;
}
reliveLayer::~reliveLayer()
{
    
}
reliveLayer* reliveLayer::create(Ref* target,SEL_CallFuncO selector)
{
    reliveLayer * pRet = new reliveLayer(target,selector);
    if(pRet && pRet->initWithColor(Color4B(0, 0, 0, 0)))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}
bool reliveLayer::initWithColor(const cocos2d::Color4B &color)
{
    if (!LayerColor::initWithColor(color)) {
        return false;
    }
    Size winSize = Director::getInstance()->getWinSize();
    //添加背景
    auto spbg=Sprite::create("relive_bg.png");
    //spbg->setScale(1.3);
    spbg->setAnchorPoint(Point::ZERO);
    spbg->setPosition(Point(0, winSize.height/2-spbg->getContentSize().height/2));
    addChild(spbg);
    // 添加选择框
    m_btnRelive = MenuItemImage::create("relive_1.png", "relive_2.png", CC_CALLBACK_1(reliveLayer::menuReiveCallback, this));
    m_btnDead = MenuItemImage::create("dead_1.png", "dead_2.png", CC_CALLBACK_1(reliveLayer::menuDeadCallback, this));
    m_btnRelive->setPosition(Point(420,90));
    m_btnDead->setPosition(Point(170,90));

    auto menu=Menu::create(m_btnRelive,m_btnDead, NULL);
    menu->setAnchorPoint(Point::ZERO);
    menu->setPosition(Point(0,0));
    spbg->addChild(menu);
    auto lb_note = Label::createWithSystemFont("少年你被敌人击败，不想复仇吗？","", 30);
    lb_note->setPosition(Point(winSize.width/2,winSize.height/2+50));
    lb_note->setColor(Color3B(54,179,175));
    addChild(lb_note);
    //设置触摸事件监听
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(reliveLayer::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(reliveLayer::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(reliveLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    touchListener->setSwallowTouches(true); //设置是否想下传递触摸
    return true;
}
bool reliveLayer::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}
void reliveLayer::onTouchMoved(Touch* touch, Event* event)
{
    
}
void reliveLayer::onTouchEnded(Touch* touch, Event* event)
{
    Point touchLocation = touch->getLocationInView();
    touchLocation = Director::getInstance()->convertToGL(touchLocation);
    
    Point pos = convertToNodeSpace( touchLocation );
    
    bool bRet = false;
    
    Point pt = m_btnRelive->getPosition();
    Size s= m_btnRelive->getContentSize();//获取精灵的文本尺寸大小
    Rect rect = Rect(pt.x - s.width * 0.5,  pt.y - s.height * 0.5, s.width, s.height);//获取精灵的矩形框
    if (GameData::Inst()->isEffectOpen) {
        SimpleAudioEngine::getInstance()->playEffect("sound/get_bomb.mp3");
    }
    bRet = rect.containsPoint(pos);
    if(bRet){ // 开启
        
        return;
    }
//    auto scaleOne=ScaleTo::create(0.1f, 0.8f);
//    auto scaleTwo=ScaleTo::create(0.1f, 0.6f);
//    auto scaleThr=ScaleTo::create(0.1f, 0.3f);
//    auto scaleFor=ScaleTo::create(0.1f, 0.1f);
//    this->runAction(Sequence::create(scaleOne,scaleTwo,scaleThr,scaleFor, NULL));
//    scheduleOnce(SEL_SCHEDULE(&reliveLayer::quitLayer), 0.4f); //每隔1.0f执行
 
}
void reliveLayer::menuReiveCallback(Ref* pSender)
{
    if (GameData::Inst()->isEffectOpen) {
        SimpleAudioEngine::getInstance()->playEffect("sound/button.mp3",false);
    }
    m_ret.iSel = 2;
    (m_pListener->*m_pfnSelector)(&m_ret);
    
    auto scaleOne=ScaleTo::create(0.1f, 0.8f);
    auto scaleTwo=ScaleTo::create(0.1f, 0.6f);
    auto scaleThr=ScaleTo::create(0.1f, 0.3f);
    auto scaleFor=ScaleTo::create(0.1f, 0.1f);
    this->runAction(Sequence::create(scaleOne,scaleTwo,scaleThr,scaleFor, NULL));
    scheduleOnce(SEL_SCHEDULE(&reliveLayer::quitLayer), 0.4f); //每隔1.0f执行
    

    
}
void reliveLayer::menuDeadCallback(Ref* pSender)
{
    if (GameData::Inst()->isEffectOpen) {
        SimpleAudioEngine::getInstance()->playEffect("sound/button.mp3",false);
    }
    m_ret.iSel = 1;
    (m_pListener->*m_pfnSelector)(&m_ret);
    //
    auto scaleOne=ScaleTo::create(0.1f, 0.8f);
    auto scaleTwo=ScaleTo::create(0.1f, 0.6f);
    auto scaleThr=ScaleTo::create(0.1f, 0.3f);
    auto scaleFor=ScaleTo::create(0.1f, 0.1f);
    this->runAction(Sequence::create(scaleOne,scaleTwo,scaleThr,scaleFor, NULL));
    scheduleOnce(SEL_SCHEDULE(&reliveLayer::quitLayer), 0.4f); //每隔1.0f执行

}
void reliveLayer::quitLayer(float dt)
{
    unschedule(SEL_SCHEDULE(&reliveLayer::quitLayer));
    this->removeFromParentAndCleanup(true);
    
}
void reliveLayer::onExit()
{
    removeAllChildrenWithCleanup(true);
    Layer::onExit();
}