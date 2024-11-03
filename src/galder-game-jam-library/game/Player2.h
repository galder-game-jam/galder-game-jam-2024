//
// Created by robin on 05.11.22.
//

#ifndef GAME_DEV_TEMPLATE_PLAYER2_H
#define GAME_DEV_TEMPLATE_PLAYER2_H

#include "../graphics/PhysicsSprite.h"
#include "../enums/KeyboardKey.h"
#include "../managers/AnimationManager.h"
#include "../enums/PlayerState.h"
#include "../interfaces/system/IMapper.h"

#include "Hitbox.hpp"

namespace ggj
{
    class Player2 : public PhysicsSprite
    {
        public:
            Player2() = default;
            Player2(ggj::IInputManager<ggj::KeyboardKey> &inputManager, ggj::IAnimationManager<ggj::Animation, ggj::AnimationName> &animationManager, IMapper &mapper, b2Body *body, const raylib::Vector2 &physicsSize,
                   const raylib::Vector2 &spriteSize,
                   const raylib::Rectangle &drawingRect, raylib::Texture * texture, const UserData &userData, bool isVisible = true)
            : PhysicsSprite(body, physicsSize, spriteSize, drawingRect, texture, userData, isVisible), m_inputManager {inputManager}, m_animationManager {animationManager}, m_mapper{mapper}
            {
                m_body->SetFixedRotation(true);
                m_animation = m_animationManager.getAnimation(AnimationName::PlayerIdleNG);
                m_startPos = ConvertToVector2(m_body->GetPosition());
                
                //Create hitbox
                raylib::Vector2 hitboxPos = PhysicsObject::ConvertToVector2(m_body->GetPosition());
                hitboxPos = raylib::Vector2(hitboxPos.GetX() + 16, hitboxPos.y);
                m_hitbox.create(this, m_body->GetWorld(), hitboxPos, {16, 16});
            }

            [[nodiscard]] const Vector2 &getVelocity() const;
            [[nodiscard]] bool cameraShouldFollowPlayer() const;
            bool hasClearedLevel() const;
            void setHasClearedLevel(bool hasClearedLevel);
            void beginContact(PhysicsObject *a, PhysicsObject *b, b2Contact *contact) override;
            int getScore();
            void update(float timeDelta) override;
            void draw() override;
            Hitbox *getHitbox();
        
        private:
            void handleInputs(float timeDelta);
            void setPlayerState(PlayerState playerState);

            ggj::IInputManager<ggj::KeyboardKey> &m_inputManager;
            ggj::IAnimationManager<ggj::Animation, ggj::AnimationName> &m_animationManager;
            raylib::Vector2 m_velocity {0.f, 0.f};
            bool m_cameraShouldFollowPlayer {true};
            Animation m_animation;
            IMapper &m_mapper;
            PlayerState m_playerState{PlayerState::Idle};

            raylib::Vector2 m_startPos{};
            bool m_hasClearedLevel {false};
            bool m_isDead {false};
            bool m_isLeftPosition {false};
            
            ggj::Hitbox m_hitbox{};
            bool m_isAttacking {false};
            uint16_t m_attackFrames {20}; //How many frames an attack takes
            uint16_t m_attackCounter {0}; //Counts attack duration
            
            int m_maxJumps{2};
            int m_jumps{0};
            int m_score{0};
    };

} // dev

#endif //GAME_DEV_TEMPLATE_PLAYER2_H
