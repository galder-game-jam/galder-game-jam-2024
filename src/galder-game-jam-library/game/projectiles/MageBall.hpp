#ifndef MAGEBALL_HPP
#define MAGEBALL_HPP
#include "Projectile.h"

namespace ggj
{
    class MageBall : public Projectile
    {
        public:
            MageBall(IAnimationManager<Animation, AnimationName>& animationManager, IMapper& mapper, b2Body* body,
                const raylib::Vector2& physicsSize, const raylib::Vector2& spriteSize, const raylib::Rectangle& drawingRect,
                raylib::Texture* texture, const UserData& userData, const raylib::Vector2& velocity,
                World* world, float timeToLive, bool isVisible)
                : Projectile(
                    animationManager, mapper, body, physicsSize, spriteSize, drawingRect, texture, userData, velocity,
                     world, timeToLive, isVisible)
            {
                m_animation = m_animationManager.getAnimation(AnimationName::MageBallFlightRed);
                m_impactAnimation = m_animationManager.getAnimation(AnimationName::MageBallImpactRed);
            }
            
            
            
            // static constexpr raylib::Vector2 DEFAULT_SIZE {16.f, 16.f};
            // static constexpr raylib::Vector2 DEFAULT_VELOCITY {25.f, 0.f};
            static constexpr float DEFAULT_SPEED {25.f};
            static constexpr float DEFAULT_TTL {1.f};
    };
}
#endif // MAGEBALL_HPP
