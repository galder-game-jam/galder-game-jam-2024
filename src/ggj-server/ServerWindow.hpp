//
// Created by robin on 08.11.24.
//

#ifndef GALDER_GAME_JAM_2024_PROJECT_SERVERWINDOW_HPP
#define GALDER_GAME_JAM_2024_PROJECT_SERVERWINDOW_HPP

#define RAYGUI_IMPLEMENTATION
#include "raygui.hpp"
#include "style_cyber_mod.h"
#include <limits>

namespace ggj
{
    struct ServerCreateWindowState
    {
        //Vector2 windowPosition = {200, 200 };
        Vector2 windowSize = {500, 400 };
        bool minimized = false;
        bool moving = false;
        bool resizing = false;
        Vector2 position {};
        Vector2 scroll {};
        std::array<char, 6> port {"13338"};
        std::array<char, 31> name {"Galder's kosebur"};
        
        bool nameEdit {false};
        bool portEdit {false};
        
        bool createClicked {false};
    };
    
    struct ServerCreateData
    {
        bool isValid {false};
        uint16_t port {0};
        std::array<char, 31> name{};
    };
    
    class ServerWindow
    {
        public:
            ServerWindow() = default;
            
            bool initialize()
            {
                m_serverCreateWindowState.position = {200, 200 };
                m_serverCreateWindowState.scroll = {0,0};
                return true;
            }
            
            void update(float timeDelta)
            {
            
            }
            
            void draw()
            {
                if(isActive)
                {
                    if(m_appState == ApplicationState::ServerInitialize)
                    {
                        GuiWindowFloating(&m_serverCreateWindowState.position, &m_serverCreateWindowState.windowSize, &m_serverCreateWindowState.minimized,
                                          &m_serverCreateWindowState.moving, &m_serverCreateWindowState.resizing, &DrawServerCreate,
                                          (Vector2) {140, 320}, &m_serverCreateWindowState.scroll, "Host server");
                    }
                }
            }
            
            bool createServer()
            {
                bool create = m_serverCreateWindowState.createClicked;
                m_serverCreateWindowState.createClicked = false;
                return create;
            }
            
            ServerCreateData getServerCreateInformation()
            {
                int port {};
                
                try
                {
                    port = std::stoi(m_serverCreateWindowState.port.data());
                }
                catch (const std::invalid_argument& e)
                {
                    return {};
                }
                
                uint16_t limit = std::numeric_limits<uint16_t>::max();
                if(port > limit)
                    port = limit;
                
                if(port > 0 && !m_serverCreateWindowState.name.empty())
                {
                    return {true, (uint16_t)port, m_serverCreateWindowState.name};
                }
                
                return {};
            }
            
            void setState(ApplicationState state)
            {
                m_appState = state;
            }
            
            bool isActive = false;
        
        private:
            //Vector2 m_scroll;
            
//            ServerCreateWindowState serverCreateWindowState {{200, 200 }, {0,0}, "13338" };
            ServerCreateWindowState m_serverCreateWindowState {};
            ApplicationState m_appState {ApplicationState::None};
            
            //std::string m_port{"13338"};
            
            void GuiWindowFloating(Vector2 *position, Vector2 *size, bool *minimized, bool *moving, bool *resizing,
                                   void (*draw_content)(ServerCreateWindowState&), Vector2 content_size, Vector2 *scroll,
                                   const char *title)
            {
                #if !defined(RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT)
                    #define RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT 24
                #endif
                
                #if !defined(RAYGUI_WINDOW_CLOSEBUTTON_SIZE)
                    #define RAYGUI_WINDOW_CLOSEBUTTON_SIZE 18
                #endif
                
                int close_title_size_delta_half =
                        (RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT - RAYGUI_WINDOW_CLOSEBUTTON_SIZE) / 2;
                
                // window movement and resize input and collision check
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !*moving && !*resizing)
                {
                    Vector2 mouse_position = GetMousePosition();
                    
                    Rectangle title_collision_rect = {position->x, position->y, size->x -
                                                                                (RAYGUI_WINDOW_CLOSEBUTTON_SIZE +
                                                                                 close_title_size_delta_half),
                                                      RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT};
                    Rectangle resize_collision_rect = {position->x + size->x - 20, position->y + size->y - 20, 20, 20};
                    
                    if(CheckCollisionPointRec(mouse_position, title_collision_rect))
                    {
                        *moving = true;
                    }
                    else if(!*minimized && CheckCollisionPointRec(mouse_position, resize_collision_rect))
                    {
                        *resizing = true;
                    }
                }
                
