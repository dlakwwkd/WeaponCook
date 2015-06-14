#include "GameOverScene.h"

USING_NS_CC;

Scene* GameOverScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameOverScene::create();
    scene->addChild(layer, 0, "over");
    return scene;
}

bool GameOverScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    return true;
}

void GameOverScene::Score(int score)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    char buf1[256];
    std::string string = " == 도달 웨이브 :  ";
    std::string count = _itoa(score, buf1, 10);
    string += count + " == ";

    auto label = Label::createWithSystemFont(string, "Arial", 24);
    label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild(label);

    auto label1 = Label::createWithSystemFont("종료", "Arial", 24);
    auto menuItem1 = MenuItemLabel::create(label1, CC_CALLBACK_1(GameOverScene::Close, this));
    auto menu = Menu::create(menuItem1, NULL);
    menu->alignItemsVertically();
    menu->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 100.0f));
    this->addChild(menu);
}

void GameOverScene::Close(cocos2d::Ref* sender)
{
    Director::getInstance()->popScene();
}
