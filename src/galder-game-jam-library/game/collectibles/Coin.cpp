//
// Created by soberga on 12.11.22.
//

#include "Coin.h"

namespace ggj
{
    void Coin::beginContact(PhysicsObject *a, PhysicsObject *b, b2Contact *contact)
    {
        UserData* userDataB = b->getUserData();

        if(userDataB->getObjectType() == ObjectType::Player)
        {
            a->destroy();
        }
    }

    void Coin::update(float timeDelta)
    {
        if(m_body == nullptr)
            return;

        m_body->SetLinearVelocity({m_velocity.x, m_velocity.y});

        PhysicsObject::update(timeDelta);

        if(m_animation.isValid())
        {
            m_animation.update(timeDelta);
            m_drawingRect = m_animation.getDrawingRect();
        }
    }
} // ggj