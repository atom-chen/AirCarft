#ifndef __reliveLayer_H__
#define __reliveLayer_H__	
#include"cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
using namespace cocos2d;

class reliveLayerRet : public Ref
{
public:
    int     iSel;   //0: add card     1: start  2: over
};
class reliveLayer:public LayerColor
{
    Ref*       m_pListener;
    SEL_CallFuncO   m_pfnSelector;
    Sprite          *m_spchose;
    Sprite          *m_spchose2;
    MenuItem          *m_btnRelive;
    MenuItem          *m_btnDead;
    reliveLayerRet    m_ret;
public:
    virtual bool initWithColor(const Color4B& color);
    static reliveLayer* create(Ref* target,SEL_CallFuncO selector);
    reliveLayer(Ref* target,SEL_CallFuncO selector);
    ~reliveLayer();
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
    virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
    virtual void onExit();
    void quitLayer(float dt);
    void menuReiveCallback(Ref* pSender);
    void menuDeadCallback(Ref* pSender);
};
#endif