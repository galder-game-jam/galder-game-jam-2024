//
// Created by soberga on 12.11.22.
//

#include "Ghost.h"

namespace ggj
{
    void Ghost::move(const raylib::Vector2 &toMove)
    {

    }

    void Ghost::beginContact(PhysicsObject *a, PhysicsObject *b, b2Contact *contact)
    {
        UserData* userDataB = b->getUserData();

        if(userDataB->getCommand() == "enemy_turn")
        {
            turn();
        }
    }

    void Ghost::update(float timeDelta)
    {
        if(m_body == nullptr)
            return;

        m_body->SetLinearVelocity({m_velocity.x, m_velocity.y});

        PhysicsObject::update(timeDelta);

        m_turnTimer += timeDelta;
        if(m_turnTimer > m_turnTriggerValue)
        {
            turn();
            m_turnTimer -= m_turnTriggerValue;
        }

        if(m_animation.isValid())
        {
            m_animation.update(timeDelta);
            m_drawingRect = m_animation.getDrawingRect();
        }
    }

    void Ghost::turn()
    {
        m_flip = !m_flip;
        m_velocity = -m_velocity;
    }
} // ggj