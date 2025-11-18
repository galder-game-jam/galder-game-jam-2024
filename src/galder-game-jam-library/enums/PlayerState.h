//
// Created by soberga on 12.11.22.
//

#ifndef GAME_DEV_TEMPLATE_PLAYERSTATE_H
#define GAME_DEV_TEMPLATE_PLAYERSTATE_H

namespace ggj
{

    enum class PlayerState
    {
        Idle = 0,
        Walk = 1,
        AttackGrounded = 2,
        Dead = 3,
    };

} // ggj

#endif //GAME_DEV_TEMPLATE_PLAYERSTATE_H
