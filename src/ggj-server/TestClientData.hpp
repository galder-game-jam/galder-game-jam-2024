//
// Created by robin on 10.11.24.
//

#ifndef GALDER_GAME_JAM_2024_PROJECT_TESTNETWORKDATA_HPP
#define GALDER_GAME_JAM_2024_PROJECT_TESTNETWORKDATA_HPP

namespace ggj
{
    class TestClientData
    {
        public:
            bool isValid{}; //Will be false if object is just default
            raylib::Vector2 position{}; //
            raylib::Color color{}; //
            uint8_t action{0}; //
            uint8_t animationState{0}; //
            uint8_t animationFrame{0}; //
            std::array<char, 21> nickname {""};
    };
}

#endif //GALDER_GAME_JAM_2024_PROJECT_TESTNETWORKDATA_HPP
