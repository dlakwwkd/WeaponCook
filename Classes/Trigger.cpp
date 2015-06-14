#include "Trigger.h"
#include "GameManager.h"
#include "Player.h"
#include "UILayer.h"
#include "Unit.h"
#include "GameOverScene.h"

USING_NS_CC;

Trigger* Trigger::s_Trigger = nullptr;

Trigger::Trigger()
{
}

bool Trigger::init()
{
    return true;
}

Trigger::~Trigger()
{
}

Trigger* Trigger::getInstance()
{
    if (!s_Trigger)
    {
        s_Trigger = new (std::nothrow) Trigger();
        CCASSERT(s_Trigger, "FATAL: Not enough memory");
        s_Trigger->init();
    }
    return s_Trigger;
}

void Trigger::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(s_Trigger);
}


void Trigger::GameStart()
{
    TurnStartC();
}

void Trigger::GameOver(Player* losePlayer)
{
    Director::getInstance()->popScene();

    auto scene = GameOverScene::createScene();
    Director::getInstance()->pushScene(scene);

    auto layer = dynamic_cast<GameOverScene*>(scene->getChildByName("over"));
    GET_GM->CallFuncAfter(layer, &GameOverScene::Score, m_WaveCount);
}

void Trigger::TurnChange()
{
    switch (m_NowTurn)
    {
    case Trigger::TURN_CUSTOM: TurnStartA(); break;
    case Trigger::TURN_ATTACK: TurnStartC(); break;
    }
    GET_UI_LAYER->UpdateTurnLabel();
}

void Trigger::TurnStartA()
{
    m_NowTurn = TURN_ATTACK;
    m_WaveCount++;

    auto objLayer = GET_OBJ_LAYER;
    auto mapLayer = GET_MAP_LAYER;
    auto mapSize = mapLayer->GetSize();
    auto randPos = rand() % (int)mapSize.width;
    auto createPos1 = Vec2(mapSize.width - (float)randPos, mapSize.height);

    Unit::Direction dir = Unit::DIR_LEFT;
    if (randPos > mapSize.width / 2)
        dir = Unit::DIR_RIGHT;

    Unit::UnitInfo info;
    info.m_DefInfo.m_ImageName = PATH_IMAGE_UNIT_C;
    info.m_DefInfo.m_CurHp = info.m_DefInfo.m_MaxHp = 50;
    info.m_DefInfo.m_Damage = 10;
    info.m_DefInfo.m_MoveSpeed = 100.0f;
    info.m_Direction = dir;
    info.m_State = Unit::US_STANDBY;

    objLayer->CreateSpaceShip(createPos1, info);
}

void Trigger::TurnStartC()
{
    m_NowTurn = TURN_CUSTOM;
}
