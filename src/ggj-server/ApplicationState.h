//
// Created by robin on 10.11.24.
//

#ifndef GALDER_GAME_JAM_2024_PROJECT_APPLICATIONSTATE_H
#define GALDER_GAME_JAM_2024_PROJECT_APPLICATIONSTATE_H
namespace ggj
{
    enum class ApplicationState
    {
        None = 0,
        ServerInitialize = 1,
        ClientInitialize = 2,
        Server = 3,
        Client = 4
    };
}

#endif //GALDER_GAME_JAM_2024_PROJECT_APPLICATIONSTATE_H
