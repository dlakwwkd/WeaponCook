#ifndef __MOB_H__
#define __MOB_H__

#include "Unit.h"

class Mob : public Unit
{
public:
    virtual bool init();
    CREATE_FUNC(Mob);

    virtual void SetDef(const UnitInfo& info);
    virtual void Damaged(int damage);
    virtual void Destroy();


};

#endif  // __MOB_H__
