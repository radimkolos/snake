#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "engine/enums/textalignment.h"

namespace game::types
{
    struct MenuOptions
    {
        sf::Font font {};
        uint16_t characterSize;
        engine::enums::ETextAlignment alignment;
        sf::Vector2i indentation;
        float itemSpacing;
        sf::Color hoveringTextColor;
        sf::Color normalTextColor;
        sf::Sound hoverSound {};
    };
}
