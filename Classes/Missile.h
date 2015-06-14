#ifndef __MISSILE_H__
#define __MISSILE_H__

#include "Object.h"

class Missile : public custom::Object
{
public:
    virtual bool init();
    CREATE_FUNC(Missile);

    virtual void SetDef(const DefInfo& info);
    virtual void Damaged(int damage);
    virtual void Destroy();

    void LifeCount();
    

private:
    int m_Count = 3;
};

#endif  // __MISSILE_H__
