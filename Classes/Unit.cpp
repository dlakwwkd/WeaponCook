#include "Unit.h"
#include "Weapon.h"
#include "GameManager.h"

USING_NS_CC;

bool Unit::init()
{
    if (!custom::Object::init())
    {
        return false;
    }
    return true;
}

void Unit::SetDef(const UnitInfo& info)
{
    Object::SetDef(info.m_DefInfo);
    getPhysicsBody()->getFirstShape()->setMaterial(PhysicsMaterial(0, 0, 0));
    getPhysicsBody()->setCategoryBitmask(OBJ_UNIT);
    getPhysicsBody()->setCollisionBitmask(OBJ_ALL - OBJ_UNIT - OBJ_DEF - OBJ_LASER);
    getPhysicsBody()->setContactTestBitmask(OBJ_LASER + OBJ_MISSILE + OBJ_DEF);
    getPhysicsBody()->setVelocityLimit(m_DefInfo.m_MoveSpeed * 1.5f);
    SetHpBar("Image/Interface/hp_bar_small.png");
    m_UnitInfo = info;
}


void Unit::Damaged(int damage)
{
    if (!m_Alive)
    {
        return;
    }
    Object::Damaged(damage);
}

void Unit::Destroy()
{
    if (!m_Alive)
    {
        return;
    }
    Object::Destroy();
    m_UnitInfo.m_State = US_DEATH;
    GET_OBJ_LAYER->DeleteUnit(this);
    GET_UI_LAYER->ShowIcon();
}

void Unit::AI()
{
    if (rand() % 3 < 1)
        Jump();

    switch (m_UnitInfo.m_State)
    {
    case Unit::US_STANDBY: Move(); break;
    case Unit::US_MOVEING: Move(); break;
    case Unit::US_ATTACK:          break;
    case Unit::US_DEATH:           break;
    default:
        break;
    }
}

void Unit::Move()
{
    switch (m_UnitInfo.m_Direction)
    {
    case Unit::DIR_RIGHT: _physicsBody->applyImpulse(Vec2(m_DefInfo.m_MoveSpeed, 0));    break;
    case Unit::DIR_LEFT: _physicsBody->applyImpulse(Vec2(-m_DefInfo.m_MoveSpeed, 0));    break;
    }
    m_UnitInfo.m_State = US_MOVEING;
}

void Unit::Jump()
{
    if (_physicsBody->getVelocity().y > 0.1f || _physicsBody->getVelocity().y < -0.1f)
        return;
    _physicsBody->applyImpulse(Vec2(0, m_DefInfo.m_MoveSpeed*1.2f));
}

void Unit::Attack()
{
    if (!m_WeaponQueue.empty())
    {
        auto weapon = m_WeaponQueue.front();
        if (--weapon->m_WeaponInfo.m_Count < 1)
        {
            weapon->Destroy();
            m_WeaponQueue.pop();
            GET_UI_LAYER->ShowIcon();
            return;
        }
        weapon->Attack(_physicsBody->getPosition(), m_UnitInfo.m_Direction);
    }
}

void Unit::Stop()
{
    _physicsBody->setVelocity(Vec2(0, _physicsBody->getVelocity().y));
    m_UnitInfo.m_State = US_STANDBY;
}

void Unit::PushWeapon(Weapon* weapon)
{
    m_WeaponQueue.push(weapon);
    GET_UI_LAYER->ShowIcon();
}

void Unit::ChangeWeapon()
{
    m_WeaponQueue.push(m_WeaponQueue.front());
    m_WeaponQueue.pop();
    GET_UI_LAYER->ShowIcon();
}

void Unit::UpgleWeapon()
{
    auto weapon = m_WeaponQueue.front();
    weapon->AddCount(1);
    weapon->AddDamage(5);
    weapon->AddSize(0.02f);
    weapon->AddSpeed(3);
    weapon->UpdateLabel();
}
