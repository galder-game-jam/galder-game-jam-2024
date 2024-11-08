//
// Created by robin on 08.11.24.
//

#ifndef GALDER_GAME_JAM_2024_PROJECT_ICLIENT_H
#define GALDER_GAME_JAM_2024_PROJECT_ICLIENT_H

#include "../../enums/ConnectionStatus.hpp"
#include "../../data/ServerHostInfo.hpp"
#include <cstdint>
namespace ggj
{
    template <class TClientData, class TServerData>
    class IClient
    {
        public:
            virtual ~IClient() noexcept = default;
            virtual bool initialize() = 0;
            virtual void connect(uint16_t port, std::string ipAddress) = 0;
            [[nodiscard]] virtual ServerHostInfo getServerInfo() const = 0;
            virtual void ping() const = 0;
            virtual void disconnect() const = 0;
        
        protected:
            virtual bool send(const TClientData &data) = 0;
            virtual TServerData receive() = 0;
            virtual void clientProgram() = 0;
    };
}

#endif //GALDER_GAME_JAM_2024_PROJECT_ICLIENT_H
