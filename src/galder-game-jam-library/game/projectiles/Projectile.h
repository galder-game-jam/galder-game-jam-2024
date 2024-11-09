#ifndef GAME_DEV_TEMPLATE_PROJECTILE_H
#define GAME_DEV_TEMPLATE_PROJECTILE_H

#include "../../graphics/PhysicsSprite.h"
#include "../../managers/AnimationManager.h"
#include "../../interfaces/system/IMapper.h"

namespace ggj
{
    class World;
    class Projectile : public PhysicsSprite
    {
        public:
            Projectile(IAnimationManager<Animation, AnimationName> &animationManager, IMapper &mapper, b2Body *body, const raylib::Vector2 &physicsSize,
            const raylib::Vector2 &spriteSize,
            const raylib::Rectangle &drawingRect, raylib::Texture * texture, const UserData &userData, const raylib::Vector2 &velocity, World* world,
            float timeToLive, bool isVisible = true)
            : PhysicsSprite(body, physicsSize, spriteSize, drawingRect, texture, userData, isVisible), m_animationManager {animationManager}, m_mapper{mapper},
              m_velocity{velocity}, m_timeToLive{timeToLive}
            {
                m_body->SetFixedRotation(true);
                m_body->SetLinearVelocity({m_velocity.x, m_velocity.y});
                m_world = world;
            }
    
            void update(float timeDelta) override;
            void beginContact(PhysicsObject *a, PhysicsObject *b, b2Contact *contact) override;
    
        protected:
            World *m_world{nullptr};
    
            float m_timeToLive {};
            float m_timeAlive {};
            bool m_isImpactActive{};
    
            IAnimationManager<Animation, AnimationName> &m_animationManager;
            IMapper &m_mapper;
            Animation m_animation;
            Animation m_impactAnimation;
            raylib::Vector2 m_velocity {0.f, 0.f};
    };
} // ggj
#endif //GAME_DEV_TEMPLATE_PROJECTILE_H