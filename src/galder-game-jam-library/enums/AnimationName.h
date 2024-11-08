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
        PlayerJumpNG = 19,
        PlayerFallNG = 20,
        PowerUpCycle = 21,
        PlayerAttackGroundedNG = 22,
        PlayerAttackAirNG = 23,
        RogueIdle = 24,
        RogueRun = 25,
        RogueDeath = 26,
    };

} // ggj

#endif //GAME_DEV_TEMPLATE_ANIMATIONNAME_H
