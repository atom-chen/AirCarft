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
    //    �ɼ��Ľڵ�����
    Node *visibleNode;
public:
    //    ������ʼ��
    virtual bool init();
    //  ����Node����ʵ��opengl����
    virtual void onEnter();
    CREATE_FUNC(NumberScroll);
    //    ���ù������ĸ�����
    void setNumber(int var);
};

#endif
