//
//  NumberScroll.h
//  starwar
//
//  Created by guohui on 14-10-25.
//
//

#ifndef starwar_NumberScroll_h
#define starwar_NumberScroll_h
#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
class NumberScroll:public Node
{
    //    可见的节点数字
    Node *visibleNode;
public:
    //    函数初始化
    virtual bool init();
    //  重载Node函数实现opengl遮罩
    virtual void onEnter();
    CREATE_FUNC(NumberScroll);
    //    设置滚动到哪个数字
    void setNumber(int var);
};

#endif
