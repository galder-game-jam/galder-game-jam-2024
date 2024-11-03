//
// Created by robin on 03.11.23.
//

#include <string>
#include "IpAddressResolver.h"

//Needed to resolve local addresses
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

const std::string ggj::IpAddressResolver::getLocalIpAddress() const
{
    int sock = socket(PF_INET, SOCK_DGRAM, 0);
    sockaddr_in loopback{};
    
    if (sock == -1) {
        std::cerr << "Could not socket\n";
        return "";
    }
    
    std::memset(&loopback, 0, sizeof(loopback));
    loopback.sin_family = AF_INET;
    loopback.sin_addr.s_addr = 1337;   // can be any IP address
    loopback.sin_port = htons(9);      // using debug port
    
    if (connect(sock, reinterpret_cast<sockaddr*>(&loopback), sizeof(loopback)) == -1) {
        close(sock);
        std::cerr << "Could not connect\n";
        return "";
    }
    
    socklen_t addrlen = sizeof(loopback);
    if (getsockname(sock, reinterpret_cast<sockaddr*>(&loopback), &addrlen) == -1) {
        close(sock);
        std::cerr << "Could not getsockname\n";
        return "";
    }
    
    close(sock);
    
    char buf[INET_ADDRSTRLEN];
    if (inet_ntop(AF_INET, &loopback.sin_addr, buf, INET_ADDRSTRLEN) == 0x0) {
        std::cerr << "Could not inet_ntop\n";
        return "";
    }
    
    return std::string(buf);
}
const std::string ggj::IpAddressResolver::getPublicIpAddress() const
{
    char addr[256];
    size_t s = sizeof(addr);
    if (ipify(addr, s))
        return "";
    
    return std::string(addr);
}
