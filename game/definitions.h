#pragma once

#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>

#include <SFML/Graphics.hpp>

#include "engine/menus/textmenu.h"

namespace game::defs
{
    static constexpr auto WINDOW_NAME = "Snake";
    static constexpr auto VERSION = "0.1.0";
    constexpr auto FPS_CAP = 144.f;

    static inline const auto ORIGINAL_RES = sf::Vector2f(1280, 720);
    static inline const auto DISPLAY_RESOLUTION = sf::Vector2f(ORIGINAL_RES.x * 1.5, ORIGINAL_RES.y * 1.5);

    // Fonts
    constexpr auto FALLBACK_FONT = "../Snake/resources/fonts/Roboto-Regular.ttf";
    constexpr auto COLLEGES_FONT = "../Snake/resources/fonts/colleges.ttf";

    // Logos
    constexpr auto SFML_LOGO = "../Snake/resources/texture/sfml_logo.png";
    constexpr auto MIXKIT_LOGO = "../Snake/resources/texture/mixkit_logo.png";
    constexpr auto FMA_LOGO = "../Snake/resources/texture/fma_logo.jpg";

    // Textures
    constexpr auto MAINMENU_STATE_FRAME = "../Snake/resources/texture/main_frame.png";
    constexpr auto GAME_STATE_FRAME = "../Snake/resources/texture/game_frame.png";
    constexpr auto MENU_FRAME = "../Snake/resources/texture/menu_frame.png";
    constexpr auto SNAKE_IMAGE_WITH_TEXT = "../Snake/resources/texture/snake_with_text.png";

    // Sounds
    constexpr auto HOVER_SOUND = "../Snake/resources/sfx/hover.wav";
    constexpr auto INTRO_SOUND = "../Snake/resources/sfx/intro_sound.wav";
    constexpr auto UI_IN_SOUND = "../Snake/resources/sfx/in.wav";
    constexpr auto UI_OUT_SOUND = "../Snake/resources/sfx/out.wav";

    // Music
    constexpr auto MENU_STATE_MUSIC = "../Snake/resources/sfx/menu_music.wav";

    // Parallax
    constexpr auto PARALLAX_L1 = "../Snake/resources/texture/parallax/L1.png";
    constexpr auto PARALLAX_L2 = "../Snake/resources/texture/parallax/L2.png";
    constexpr auto PARALLAX_L3 = "../Snake/resources/texture/parallax/L3.png";
    constexpr auto PARALLAX_L4 = "../Snake/resources/texture/parallax/L4.png";
    constexpr auto PARALLAX_L5 = "../Snake/resources/texture/parallax/L5.png";
    constexpr auto PARALLAX_L6 = "../Snake/resources/texture/parallax/L6.png";

    // Other constants
    constexpr auto MAX_8_BIT_VAL = 255;
    constexpr auto MIN_8_BIT_VAL = 0;
}
