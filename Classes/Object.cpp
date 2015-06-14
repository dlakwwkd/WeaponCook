#include "Object.h"
#include "GameManager.h"

USING_NS_CC;

bool custom::Object::init()
{
    if (!Sprite::init())
    {
        return false;
    }
    return true;
}

void custom::Object::SetDef(const DefInfo& info)
{
    SetDefInfo(info);
    setTexture(m_DefInfo.m_ImageName);
    auto body = PhysicsBody::createBox(_contentSize);
    body->setRotationEnable(false);
    setPhysicsBody(body);
}

void custom::Object::Damaged(int damage)
{
    m_DefInfo.m_CurHp -= damage;
    if (m_DefInfo.m_CurHp <= 0)
    {
        m_DefInfo.m_CurHp = 0;
        Destroy();
    }
    else
        UpdateHpBar();
}

void custom::Object::Destroy()
{
    m_Alive = false;
    GET_GM->CallFuncAfter(GET_OBJ_LAYER, &ObjectLayer::removeChild, this, true);
}

void custom::Object::SetHpBar(const std::string& image)
{
    m_HpBar = Sprite::create(image);
    m_HpBar->setAnchorPoint(Vec2(0, 0.5f));
    m_HpBar->setPosition(Vec2(-1.0f, _contentSize.height + 5.0f));
    this->addChild(m_HpBar);
}

void custom::Object::UpdateHpBar()
{
    if (m_HpBar)
    {
        m_HpBar->setScaleX((float)m_DefInfo.m_CurHp / m_DefInfo.m_MaxHp);
    }
}
