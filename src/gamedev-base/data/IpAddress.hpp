//
// Created by robin on 08.11.24.
//

#ifndef GALDER_GAME_JAM_2024_PROJECT_IPADDRESS_HPP
#define GALDER_GAME_JAM_2024_PROJECT_IPADDRESS_HPP

#include <string>

namespace ggj
{
    class IpAddress
    {
        public:
            IpAddress() = default;
            IpAddress(std::string localIp, std::string publicIp) :
                    m_localIp {std::move(localIp)}, m_publicIp {std::move(publicIp)}
            {
            
            }
            
            [[nodiscard]] const std::string &getLocalIp() const { return m_localIp; }
            [[nodiscard]] const std::string &getPublicIp() const { return m_publicIp; }
        
        private:
            std::string m_localIp {};
            std::string m_publicIp {};
    };
}

#endif //GALDER_GAME_JAM_2024_PROJECT_IPADDRESS_HPP
