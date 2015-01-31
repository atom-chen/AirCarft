#include "logo.h"
#include "beginLayer.h"
#include "GameData.h"
#include "WelcomeLayer.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

bool logo::init()
{
    bool flag=false;
    if(!Layer::init())
    {
        return false;
    }
    flag=true;
	Size winSize=Director::getInstance()->getWinSize();
    Sprite *sprite=Sprite::create("firstload.jpg");
    sprite->setPosition(Point(winSize.width/2, winSize.height/2));
    this->addChild(sprite);
    //��ȡ���������ļ�
    if(!CCUserDefault::getInstance()->getBoolForKey("isHaveSaveFileXml"))
    {
        CCUserDefault::getInstance()->setBoolForKey("isHaveSaveFileXml", true);
        CCUserDefault::getInstance()->flush();//�ύ
        //CCLOG("�洢�ļ�������,ͷ�ο�ʼ������Ϸ");
        CCUserDefault::getInstance()->setBoolForKey("isBgMusic", true);
        CCUserDefault::getInstance()->flush();//�ύ
        CCUserDefault::getInstance()->setBoolForKey("isEffectMusic", true);
        CCUserDefault::getInstance()->flush();//�ύ
    }else{
        //        CCLOG("�洢�ļ��Ѵ���");
        bool isBgmusicOpen = CCUserDefault::getInstance()->getBoolForKey("isBgMusic");
        GameData::Inst()->isMusicBgOpen=isBgmusicOpen;
        bool isEffectOpen = CCUserDefault::getInstance()->getBoolForKey("isEffectMusic");
        GameData::Inst()->isEffectOpen=isEffectOpen;
    }
    
//    if (GameData::Inst()->isEffectOpen) {
//        SimpleAudioEngine::getInstance()->playEffect("shaoye.mp3",false);
//    }
   

    CallFunc *callLoad=CallFunc::create(this, SEL_CallFunc(&logo::loading));
    
    FadeOut *out=FadeOut::create(4.0f);
    CallFunc *call=CallFunc::create(this, SEL_CallFunc(&logo::replace));
    FiniteTimeAction *finite=Sequence::create(callLoad,out,call,NULL);
    sprite->runAction(finite);
      
    return flag;
}
Scene* logo::scene()
{
    Scene *scene=Scene::create();
    logo *layer = logo::create();
    scene->addChild(layer);
    return scene;
}
void logo::loading()
{

}
void logo::replace()
{
	Scene *scene = WelcomeLayer::scene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f,scene));
}