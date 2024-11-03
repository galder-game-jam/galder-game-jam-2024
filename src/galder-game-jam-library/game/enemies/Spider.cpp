#include "Spider.h"

namespace ggj
{
    void Spider::update(float timeDelta)
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

    void Spider::beginContact(PhysicsObject *a, PhysicsObject *b, b2Contact *contact)
    {
        UserData* userDataB = b->getUserData();

        if(userDataB->getCommand() == "enemy_turn")
        {
            turn();
        }
    }

    void Spider::turn()
    {
        m_flip = !m_flip;
        m_velocity = -m_velocity;
    }
} // ggj