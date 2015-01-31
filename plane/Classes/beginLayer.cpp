//
//  beginLayer.cpp
//  Bing
//
//  Created by gh on 2014年10月27日
//
//
#include "beginLayer.h"
#include "WelcomeLayer.h"
#include "GameData.h"
//#include "LHVideoPlayerImplCpp.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
bool beginLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    size = Director::getInstance()->getWinSize();

    scheduleOnce(SEL_SCHEDULE(&beginLayer::loading), 0.6f); //每隔1.0f执行
    
    return true;
}
Scene* beginLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = beginLayer::create();
    scene->addChild(layer);
    return scene;
}
Animation* beginLayer::createAnimation(const char* formatStr, int frameCount, int fps)
{
	Vector<SpriteFrame *> pFrames ;//= __Array::createWithCapacity(frameCount);
	for(int i = 1; i < frameCount; ++ i)
	{
		const char* imgName = String::createWithFormat(formatStr, i)->getCString();
		SpriteFrame *pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(imgName);
		if (pFrame)
		{
            //			pFrames->addObject(pFrame);
			pFrames.pushBack(pFrame);
		}
	}
	return Animation::createWithSpriteFrames(pFrames, 1.0f / fps);
}
void beginLayer::loading()
{
    GameData::Inst()->playVideo("video2.mp4");
    scheduleOnce(SEL_SCHEDULE(&beginLayer::enterGame), 18.0f); //每隔1.0f执行
}
void beginLayer::enterGame()
{
    unschedule(SEL_SCHEDULE(&beginLayer::enterGame));
    auto scene=WelcomeLayer::scene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f,scene));
    Director::getInstance()->resume();
}