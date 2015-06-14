#include "SpaceShip.h"
#include "GameManager.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

bool SpaceShip::init()
{
    if (!custom::Object::init())
    {
        return false;
    }
    return true;
}

void SpaceShip::SetDef(const DefInfo& info)
{
    Object::SetDef(info);
    getPhysicsBody()->setCategoryBitmask(OBJ_DEF);
    getPhysicsBody()->setContactTestBitmask(OBJ_MISSILE + OBJ_LASER);
    SetHpBar("Image/Interface/hp_bar_big.png");
}

void SpaceShip::Damaged(int damage)
{
    if (!m_Alive)
    {
        return;
    }
    Object::Damaged(damage);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(PATH_SOUND_ATTACK_A);
    /*
        todo : 피격 이펙트
    */
}

void SpaceShip::Destroy()
{
    if (!m_Alive)
    {
        return;
    }
    Object::Destroy();
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(PATH_SOUND_BOOM_B);
}

void SpaceShip::CreateUnit()
{
    auto pos = Vec2(getPositionX(), getPositionY());
    auto delay = 0.1f;
    
    for (auto& unitInfo : m_UnitInfoList)
    {
        GET_GM->CallFuncAfter(delay, GET_OBJ_LAYER, &ObjectLayer::CreateUnit, pos, m_Owner, unitInfo);
        delay += 0.1f;
    }
    GET_GM->CallFuncAfter(2.0f, this, &SpaceShip::CreateUnit);
}
