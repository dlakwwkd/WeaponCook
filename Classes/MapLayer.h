#ifndef __MAP_LAYER_H__
#define __MAP_LAYER_H__

#include "cocos2d.h"

class MapLayer : public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(MapLayer);

    inline float GetGroundHeight() const { return m_GroundHeight; }
    inline cocos2d::Size GetSize() const { return m_MapSize; }

private:
    float m_GroundHeight = 0;
    cocos2d::Size m_MapSize;
};

#endif  // __MAP_LAYER_H__
