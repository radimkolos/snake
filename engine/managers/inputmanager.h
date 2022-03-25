#pragma once

#include <SFML/Graphics.hpp>

namespace game::manager
{
    class InputManager
    {
    public:
        /**
         * @brief Check if sf::Sprite has been clicked on
         *
         * @param aSprite The sprite to be checked
         * @param aButton A reference to the mouse button
         * @param aWindow A window to search in
         *
         * @return True if sprite has been clicked, otherwise false
         */
        bool isSpriteClicked(const sf::Sprite& aSprite, const sf::Mouse::Button& aButton, const sf::RenderWindow& aWindow) noexcept
        {
            if(sf::Mouse::isButtonPressed(aButton) && aSprite.getTextureRect().contains(sf::Mouse::getPosition(aWindow)))
            {
                return true;
            }
            else
            {
                return false;
            }
        };
    };
}

