//
// Created by soberga on 12.11.22.
//

#ifndef GAME_DEV_TEMPLATE_ANIMATIONNAME_H
#define GAME_DEV_TEMPLATE_ANIMATIONNAME_H

namespace ggj
{

    enum class AnimationName
    {
        None = 0,
        PlayerIdle = 1,
        PlayerWalk = 2,
        PlayerJump = 3,
        PlayerFall = 4,
        EnemyBatMove = 5,
        EnemyBatDead = 6,
        EnemySnakeMove = 7,
        CoinSpin = 8,
        EnemySpiderWalk = 9,
        EnemyThingWalk = 10,
        EnemyGhostFly = 11,
        PortalIdle = 12,
        PortalActive = 13,
        PortalTeleport = 14,
        PortalClosing = 15,
        PortalClosed = 16,
        PlayerIdleNG = 17,
        PlayerWalkNG = 18,
        PowerUpCycle = 21,
        RogueIdle = 24,
        RogueRun = 25,
        RogueDeath = 26,
        RogueAttackSwing = 27,
        RogueAttackStab = 28,
        MageBallFlightYellow = 29,
        MageBallImpactYellow = 30,
        MageBallFlightBlue = 31,
        MageBallImpactBlue = 32,
        MageBallFlightRed = 33,
        MageBallImpactRed = 34,
    };

} // ggj

#endif //GAME_DEV_TEMPLATE_ANIMATIONNAME_H
