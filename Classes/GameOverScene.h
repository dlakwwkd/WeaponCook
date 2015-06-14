#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"

class Player;

class GameOverScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameOverScene);

    void Score(int score);
    void Close(cocos2d::Ref* sender);
};

#endif  // __GAMEOVER_SCENE_H__
