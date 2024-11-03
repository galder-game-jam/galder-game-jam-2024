#include "../galder-game-jam-library/GalderGameJamLibrary.h"
#include "di.hpp"
#include "fmt/color.h"
#include "raylib-cpp.hpp"
#include <stdio.h>

auto buildInjectorForNetworking(ggj::ILogger &logger)
{
    auto injector = boost::di::make_injector(
            boost::di::bind<ggj::IIpAddressResolver>().to<ggj::IpAddressResolver>(),
            boost::di::bind<ggj::IExecutableInfo>().to<ggj::ExecutableInfo>(),
            boost::di::bind<ggj::ILogger>().to(logger)
    );
    
    return injector;
}

struct App
{
    ggj::ILogger &logger;
    ggj::IExecutableInfo &executableInfo;
    ggj::IIpAddressResolver &ipResolver;
    
    bool initialize()
    {
        return true;
    }
};

int testNetworking()
{
    ggj::ConsoleLogger l = ggj::ConsoleLogger(ggj::LogLevel::Debug);
    
    //Handle dependency injection
    auto injector = buildInjectorForNetworking(l);
    App app = injector.create<App>();
    ggj::ILogger &logger = app.logger;
    
    //logger.information(fmt::format("Content path: {0}", app.executableInfo.getContentRootDirectory().string()));
    //Initialize everything
    if(!app.initialize())
        app.logger.critical("App initialization failed!");
    
    std::string localIp = fmt::format("Local IP: {0}", app.ipResolver.getLocalIpAddress());
    std::string publicIp = fmt::format("Public IP: {0}", app.ipResolver.getPublicIpAddress());
    logger.information(localIp);
    logger.information(publicIp);
    
    return 0;
}

int main(int argc, char **argv)
{
    int result = testNetworking();
    return result;
}

