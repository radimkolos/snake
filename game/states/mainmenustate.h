#pragma once

#include <iostream>
#include <utility>

#include <SFML/Graphics.hpp>

#include <fmt/format.h>

#include "engine/animations/parallax.h"
#include "engine/menus/textmenu.h"

#include "game/states/splashstate.h"
#include "game/types/gamedata.h"
#include "game/definitions.h"

using game::defs::DISPLAY_RESOLUTION;
using game::defs::ORIGINAL_RES;
using game::defs::MAX_8_BIT_VAL;

namespace game::states
{
    namespace internal
    {
        enum class EScreen
        {
            MENU,
            SETTINGS,
            CREDITS
        };
    }

    class MainMenuState final : public engine::state::IState
    {
    public:
        MainMenuState(std::shared_ptr<engine::GameData> aGameData);

        void init() override;
        void handleInput() override;
        void update(const double aDelta) override;
        void draw() override;

    private:
        std::shared_ptr<engine::GameData> _gameData;

        engine::animations::Parallax _parallaxBg;

        engine::menu::TextMenu _menu;
        engine::menu::TextMenu _settingsMenu;
        engine::menu::TextMenu _creditsMenu;

        sf::Text _copyrightText;

        sf::Sprite _mainFrame;
        sf::Sprite _gameFrame;
        sf::Sprite _menuFrame;
        sf::Sprite _snakeImage;

        sf::Sound _menuMusic;

        sf::Sound _uiInSound;
        sf::Sound _uiOutSound;

        internal::EScreen _currentScreen = internal::EScreen::MENU;

    private:
        static constexpr auto START_GAME_STRING = "Start Game";
        static constexpr auto SETTINGS_STRING = "Options";
        static constexpr auto CREDITS_STRING = "Credits";
        static constexpr auto EXIT_STRING = "Quit game";
        static constexpr auto CLOSE_STRING = "Close";

        inline static const auto MENU_TEXT_FONT_SIZE    = uint16_t(DISPLAY_RESOLUTION.x / ORIGINAL_RES.x * 25);
        inline static const auto MENU_TEXT_ITEM_SPACING = uint16_t(DISPLAY_RESOLUTION.x / ORIGINAL_RES.x * 15);
        inline static const auto MENU_TEXT_INDENTATION  = sf::Vector2i(DISPLAY_RESOLUTION.x / ORIGINAL_RES.x * 0 , DISPLAY_RESOLUTION.y / ORIGINAL_RES.y * 125);
        static constexpr auto MENU_TEXT_ITEM_ALIGNMENT  = engine::enums::ETextAlignment::CENTER;


        inline static const auto MENU_TEXT_HOVER_COLOR  = sf::Color(100, 100, 100, MAX_8_BIT_VAL); // sf::Color(89,  150, 8,   MAX_8_BIT_VAL);
        inline static const auto MENU_TEXT_NORMAL_COLOR = sf::Color(MAX_8_BIT_VAL, MAX_8_BIT_VAL, MAX_8_BIT_VAL, MAX_8_BIT_VAL);
    };
}
