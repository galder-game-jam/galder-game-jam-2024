#ifndef GAME_DEV_TEMPLATE_PORTAL_H
#define GAME_DEV_TEMPLATE_PORTAL_H

#include "../../graphics/PhysicsSprite.h"
#include "../../managers/AnimationManager.h"
#include "../../interfaces/system/IMapper.h"

namespace ggj
{
    class World;
    class Portal : public PhysicsSprite
    {
        public:
            Portal() = default;
            Portal(ggj::IAnimationManager<ggj::Animation, ggj::AnimationName> &animationManager, IMapper &mapper, b2Body *body, const raylib::Vector2 &physicsSize,
            const raylib::Vector2 &spriteSize,
            const raylib::Rectangle &drawingRect, raylib::Texture * texture, const UserData &userData, const raylib::Vector2 &velocity, int portalTime, World* world, bool isVisible = true)
            : PhysicsSprite(body, physicsSize, spriteSize, drawingRect, texture, userData, isVisible), m_animationManager {animationManager}, m_mapper{mapper},
              m_velocity{velocity}
            {
                m_activationTimeInSeconds = (float)portalTime;
                m_body->SetFixedRotation(true);
                m_animation = m_animationManager.getAnimation(AnimationName::PortalIdle);
                m_body->SetLinearVelocity({m_velocity.x, m_velocity.y});
                m_flip = m_velocity.x < 0.f;
                m_world = world;
            }

            void update(float timeDelta) override;
            void beginContact(PhysicsObject *a, PhysicsObject *b, b2Contact *contact) override;
            [[nodiscard]] float getTimeUntilPortalOpens() const;

        private:
            ggj::World *m_world{nullptr};

            // Activation
            float m_activationTimer{0.f};
            float m_activationTimeInSeconds{0.f};

            //After use
            bool m_hasTeleported = false;
            float m_teleportTime {3.f};

            void activate();
            void teleport();
            void close();

            ggj::IAnimationManager<ggj::Animation, ggj::AnimationName> &m_animationManager;
            IMapper &m_mapper;
            Animation m_animation;
            raylib::Vector2 m_velocity {0.f, 0.f};
    };
} // ggj
#endif //GAME_DEV_TEMPLATE_PORTAL_H