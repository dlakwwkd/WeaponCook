#ifndef __LASER_H__
#define __LASER_H__

#include "Object.h"

class Laser : public custom::Object
{
public:
    virtual bool init();
    CREATE_FUNC(Laser);

    virtual void SetDef(const DefInfo& info);
    virtual void Damaged(int damage);
    virtual void Destroy();

    void LifeCount();
    

private:
    int m_Count = 3;
};

#endif  // __LASER_H__
