#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

#include "cocos2d.h"

#define KEY_ENTER			cocos2d::EventKeyboard::KeyCode::KEY_ENTER
#define KEY_SPACE			cocos2d::EventKeyboard::KeyCode::KEY_SPACE
#define KEY_UP_ARROW		cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW
#define KEY_DOWN_ARROW		cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW
#define KEY_LEFT_ARROW		cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW
#define KEY_RIGHT_ARROW		cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW
#define KEY_SHIFT			cocos2d::EventKeyboard::KeyCode::KEY_SHIFT
#define KEY_Z				cocos2d::EventKeyboard::KeyCode::KEY_Z
#define KEY_X				cocos2d::EventKeyboard::KeyCode::KEY_X

class InputManager : public cocos2d::Ref
{
public:
    static InputManager* getInstance();
    static void destroyInstance();

    virtual bool init();
    virtual ~InputManager();

    cocos2d::Vec2	GetMouseLocation()								                { return m_MouseLocation; }
    bool	        GetMouseStatus(int button)								        { return m_MouseStatus[button]; }
    bool	        GetKeyStatus(cocos2d::EventKeyboard::KeyCode key)				{ return m_KeyStatus[key]; }

    void	        SetMouseLocation(cocos2d::Vec2 p)						        { m_MouseLocation = p; }
    void	        SetMouseStatus(int button, bool status)					        { m_MouseStatus[button] = status; }
    void	        SetKeyStatus(cocos2d::EventKeyboard::KeyCode key, bool status)	{ m_KeyStatus[key] = status; }

private:
    InputManager();
    static InputManager* s_InputManager;

    cocos2d::Vec2							        m_MouseLocation;
    std::map<int, bool>						        m_MouseStatus;
    std::map<cocos2d::EventKeyboard::KeyCode, bool>	m_KeyStatus;
};

#endif  // __INPUT_MANAGER_H__
