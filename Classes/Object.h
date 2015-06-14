#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "cocos2d.h"

class Player;

namespace custom
{
    class Object : public cocos2d::Sprite
    {
    public:
        enum Type   // for Bitmask
        {
            OBJ_ALL         = -1,   // 0xFFFFFFFF
            OBJ_DEF         = 0x01, // 00001
            OBJ_UNIT        = 0x02, // 00010
            OBJ_MISSILE     = 0x04, // 00100
            OBJ_LASER       = 0x08, // 01000
        };
        struct DefInfo
        {
            std::string m_ImageName = "";
            int         m_MaxHp = 0;
            int         m_CurHp = 0;
            int         m_Damage = 0;
            float       m_MoveSpeed = 0.0f;
        };
    public:
        virtual bool init();
        CREATE_FUNC(Object);

        inline void             SetOwner(Player* owner){ m_Owner = owner; }
        inline Player*          GetOwner() const { return m_Owner; }
        inline void             SetDefInfo(const DefInfo& info){ m_DefInfo = info; }
        inline const DefInfo&   GetDefInfo() const { return m_DefInfo; }
        inline bool             IsAlive() const { return m_Alive; }

        virtual void SetDef(const DefInfo& info);
        virtual void Damaged(int damage);
        virtual void Destroy();

        void SetHpBar(const std::string& image);
        void UpdateHpBar();

    protected:
        Player* m_Owner = nullptr;
        DefInfo m_DefInfo;
        Sprite* m_HpBar = nullptr;
        bool    m_Alive = true;
    };
}

#endif  // __OBJECT_H__
