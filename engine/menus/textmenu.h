#pragma once

#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "engine/managers/assetmanager.h"
#include "engine/types/menuoptions.h"
#include "engine/enums/textalignment.h"
#include "engine/enums/movedirection.h"

namespace engine::menu
{
    class TextMenu
    {
    public:
        TextMenu(const sf::Vector2u& aWindowSize, const std::vector<std::string>& aStrings);

        void setOptions(const game::types::MenuOptions& aOptions);
        void change(engine::enums::EMoveDirection aDirection);

        void update(const sf::Vector2f& aMousePosition);
        void draw(sf::RenderWindow& aWindow);

        void reposition();

        [[nodiscard]] std::string selectedString() const noexcept;
        [[nodiscard]] sf::FloatRect selectedGlobalBounds() const noexcept;

    private:
        void select(sf::Text &aSelect, bool aPlaySound = true);
        void deselect();

        std::vector<sf::Text> _text;
        game::types::MenuOptions _options {};
        sf::Text* _selected = nullptr;

        sf::Vector2u _windowSize {};
    };
}
