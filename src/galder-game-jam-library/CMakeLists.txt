project(galder-game-jam-library VERSION 1.0.0)

add_library(galder-game-jam-library GalderGameJamLibrary.h managers/GameManager.cpp managers/GameManager.h
        managers/ResourceManager.hpp managers/InputManager.cpp managers/InputManager.h enums/KeyboardKey.h
        managers/WorldManager.cpp managers/WorldManager.h system/World.cpp system/World.h
        enums/TextureName.h system/Mapper.hpp managers/TextureManager.h managers/TextureManager.cpp interfaces/system/IMapper.h
        system/WorldLayer.cpp system/WorldLayer.h graphics/Sprite.cpp graphics/Sprite.h graphics/PhysicsObject.cpp
        graphics/PhysicsObject.h enums/PhysicsShape.h graphics/PhysicsSprite.cpp graphics/PhysicsSprite.h
        managers/CollisionManager.cpp managers/CollisionManager.h managers/DummyDebugManager.hpp
        managers/DebugManager.cpp managers/DebugManager.h game/Player.cpp game/Player.h game/Player2.cpp game/Player2.h
        managers/AnimationManager.cpp managers/AnimationManager.h graphics/Animation.cpp
        graphics/Animation.h graphics/Frame.hpp enums/AnimationName.h enums/PlayerState.h
        system/UserData.hpp enums/ObjectType.h interfaces/manager/IUserDataManager.h managers/UserDataManager.hpp
        game/enemies/Bat.cpp game/enemies/Bat.h system/ObjectGeneratorData.hpp
        game/enemies/Snake.cpp game/enemies/Snake.h game/collectibles/Coin.cpp game/collectibles/Coin.h
        game/enemies/Spider.cpp game/enemies/Spider.h game/enemies/Thing.cpp game/enemies/Thing.h
        game/enemies/Ghost.cpp game/enemies/Ghost.h game/interactables/Portal.cpp game/interactables/Portal.h
        game/interactables/PowerUp.cpp game/interactables/PowerUp.h game/Hitbox.hpp
        game/projectiles/MageBall.hpp
        game/projectiles/Projectile.cpp
        game/projectiles/Projectile.h)
