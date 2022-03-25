#include "splashstate.h"

using game::defs::MAX_8_BIT_VAL;
using game::defs::MIN_8_BIT_VAL;

game::states::SplashScreenState::SplashScreenState(std::shared_ptr<engine::GameData> aGameData)
    : _gameData(std::move(aGameData))
{

}

void game::states::SplashScreenState::init()
{
    const auto& windowSize = static_cast<sf::Vector2f>(_gameData->window.getSize());
    const auto& windowCenter = sf::Vector2f(windowSize.x / 2, windowSize.y / 2);
    const auto& textureScale = sf::Vector2f(windowSize.x / game::defs::ORIGINAL_RES.x, windowSize.y / game::defs::ORIGINAL_RES.y);

    auto& textureManager = _gameData->textureManager;
    auto& soundBufferManager = _gameData->soundBufferManager;

    _introSound.setBuffer(soundBufferManager.loadFromFile(game::defs::INTRO_SOUND));

    textureManager.loadFromFile(game::defs::SFML_LOGO);
    textureManager.loadFromFile(game::defs::MIXKIT_LOGO);
    textureManager.loadFromFile(game::defs::FMA_LOGO);

    _logos.emplace_back(textureManager.getAsset(game::defs::FMA_LOGO));
    _logos.emplace_back(textureManager.getAsset(game::defs::MIXKIT_LOGO));
    _logos.emplace_back(textureManager.getAsset(game::defs::SFML_LOGO));

    for(auto& logo : _logos)
    {
        logo.setScale(textureScale);
        logo.setPosition(windowCenter.x - logo.getGlobalBounds().width / 2, windowCenter.y - logo.getGlobalBounds().height / 2);
        logo.setColor(sf::Color(MAX_8_BIT_VAL, MAX_8_BIT_VAL, MAX_8_BIT_VAL, MIN_8_BIT_VAL));
    }

    _introSound.play();
}

void game::states::SplashScreenState::handleInput()
{   
    sf::Event event {};

    while(_gameData->window.pollEvent(event))
    {
        if(event.type == sf::Event::KeyPressed)
        {
            _skip = true;
        }
    }
}

void game::states::SplashScreenState::update([[maybe_unused]] double aDelta)
{
    const auto& timeOnUpdate = _clock.getElapsedTime().asMilliseconds();

    _currentIndex = timeOnUpdate / DISPLAY_DURATION;

    if(_currentIndex >= _logos.size() || _skip)
    {
        _gameData->statePool.addState(std::make_unique<MainMenuState>(_gameData));

        return;
    }

    const auto& duration = static_cast<float>(timeOnUpdate % DISPLAY_DURATION);

    if(duration <= FADE_IN_DURATION)
    {
        const auto& newColor = sf::Color(MAX_8_BIT_VAL, MAX_8_BIT_VAL, MAX_8_BIT_VAL, static_cast<uint8_t>(duration / FADE_IN_DURATION * MAX_8_BIT_VAL));

        _logos[_currentIndex].setColor(newColor);
    }
    else if(duration >= DISPLAY_DURATION - FADE_OUT_DURATION)
    {
        const auto& newColor = sf::Color(MAX_8_BIT_VAL, MAX_8_BIT_VAL, MAX_8_BIT_VAL, static_cast<uint8_t>(DISPLAY_DURATION - duration / FADE_OUT_DURATION) * MAX_8_BIT_VAL);

        _logos[_currentIndex].setColor(newColor);
    }
}

void game::states::SplashScreenState::draw()
{
    _gameData->window.clear();

    _gameData->window.draw(_logos[_currentIndex]);

    _gameData->window.display();
}
