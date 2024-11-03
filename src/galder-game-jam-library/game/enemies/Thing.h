#ifndef GAME_DEV_TEMPLATE_THING_H
#define GAME_DEV_TEMPLATE_THING_H

#include "../../graphics/PhysicsSprite.h"
#include "../../managers/AnimationManager.h"
#include "../../interfaces/system/IMapper.h"

namespace ggj
{
    class Thing : public PhysicsSprite
    {
        public:
            Thing() = default;
            Thing(ggj::IAnimationManager<ggj::Animation, ggj::AnimationName> &animationManager, IMapper &mapper, b2Body *body, const raylib::Vector2 &physicsSize,
                const raylib::Vector2 &spriteSize,
                const raylib::Rectangle &drawingRect, raylib::Texture * texture, const UserData &userData, const raylib::Vector2 &velocity, bool isVisible = true)
                    : PhysicsSprite(body, physicsSize, spriteSize, drawingRect, texture, userData, isVisible), m_animationManager {animationManager}, m_mapper{mapper},
                      m_velocity{velocity}
            {
                m_body->SetGravityScale(1.f);
                m_body->SetFixedRotation(true);
                m_animation = m_animationManager.getAnimation(AnimationName::EnemyThingWalk);
                m_body->SetLinearVelocity({m_velocity.x, m_velocity.y});
                m_flip = m_velocity.x > 0.f;
            }

            void update(float timeDelta) override;
            void beginContact(PhysicsObject *a, PhysicsObject *b, b2Contact *contact) override;

        private:
            void turn();
            ggj::IAnimationManager<ggj::Animation, ggj::AnimationName> &m_animationManager;
            IMapper &m_mapper;
            Animation m_animation;
            raylib::Vector2 m_velocity {0.f, 0.f};
    };
} // ggj
#endif //GAME_DEV_TEMPLATE_THING_H