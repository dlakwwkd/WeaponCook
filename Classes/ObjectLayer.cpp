#include "ObjectLayer.h"
#include "GameManager.h"
#include "Player.h"
#include "Oven.h"
#include "Trigger.h"
#include "Mob.h"
#include "SpaceShip.h"
#include "Ingredient.h"
#include "Laser.h"

USING_NS_CC;

bool ObjectLayer::init()
{
	if (!Layer::init())
	{
		return false;
    }
    m_UnitList.reserve(UNIT_LIST_SIZE_DEF);

    auto keyListener = EventListenerKeyboard::create();
    keyListener->onKeyPressed = CC_CALLBACK_2(ObjectLayer::onKeyPressed, this);
    keyListener->onKeyReleased = CC_CALLBACK_2(ObjectLayer::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(ObjectLayer::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    this->schedule(schedule_selector(ObjectLayer::Tick));
    this->schedule(schedule_selector(ObjectLayer::Tick2), 1.0f);
	return true;
}

void ObjectLayer::Tick(float dt)
{
    ScreenScroll(dt);
}

void ObjectLayer::Tick2(float dt)
{
    for (auto& unit : m_UnitList)
    {
        unit->AI();
    }
    Trigger::getInstance()->TurnChange();
}

void ObjectLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    GET_IM->SetKeyStatus(keyCode, true);
    if (keyCode == KEY_LEFT_ARROW)
    {
        m_Hero->SetDir(Unit::DIR_LEFT);
        m_Hero->Move();
    }
    if (keyCode == KEY_RIGHT_ARROW)
    {
        m_Hero->SetDir(Unit::DIR_RIGHT);
        m_Hero->Move();
    }
    if (keyCode == KEY_Z)
        m_Hero->Attack();
    if (keyCode == KEY_X)
        m_Hero->Jump();
    if (keyCode == KEY_SHIFT)
        m_Hero->ChangeWeapon();
}

void ObjectLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    GET_IM->SetKeyStatus(keyCode, false);
    if (keyCode == KEY_LEFT_ARROW || keyCode == KEY_RIGHT_ARROW)
    {
        m_Hero->Stop();
        if (GET_IM->GetKeyStatus(KEY_RIGHT_ARROW) || GET_IM->GetKeyStatus(KEY_LEFT_ARROW))
            m_Hero->Move();
    }
}

bool ObjectLayer::onContactBegin(PhysicsContact& contact)
{
    auto objectA = static_cast<custom::Object*>(contact.getShapeA()->getBody()->getNode());
    auto objectB = static_cast<custom::Object*>(contact.getShapeB()->getBody()->getNode());

    if (!objectA || !objectB || !objectA->GetOwner() || !objectB->GetOwner())
    {
        return false;
    }
    if (objectA->GetOwner()->GetType() != objectB->GetOwner()->GetType())
    {
        objectA->Damaged(objectB->GetDefInfo().m_Damage);
        objectB->Damaged(objectA->GetDefInfo().m_Damage);
    }
    return true;
}

void ObjectLayer::CreateOven(const Vec2& pos, Player* owner)
{
    Unit::DefInfo info;
    info.m_ImageName = PATH_IMAGE_CASTLE;
    info.m_CurHp = info.m_MaxHp = 200;
    info.m_Damage = 50;
    info.m_MoveSpeed = 0.0f;

    auto oven = Oven::create();
    oven->SetDef(info);
    oven->SetOwner(owner);
    oven->setPosition(Vec2(pos.x, pos.y + oven->getContentSize().height / 2 + 3.0f));
    this->addChild(oven);
}

void ObjectLayer::CreateHero(const cocos2d::Vec2& pos, Player* owner)
{
    Hero::UnitInfo info;
    info.m_DefInfo.m_ImageName = PATH_IMAGE_UNIT_B;
    info.m_DefInfo.m_CurHp = info.m_DefInfo.m_MaxHp = 100;
    info.m_DefInfo.m_Damage = 10;
    info.m_DefInfo.m_MoveSpeed = 250.0f;
    info.m_Direction = Unit::DIR_LEFT;
    info.m_State = Unit::US_STANDBY;

    auto hero = Hero::create();
    hero->SetDef(info);
    hero->SetOwner(owner);
    hero->setPosition(Vec2(pos.x, pos.y + hero->getContentSize().height / 2));
    this->addChild(hero);

    m_Hero = hero;
    CreateWeaponDefault(hero);
}

