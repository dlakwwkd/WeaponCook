#ifndef __OVEN_H__
#define __OVEN_H__

#include "Object.h"
#include "Weapon.h"

class Oven : public custom::Object
{
public:
    virtual bool init();
    CREATE_FUNC(Oven);

    virtual void    SetDef(const DefInfo& info);
    virtual void    Damaged(int damage);
    virtual void    Destroy();

    void CookingWeapon(const Weapon::WeaponInfo& info);
    void CreateWeapon();
    void InitWeaponInfo();


private:
    Weapon::WeaponInfo m_WeaponInfo;
};

#endif  // __OVEN_H__
