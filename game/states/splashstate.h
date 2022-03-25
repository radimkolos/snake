#pragma once

#include <iostream>
#include <sstream>
#include <thread>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "engine/interfaces/istate.h"

#include "game/types/gamedata.h"
#include "game/states/mainmenustate.h"
#include "game/definitions.h"

namespace game::states
{
    class SplashScreenState final : public engine::state::IState
    {
    public:
        explicit SplashScreenState(std::shared_ptr<engine::GameData> aGameData);

        void init() override;
        void handleInput() override;
        void update(double aDelta) override;
        void draw() override;

    private:
        std::shared_ptr<engine::GameData> _gameData;
        sf::Clock _clock {};
        std::vector<sf::Sprite> _logos;
        sf::Sound _introSound;
        size_t _currentIndex = 0;
        bool _skip = false;

    private:
        static constexpr auto DISPLAY_DURATION = 2000;
        static constexpr auto FADE_IN_DURATION = 500;
        static constexpr auto FADE_OUT_DURATION = 100;
    };
}