void ObjectLayer::CreateUnit(const Vec2& pos, Player* owner, const Unit::UnitInfo& info)
{
    auto unit = Mob::create();
    unit->SetDef(info);
    unit->SetOwner(owner);
    unit->setPosition(Vec2(pos.x, pos.y + unit->getContentSize().height / 2));
    unit->setScale(0.5f);
    unit->Move();
    this->addChild(unit);

    m_UnitList.pushBack(unit);
}

void ObjectLayer::CreateSpaceShip(const cocos2d::Vec2& pos, const Unit::UnitInfo& info)
{
    Unit::DefInfo defInfo;
    defInfo.m_ImageName = PATH_IMAGE_SPACE_SHIP2;
    defInfo.m_CurHp = defInfo.m_MaxHp = 100;
    defInfo.m_Damage = 0;
    defInfo.m_MoveSpeed = 0.0f;

    auto ship = SpaceShip::create();
    ship->SetDef(defInfo);
    ship->SetOwner(GET_GAME_SCENE->GetEnemy());
    ship->setPosition(Vec2(pos.x, pos.y - ship->getContentSize().height / 2));
    ship->setScale(0.5f);
    this->addChild(ship);

    ship->PushUnit(info);

    GET_GM->CallFuncAfter(3.0f, ship, &SpaceShip::CreateUnit);
}

void ObjectLayer::CreateMissile(const cocos2d::Vec2& pos, Player* owner, const Weapon::WeaponInfo& info, Unit::Direction dir)
{
    auto speed = info.m_Speed;
    if (dir == Unit::DIR_LEFT)
        speed = -speed;

    auto physicsLayer = this->getParent();
    auto layerPos = physicsLayer->getPositionX();

    auto missile = Missile::create();
    missile->SetDef(info.m_DefInfo);
    missile->SetOwner(owner);
    missile->setPosition(Vec2(pos.x - layerPos, pos.y));
    missile->setScale(info.m_Size);
    missile->getPhysicsBody()->setVelocity(Vec2(speed, 0));
    this->addChild(missile);
}

void ObjectLayer::CreateLaser(const cocos2d::Vec2& pos, Player* owner, const Weapon::WeaponInfo& info, Unit::Direction dir)
{
    auto speed = info.m_Speed;
    if (dir == Unit::DIR_LEFT)
        speed = -speed;

    auto physicsLayer = this->getParent();
    auto layerPos = physicsLayer->getPositionX();

    auto missile = Laser::create();
    missile->SetDef(info.m_DefInfo);
    missile->SetOwner(owner);
    missile->setPosition(Vec2(pos.x - layerPos, pos.y));
    missile->setScale(info.m_Size);
    missile->getPhysicsBody()->setVelocity(Vec2(speed, 0));
    this->addChild(missile);
}

void ObjectLayer::CreateWeapon(const Weapon::WeaponInfo& info, Player* owner, Unit* unit)
{
    auto weapon = Weapon::create();
    weapon->SetDef(info);
    weapon->SetOwner(owner);
    weapon->SetIcon(info.m_IconImage);
    this->addChild(weapon);

    unit->PushWeapon(weapon);
}

