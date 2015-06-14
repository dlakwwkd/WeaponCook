#include "Ingredient.h"
#include "GameManager.h"

USING_NS_CC;

bool Ingredient::init()
{
    if (!custom::Object::init())
    {
        return false;
    }
    return true;
}

void Ingredient::SetDef(const DefInfo& info)
{
    auto info2 = info;
    info2.m_ImageName = PATH_IMAGE_LASIER_B;
    Object::SetDef(info2);
    getPhysicsBody()->getFirstShape()->setMaterial(PhysicsMaterial(0, 0, 0));
    getPhysicsBody()->setCategoryBitmask(OBJ_DEF);
    getPhysicsBody()->setContactTestBitmask(OBJ_UNIT);
}


void Ingredient::Damaged(int damage)
{
    if (!m_Alive)
    {
        return;
    }
    Object::Damaged(damage);
}

void Ingredient::Destroy()
{
    if (!m_Alive)
    {
        return;
    }
    Object::Destroy();
}

void Ingredient::InitWeaponInfo()
{
    m_WeaponInfo.m_DefInfo.m_ImageName = PATH_IMAGE_LASIER_B;
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

void Pork::InitWeaponInfo()
{
    Ingredient::InitWeaponInfo();
    m_WeaponInfo.m_DefInfo.m_ImageName = PATH_IMAGE_LASIER_B;
    m_WeaponInfo.m_AttackType = Weapon::AT_MISSILE;
}

void Beef::InitWeaponInfo()
{
    Ingredient::InitWeaponInfo();
    m_WeaponInfo.m_DefInfo.m_ImageName = PATH_IMAGE_LASIER_B;
    m_WeaponInfo.m_AttackType = Weapon::AT_LASIER;
}

void Wheat::InitWeaponInfo()
{
    Ingredient::InitWeaponInfo();
    m_WeaponInfo.m_DefInfo.m_ImageName = PATH_IMAGE_LASIER_B;
    m_WeaponInfo.m_Damage = 5;
    m_WeaponInfo.m_Delay = 0.1f;
}

void Rice::InitWeaponInfo()
{
    Ingredient::InitWeaponInfo();
    m_WeaponInfo.m_DefInfo.m_ImageName = PATH_IMAGE_LASIER_B;
    m_WeaponInfo.m_Count = 5;
    m_WeaponInfo.m_DefInfo.m_CurHp = 10;
    m_WeaponInfo.m_DefInfo.m_MaxHp = 10;
}

void Onion::InitWeaponInfo()
{
    Ingredient::InitWeaponInfo();
    m_WeaponInfo.m_DefInfo.m_ImageName = PATH_IMAGE_LASIER_B;
    m_WeaponInfo.m_Speed = 30.0f;
    m_WeaponInfo.m_Delay = -0.1f;
}

void Bean::InitWeaponInfo()
{
    Ingredient::InitWeaponInfo();
    m_WeaponInfo.m_DefInfo.m_ImageName = PATH_IMAGE_LASIER_B;
    m_WeaponInfo.m_Size = 0.1f;
}

void Pepper::InitWeaponInfo()
{
    Ingredient::InitWeaponInfo();
    m_WeaponInfo.m_DefInfo.m_ImageName = PATH_IMAGE_LASIER_B;
    m_WeaponInfo.m_Delay = -0.1f;
}
