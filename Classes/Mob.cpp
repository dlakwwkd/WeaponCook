#include "Mob.h"
#include "GameManager.h"
#include "Ingredient.h"

USING_NS_CC;

bool Mob::init()
{
    if (!Unit::init())
    {
        return false;
    }
    return true;
}

void Mob::SetDef(const UnitInfo& info)
{
    Unit::SetDef(info);
}

void Mob::Damaged(int damage)
{
    Unit::Damaged(damage);
}

void Mob::Destroy()
{
    if (!m_Alive)
    {
        return;
    }
    //     Ingredient::Type type;
//     int n = rand() % 12;
//     if (n < 7)
//     {
//         switch (n)
//         {
//         case 0: type = Ingredient::IT_PORK; break;
//         case 1: type = Ingredient::IT_BEEF; break;
//         case 2: type = Ingredient::IT_WHEAT; break;
//         case 3: type = Ingredient::IT_RICE; break;
//         case 4: type = Ingredient::IT_ONION; break;
//         case 5: type = Ingredient::IT_BEAN; break;
//         case 6: type = Ingredient::IT_PEPPER; break;
//         }
//         GET_OBJ_LAYER->CreateIngredient(type, _position);
//     }
    Unit::Destroy();
}