void ObjectLayer::CreateWeaponDefault(Unit* unit)
{
    Weapon::DefInfo definfo;
    definfo.m_ImageName = PATH_IMAGE_MISSILE_A;
    definfo.m_CurHp = definfo.m_MaxHp = 0;
    definfo.m_Damage = 20;
    definfo.m_MoveSpeed = 400.0f;

    Weapon::WeaponInfo weaponInfo;
    weaponInfo.m_IconImage = PATH_IMAGE_ICON1;
    weaponInfo.m_AttackType = Weapon::AT_MISSILE;
    weaponInfo.m_Count = 810;
    weaponInfo.m_Size = 1.0f;
    weaponInfo.m_Damage = definfo.m_Damage;
    weaponInfo.m_Speed = definfo.m_MoveSpeed;
    weaponInfo.m_DefInfo = definfo;

    CreateWeapon(weaponInfo, unit->GetOwner(), unit);

    weaponInfo.m_IconImage = PATH_IMAGE_ICON2;
    weaponInfo.m_DefInfo.m_ImageName = PATH_IMAGE_LASIER_A;
    weaponInfo.m_DefInfo.m_CurHp = weaponInfo.m_DefInfo.m_MaxHp = 50;
    weaponInfo.m_AttackType = Weapon::AT_LASIER;
    weaponInfo.m_Count = 90;
    weaponInfo.m_Size = 0.3f;
    weaponInfo.m_Damage = 15;
    weaponInfo.m_Speed = 500.0f;

    CreateWeapon(weaponInfo, unit->GetOwner(), unit);

    weaponInfo.m_IconImage = PATH_IMAGE_ICON3;
    weaponInfo.m_DefInfo.m_ImageName = PATH_IMAGE_LASIER_B;
    weaponInfo.m_DefInfo.m_CurHp = weaponInfo.m_DefInfo.m_MaxHp = 30;
    weaponInfo.m_AttackType = Weapon::AT_LASIER;
    weaponInfo.m_Count = 270;
    weaponInfo.m_Size = 1.5f;
    weaponInfo.m_Damage = 30;
    weaponInfo.m_Speed = 150.0f;

    CreateWeapon(weaponInfo, unit->GetOwner(), unit);

    weaponInfo.m_IconImage = PATH_IMAGE_ICON4;
    weaponInfo.m_DefInfo.m_ImageName = PATH_IMAGE_MISSILE_B;
    weaponInfo.m_DefInfo.m_CurHp = weaponInfo.m_DefInfo.m_MaxHp = 30;
    weaponInfo.m_AttackType = Weapon::AT_MISSILE;
    weaponInfo.m_Count = 30;
    weaponInfo.m_Size = 0.8f;
    weaponInfo.m_Damage = 45;
    weaponInfo.m_Speed = 350.0f;

    CreateWeapon(weaponInfo, unit->GetOwner(), unit);
}

void ObjectLayer::CreateIngredient(Ingredient::Type type, const Vec2& pos)
{
    Ingredient* item;
    Ingredient::DefInfo def;
    switch (type)
    {
    case Ingredient::IT_PORK:   item = Pork::create();      item->SetDef(def);  item->InitWeaponInfo(); break;
    case Ingredient::IT_BEEF:   item = Beef::create();      item->SetDef(def);  item->InitWeaponInfo(); break;
    case Ingredient::IT_WHEAT:  item = Wheat::create();     item->SetDef(def);  item->InitWeaponInfo(); break;
    case Ingredient::IT_RICE:   item = Rice::create();      item->SetDef(def);  item->InitWeaponInfo(); break;
    case Ingredient::IT_ONION:  item = Onion::create();     item->SetDef(def);  item->InitWeaponInfo(); break;
    case Ingredient::IT_BEAN:   item = Bean::create();      item->SetDef(def);  item->InitWeaponInfo(); break;
    case Ingredient::IT_PEPPER: item = Pepper::create();    item->SetDef(def);  item->InitWeaponInfo(); break;
    default:
        return;
    }

    auto physicsLayer = this->getParent();
    auto layerPos = physicsLayer->getPositionX();
    item->setPosition(Vec2(pos.x - layerPos, pos.y));

    this->addChild(item);
}

void ObjectLayer::DeleteUnit(Unit* unit)
{
    auto iter = m_UnitList.find(unit);
    m_UnitList.erase(iter);

}


void ObjectLayer::ScreenScroll(float dt)
{
    auto screenSize = Director::getInstance()->getVisibleSize();
    auto leftSide = screenSize.width / 3;
    auto rightSide = screenSize.width - leftSide;

    auto physicsLayer = this->getParent();
    auto layerPos = physicsLayer->getPositionX();
    auto heroPos = m_Hero->getPositionX() + layerPos;
    auto moveSpeed = m_Hero->GetDefInfo().m_MoveSpeed * dt;

    if (heroPos < leftSide)
        physicsLayer->setPositionX(layerPos + moveSpeed);
    else if (heroPos > rightSide)
        physicsLayer->setPositionX(layerPos - moveSpeed);
}
