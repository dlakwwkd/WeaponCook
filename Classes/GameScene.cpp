#include "GameScene.h"
#include "PhysicsLayer.h"
#include "UILayer.h"
#include "GameManager.h"
#include "Trigger.h"
#include "Player.h"
#include "TextDefine.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
    scene->getPhysicsWorld()->setGravity(Vect(0.0f, -1000.0f));

    auto layer = GameScene::create();
    auto layer2 = PhysicsLayer::create();
    auto layer3 = UILayer::create();
    layer2->setPhyWorld(scene->getPhysicsWorld());

    scene->addChild(layer, 0, GAME_SCENE);
    layer->addChild(layer2, 0, PHYSICS_LAYER);
    layer->addChild(layer3, 1, UI_LAYER);
    return scene;
}

bool GameScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    InitPlayers();
    InitDefInfoList();
    GET_GM->CallFuncAfter(this, &GameScene::InitGameState);
    return true;
}

GameScene::~GameScene()
{
    GameManager::destroyInstance();
    Trigger::destroyInstance();
    CC_SAFE_RELEASE(m_Player);
    CC_SAFE_RELEASE(m_Enemy);
}

void GameScene::InitPlayers()
{
    m_Player = Player::create();
    m_Player->SetType(Player::PT_HUMAN);

    m_Enemy = Player::create();
    m_Enemy->SetType(Player::PT_COMPUTER);

    CC_SAFE_RETAIN(m_Player);
    CC_SAFE_RETAIN(m_Enemy);
}

void GameScene::InitDefInfoList()
{
    
}


void GameScene::InitGameState()
{
    auto objLayer = GET_OBJ_LAYER;
    auto mapLayer = GET_MAP_LAYER;
    auto mapImage = static_cast<Sprite*>(mapLayer->getChildByName(SPRITE_MAP_IMAGE));
    auto mapSize = mapImage->getContentSize();
    auto createPos1 = Vec2(mapSize.width / 2, mapLayer->GetGroundHeight());

    objLayer->CreateOven(createPos1, m_Player);
    objLayer->CreateHero(createPos1, m_Player);

    Trigger::getInstance()->GameStart();
}
