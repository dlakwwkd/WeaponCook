#include "Weapon.h"
#include "GameManager.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

bool Weapon::init()
{
    if (!custom::Object::init())
    {
        return false;
    }
    return true;
}

void Weapon::SetDef(const WeaponInfo& info)
{
    SetDefInfo(info.m_DefInfo);
    m_WeaponInfo = info;
}

void Weapon::Destroy()
{
    if (!m_Alive)
    {
        return;
    }
    GET_UI_LAYER->removeChild(m_Icon);
    Object::Destroy();
}

void Weapon::SetIcon(const std::string& image)
{
    m_Icon = Sprite::create(image);
    GET_UI_LAYER->addChild(m_Icon);
    SetLabel();
    UpdateLabel();
}

void Weapon::SetLabel()
{
    m_Count = Label::createWithSystemFont("999", "Arial", 12);
    m_Count->setColor(Color3B::WHITE);
    m_Count->setPosition(Vec2(m_Icon->getContentSize().width / 2, - 6.0f));
    m_Icon->addChild(m_Count);
}

void Weapon::UpdateLabel()
{
    char buf1[256];
    std::string count = _itoa(m_WeaponInfo.m_Count, buf1, 10);
    m_Count->setString(count);
}

void Weapon::Attack(const Vec2& unitPos, Unit::Direction dir)
{
    switch (m_WeaponInfo.m_AttackType)
    {
    case Weapon::AT_MISSILE:    ShootMissile(unitPos, dir); break;
    case Weapon::AT_LASIER:     ShootLasier(unitPos, dir);  break;
    default:
        break;
    }
    GET_UI_LAYER->Shoot();
    UpdateLabel();
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(m_WeaponInfo.m_Sound.c_str());
}

void Weapon::ShootMissile(const Vec2& unitPos, Unit::Direction dir)
{
    auto objLayer = GET_OBJ_LAYER;
    objLayer->CreateMissile(unitPos, m_Owner, m_WeaponInfo, dir);
}

void Weapon::ShootLasier(const Vec2& unitPos, Unit::Direction dir)
{
    auto objLayer = GET_OBJ_LAYER;
    objLayer->CreateLaser(unitPos, m_Owner, m_WeaponInfo, dir);
}
