#include "Missile.h"
#include "GameManager.h"

USING_NS_CC;

bool Missile::init()
{
    if (!custom::Object::init())
    {
        return false;
    }
    return true;
}

void Missile::SetDef(const DefInfo& info)
{
    Object::SetDef(info);
    getPhysicsBody()->getFirstShape()->setMaterial(PhysicsMaterial(1.0f, 0, 0));
    getPhysicsBody()->setCategoryBitmask(OBJ_MISSILE);
    getPhysicsBody()->setCollisionBitmask(OBJ_ALL - OBJ_MISSILE - OBJ_LASER);
    getPhysicsBody()->setContactTestBitmask(OBJ_ALL - OBJ_MISSILE - OBJ_LASER);
    getPhysicsBody()->setGravityEnable(false);
    LifeCount();
}


void Missile::Damaged(int damage)
{
    if (!m_Alive)
    {
        return;
    }
    Object::Damaged(damage);
}

void Missile::Destroy()
{
    if (!m_Alive)
    {
        return;
    }
    Object::Destroy();
}

void Missile::LifeCount()
{
    m_Count--;

    if (m_Count < 1)
        Destroy();
    else
        GET_GM->CallFuncAfter(1.0f, this, &Missile::LifeCount);
}
