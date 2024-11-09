#include "../galder-game-jam-library/GalderGameJamLibrary.h"
#include "di.hpp"
#include "fmt/color.h"
//#include "raylib-cpp.hpp"
#include <stdio.h>
#include "ServerApplication.hpp"

auto buildInjectorForNetworking(ggj::ILogger &logger, raylib::Window &window)
{
    auto injector = boost::di::make_injector(
            boost::di::bind<ggj::IServerApplication>().to<ggj::ServerApplication>(),
            boost::di::bind<ggj::IIpAddressResolver>().to<ggj::IpAddressResolver>(),
            boost::di::bind<ggj::IExecutableInfo>().to<ggj::ExecutableInfo>(),
            boost::di::bind<ggj::IInputManager<ggj::KeyboardKey>>().to<ggj::InputManager>(),
            boost::di::bind<ggj::IDebugManager>().to<ggj::DebugManager>(),
            boost::di::bind<raylib::Window>().to(window),
            boost::di::bind<ggj::ILogger>().to(logger)
    );
    
    return injector;
}

struct App
{
    ggj::ILogger &logger;
    ggj::IExecutableInfo &executableInfo;
    ggj::IIpAddressResolver &ipResolver;
    ggj::IServerApplication &server;
    
    bool initialize()
    {
        if(!server.initialize())
            
            return false;
        return true;
    }
};

int testNetworking()
{
    int screenWidth = 1440;
    int screenHeight = 900; // HalfHeight: 450
    raylib::Window window {screenWidth, screenHeight, "GGJ Server/Client App"};
    window.SetState(FLAG_WINDOW_RESIZABLE);
    
    ggj::ConsoleLogger l = ggj::ConsoleLogger(ggj::LogLevel::Debug);
    
    //Handle dependency injection
    auto injector = buildInjectorForNetworking(l, window);
    App app = injector.create<App>();
    ggj::ILogger &logger = app.logger;
    
    //logger.information(fmt::format("Content path: {0}", app.executableInfo.getContentRootDirectory().string()));
    //Initialize everything
    if(!app.initialize())
        app.logger.critical("App initialization failed!");
    
    SetTargetFPS(60);
    ggj::Timer timer;
    while (!window.ShouldClose())
    {
        float timeDelta = timer.secondsElapsed();
        app.server.update(timeDelta);
        timer.restart();
        app.server.draw();
    }
    app.server.cleanup();
//    std::string localIp = fmt::format("Local IP: {0}", app.ipResolver.getLocalIpAddress());
//    std::string publicIp = fmt::format("Public IP: {0}", app.ipResolver.getPublicIpAddress());
//    logger.information(localIp);
//    logger.information(publicIp);
    
    return 0;
}

int main(int argc, char **argv)
{
    int result = testNetworking();
    return result;
}

