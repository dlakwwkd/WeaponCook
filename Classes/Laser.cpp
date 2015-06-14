#include "Laser.h"
#include "GameManager.h"

USING_NS_CC;

bool Laser::init()
{
    if (!custom::Object::init())
    {
        return false;
    }
    return true;
}

void Laser::SetDef(const DefInfo& info)
{
    Object::SetDef(info);
    getPhysicsBody()->getFirstShape()->setMaterial(PhysicsMaterial(0, 0, 0));
    getPhysicsBody()->setCategoryBitmask(OBJ_LASER);
    getPhysicsBody()->setCollisionBitmask(0);
    getPhysicsBody()->setContactTestBitmask(OBJ_ALL - OBJ_MISSILE - OBJ_LASER);
    getPhysicsBody()->setGravityEnable(false);
    LifeCount();
}


void Laser::Damaged(int damage)
{
    if (!m_Alive)
    {
        return;
    }
    Object::Damaged(damage);
}

void Laser::Destroy()
{
    if (!m_Alive)
    {
        return;
    }
    Object::Destroy();
}

void Laser::LifeCount()
{
    m_Count--;

    if (m_Count < 1)
        Destroy();
    else
        GET_GM->CallFuncAfter(1.0f, this, &Laser::LifeCount);
}
