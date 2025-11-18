//
// Created by robin on 08.11.24.
//

#ifndef GALDER_GAME_JAM_2024_PROJECT_SERVERHOSTINFO_HPP
#define GALDER_GAME_JAM_2024_PROJECT_SERVERHOSTINFO_HPP

#include <cstdint>
#include <string>
#include <utility>
#include "IpAddress.hpp"

namespace ggj
{
    class ServerHostInfo
    {
        public:
            ServerHostInfo() = default;
            ServerHostInfo(uint16_t port, IpAddress ipAddress, std::string name)
                    : m_port {port}, m_ipAddress {std::move(ipAddress)}, m_name {std::move(name)}
            {
            
            }
            
            [[nodiscard]] uint16_t getPort() const { return m_port; }
            [[nodiscard]] const IpAddress &getIpAddress() const { return m_ipAddress; }
            [[nodiscard]] const std::string &getName() const { return m_name; }
        
        private:
            uint16_t m_port {};
            IpAddress m_ipAddress {};
            std::string m_name {};
        
    };
}

#endif //GALDER_GAME_JAM_2024_PROJECT_SERVERHOSTINFO_HPP
