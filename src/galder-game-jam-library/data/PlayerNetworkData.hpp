//
// Created by robin on 08.11.24.
//

#ifndef GALDER_GAME_JAM_2024_PROJECT_PLAYERNETWORKDATA_HPP
#define GALDER_GAME_JAM_2024_PROJECT_PLAYERNETWORKDATA_HPP

#include "../../gamedev-base/GameDevBase.h"
#include "raylib-cpp.hpp"

namespace ggj
{
    class PlayerNetworkData
    {
        public:
            bool isValid{}; //Will be false if object is just default
            raylib::Vector2 position{}; //
            uint8_t action{0}; //
            uint8_t animationState{0}; //
            uint8_t animationFrame{0}; //
    };
}

#endif //GALDER_GAME_JAM_2024_PROJECT_PLAYERNETWORKDATA_HPP