                // window movement and resize update
                if(*moving)
                {
                    Vector2 mouse_delta = GetMouseDelta();
                    position->x += mouse_delta.x;
                    position->y += mouse_delta.y;
                    
                    if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                    {
                        *moving = false;
                        
                        // clamp window position keep it inside the application area
                        if(position->x < 0) position->x = 0;
                        else if(position->x > GetScreenWidth() - size->x) position->x = GetScreenWidth() - size->x;
                        if(position->y < 0) position->y = 0;
                        else if(position->y > GetScreenHeight()) position->y = GetScreenHeight() -
                                                                               RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT;
                    }
                    
                }
                else if(*resizing)
                {
                    Vector2 mouse = GetMousePosition();
                    if(mouse.x > position->x)
                        size->x = mouse.x - position->x;
                    if(mouse.y > position->y)
                        size->y = mouse.y - position->y;
                    
                    // clamp window size to an arbitrary minimum value and the window size as the maximum
                    if(size->x < 100) size->x = 100;
                    else if(size->x > GetScreenWidth()) size->x = GetScreenWidth();
                    if(size->y < 100) size->y = 100;
                    else if(size->y > GetScreenHeight()) size->y = GetScreenHeight();
                    
                    if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                    {
                        *resizing = false;
                    }
                }
                
                // window and content drawing with scissor and scroll area
                if(*minimized)
                {
                    GuiStatusBar((Rectangle) {position->x, position->y, size->x, RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT},
                                 title);
                    
                    if(GuiButton((Rectangle) {
                                         position->x + size->x - RAYGUI_WINDOW_CLOSEBUTTON_SIZE - close_title_size_delta_half,
                                         position->y + close_title_size_delta_half,
                                         RAYGUI_WINDOW_CLOSEBUTTON_SIZE,
                                         RAYGUI_WINDOW_CLOSEBUTTON_SIZE},
                                 "#120#"))
                    {
                        *minimized = false;
                    }
                    
                }
                else
                {
                    *minimized = GuiWindowBox((Rectangle) {position->x, position->y, size->x, size->y}, title);
                    
                    // scissor and draw content within a scroll panel
                    if(draw_content != NULL)
                    {
                        Rectangle scissor = {0};
                        GuiScrollPanel(
                                (Rectangle) {position->x, position->y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT, size->x,
                                             size->y - RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT},
                                NULL,
                                (Rectangle) {position->x, position->y, content_size.x, content_size.y},
                                scroll,
                                &scissor);
                        
                        bool require_scissor = size->x < content_size.x || size->y < content_size.y;
                        
                        if(require_scissor)
                        {
                            BeginScissorMode(scissor.x, scissor.y, scissor.width, scissor.height);
                        }
                        
                        draw_content(m_serverCreateWindowState);
                        
                        if(require_scissor)
                        {
                            EndScissorMode();
                        }
                    }
                    
                    // draw the resize button/icon
                    GuiDrawIcon(71, position->x + size->x - 20, position->y + size->y - 20, 1, WHITE);
                }
            }
            
            static void DrawServerCreate(ServerCreateWindowState &state)//(Vector2 position, Vector2 scroll, std::string &port)
            {
                GuiLabel((Rectangle) {state.position.x + 20 + state.scroll.x, state.position.y + 50 + state.scroll.y, 100, 25}, "Name: ");
                if(GuiTextBox((Rectangle) {state.position.x + 120 + state.scroll.x, state.position.y + 50 + state.scroll.y, 300, 25}, state.name.data(), 30, state.nameEdit))
                {
                    state.nameEdit = true;
                    state.portEdit = false;
                }
                GuiLabel((Rectangle) {state.position.x + 20 + state.scroll.x, state.position.y + 90 + state.scroll.y, 100, 25}, "Port: ");
                if(NumericGuiTextBox((Rectangle) {state.position.x + 120 + state.scroll.x, state.position.y + 90 + state.scroll.y, 100, 25}, state.port.data(), 6,
                                  state.portEdit))
                {
                    state.portEdit = true;
                    state.nameEdit = false;
                }
                if(GuiButton((Rectangle) {state.position.x + 20 + state.scroll.x, state.position.y + 130 + state.scroll.y, 100, 25}, "Create"))
                    state.createClicked = true;

            }
            
            static bool NumericGuiTextBox(Rectangle bounds, char *text, int textSize, bool editMode)
            {
                // Call GuiTextBox with editMode to allow editing
                bool result = GuiTextBox(bounds, text, textSize, editMode);

                // Process each character to allow only digits
                if (editMode)
                {
                    int length = strlen(text);
                    for (int i = 0; i < length; i++)
                    {
                        // Check if the character is a digit
                        if (!isdigit(text[i]))
                        {
                            // Shift all characters after the non-digit one position to the left
                            memmove(&text[i], &text[i + 1], length - i);
                            length--; // Adjust length due to removed character
                            i--; // Adjust loop index
                        }
                    }
                }

                return result;
            }

    };
}

#endif //GALDER_GAME_JAM_2024_PROJECT_SERVERWINDOW_HPP
