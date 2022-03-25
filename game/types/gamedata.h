#pragma once

#include "engine/managers/assetmanager.h"
#include "engine/managers/inputmanager.h"
#include "engine/managers/statemanager.h"

namespace engine
{
    struct GameData
    {
        sf::RenderWindow window;

        engine::manager::StateManager statePool;

        engine::manager::ResourceManager<sf::Texture> textureManager;
        engine::manager::ResourceManager<sf::Font> fontManager;
        engine::manager::ResourceManager<sf::SoundBuffer> soundBufferManager;

        game::manager::InputManager inputManager;
    };
}

