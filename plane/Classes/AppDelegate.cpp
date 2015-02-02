#include "AppDelegate.h"
#include "logo.h"
#include "GameData.h"
#include "SimpleAudioEngine.h"
#include "WelcomeLayer.h"
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director  
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if(!glview) {
		glview = GLViewImpl::create("star war");
		director->setOpenGLView(glview);
	}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	glview->setFrameSize(480, 800);
#endif
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if(visibleSize.height/visibleSize.width > 800/480){
		glview->setDesignResolutionSize(480, 800, ResolutionPolicy::EXACT_FIT);
	}
	else{
		glview->setDesignResolutionSize(480, 800, ResolutionPolicy::NO_BORDER);
	}

	// create a scene. it's an autorelease object
	auto scene = logo::scene();
	// run
	director->runWithScene(scene);

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();
	//GameData::Inst()->showInsert();
	// if you use SimpleAudioEngine, it must be pause
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	SimpleAudioEngine::getInstance()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();
	// if you use SimpleAudioEngine, it must resume here
	if (GameData::Inst()->isMusicBgOpen) {
		SimpleAudioEngine::getInstance()->rewindBackgroundMusic();
	}
	if (GameData::Inst()->isMusicBgOpen) {
		SimpleAudioEngine::getInstance()->resumeAllEffects();
	}
}