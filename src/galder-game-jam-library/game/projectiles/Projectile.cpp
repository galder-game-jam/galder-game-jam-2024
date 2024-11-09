//
// Created by soberga on 09.11.24.
//

#include "Projectile.h"

void ggj::Projectile::update(float timeDelta)
{
    PhysicsSprite::update(timeDelta);
    m_timeAlive += timeDelta;
    

    if(m_animation.isValid())
    {
        m_animation.update(timeDelta);
        m_drawingRect = m_animation.getDrawingRect();
    }
    
    if(m_isImpactActive)
    {
        if(m_timeAlive >= m_timeToLive)
        {
            destroy();
        }
    }
    else
    {
        if(m_animation.isValid())
        {
            m_animation.update(timeDelta);
            m_drawingRect = m_animation.getDrawingRect();
        }
        
        if(m_timeAlive >= m_timeToLive)
        {
            m_isImpactActive = true;
            m_timeAlive = 0;
            m_velocity.x = 0.f;
            m_velocity.y = 0.f;
            m_animation = m_impactAnimation;
        }
    }
    
}

void ggj::Projectile::beginContact(PhysicsObject* a, PhysicsObject* b, b2Contact* contact)
{
    PhysicsSprite::beginContact(a, b, contact);
}
