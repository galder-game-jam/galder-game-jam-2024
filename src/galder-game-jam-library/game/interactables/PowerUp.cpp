#include "PowerUp.h"

namespace ggj
{
    void PowerUp::beginContact(PhysicsObject *a, PhysicsObject *b, b2Contact *contact)
    {
        if(b->getUserData()->getObjectType() == ObjectType::Player)
        {
            a->destroy();
        }
    }

    void PowerUp::update(float timeDelta)
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