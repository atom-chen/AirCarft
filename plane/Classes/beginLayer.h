//
//  beginLayer.h
//
//
//  Created by gh on 2014��10��27��
//
//

#ifndef Bing_beginLayer_h
#define Bing_beginLayer_h

#include "cocos2d.h"
USING_NS_CC;
class beginLayer:public Layer
{
private:
    Size size;
    Sprite *spFirst;
    Sprite *m_pBearSprite;
public:
    static cocos2d::Scene* createScene();
    static cocos2d::Animation* createAnimation(const char* formatStr, int frameCount, int fps);
    virtual bool init();
    CREATE_FUNC(beginLayer);
    void loading();
    void enterGame();

};


#endif
