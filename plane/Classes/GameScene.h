#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "cocos2d.h"
#include "FKSprite.h"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;

class Game : public cocos2d::Layer
{
private:
    // ��Ϸ����ͼ
    Sprite* _bg1;
    Sprite* _bg2;
    // ��ҷɻ�����
    Sprite* _plane;
    // ��Ļ��ȡ��߶ȵı���
    int _screenWidth , _screenHeight;
    // ��Ϸ֡������
    int _count;
    // �л�����
    Vector<FKSprite*> _enemyVector;
    // �ӵ�����
    Vector<Sprite*> _bulletVector;
    // ����ֵ��ǩ
    Label* _scoreLabel;
    // ����
    int _scoreValue;
    // ��Boss
    FKSprite* _boss;
    // ��Boss�ӵ���������
    Vector<Sprite*> _bossBulletVector;
    // �Ƿ�������Boss����Boss�Ƿ�ʼ�ƶ��ʹ�Boss�Ƿ����ӵ�
    bool _isStart,_isMove,_isShoot;
public:
    /**
     * ��̬����������Scene����
     * ע�⣺��Cocos2d-x��û��Cocos2d-iPhone�еġ�id��,���鷵����ʵ����ָ��
     */
    static cocos2d::Scene* createScene();
    /**
     * init��������ɳ�ʼ��������
     * ע�⣺init������Cocos2d-x�з���boolֵ�������Ƿ���Cocos2d-iPhone�еġ�id��
     */
    virtual bool init();
    
    // ��Node�ڵ���롰��̨��ʱ����
    virtual void onEnter();
    
    // �ص����º������ú���ÿһ֡�������
    void update(float delta);
    // ����ͼƬ��������
    void updateBackground();
    // ������һ���
    void updateHUD(float delta);
    
    // ���µл�����
    void enemyPlaneDive(float delta);
    // �л��뿪��Ļɾ������
    void removeEnemy(float delta);
    
    // ��ҷɻ����Ϸ����ӵ�����
    void shootBullet(float delta);
    // �ӵ��뿪��Ļɾ������
    void removeBullet(float delta);
    // �����ײ�ĺ���
    void collisionDetection(float delta);

    // ��ö�������
    Animation* getAnimationByName(std::string animName,float delay,int animNum);
    // ���ű�ը����
    void playBombAnimate(std::string name,Vec2 position);
    
    // ������Boss
    void startBoss();
    // �ƶ���Boss
    void moveBoss();
    // ��Boss�����ڵ�
    void shootBoss(float delta);

    // ��Ϸ����
    void gameOver(std::string message);
    // ���¿�ʼ
    void restart(int tag);
    
    /**
     * ʹ��CREATE_FUNC�괴����ǰ��Ķ��󣬷��صĶ��󽫻����Զ��ͷųع����ڴ���ͷ�
     */
    CREATE_FUNC(Game);


};

#endif /* defined(__AirfightGame__GameScene__) */
