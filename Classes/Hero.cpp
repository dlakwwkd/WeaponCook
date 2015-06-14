#include "Hero.h"
#include "GameManager.h"

USING_NS_CC;

bool Hero::init()
{
    if (!Unit::init())
    {
        return false;
    }
    return true;
}

void Hero::SetDef(const UnitInfo& info)
{
    Unit::SetDef(info);
}

void Hero::Damaged(int damage)
{
    Unit::Damaged(damage);
}

void Hero::Destroy()
{
    Unit::Destroy();
}

void Hero::GetItem(Ingredient* item)
{
    m_Bag.pushBack(item);
}
