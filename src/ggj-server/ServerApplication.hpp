//
// Created by robin on 08.11.24.
//

#ifndef GALDER_GAME_JAM_2024_PROJECT_SERVER_APPLICATION_HPP
#define GALDER_GAME_JAM_2024_PROJECT_SERVER_APPLICATION_HPP

namespace ggj
{
    class IServerApplication
    {
        public:
            virtual ~IServerApplication() noexcept = default;
            virtual bool initialize() = 0;
            
            virtual void update(float timeDelta) = 0;
            virtual void draw() = 0;
    };
    
    class ServerApplication : public IServerApplication
    {
        public:
            ServerApplication(raylib::Window &window, ILogger &logger, IInputManager<ggj::KeyboardKey> input, IDebugManager &debugManager,
                              ggj::IIpAddressResolver &ipResolver) :
            m_window {window}, m_logger {logger}, m_input {input}, m_debugManager {debugManager}, m_ipResolver {ipResolver}
            {
            
            }
            
            bool initialize() override
            {
                std::string localIp = fmt::format("Local IP: {0}", m_ipResolver.getLocalIpAddress());
                std::string publicIp = fmt::format("Public IP: {0}", m_ipResolver.getPublicIpAddress());
                m_logger.information(localIp);
                m_logger.information(publicIp);
                
                return true;
            }
            
            void update(float timeDelta) override
            {
            
            }
            
            void draw() override
            {
            
            }
        
        private:
            void render()
            {
            
            }
            
            raylib::Window &m_window;
            ILogger &m_logger;
            IInputManager<ggj::KeyboardKey> &m_input;
            IDebugManager &m_debugManager;
            ggj::IIpAddressResolver &m_ipResolver;
            
            raylib::Vector2 m_originalWindowSize;
            raylib::RenderTexture2D m_renderTexture;
    };
}

#endif //GALDER_GAME_JAM_2024_PROJECT_SERVER_APPLICATION_HPP
