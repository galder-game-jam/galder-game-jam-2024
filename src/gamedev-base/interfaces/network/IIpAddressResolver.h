//
// Created by robin on 03.11.23.
//

#ifndef GALDER_GAME_JAM_2023_PROJECT_IIPADDRESSRESOLVER_H
#define GALDER_GAME_JAM_2023_PROJECT_IIPADDRESSRESOLVER_H

#include <string>

namespace ggj
{
    class IIpAddressResolver
    {
        public:
            virtual ~IIpAddressResolver() noexcept = default;
            virtual const std::string getLocalIpAddress() const = 0;
            virtual const std::string getPublicIpAddress() const = 0;
    };
    
} // dev

#endif //GALDER_GAME_JAM_2023_PROJECT_IIPADDRESSRESOLVER_H
