#include "UILayer.h"
#include "GameManager.h"
#include "Trigger.h"
#include "Player.h"
#include "Oven.h"
#include "Weapon.h"
#include "Hero.h"
#include "TextDefine.h"

USING_NS_CC;

bool UILayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto label2 = Label::createWithSystemFont(" [ 진행 웨이브 : 0 ]", "Arial", 15);
    label2->setColor(Color3B::BLACK);
    label2->setAnchorPoint(Vec2(0, 0.5f));
    label2->setPosition(Vec2(origin.x, origin.y + visibleSize.height - label2->getContentSize().height));
    this->addChild(label2, 0, LABEL_TURN);

    auto turnButton = MenuItemImage::create(
        PATH_IMAGE_TURN_BUTTON,
        PATH_IMAGE_TURN_BUTTON_PUSH,
        CC_CALLBACK_1(UILayer::TurnOver, this));
    turnButton->setPosition(Vec2(origin.x + visibleSize.width - turnButton->getContentSize().width / 2, origin.y + visibleSize.height / 2));

    auto closeButton = MenuItemImage::create(
        PATH_IMAGE_CLOSE_BUTTON,
        PATH_IMAGE_CLOSE_BUTTON_PUSH,
        CC_CALLBACK_1(UILayer::OutGame, this));
    closeButton->setPosition(Vec2(origin.x + visibleSize.width - closeButton->getContentSize().width / 2, origin.y + closeButton->getContentSize().height / 2));

    auto menu = Menu::create(turnButton, closeButton, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto icon = Sprite::create(PATH_IMAGE_ICON0);
    icon->setPosition(Vec2(origin.x + visibleSize.width / 2 - 60.0f, origin.y + 40.0f));
    icon->setVisible(false);
    this->addChild(icon, 1, "icon");

    return true;
}


void UILayer::TurnOver(Ref* sender)
{
    switch (Trigger::getInstance()->GetNowTurn())
    {
    case Trigger::TURN_ATTACK: Trigger::getInstance()->TurnChange();  break;
    case Trigger::TURN_CUSTOM: Trigger::getInstance()->TurnChange();  break;
    }
}

void UILayer::OutGame(Ref* sender)
{
    Director::getInstance()->popScene();
}


void UILayer::UpdateTurnLabel()
{
    auto label = static_cast<Label*>(this->getChildByName(LABEL_TURN));
    if (label)
    {
        char buf1[256];
        std::string string = " [ 진행 웨이브 : ";
        std::string count = _itoa(Trigger::getInstance()->GetCount(), buf1, 10);
        string += count + " ]";
        label->setString(string);
    }
}

void UILayer::Shoot()
{
    auto icon = static_cast<Sprite*>(this->getChildByName("icon"));
    icon->setVisible(true);
    GET_GM->CallFuncAfter(0.05f, icon, &Sprite::setVisible, false);
}

void UILayer::ShowIcon()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto hero = GET_OBJ_LAYER->GetHero();
    auto queue = hero->m_WeaponQueue;

    int i = 0;
    float gap = 55.0f;
    while (!queue.empty())
    {
        auto weapon = queue.front();
        auto icon = weapon->GetIcon();
        auto pos = Vec2(origin.x + visibleSize.width / 2 - 60.0f + i++*gap, origin.y + 40.0f);
        icon->setPosition(pos);
        queue.pop();
    }
}
