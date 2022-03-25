#include "game/states/splashstate.h"
#include "game/definitions.h"

int main()
{
    std::shared_ptr<engine::GameData> gameData = std::make_shared<engine::GameData>();

    gameData->window.create(sf::VideoMode(game::defs::DISPLAY_RESOLUTION.x, game::defs::DISPLAY_RESOLUTION.y), game::defs::WINDOW_NAME, sf::Style::Resize);
    gameData->statePool.addState(std::make_unique<game::states::SplashScreenState>(gameData));

    const sf::Clock _clock {};

    const auto& frameTime = 1.F / game::defs::FPS_CAP;

    auto previous = 0.F;
    auto delta = 0.F;

    while(gameData->window.isOpen())
    {
        const auto& now = _clock.getElapsedTime().asSeconds();

        delta += now - previous;
        previous = now;

        if(delta >= frameTime)
        {
            gameData->statePool.getActiveState()->handleInput();
            gameData->statePool.getActiveState()->update(delta);

            delta = delta - frameTime;
        }

        gameData->statePool.getActiveState()->draw();
    }

    return EXIT_SUCCESS;
}
