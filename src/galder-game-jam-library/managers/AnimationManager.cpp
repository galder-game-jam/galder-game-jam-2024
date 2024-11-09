//
// Created by soberga on 12.11.22.
//

#include "AnimationManager.h"

namespace ggj
{
    Animation AnimationManager::getAnimation(const AnimationName &id)
    {
        return (m_animations.count(id) > 0) ? m_animations[id] : Animation();
    }

    bool AnimationManager::initialize()
    {
        m_animations[AnimationName::None] =
        {
        raylib::Vector2(32, 32),
     {
                {raylib::Vector2(32 * 0,32), 100},
                {raylib::Vector2(32 * 1,32), 100},
                {raylib::Vector2(32 * 2,32), 100},
                {raylib::Vector2(32 * 3,32), 100},
                {raylib::Vector2(32 * 4,32), 100},
                {raylib::Vector2(32 * 5,32), 100},
                {raylib::Vector2(32 * 6,32), 100},
                {raylib::Vector2(32 * 7,32), 100},
                {raylib::Vector2(32 * 8,32), 100},
                {raylib::Vector2(32 * 9,32), 100},
                {raylib::Vector2(32 * 10,32), 100},
                {raylib::Vector2(32 * 11,32), 100},
                {raylib::Vector2(32 * 12,32), 100},
                {raylib::Vector2(32 * 13,32), 100},
                {raylib::Vector2(32 * 14,32), 100},
                {raylib::Vector2(32 * 15,32), 100},
                {raylib::Vector2(32 * 16,32), 100},
                {raylib::Vector2(32 * 17,32), 100},
                {raylib::Vector2(32 * 18,32), 100},
             }
        };
        m_animations[AnimationName::PlayerIdle] =
        {
        raylib::Vector2(32, 32),
    {
                {raylib::Vector2(32 * 0,32), 100},
            }
        };
        m_animations[AnimationName::PlayerWalk] =
        {
        raylib::Vector2(32, 32),
    {
                {raylib::Vector2(32 * 1,32), 100},
                {raylib::Vector2(32 * 2,32), 100},
                {raylib::Vector2(32 * 3,32), 100},
                {raylib::Vector2(32 * 2,32), 100},
            }
        };
        m_animations[AnimationName::PlayerJump] =
        {
        raylib::Vector2(32, 32),
      {
                {raylib::Vector2(32 * 5,32), 100},
              }
        };
        m_animations[AnimationName::PlayerFall] =
        {
        raylib::Vector2(32, 32),
     {
                {raylib::Vector2(32 * 6,32), 100},
             }
        };
        m_animations[AnimationName::EnemyBatMove] =
        {
        raylib::Vector2(32, 32),
     {
                {raylib::Vector2(32 * 1,32), 100},
                {raylib::Vector2(32 * 2,32), 100},
                {raylib::Vector2(32 * 3,32), 100},
                {raylib::Vector2(32 * 2,32), 100},
             }
        };
        m_animations[AnimationName::EnemyBatDead] =
        {
        raylib::Vector2(32, 32),
     {
                {raylib::Vector2(32 * 0,32), 100},
             }
        };

        m_animations[AnimationName::EnemySnakeMove] =
                {
                        raylib::Vector2(32, 32),
                        {
                                {raylib::Vector2(32 * 0,32 * 3), 100},
                                {raylib::Vector2(32 * 1,32 * 3), 100},
                                {raylib::Vector2(32 * 2,32 * 3), 100},
                                {raylib::Vector2(32 * 3,32 * 3), 100},
                        }
                };

        m_animations[AnimationName::CoinSpin] =
                {
                        raylib::Vector2(16, 16),
                        {
                                {raylib::Vector2(16 * 0,16), 75},
                                {raylib::Vector2(16 * 1,16), 75},
                                {raylib::Vector2(16 * 2,16), 75},
                                {raylib::Vector2(16 * 3,16), 75},
                                {raylib::Vector2(16 * 4,16), 75},
                                {raylib::Vector2(16 * 5,16), 75},
                                {raylib::Vector2(16 * 6,16), 75},
                                {raylib::Vector2(16 * 7,16), 75},
                        }
                };

        m_animations[AnimationName::EnemySpiderWalk] =
                {
                        raylib::Vector2(32, 21),
                        {
                                {raylib::Vector2(32 * 0,21), 70},
                                {raylib::Vector2(32 * 1,21), 70},
                                {raylib::Vector2(32 * 2,21), 70},
                                {raylib::Vector2(32 * 3,21), 70},
                        }
                };

        m_animations[AnimationName::EnemyThingWalk] =
                {
                        raylib::Vector2(33, 45),
                        {
                                {raylib::Vector2(33 * 0,45), 200},
                                {raylib::Vector2(33 * 1,45), 200},
                                {raylib::Vector2(33 * 2,45), 200},
                                {raylib::Vector2(33 * 3,45), 200},
                        }
                };

        m_animations[AnimationName::EnemyGhostFly] =
                {
                        raylib::Vector2(31, 44),
                        {
                                {raylib::Vector2(31 * 0,44), 100},
                                {raylib::Vector2(31 * 1,44), 100},
                                {raylib::Vector2(31 * 2,44), 100},
                                {raylib::Vector2(31 * 3,44), 100},
                        }
                };

        m_animations[AnimationName::PortalActive] =
                {
                        raylib::Vector2(32, 32),
                        {
                                {raylib::Vector2(32 * 0,32), 50},
                                {raylib::Vector2(32 * 1,32), 50},
                                {raylib::Vector2(32 * 2,32), 50},
                                {raylib::Vector2(32 * 3,32), 50},
                                {raylib::Vector2(32 * 4,32), 50},
                                {raylib::Vector2(32 * 5,32), 50},
                                {raylib::Vector2(32 * 6,32), 50},
                                {raylib::Vector2(32 * 7,32), 50},
                                {raylib::Vector2(32 * 8,32), 50},
                                {raylib::Vector2(32 * 9,32), 50},
                                {raylib::Vector2(32 * 10,32), 50},
                                {raylib::Vector2(32 * 11,32), 50},
                                {raylib::Vector2(32 * 12,32), 50},
                                {raylib::Vector2(32 * 13,32), 50},
                                {raylib::Vector2(32 * 14,32), 50},
                                {raylib::Vector2(32 * 15,32), 50},
                                {raylib::Vector2(32 * 16,32), 50},
                        }
                };

        m_animations[AnimationName::PortalTeleport] =
                {
                        raylib::Vector2(32, 32),
                        {
                                {raylib::Vector2(32 * 17,32), 100},
                                {raylib::Vector2(32 * 18,32), 100},
                                {raylib::Vector2(32 * 19,32), 100},
                                {raylib::Vector2(32 * 20,32), 100},
                                {raylib::Vector2(32 * 21,32), 100},
                        }
                };

        m_animations[AnimationName::PortalIdle] =
                {
                        raylib::Vector2(32, 32),
                        {
                                {raylib::Vector2(32 * 16,32), 300},
                                {raylib::Vector2(32 * 0,32), 300},
                                {raylib::Vector2(32 * 1,32), 300},
                                {raylib::Vector2(32 * 0,32), 300},
                        }
                };
        m_animations[AnimationName::PortalClosing] =
                {
                        raylib::Vector2(32, 32),
                        {
                                {raylib::Vector2(32 * 1,32), 300},
                                {raylib::Vector2(32 * 0,32), 300},
                                {raylib::Vector2(32 * 16,32), 10000},
                        }
                };
        m_animations[AnimationName::PortalClosed] =
                {
                        raylib::Vector2(32, 32),
                        {
                                {raylib::Vector2(32 * 16,32), 300},
                        }
                };
        m_animations[AnimationName::PlayerIdleNG] =
                {
                        raylib::Vector2(64, 64),
                        {
                                {raylib::Vector2(64 * 0,0), 100},
                        }
                };
        m_animations[AnimationName::PlayerWalkNG] =
                {
                        raylib::Vector2(46, 50),
                        {
                                {raylib::Vector2(46 * 0, 50 * 3), 100},
                                {raylib::Vector2(46 * 1, 50 * 3), 100},
                                {raylib::Vector2(46 * 2, 50 * 3), 100},
                                {raylib::Vector2(46 * 3, 50 * 3), 100},
                                {raylib::Vector2(46 * 4, 50 * 3), 100},
                                {raylib::Vector2(46 * 5, 50 * 3), 100},
                                {raylib::Vector2(46 * 6, 50 * 3), 100},
                                {raylib::Vector2(46 * 7, 50 * 3), 100},
                        }
                };

        m_animations[AnimationName::PowerUpCycle] =
                {
                        raylib::Vector2(50, 50),
                        {
                                {raylib::Vector2(50 * 0, 50 * 5), 70},
                                {raylib::Vector2(50 * 1, 50 * 5), 70},
                                {raylib::Vector2(50 * 2, 50 * 5), 70},
                                {raylib::Vector2(50 * 3, 50 * 5), 70},
                                {raylib::Vector2(50 * 4, 50 * 5), 70},
                                {raylib::Vector2(50 * 5, 50 * 5), 70},
                                {raylib::Vector2(50 * 6, 50 * 5), 70},
                                {raylib::Vector2(50 * 7, 50 * 5), 70},
                                {raylib::Vector2(50 * 8, 50 * 5), 70},
                                {raylib::Vector2(50 * 9, 50 * 5), 70},
                                {raylib::Vector2(50 * 10, 50 * 5), 70},
                        }
                };

            m_animations[AnimationName::RogueIdle] =
                {
                    raylib::Vector2(64, 64),
                    {
                                {raylib::Vector2(64 * 0, 64 * 1), 100},
                                {raylib::Vector2(64 * 1, 64 * 1), 100},
                                {raylib::Vector2(64 * 2, 64 * 1), 100},
                                {raylib::Vector2(64 * 3, 64 * 1), 100},
                        }
                };

            m_animations[AnimationName::RogueRun] =
                {
                    raylib::Vector2(64, 64),
                    {
                                {raylib::Vector2(64 * 0, 64 * 0), 100},
                                {raylib::Vector2(64 * 1, 64 * 0), 100},
                                {raylib::Vector2(64 * 2, 64 * 0), 100},
                                {raylib::Vector2(64 * 3, 64 * 0), 100},
                                {raylib::Vector2(64 * 4, 64 * 0), 100},
                                {raylib::Vector2(64 * 5, 64 * 0), 100},
                        }
                };

            m_animations[AnimationName::RogueDeath] =
                {
                    raylib::Vector2(64, 64),
                    {
                                {raylib::Vector2(64 * 0, 64 * 2), 100},
                                {raylib::Vector2(64 * 1, 64 * 2), 100},
                                {raylib::Vector2(64 * 2, 64 * 2), 100},
                                {raylib::Vector2(64 * 3, 64 * 2), 100},
                                {raylib::Vector2(64 * 4, 64 * 2), 100},
                                {raylib::Vector2(64 * 5, 64 * 2), 100000},
                        }
                };

            m_animations[AnimationName::RogueAttackStab] =
                {
                    raylib::Vector2(64, 64),
                    {
                                {raylib::Vector2(64 * 0, 64 * 4), 100},
                                {raylib::Vector2(64 * 1, 64 * 4), 200},
                                {raylib::Vector2(64 * 2, 64 * 4), 300},
                                {raylib::Vector2(64 * 3, 64 * 4), 200},
                                {raylib::Vector2(64 * 4, 64 * 4), 100},
                                {raylib::Vector2(64 * 5, 64 * 4), 100},
                        }
                };

            m_animations[AnimationName::RogueAttackSwing] =
                {
                    raylib::Vector2(64, 64),
                    {
                                {raylib::Vector2(64 * 0, 64 * 3), 100},
                                {raylib::Vector2(64 * 1, 64 * 3), 40},
                                {raylib::Vector2(64 * 2, 64 * 3), 40},
                                {raylib::Vector2(64 * 3, 64 * 3), 40},
                                {raylib::Vector2(64 * 4, 64 * 3), 40},
                                {raylib::Vector2(64 * 5, 64 * 3), 40},
                                {raylib::Vector2(64 * 6, 64 * 3), 100},
                        }
                };

            m_animations[AnimationName::MageBallFlightYellow] =
                {
                    raylib::Vector2(16, 16),
                    {
                                {raylib::Vector2(16 * 0, 16 * 0), 50},
                                {raylib::Vector2(16 * 1, 16 * 0), 50},
                        }
                };

            m_animations[AnimationName::MageBallImpactYellow] =
                {
                    raylib::Vector2(16, 16),
                    {
                                {raylib::Vector2(16 * 0, 16 * 1), 50},
                                {raylib::Vector2(16 * 1, 16 * 1), 50},
                                {raylib::Vector2(16 * 2, 16 * 1), 50},
                                {raylib::Vector2(16 * 3, 16 * 1), 50},
                                {raylib::Vector2(16 * 4, 16 * 1), 50},
                                {raylib::Vector2(16 * 5, 16 * 1), 50},
                                {raylib::Vector2(16 * 6, 16 * 1), 50},
                                {raylib::Vector2(16 * 7, 16 * 1), 50},
                                {raylib::Vector2(16 * 8, 16 * 1), 50},
                        }
                };

            m_animations[AnimationName::MageBallFlightBlue] =
                {
                    raylib::Vector2(16, 16),
                    {
                                {raylib::Vector2(16 * 0, 16 * 2), 50},
                                {raylib::Vector2(16 * 1, 16 * 2), 50},
                        }
                };

            m_animations[AnimationName::MageBallImpactBlue] =
                {
                    raylib::Vector2(16, 16),
                    {
                                {raylib::Vector2(16 * 0, 16 * 3), 50},
                                {raylib::Vector2(16 * 1, 16 * 3), 50},
                                {raylib::Vector2(16 * 2, 16 * 3), 50},
                                {raylib::Vector2(16 * 3, 16 * 3), 50},
                                {raylib::Vector2(16 * 4, 16 * 3), 50},
                                {raylib::Vector2(16 * 5, 16 * 3), 50},
                                {raylib::Vector2(16 * 6, 16 * 3), 50},
                                {raylib::Vector2(16 * 7, 16 * 3), 50},
                                {raylib::Vector2(16 * 8, 16 * 3), 50},
                        }
                };

            m_animations[AnimationName::MageBallFlightRed] =
                {
                    raylib::Vector2(16, 16),
                    {
                                {raylib::Vector2(16 * 0, 16 * 4), 50},
                                {raylib::Vector2(16 * 1, 16 * 4), 50},
                        }
                };

            m_animations[AnimationName::MageBallImpactRed] =
                {
                    raylib::Vector2(16, 16),
                    {
                                {raylib::Vector2(16 * 0, 16 * 5), 50},
                                {raylib::Vector2(16 * 1, 16 * 5), 50},
                                {raylib::Vector2(16 * 2, 16 * 5), 50},
                                {raylib::Vector2(16 * 3, 16 * 5), 50},
                                {raylib::Vector2(16 * 4, 16 * 5), 50},
                                {raylib::Vector2(16 * 5, 16 * 5), 50},
                                {raylib::Vector2(16 * 6, 16 * 5), 50},
                                {raylib::Vector2(16 * 7, 16 * 5), 50},
                                {raylib::Vector2(16 * 8, 16 * 5), 50},
                        }
                };
        return true;
    }
} // ggj