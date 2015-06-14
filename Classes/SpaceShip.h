#ifndef __SPACE_SHIP_H__
#define __SPACE_SHIP_H__

#include "Object.h"
#include "Unit.h"

class SpaceShip : public custom::Object
{
public:
    virtual bool init();
    CREATE_FUNC(SpaceShip);

    virtual void    SetDef(const DefInfo& info);
    virtual void    Damaged(int damage);
    virtual void    Destroy();

    inline void     PushUnit(const Unit::UnitInfo& info) { m_UnitInfoList.push_back(info); }
    void            CreateUnit();

protected:
    std::vector<Unit::UnitInfo> m_UnitInfoList;
};

#endif  // __SPACE_SHIP_H__
