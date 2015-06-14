#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"

class Player : public cocos2d::Ref
{
public:
    enum Type
    {
        PT_NONE,
        PT_HUMAN,
        PT_COMPUTER,
    };
public:
    virtual bool init();
    CREATE_FUNC(Player);

    inline void             SetType(const Type& type){ m_Type = type; }
    inline const Type&      GetType() const { return m_Type; }

private:
    Type    m_Type = PT_NONE;

};

#endif  // __PLAYER_H__
