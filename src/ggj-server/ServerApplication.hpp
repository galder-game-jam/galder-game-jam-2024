//
// Created by robin on 08.11.24.
//

#ifndef GALDER_GAME_JAM_2024_PROJECT_SERVER_APPLICATION_HPP
#define GALDER_GAME_JAM_2024_PROJECT_SERVER_APPLICATION_HPP

#include "../galder-game-jam-library/GalderGameJamLibrary.h"

#include "ApplicationState.h"
#include "ServerWindow.hpp"
#include "ClientWindow.hpp"
//#include "raygui-cpp/include/raygui-cpp.h"

namespace ggj
{
    class IServerApplication
    {
        public:
            virtual ~IServerApplication() noexcept = default;
            virtual bool initialize() = 0;
            
            virtual void update(float timeDelta) = 0;
            virtual void draw() = 0;
            
            virtual void cleanup() = 0;
    };
    
    class ServerApplication : public IServerApplication
    {
        public:
            ServerApplication(raylib::Window &window, ILogger &logger, IInputManager<ggj::KeyboardKey> &input, IDebugManager &debugManager,
                              ggj::IIpAddressResolver &ipResolver, ggj::IExecutableInfo &executable, ggj::IServer<ggj::TestServerData,
                              ggj::TestClientData> &server, ggj::IClient<ggj::TestClientData, ggj::TestServerData> &client) :
            m_window {window}, m_logger {logger}, m_input {input}, m_debugManager {debugManager}, m_ipResolver {ipResolver}, m_executable {executable}, m_server {server}, m_client {client}
            {
            
            }
            
            bool initialize() override
            {
                m_localIp = fmt::format("Local IP: {0}", m_ipResolver.getLocalIpAddress());
                m_publicIp = fmt::format("Public IP: {0}", m_ipResolver.getPublicIpAddress());
                m_logger.information(m_localIp);
                m_logger.information(m_publicIp);
                
                //Gui settings
                GuiLoadStyleCyber();
                auto path = m_executable.getContentRootDirectory();
                
                //Font
                std::string fullPath = fmt::format("{0}/DejaVuSansBold.ttf", path.c_str());
                GetFontDefault();
                m_font = LoadFontEx(fullPath.c_str(), 24, nullptr, 0);  // 32 is the font size
                GuiGetFont();
                GuiSetFont(m_font);
                GuiSetStyle(DEFAULT, TEXT_SIZE, 24);
                //m_debugManager.setFont(&m_font);
                
                //Gui tools
                m_clientTool.initialize();
                m_serverTool.initialize();
                
                return true;
            }
            
            void update(float timeDelta) override
            {
                m_lastTimeDelta = timeDelta;
                m_debugManager.clearText();
                m_debugManager.setText(0, m_localIp);
                m_debugManager.setText(1, m_publicIp);
                m_debugManager.setText(2, m_clickedText);
                
                m_clientTool.update(timeDelta);
                
                if(m_state == ApplicationState::ServerInitialize)
                {
                    runServerLogic(timeDelta);
                }
                
                if(m_state == ApplicationState::ClientInitialize)
                {
                    runClientLogic(timeDelta);
                }
            }
            
            void runServerLogic(float timeDelta)
            {
                m_serverTool.update(timeDelta);
                if(m_serverTool.createServer())
                {
                    auto createData = m_serverTool.getServerCreateInformation();
                    if(createData.isValid)
                    {
                        m_server.initialize(createData.port, createData.name.data());
                        m_server.run();
                        m_state = ApplicationState::Server;
                        m_serverTool.setState(m_state);
                    }
                }
            }
            
