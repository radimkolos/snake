#pragma once

#include <SFML/Graphics.hpp>

namespace engine::animations
{
    class Parallax
    {
    public:
        explicit Parallax(const sf::Vector2f& aWindowSize)
            : _windowSize(aWindowSize)
        {

        };

        void addImage(sf::Texture& aTexture, uint16_t aPxPerSecond) noexcept
        {
            aTexture.setRepeated(true);

            const auto& scaledPxPerSecond = static_cast<uint16_t>(_windowSize.x) / aTexture.getSize().x * aPxPerSecond;

            _parallax.emplace_back(aTexture, scaledPxPerSecond);

            const auto& textureSize = _parallax.back().first.getTexture()->getSize();

            _parallax.back().first.setScale(_windowSize.x / static_cast<float>(textureSize.x), _windowSize.y / static_cast<float>(textureSize.y));
            _parallax.back().first.setTextureRect({0, 0, static_cast<int>(_windowSize.x * 2), static_cast<int>(_windowSize.y)});
        };

        void update(float aDeltaTime) noexcept
        {
            for(auto& sprite : _parallax)
            {
                sprite.first.move(-sprite.second * aDeltaTime, 0);

                if(sprite.first.getPosition().x < -_windowSize.x)
                {
                    sprite.first.setPosition(0, 0);
                }
            }
        };

        void draw(sf::RenderWindow& aWindow)
        {
            for(const auto& p : _parallax)
            {
                aWindow.draw(p.first);
            }
        }

        [[nodiscard]] std::vector<std::pair<sf::Sprite, float>> getParallax() const noexcept
        {
            return _parallax;
        }

    private:
        std::vector<std::pair<sf::Sprite, float>> _parallax;
        sf::Vector2f _windowSize;
    };
}
