#pragma once

#include <Graphics.hpp>
#include "engine/menus/textmenu.h"

#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>

namespace game::defs
{
    static constexpr auto WINDOW_NAME = "snake";
    static constexpr auto VERSION = "0.1.0";
    constexpr auto FPS_CAP = 144.f;

    static inline const auto ORIGINAL_RES = sf::Vector2f(1280, 720);
    static inline const auto DISPLAY_RESOLUTION = sf::Vector2f(ORIGINAL_RES.x * 1.5, ORIGINAL_RES.y * 1.5);

    // Fonts
    constexpr auto FALLBACK_FONT = "../snake/resources/fonts/Roboto-Regular.ttf";
    constexpr auto COLLEGES_FONT = "../snake/resources/fonts/colleges.ttf";

    // Logos
    constexpr auto SFML_LOGO = "../snake/resources/texture/sfml_logo.png";
    constexpr auto MIXKIT_LOGO = "../snake/resources/texture/mixkit_logo.png";
    constexpr auto FMA_LOGO = "../snake/resources/texture/fma_logo.jpg";

    // Textures
    constexpr auto MAINMENU_STATE_FRAME = "../snake/resources/texture/main_frame.png";
    constexpr auto GAME_STATE_FRAME = "../snake/resources/texture/game_frame.png";
    constexpr auto MENU_FRAME = "../snake/resources/texture/menu_frame.png";
    constexpr auto SNAKE_IMAGE_WITH_TEXT = "../snake/resources/texture/snake_with_text.png";

    // Sounds
    constexpr auto HOVER_SOUND = "../snake/resources/sfx/hover.wav";
    constexpr auto INTRO_SOUND = "../snake/resources/sfx/intro_sound.wav";
    constexpr auto UI_IN_SOUND = "../snake/resources/sfx/in.wav";
    constexpr auto UI_OUT_SOUND = "../snake/resources/sfx/out.wav";

    // Music
    constexpr auto MENU_STATE_MUSIC = "../snake/resources/sfx/menu_music.wav";

    // Parallax
    constexpr auto PARALLAX_L1 = "../snake/resources/texture/parallax/L1.png";
    constexpr auto PARALLAX_L2 = "../snake/resources/texture/parallax/L2.png";
    constexpr auto PARALLAX_L3 = "../snake/resources/texture/parallax/L3.png";
    constexpr auto PARALLAX_L4 = "../snake/resources/texture/parallax/L4.png";
    constexpr auto PARALLAX_L5 = "../snake/resources/texture/parallax/L5.png";
    constexpr auto PARALLAX_L6 = "../snake/resources/texture/parallax/L6.png";

    // Other constants
    constexpr auto MAX_8_BIT_VAL = 255;
    constexpr auto MIN_8_BIT_VAL = 0;
}
