#ifndef __INGREDIENT_H__
#define __INGREDIENT_H__

#include "Object.h"
#include "Weapon.h"

class Ingredient : public custom::Object
{
public:
    enum Type
    {
        IT_PORK,
        IT_BEEF,
        IT_WHEAT,
        IT_RICE,
        IT_ONION,
        IT_BEAN,
        IT_PEPPER,
    };
public:
    virtual bool init();
    CREATE_FUNC(Ingredient);

    virtual void SetDef(const DefInfo& info);
    virtual void Damaged(int damage);
    virtual void Destroy();
    
    virtual void InitWeaponInfo();

protected:
    Weapon::WeaponInfo m_WeaponInfo;
};



class Pork : public Ingredient
{
public:
    CREATE_FUNC(Pork);
    virtual bool init(){ Ingredient::init(); return true; }
    virtual void SetDef(const DefInfo& info){ Ingredient::SetDef(info); }
    virtual void Damaged(int damage){ Ingredient::Damaged(damage); }
    virtual void Destroy(){ Ingredient::Destroy(); }
    virtual void InitWeaponInfo();
};

class Beef : public Ingredient
{
public:
    CREATE_FUNC(Beef);
    virtual bool init(){ Ingredient::init(); return true; }
    virtual void SetDef(const DefInfo& info){ Ingredient::SetDef(info); }
    virtual void Damaged(int damage){ Ingredient::Damaged(damage); }
    virtual void Destroy(){ Ingredient::Destroy(); }
    virtual void InitWeaponInfo();
};

class Wheat : public Ingredient
{
public:
    CREATE_FUNC(Wheat);
    virtual bool init(){ Ingredient::init(); return true; }
    virtual void SetDef(const DefInfo& info){ Ingredient::SetDef(info); }
    virtual void Damaged(int damage){ Ingredient::Damaged(damage); }
    virtual void Destroy(){ Ingredient::Destroy(); }
    virtual void InitWeaponInfo();
};
class Rice : public Ingredient
{
public:
    CREATE_FUNC(Rice);
    virtual bool init(){ Ingredient::init(); return true; }
    virtual void SetDef(const DefInfo& info){ Ingredient::SetDef(info); }
    virtual void Damaged(int damage){ Ingredient::Damaged(damage); }
    virtual void Destroy(){ Ingredient::Destroy(); }
    virtual void InitWeaponInfo();
};

class Onion : public Ingredient
{
public:
    CREATE_FUNC(Onion);
    virtual bool init(){ Ingredient::init(); return true; }
    virtual void SetDef(const DefInfo& info){ Ingredient::SetDef(info); }
    virtual void Damaged(int damage){ Ingredient::Damaged(damage); }
    virtual void Destroy(){ Ingredient::Destroy(); }
    virtual void InitWeaponInfo();
};

class Bean : public Ingredient
{
public:
    CREATE_FUNC(Bean);
    virtual bool init(){ Ingredient::init(); return true; }
    virtual void SetDef(const DefInfo& info){ Ingredient::SetDef(info); }
    virtual void Damaged(int damage){ Ingredient::Damaged(damage); }
    virtual void Destroy(){ Ingredient::Destroy(); }
    virtual void InitWeaponInfo();
};

class Pepper : public Ingredient
{
public:
    CREATE_FUNC(Pepper);
    virtual bool init(){ Ingredient::init(); return true; }
    virtual void SetDef(const DefInfo& info){ Ingredient::SetDef(info); }
    virtual void Damaged(int damage){ Ingredient::Damaged(damage); }
    virtual void Destroy(){ Ingredient::Destroy(); }
    virtual void InitWeaponInfo();
};





#endif  // __INGREDIENT_H__
