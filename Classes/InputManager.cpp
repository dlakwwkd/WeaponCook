#include "InputManager.h"

USING_NS_CC;

InputManager* InputManager::s_InputManager = nullptr;

InputManager::InputManager()
{
}

bool InputManager::init()
{
    m_MouseLocation = Vec2::ZERO;
    m_MouseStatus[MOUSE_BUTTON_LEFT] = false;
    m_MouseStatus[MOUSE_BUTTON_RIGHT] = false;
    return true;
}

InputManager::~InputManager()
{
}

InputManager* InputManager::getInstance()
{
    if (!s_InputManager)
    {
        s_InputManager = new (std::nothrow) InputManager();
        CCASSERT(s_InputManager, "FATAL: Not enough memory");
        s_InputManager->init();
    }
    return s_InputManager;
}

void InputManager::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(s_InputManager);
}
