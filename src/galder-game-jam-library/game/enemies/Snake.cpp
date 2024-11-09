#include "Snake.h"
#include "../projectiles/Projectile.h"

namespace ggj
{
    void Snake::update(float timeDelta)
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

    void Snake::beginContact(PhysicsObject *a, PhysicsObject *b, b2Contact *contact)
    {
        UserData* userDataB = b->getUserData();

        if(userDataB->getCommand() == "enemy_turn")
        {
            turn();
        }
        else if(userDataB->getObjectType() == ObjectType::Player)
        {
            b2Body *body = b->getBody();
            const auto playerVelocity = b->getVelocity();

            if(m_velocity.x != 0.f)
            {
                if(m_velocity.x < 0.f && playerVelocity.x < 0.f)
                    body->ApplyLinearImpulseToCenter({50.f, 0.f}, true);
                else if(m_velocity.x > 0.f && playerVelocity.x > 0.f)
                    body->ApplyLinearImpulseToCenter({-50.f, 0.f}, true);
                else
                    body->ApplyLinearImpulseToCenter({m_velocity.x < 0.f ? -50.f : 50.f, 0.f}, true);
            }
            if(m_velocity.y != 0.f)
            {
                if(m_velocity.y < 0.f && playerVelocity.y < 0.f)
                    body->ApplyLinearImpulseToCenter({0.f, 50.f}, true);
                else if(m_velocity.y > 0.f && playerVelocity.y > 0.f)
                    body->ApplyLinearImpulseToCenter({0.f, -50.f}, true);
                else
                    body->ApplyLinearImpulseToCenter({0.f, m_velocity.y < 0.f ? -50.f : 50.f}, true);
            }
        }
        else if(userDataB->getObjectType() == ObjectType::Projectile)
        {
            destroy();
            Projectile *p = dynamic_cast<Projectile*>(b);
            p->explode();
        }
    }

    void Snake::turn()
    {
        m_flip = !m_flip;
        m_velocity = -m_velocity;
    }
} // ggj