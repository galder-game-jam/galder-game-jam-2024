//
// Created by robin on 09.11.24.
//

#ifndef GALDER_GAME_JAM_2024_PROJECT_CLIENTWINDOW_HPP
#define GALDER_GAME_JAM_2024_PROJECT_CLIENTWINDOW_HPP

namespace ggj
{
    class ClientWindow
    {
        public:
            ClientWindow() = default;
            
            bool initialize()
            {
                return true;
            }
            
            void update(float timeDelta)
            {
            
            }
            
            void draw()
            {
                if(isActive)
                {

                }
            }
            
            bool isActive = false;
        
        private:
        
    };
}

#endif //GALDER_GAME_JAM_2024_PROJECT_CLIENTWINDOW_HPP
