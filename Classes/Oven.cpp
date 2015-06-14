#include "Oven.h"
#include "GameManager.h"
#include "Trigger.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

bool Oven::init()
{
    if (!custom::Object::init())
    {
        return false;
    }
    return true;
}

void Oven::SetDef(const DefInfo& info)
{
    Object::SetDef(info);
    getPhysicsBody()->setDynamic(false);
    getPhysicsBody()->setCategoryBitmask(OBJ_DEF);
    getPhysicsBody()->setCollisionBitmask(0);
    getPhysicsBody()->setContactTestBitmask(OBJ_UNIT);
    SetHpBar("Image/Interface/hp_bar_big.png");
}

void Oven::Damaged(int damage)
{
    if (!m_Alive)
    {
        return;
    }
    Object::Damaged(damage);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(PATH_SOUND_ATTACK_A);
}

void Oven::Destroy()
{
    if (!m_Alive)
    {
        return;
    }
    Object::Destroy();
    Trigger::getInstance()->GameOver(m_Owner);
}

void Oven::CookingWeapon(const Weapon::WeaponInfo& info)
{
    m_WeaponInfo.m_AttackType = info.m_AttackType;
    m_WeaponInfo.m_Count += info.m_Count;
    m_WeaponInfo.m_Damage += info.m_Damage;
    m_WeaponInfo.m_Size += info.m_Size;
    m_WeaponInfo.m_Speed += info.m_Speed;
    m_WeaponInfo.m_Delay += info.m_Delay;
    m_WeaponInfo.m_Range += info.m_Range;

    m_WeaponInfo.m_DefInfo.m_ImageName = info.m_DefInfo.m_ImageName;
    m_WeaponInfo.m_DefInfo.m_CurHp += info.m_DefInfo.m_CurHp;
    m_WeaponInfo.m_DefInfo.m_MaxHp += info.m_DefInfo.m_MaxHp;

    m_WeaponInfo.m_DefInfo.m_Damage = m_WeaponInfo.m_Damage;
    m_WeaponInfo.m_DefInfo.m_MoveSpeed = m_WeaponInfo.m_Speed;
}

void Oven::CreateWeapon()
{
    auto objLayer = GET_OBJ_LAYER;
    auto hero = objLayer->GetHero();

    objLayer->CreateWeapon(m_WeaponInfo, m_Owner, hero);
    InitWeaponInfo();
}

void Oven::InitWeaponInfo()
{
    m_WeaponInfo.m_DefInfo.m_ImageName = PATH_IMAGE_UNIT_A;
    m_WeaponInfo.m_DefInfo.m_CurHp = 0;
    m_WeaponInfo.m_DefInfo.m_MaxHp = 0;
    m_WeaponInfo.m_DefInfo.m_Damage = 0;
    m_WeaponInfo.m_DefInfo.m_MoveSpeed = 0.0f;

    m_WeaponInfo.m_AttackType = Weapon::AT_MISSILE;
    m_WeaponInfo.m_Count = 0;
    m_WeaponInfo.m_Damage = 0;
    m_WeaponInfo.m_Size = 0.0f;
    m_WeaponInfo.m_Speed = 0.0f;
    m_WeaponInfo.m_Delay = 0.0f;
    m_WeaponInfo.m_Range = 0.0f;
}
