#include "beginLayer.h"
#include "WelcomeLayer.h"
#include "GameData.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
bool beginLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    size = Director::getInstance()->getWinSize();

	scheduleOnce(schedule_selector(beginLayer::loading), 0.6f); //每隔1.0f执行
    
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
	Vector<SpriteFrame *> pFrames;
	for(int i = 1; i < frameCount; ++ i)
	{
		const char* imgName = String::createWithFormat(formatStr, i)->getCString();
		SpriteFrame *pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(imgName);
		if (pFrame)
		{
			pFrames.pushBack(pFrame);
		}
	}
	return Animation::createWithSpriteFrames(pFrames, 1.0f / fps);
}
void beginLayer::loading(float dt)
{
    GameData::Inst()->playVideo("video2.mp4");
    scheduleOnce(schedule_selector(beginLayer::enterGame), 18.0f); //每隔1.0f执行
}
void beginLayer::enterGame(float dt)
{
    unschedule(SEL_SCHEDULE(&beginLayer::enterGame));
    auto scene=WelcomeLayer::scene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f,scene));
    Director::getInstance()->resume();
}