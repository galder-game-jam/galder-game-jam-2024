//
// Created by robin on 27.10.22.
//

#ifndef GAME_DEV_TEMPLATE_RESOURCEMANAGER_HPP
#define GAME_DEV_TEMPLATE_RESOURCEMANAGER_HPP

#include <map>
#include "../../gamedev-base/GameDevBase.h"
#include "fmt/format.h"

namespace ggj
{
    template <class T>
    class ResourceManager : public IResourceManager<T>
    {
        public:
            explicit ResourceManager(ggj::IExecutableInfo &executableInfo) : m_executableInfo {executableInfo} {};
            void initialize() override;

            void add(T resourceType, std::string value) override;
            bool exists(T resourceType) override;

            std::string getResource(T resourceType) override;

            std::string getResource(const std::string &resource) override;

        private:
            std::map<T, std::string> m_resources;

            ggj::IExecutableInfo &m_executableInfo;
    };

    template<class T>
    void ResourceManager<T>::initialize()
    {
        add(ggj::ResourceName::GraphicsPlayer, "graphics/characters.png");
        add(ggj::ResourceName::GraphicsMagicCliffsTileset, "graphics/magic-cliffs.png");
        add(ggj::ResourceName::GraphicsEnemyBat, "graphics/bat.png");
        add(ggj::ResourceName::GraphicsCrate, "graphics/crate.png");
        add(ggj::ResourceName::GraphicsJumpolini, "graphics/jumpolini.png");
        add(ggj::ResourceName::GraphicsNinjaSmiley, "graphics/ninja.png");
        add(ggj::ResourceName::GraphicsGem1, "graphics/gem1.png");
        add(ggj::ResourceName::GraphicsGem2, "graphics/gem2.png");
        add(ggj::ResourceName::GraphicsGem3, "graphics/gem3.png");
        add(ggj::ResourceName::GraphicsGem4, "graphics/gem4.png");
        add(ggj::ResourceName::MapProject, "maps/gamedev.tiled-project");

        add(ggj::ResourceName::GraphicsBackground01MountainsGrass, "graphics/backgrounds/background01_mountains_grass.png");
        add(ggj::ResourceName::GraphicsBackground02MountainsDesert, "graphics/backgrounds/background02_mountains_desert.png");
        add(ggj::ResourceName::GraphicsBackground03MountainsSnow, "graphics/backgrounds/background03_mountains_snow.png");
        add(ggj::ResourceName::GraphicsBackground04CityNight, "graphics/backgrounds/background04_city_night.png");
        add(ggj::ResourceName::GraphicsBackground05Graveyard, "graphics/backgrounds/background05_graveyard.png");
        add(ggj::ResourceName::GraphicsCharacterHudChar01, "graphics/character_hud/char01.png");
        add(ggj::ResourceName::GraphicsCharacterHudChar02, "graphics/character_hud/char02.png");
        add(ggj::ResourceName::GraphicsCharacterHudChar03, "graphics/character_hud/char03.png");
        add(ggj::ResourceName::GraphicsCharacterHudChar04, "graphics/character_hud/char04.png");
        add(ggj::ResourceName::GraphicsCharacterHudChar05, "graphics/character_hud/char05.png");
        add(ggj::ResourceName::GraphicsCharacterHudChar06, "graphics/character_hud/char06.png");
        add(ggj::ResourceName::GraphicsCharacterHudChar07, "graphics/character_hud/char07.png");
        add(ggj::ResourceName::GraphicsCharacterHudChar08, "graphics/character_hud/char08.png");
        add(ggj::ResourceName::GraphicsCharacterHudChar09, "graphics/character_hud/char09.png");
        add(ggj::ResourceName::GraphicsCharacterHudChar10, "graphics/character_hud/char10.png");
        add(ggj::ResourceName::GraphicsCharacterHudChar11, "graphics/character_hud/char11.png");
        add(ggj::ResourceName::GraphicsCharacterHudChar12, "graphics/character_hud/char12.png");
        add(ggj::ResourceName::GraphicsCharacterHudChar13, "graphics/character_hud/char13.png");
        add(ggj::ResourceName::GraphicsCharacterHudChar14, "graphics/character_hud/char14.png");
        add(ggj::ResourceName::GraphicsCharacterHudChar15, "graphics/character_hud/char15.png");
        add(ggj::ResourceName::GraphicsCharacterHudChar16, "graphics/character_hud/char16.png");
        add(ggj::ResourceName::GraphicsCharacterHudChar17, "graphics/character_hud/char17.png");
        add(ggj::ResourceName::GraphicsCharacterHudChar18, "graphics/character_hud/char18.png");
        add(ggj::ResourceName::GraphicsCharacterHudChar19, "graphics/character_hud/char19.png");
        add(ggj::ResourceName::GraphicsCharacterHudChar20, "graphics/character_hud/char20.png");
        add(ggj::ResourceName::GraphicsCharacterHudChar21, "graphics/character_hud/char21.png");
        add(ggj::ResourceName::GraphicsCharacterHudChar22, "graphics/character_hud/char22.png");
        add(ggj::ResourceName::GraphicsCharacterHudChar23, "graphics/character_hud/char23.png");
        add(ggj::ResourceName::GraphicsCharacterHudChar24, "graphics/character_hud/char24.png");
        add(ggj::ResourceName::GraphicsCharacterHudChar25, "graphics/character_hud/char25.png");
        add(ggj::ResourceName::GraphicsEnemyGhostFlying, "graphics/enemies/ghost/Ghost.png");
        add(ggj::ResourceName::GraphicsEnemySpiderWalk, "graphics/enemies/spider/spider.png");
        add(ggj::ResourceName::GraphicsEnemyThingWalk, "graphics/enemies/thing/thing.png");
        add(ggj::ResourceName::GraphicsExplosion1, "graphics/explosions/explosion-1.png");
        add(ggj::ResourceName::GraphicsExplosion2, "graphics/explosions/explosion-2.png");
        add(ggj::ResourceName::GraphicsExplosion3, "graphics/explosions/explosion-3.png");
        add(ggj::ResourceName::GraphicsExplosion4, "graphics/explosions/explosion-4.png");
        add(ggj::ResourceName::GraphicsExplosion5, "graphics/explosions/explosion-5.png");
        add(ggj::ResourceName::GraphicsExplosion6, "graphics/explosions/explosion-6.png");
        add(ggj::ResourceName::GraphicsHudUiBigPieces, "graphics/hud/ui_big_pieces.png");
        add(ggj::ResourceName::GraphicsMeleeSwoosh, "graphics/melee/swoosh.png");
        add(ggj::ResourceName::GraphicsPlayerSpritemapGreenpants, "graphics/player/player-spritemap-greenpants.png");
        add(ggj::ResourceName::GraphicsPlayerSpritemapGreypants, "graphics/player/player-spritemap-greypants.png");
        add(ggj::ResourceName::GraphicsPlayerSpritemapBluepants, "graphics/player/player-spritemap-bluepants.png");
        add(ggj::ResourceName::GraphicsPlayerSpritemapRedpants, "graphics/player/player-spritemap-redpants.png");
        add(ggj::ResourceName::GraphicsPowerupsRpgIcons, "graphics/powerups/rpg-icons.png");
        add(ggj::ResourceName::GraphicsShootFire, "graphics/shoot/fire/fire.png");
        add(ggj::ResourceName::GraphicsTilesJungleTerrain, "graphics/tiles/jungle_terrain.png");
        add(ggj::ResourceName::GraphicsTilesObjects, "graphics/tiles/objects.png");
        add(ggj::ResourceName::GraphicsCoin, "graphics/coin/coin_full.png");
        add(ggj::ResourceName::GraphicsPortal, "graphics/portal/portalRings.png");

        add(ggj::ResourceName::TopDownForest, "graphics/tiles/complete-top-down_32x32.png");
        add(ggj::ResourceName::RoguePlayer, "graphics/player/Rogue.png");
        add(ggj::ResourceName::WizardPlayer, "graphics/player/Wizard.png");
    }

    template<class T>
    std::string ResourceManager<T>::getResource(T resourceType)
    {
        static std::string defaultStr;
        return (m_resources.count(resourceType) > 0)
                    ? fmt::format("{0}/{1}", m_executableInfo.getContentRootDirectory().string(), m_resources[resourceType])
                    : defaultStr;
    }

    template<class T>
    void ResourceManager<T>::add(T resourceType, std::string value)
    {
        m_resources[resourceType] = value;
    }

    template<class T>
    bool ResourceManager<T>::exists(T resourceType)
    {
        if(m_resources.count(resourceType) > 0)
        {
            std::filesystem::path p = std::filesystem::path(getResource(resourceType));
            return std::filesystem::exists(p);
        }
        return false;
    }

    template<class T>
    std::string ResourceManager<T>::getResource(const std::string &resource)
    {
        return fmt::format("{0}/{1}", m_executableInfo.getContentRootDirectory().string(), resource);
    }

} // dev

#endif //GAME_DEV_TEMPLATE_RESOURCEMANAGER_HPP
