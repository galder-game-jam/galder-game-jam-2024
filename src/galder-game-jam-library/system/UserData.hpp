//
// Created by soberga on 12.11.22.
//

#ifndef GAME_DEV_TEMPLATE_USERDATA_HPP
#define GAME_DEV_TEMPLATE_USERDATA_HPP

#include <utility>

#include "raylib-cpp.hpp"
#include "../enums/ObjectType.h"

namespace ggj
{

    class UserData
    {
        public:
            UserData() = default;
            UserData(ObjectType objectType, const raylib::Vector2 &force, std::string command, std::string name): m_objectType{objectType}, m_force{force}, m_command {std::move(command)}, m_name {std::move(name)}
            {
            }

            void destroy() { m_shouldBeDestroyed = true; };

            [[nodiscard]] ObjectType getObjectType() const { return m_objectType; }
            [[nodiscard]] const raylib::Vector2 &getForce() const { return m_force; }
            [[nodiscard]] bool shouldBeDestroyed() const { return m_shouldBeDestroyed; }
            [[nodiscard]] const std::string &getCommand() const { return m_command; }
            [[nodiscard]] const std::string &getName() const { return m_name; }

            int enemiesKilled {0};

        private:
            ObjectType m_objectType {ObjectType::Undefined};
            raylib::Vector2 m_force {0.f, 0.f};
            bool m_shouldBeDestroyed{false};
            std::string m_command{};
            std::string m_name{};
    };

} // ggj

#endif //GAME_DEV_TEMPLATE_USERDATA_HPP
