#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "Object.h"
#include "Missile.h"
#include "Unit.h"

class Weapon : public custom::Object
{
public:
    enum AttackType
    {
        AT_MISSILE,
        AT_LASIER,
    };
    struct WeaponInfo
    {
        DefInfo     m_DefInfo;
        std::string m_IconImage;
        std::string m_Sound;
        AttackType  m_AttackType = AT_MISSILE;
        int         m_Damage;
        int         m_Speed;
        int         m_Count;
        float       m_Delay;
        float       m_Range;
        float       m_Size;
    };
public:
    virtual bool init();
    CREATE_FUNC(Weapon);

    virtual void    SetDef(const WeaponInfo& info);
    virtual void    Destroy();

    const WeaponInfo&   GetWeaponInfo(){ return m_WeaponInfo; }
    
    void                SetIcon(const std::string& image);
    cocos2d::Sprite*    GetIcon() const { return m_Icon; }

    void AddCount(int count) { m_WeaponInfo.m_Count += count; }
    void AddDamage(int damage) { m_WeaponInfo.m_Damage += damage; }
    void AddSpeed(int speed) { m_WeaponInfo.m_Speed += speed; }
    void AddSize(float size) { m_WeaponInfo.m_Size += size; }

    void SetLabel();
    void UpdateLabel();
    void Attack(const cocos2d::Vec2& unitPos, Unit::Direction dir);

private:
    void ShootMissile(const cocos2d::Vec2& unitPos, Unit::Direction dir);
    void ShootLasier(const cocos2d::Vec2& unitPos, Unit::Direction dir);

private:
    WeaponInfo m_WeaponInfo;
    cocos2d::Sprite* m_Icon;
    cocos2d::Label* m_Count;

    friend class Unit;
};

#endif  // __WEAPON_H__
