//
// Created by robin on 29.10.22.
//

#ifndef GAME_DEV_TEMPLATE_WORLD_H
#define GAME_DEV_TEMPLATE_WORLD_H

#include "../../gamedev-base/GameDevBase.h"
#include "../enums/ResourceName.h"
#include "box2d/box2d.h"
#include "tileson.hpp"
#include "../interfaces/system/IMapper.h"
#include "raylib-cpp.hpp"
#include "WorldLayer.h"
#include "../enums/KeyboardKey.h"
#include "../graphics/PhysicsObject.h"
#include "../GalderGameJamLibrary.h"
#include "ObjectGeneratorData.hpp"

namespace ggj
{
    class World : public ggj::IWorld<int32_t>
    {
        public:
            World(ggj::ILogger &logger, ggj::IResourceManager<ResourceName> &resources, IMapper &mapper,
                  ggj::ITextureManager<TextureName, raylib::Texture> &textures,
                  raylib::Window &window, ggj::IInputManager<ggj::KeyboardKey> &input, CollisionManager &collisionManager,
                  IDebugManager &debugManager, ggj::IAnimationManager<ggj::Animation, ggj::AnimationName> &animationManager,
                  IUserDataManager<PhysicsObject*> &userDataManager, std::unique_ptr<tson::Map> map)
                    : m_logger{logger}, m_resources{resources}, m_mapper{mapper}, m_textures{textures}, m_window{window},
                    m_input {input}, m_collisionManager {collisionManager}, m_debugManager {debugManager},
                    m_animationManager {animationManager}, m_userDataManager{userDataManager}, m_map{std::move(map)}
            {
                m_camera.target = Vector2{ 0.f, 0.f };
                m_camera.offset = {0.f, 0.f};//{8.f, 8.f};//(Vector2){ (float) window.GetWidth() / 2.0f, (float)window.GetHeight() / 2.0f };
                m_camera.rotation = 0.0f;
                m_camera.zoom = 1.0f;
            }

            bool initialize() override;
            void update(float timeDelta) override;
            void draw() override;
            std::string getLeadingPlayer() const;
            [[nodiscard]] int getEnemies() const;
            void reduceEnemyKillCountByOne();
            [[nodiscard]] int getNumberOfEnemiesLeft() const;

            template <typename T>
            T * createProjectile(TextureName texture, raylib::Vector2 size, raylib::Vector2 pos, Vector2 velocity, float timeToLive);

        private:
            template <typename T, typename... Args>
            T * createObject(Args &&... args);
            //Generator logic
            void generatePhysicsObject(const std::string &name, b2Body* body, const ObjectGeneratorData &generatorData);
            void generatePlayer(const std::string &name, b2Body* body, const ObjectGeneratorData &generatorData);
            void generatePlayer2(const std::string &name, b2Body* body, const ObjectGeneratorData &generatorData);
            void generateBat(const std::string &name, b2Body* body, const ObjectGeneratorData &generatorData);
            void generateSnake(const std::string &name, b2Body* body, const ObjectGeneratorData &generatorData);
            void generateCoin(const std::string &name, b2Body* body, const ObjectGeneratorData &generatorData);
            void generateSpider(const std::string &name, b2Body* body, const ObjectGeneratorData &generatorData);
            void generateThing(const std::string &name, b2Body* body, const ObjectGeneratorData &generatorData);
            void generateGhost(const std::string &name, b2Body* body, const ObjectGeneratorData &generatorData);
            void generatePortal(const std::string &name, b2Body* body, const ObjectGeneratorData &generatorData);
            void generatePowerUp(const std::string &name, b2Body* body, const ObjectGeneratorData &generatorData);
            void generateGenericPhysicsObject(const std::string &name, b2Body* body, const ObjectGeneratorData &generatorData);
            void destroyMarkedObjects();

            ggj::ILogger &m_logger;
            ggj::IResourceManager<ResourceName> &m_resources;
            IMapper &m_mapper;
            ggj::ITextureManager<TextureName, raylib::Texture> &m_textures;
            raylib::Window &m_window;
            ggj::IInputManager<ggj::KeyboardKey> &m_input;
            ggj::CollisionManager &m_collisionManager;
            ggj::IDebugManager &m_debugManager;
            ggj::IAnimationManager<ggj::Animation, ggj::AnimationName> &m_animationManager;
            IUserDataManager<PhysicsObject*> &m_userDataManager;
            raylib::Camera2D m_camera;

            raylib::Vector2 m_cameraMin {0.f, 0.f};
            raylib::Vector2 m_cameraMax {0.f, 0.f};
            raylib::Vector2 m_cameraDefault {0.f, 0.f};

            int m_portalTimer{5};

            Player *m_player = nullptr;
            Player2 *m_player2 = nullptr;

            Portal *m_portal = nullptr;

            b2World m_world{{0.f, 0.f}};
            std::unique_ptr<tson::Map> m_map{nullptr};

            raylib::Color m_backgroundColor = raylib::Color::White();
            std::map<int32_t, ggj::WorldLayer> m_layers;

            int m_numberOfEnemies{0};
    };

    template <typename T>
    T* World::createProjectile(TextureName texture, raylib::Vector2 size, raylib::Vector2 pos, Vector2 velocity, float timeToLive)
    {
        b2BodyType bodyType = b2_dynamicBody;
        b2BodyDef bodyDef;
        bodyDef.type = bodyType;
        b2Vec2 b2size = PhysicsObject::ConvertToB2Vec2({(float) size.x, (float) size.y});
        b2Vec2 b2origin = PhysicsObject::ConvertToB2Vec2({(float) size.x / 2, (float) size.y / 2});
        b2Vec2 b2pos = PhysicsObject::ConvertToB2Vec2({(float) pos.x, (float) pos.y});

        bodyDef.position.Set(b2pos.x + b2origin.x, b2pos.y + b2origin.y);
        b2Body *body = m_world.CreateBody(&bodyDef);

        b2CircleShape circle;
        circle.m_p.Set(0.f, 0.f);
        circle.m_radius = b2origin.x;

        b2FixtureDef fd;
        fd.shape = &circle;
        fd.density = 1.0f; //Density must be something to react to gravity.
        fd.friction = 1.0f;

        body->CreateFixture(&fd);

        for (b2Fixture *f = body->GetFixtureList(); f; f = f->GetNext())
        {
            f->SetSensor(true);
        }

        raylib::Rectangle rect = {0.f, 0.f, (float) size.x, (float) size.y};
        raylib::Vector2 origin = {(float) rect.width / 2, (float) rect.height / 2};
        raylib::Vector2 v = {(float) pos.x + origin.x, (float) pos.y + origin.y};
        raylib::Rectangle r = {(float) rect.x, (float) rect.y, (float) rect.width, (float) rect.height};
        raylib::Vector2 spriteSize = raylib::Vector2(r.width, r.height);

        raylib::Texture *tex = m_textures.get(texture);
        UserData userData{ObjectType::Projectile, {0.f, 0.f}, "damage", "projectile"};

        bool isVisible = true;
        T* obj = createObject<T>(m_animationManager, m_mapper, body, size, size, rect, tex, userData, velocity,
            this, timeToLive, isVisible);
        m_userDataManager.addUserData(body, obj);
        return obj;
    }

    template <typename T, typename ... Args>
    T* World::createObject(Args&&... args)
    {
        for (auto &layer: m_layers)
        {
            if(layer.second.getName() == "objects")
            {
                return layer.second.createGameObject<T>(args...);
            }
        }
        return nullptr;
    }
}

#endif //GAME_DEV_TEMPLATE_WORLD_H
