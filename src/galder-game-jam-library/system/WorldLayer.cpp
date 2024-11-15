//
// Created by robin on 30.10.22.
//

#include "WorldLayer.h"

namespace ggj
{
    int32_t WorldLayer::getLayer() const
    {
        return m_layer;
    }

    void WorldLayer::setLayer(int32_t layer)
    {
        m_layer = layer;
    }

    void WorldLayer::update(float timeDelta)
    {
        if(m_disableUpdate)
            return;

        for(auto &obj : m_gameObjects)
        {
            obj->update(timeDelta);
        }
    }

    void WorldLayer::draw()
    {
        //TODO: REMOVE THIS DISABLE THING! TEMPORARILY ADDED
//        if(m_disableUpdate)
//            return;

        for(auto &obj : m_gameObjects)
        {
            obj->draw();
        }
    }

    void WorldLayer::destroyMarkedObjects()
    {
        std::erase_if(m_gameObjects, [&](auto & item)
        {
            bool shouldDestroy = item->shouldBeDestroyed();
            return shouldDestroy;
        });
    }
} // dev