            void runClientLogic(float timeDelta)
            {
                m_clientTool.update(timeDelta);
                if(m_clientTool.createClient())
                {
                    ClientCreateData createData = m_clientTool.getClientCreateInformation();
                    if(createData.isValid)
                    {
                        m_client.initialize();
                        
                        TestClientData data {};
                        data.nickname = createData.nickname;
                        data.color = createData.color;
                        data.isValid = true;
                        data.position = raylib::Vector2{1337.f, 1337.f};
                        m_client.queueData(data);
                        m_client.connect(createData.port, createData.serverIp.data());
                        m_state = ApplicationState::Client;
                        m_clientTool.setState(m_state);
                    }
                }
            }
            
            
            void draw() override
            {
                m_renderTexture.BeginMode();
                m_window.ClearBackground(m_backgroundColor);
                m_renderTexture.EndMode();
                
                render();
            }
            
            void cleanup() override
            {
                UnloadFont(m_font);
            }
        
        private:
            void render()
            {
                float scale = std::min((float)m_window.GetWidth()/m_originalWindowSize.x, (float)m_window.GetHeight()/m_originalWindowSize.y);
                BeginDrawing();
                m_window.ClearBackground(m_backgroundColor);
                DrawTexturePro(m_renderTexture.texture, raylib::Rectangle( 0.0f, 0.0f, (float)m_renderTexture.texture.width, (float)-m_renderTexture.texture.height ),
                               raylib::Rectangle( ((float)m_window.GetWidth() - ((float)m_originalWindowSize.x*scale))*0.5f, ((float)m_window.GetHeight() - ((float)m_originalWindowSize.y*scale))*0.5f,
                                                  (float)m_originalWindowSize.x*scale, (float)m_originalWindowSize.y*scale ), { 0, 0 }, 0.0f, WHITE);
                
                renderGui();
                m_clientTool.draw();
                m_serverTool.draw();
                m_debugManager.draw();
                EndDrawing();
            }
            
            void renderGui()
            {
                if(m_state != ApplicationState::Server && m_state != ApplicationState::Client)
                {
                    if(GuiButton((Rectangle) {300, 0, 200, 50}, "Server Mode"))
                    {
                        m_clickedText = "Server";
                        m_state = ApplicationState::ServerInitialize;
                        m_clientTool.isActive = false;
                        m_serverTool.isActive = true;
                        m_serverTool.setState(m_state);
                    }
                    if(GuiButton((Rectangle) {500, 0, 200, 50}, "Client Mode"))
                    {
                        m_clickedText = "Client";
                        m_state = ApplicationState::ClientInitialize;
                        m_clientTool.isActive = true;
                        m_serverTool.isActive = false;
                        m_clientTool.setState(m_state);
                    }
                }
            }
            
            ggj::IServer<ggj::TestServerData, ggj::TestClientData> &m_server;
            ggj::IClient<ggj::TestClientData, ggj::TestServerData> &m_client;
            //std::vector<std::unique_ptr<ggj::IServer<ggj::TestServerData, ggj::TestClientData>>> m_servers;
            //std::vector<std::unique_ptr<ggj::IClient<ggj::TestClientData, ggj::TestServerData>>> m_clients;
            
            raylib::Window &m_window;
            ILogger &m_logger;
            IInputManager<ggj::KeyboardKey> &m_input;
            IDebugManager &m_debugManager;
            ggj::IIpAddressResolver &m_ipResolver;
            ggj::IExecutableInfo &m_executable;
            raylib::Color m_backgroundColor = raylib::Color(8, 140, 197);
            Font m_font{};
            float m_lastTimeDelta {};
            ApplicationState m_state {ApplicationState::None};
            
            raylib::Vector2 m_originalWindowSize;
            raylib::RenderTexture2D m_renderTexture;
            
            ggj::ServerWindow m_serverTool{};
            ggj::ClientWindow m_clientTool{};
            
            std::string m_localIp = "";
            std::string m_publicIp = "";
            std::string m_clickedText = "";
            
            //Gui
//            rgc::WindowBox m_popup{};
//            rgc::Button m_testBtn {};
//            rgc::TextInputBox m_textBox {};
    };
}

#endif //GALDER_GAME_JAM_2024_PROJECT_SERVER_APPLICATION_HPP
