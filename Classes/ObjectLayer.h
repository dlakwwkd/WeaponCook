#ifndef __OBJECT_LAYER_H__
#define __OBJECT_LAYER_H__

#include "cocos2d.h"
#include "Player.h"
#include "Hero.h"
#include "Weapon.h"
#include "Ingredient.h"

class ObjectLayer : public cocos2d::Layer
{
public:
    enum
    {
        UNIT_LIST_SIZE_DEF = 100,
    };
public:
	virtual bool init();
    CREATE_FUNC(ObjectLayer);

    void Tick(float dt);
    void Tick2(float dt);

    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    virtual bool onContactBegin(cocos2d::PhysicsContact& contact);

    Hero* GetHero() const { return m_Hero; }

    void CreateOven(const cocos2d::Vec2& pos, Player* owner);
    void CreateHero(const cocos2d::Vec2& pos, Player* owner);
    void CreateUnit(const cocos2d::Vec2& pos, Player* owner, const Unit::UnitInfo& info);
    void CreateSpaceShip(const cocos2d::Vec2& pos, const Unit::UnitInfo& info);
    void CreateMissile(const cocos2d::Vec2& pos, Player* owner, const Weapon::WeaponInfo& info, Unit::Direction dir);
    void CreateLaser(const cocos2d::Vec2& pos, Player* owner, const Weapon::WeaponInfo& info, Unit::Direction dir);
    void CreateWeapon(const Weapon::WeaponInfo& info, Player* owner, Unit* unit);
    void CreateWeaponDefault(Unit* unit);
    void CreateIngredient(Ingredient::Type type, const cocos2d::Vec2& pos);
    void DeleteUnit(Unit* unit);

private:
    void ScreenScroll(float dt);

private:
    Hero*                   m_Hero;
    cocos2d::Vector<Unit*>  m_UnitList;
};

#endif  // __OBJECT_LAYER_H__
