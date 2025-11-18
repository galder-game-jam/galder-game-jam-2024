//
// Created by robin on 08.11.24.
//

#ifndef GALDER_GAME_JAM_2024_PROJECT_STRINGTRIM_HPP
#define GALDER_GAME_JAM_2024_PROJECT_STRINGTRIM_HPP

#include <string>
#include <functional>

namespace ggj
{
    // trim from start (in place)
    static inline void ltrim(std::string &s) {
        s.erase(s.begin(), std::ranges::find_if(s.begin(), s.end(), [](int ch) {
            return !std::isspace(ch);
        }));
    }
    
    // trim from end (in place)
    static inline void rtrim(std::string &s) {
        s.erase(std::ranges::find_if(s.rbegin(), s.rend(), [](int ch) {
            return !std::isspace(ch);
        }).base(), s.end());
    }
}


#endif //GALDER_GAME_JAM_2024_PROJECT_STRINGTRIM_HPP
