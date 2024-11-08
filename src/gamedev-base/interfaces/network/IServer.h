//
// Created by robin on 08.11.24.
//

#ifndef GALDER_GAME_JAM_2024_PROJECT_ISERVER_H
#define GALDER_GAME_JAM_2024_PROJECT_ISERVER_H

#include <cstdint>
#include <string>
#include "../../data/ServerHostInfo.hpp"
#include "steam/steamnetworkingtypes.h"

namespace ggj
{
    template <class TServerData, class TClientData>
    class IServer
    {
        public:
            virtual ~IServer() noexcept = default;
            virtual bool initialize(uint16_t port, const std::string& name ) = 0;
            virtual void run() = 0;
            virtual void stop() = 0;
        
        protected:
            virtual bool send(HSteamNetConnection connection, const TServerData &data) = 0;
            virtual TClientData receive(HSteamNetConnection connection) = 0;
            virtual TClientData receive() = 0;
            virtual void serverProgram() = 0;
    };
}

#endif //GALDER_GAME_JAM_2024_PROJECT_ISERVER_H
