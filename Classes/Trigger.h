#ifndef __TRIGGER_H__
#define __TRIGGER_H__

#include "cocos2d.h"

class Player;

class Trigger : public cocos2d::Ref
{
public:
    enum Turn
    {
        TURN_NONE,
        TURN_CUSTOM,
        TURN_ATTACK,
    };
public:
    static Trigger* getInstance();
    static void destroyInstance();

    virtual bool init();
    virtual ~Trigger();

public:
    inline const Turn& GetNowTurn() const { return m_NowTurn; }
    int GetCount(){ return m_WaveCount; }

    void GameStart();
    void GameOver(Player* losePlayer);
    void TurnChange();

private:
    Trigger();
    static Trigger* s_Trigger;

    void TurnStartA();
    void TurnStartC();

private:
    Turn m_NowTurn = TURN_NONE;
    int m_WaveCount = 0;
};

#endif  // __TRIGGER_H__
