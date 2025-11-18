//
// Created by robin on 10.11.24.
//

#ifndef GALDER_GAME_JAM_2024_PROJECT_TESTSERVEDATA_HPP
#define GALDER_GAME_JAM_2024_PROJECT_TESTSERVEDATA_HPP

namespace ggj
{
    class TestServerData
    {
        public:
            bool isInvalid {true}; //0 = false, everything else is true.
            uint32_t id{}; //Just an ID sent
            std::array<char, 256> message{};
            raylib::Color color{};
    };
}
#endif //GALDER_GAME_JAM_2024_PROJECT_TESTSERVEDATA_HPP
