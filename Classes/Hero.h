#ifndef __HERO_H__
#define __HERO_H__

#include "Unit.h"
#include "Ingredient.h"

class Hero : public Unit
{
public:
    virtual bool init();
    CREATE_FUNC(Hero);

    virtual void SetDef(const UnitInfo& info);
    virtual void Damaged(int damage);
    virtual void Destroy();

    void GetItem(Ingredient* item);

private:
    cocos2d::Vector<Ingredient*> m_Bag;
};

#endif  // __HERO_H__
