//
// Created by soberga on 09.11.24.
//

#include "Projectile.h"

void ggj::Projectile::update(float timeDelta)
{
    m_animation = m_animation;
    PhysicsSprite::update(timeDelta);
    m_timeAlive += timeDelta;
    if(m_timeAlive >= m_timeToLive)
    {
        destroy();
    }
}

void ggj::Projectile::beginContact(PhysicsObject* a, PhysicsObject* b, b2Contact* contact)
{
    PhysicsSprite::beginContact(a, b, contact);
}
