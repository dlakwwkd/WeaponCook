#ifndef __UNIT_H__
#define __UNIT_H__

#include "Object.h"

class Weapon;

class Unit : public custom::Object
{
public:
    enum State
    {
        US_STANDBY,
        US_MOVEING,
        US_CHASING,
        US_ATTACK,
        US_DEATH,
    };
    enum Direction
    {
        DIR_RIGHT,
        DIR_LEFT,
    };
    struct UnitInfo
    {
        DefInfo     m_DefInfo;
        State       m_State = US_STANDBY;
        Direction   m_Direction = DIR_RIGHT;
    };
public:
    virtual bool init();
    CREATE_FUNC(Unit);

    virtual void SetDef(const UnitInfo& info);
    virtual void Damaged(int damage);
    virtual void Destroy();

    void SetDir(Direction dir){ m_UnitInfo.m_Direction = dir; }
    void PushWeapon(Weapon* weapon);
    void ChangeWeapon();

    void AI();
    void Move();
    void Jump();
    void Attack();
    void Stop();

protected:
    UnitInfo    m_UnitInfo;
    std::queue<Weapon*> m_WeaponQueue;

    friend class UILayer;
};

#endif  // __UNIT_H__
