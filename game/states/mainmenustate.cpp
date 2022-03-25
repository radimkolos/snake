#include "mainmenustate.h"

using namespace game::defs;

game::states::MainMenuState::MainMenuState(std::shared_ptr<engine::GameData> aGameData)
    : _gameData(std::move(aGameData))
    , _parallaxBg({static_cast<float>(_gameData->window.getSize().x), static_cast<float>(_gameData->window.getSize().y)})
    , _menu({_gameData->window.getSize()}, {START_GAME_STRING, SETTINGS_STRING, CREDITS_STRING, EXIT_STRING})
    , _settingsMenu({_gameData->window.getSize()},{CLOSE_STRING})
    , _creditsMenu({_gameData->window.getSize()},{CLOSE_STRING})
{

}

void game::states::MainMenuState::init()
{
    const auto& wSize = static_cast<sf::Vector2f>(_gameData->window.getSize());
    const auto& wCenter = sf::Vector2f(wSize.x / 2, wSize.y / 2);
    const auto& wScale = sf::Vector2f(wSize.x / ORIGINAL_RES.x, wSize.y / ORIGINAL_RES.y);

    auto& fMngr = _gameData->fontManager;
    auto& tMngr = _gameData->textureManager;
    auto& sbMngr = _gameData->soundBufferManager;

    const auto& font = fMngr.loadFromFile(COLLEGES_FONT);

    _uiInSound.setBuffer(sbMngr.loadFromFile(UI_IN_SOUND));
    _uiOutSound.setBuffer(sbMngr.loadFromFile(UI_OUT_SOUND));

    _menuMusic.setBuffer(sbMngr.loadFromFile(MENU_STATE_MUSIC));
    _menuMusic.setLoop(true);
    _menuMusic.play();

    game::types::MenuOptions menuOptions
    {
        _gameData->fontManager.getAsset(COLLEGES_FONT),
        MENU_TEXT_FONT_SIZE, MENU_TEXT_ITEM_ALIGNMENT, MENU_TEXT_INDENTATION,
        static_cast<float>(MENU_TEXT_ITEM_SPACING), MENU_TEXT_HOVER_COLOR, MENU_TEXT_NORMAL_COLOR,
        sf::Sound(_gameData->soundBufferManager.loadFromFile(HOVER_SOUND))
    };

    _menu.setOptions(menuOptions);
    _settingsMenu.setOptions(menuOptions);
    _creditsMenu.setOptions(menuOptions);

    _parallaxBg.addImage(tMngr.loadFromFile(PARALLAX_L1), 1);
    _parallaxBg.addImage(tMngr.loadFromFile(PARALLAX_L2), 2);
    _parallaxBg.addImage(tMngr.loadFromFile(PARALLAX_L3), 3);
    _parallaxBg.addImage(tMngr.loadFromFile(PARALLAX_L4), 9);
    _parallaxBg.addImage(tMngr.loadFromFile(PARALLAX_L5), 12);
    _parallaxBg.addImage(tMngr.loadFromFile(PARALLAX_L6), 15);

    _mainFrame.setTexture(tMngr.loadFromFile(MAINMENU_STATE_FRAME));
    _gameFrame.setTexture(tMngr.loadFromFile(GAME_STATE_FRAME));
    _menuFrame.setTexture(tMngr.loadFromFile(MENU_FRAME));
    _snakeImage.setTexture(tMngr.loadFromFile(SNAKE_IMAGE_WITH_TEXT));

    _mainFrame.setScale(wScale);
    _gameFrame.setScale(wScale);
    _menuFrame.setScale(wScale);
    _snakeImage.setScale(wScale);

    _menuFrame.setPosition(wCenter.x - _menuFrame.getGlobalBounds().width / 2, wCenter.y + _menuFrame.getGlobalBounds().height / 100 * 20);
    _snakeImage.setPosition(wCenter.x - _snakeImage.getGlobalBounds().width / 2, wCenter.y - _snakeImage.getGlobalBounds().height);

    _mainFrame.setColor({MAX_8_BIT_VAL, MAX_8_BIT_VAL, MAX_8_BIT_VAL, 220});
    _gameFrame.setColor({MAX_8_BIT_VAL, MAX_8_BIT_VAL, MAX_8_BIT_VAL, 220});
    _menuFrame.setColor({MAX_8_BIT_VAL, MAX_8_BIT_VAL, MAX_8_BIT_VAL, 220});

    _copyrightText = sf::Text(fmt::format("Copyright Gamospace. All rights reserved. Version {}", VERSION), font, MENU_TEXT_FONT_SIZE / 1.5);

    _copyrightText.setPosition(wSize.x / 2 - _copyrightText.getGlobalBounds().width / 2, wSize.y - _copyrightText.getGlobalBounds().height * 2);
}

void game::states::MainMenuState::handleInput()
{
    sf::Event event {};
    sf::Vector2f mouse(sf::Mouse::getPosition(_gameData->window));

    while(_gameData->window.pollEvent(event))
    {
        if(event.type == sf::Event::KeyPressed)
        {
            switch(_currentScreen)
            {
            case internal::EScreen::MENU :
            {
                if(event.key.code == sf::Keyboard::Down)
                {
                    _menu.change(engine::enums::EMoveDirection::DOWN);
                }
                else if(event.key.code == sf::Keyboard::Up)
                {
                    _menu.change(engine::enums::EMoveDirection::UP);
                }
                else if(event.key.code == sf::Keyboard::Enter)
                {
                    _uiInSound.play();

                    const auto& selected = _menu.selectedString();

                    if(selected == START_GAME_STRING)
                    {
                        return;
                    }
                    else if(selected == SETTINGS_STRING)
                    {
                        _currentScreen = internal::EScreen::SETTINGS;
                    }
                    else if(selected == CREDITS_STRING)
                    {
                        _currentScreen = internal::EScreen::CREDITS;
                    }
                    else
                    {
                        _gameData->window.close();
                    }

                }
                else if(event.key.code == sf::Keyboard::Escape)
                {

                }

                break;
            }
            case internal::EScreen::SETTINGS :
            {
                if(event.key.code == sf::Keyboard::Down)
                {
                    _settingsMenu.change(engine::enums::EMoveDirection::DOWN);
                }
                else if(event.key.code == sf::Keyboard::Up)
                {
                    _settingsMenu.change(engine::enums::EMoveDirection::UP);
                }
                else if(event.key.code == sf::Keyboard::Enter)
                {
                    if(_settingsMenu.selectedString() == CLOSE_STRING)
                    {
                        _uiOutSound.play();

                        _currentScreen = internal::EScreen::MENU;
                    }
                }
                else if(event.key.code == sf::Keyboard::Escape)
                {
                    _uiOutSound.play();

                    _currentScreen = internal::EScreen::MENU;
                }

                break;
            }
            case internal::EScreen::CREDITS :
            {
                if(event.key.code == sf::Keyboard::Down)
                {
                    _creditsMenu.change(engine::enums::EMoveDirection::DOWN);
                }
                else if(event.key.code == sf::Keyboard::Up)
                {
                    _creditsMenu.change(engine::enums::EMoveDirection::UP);
                }
                else if(event.key.code == sf::Keyboard::Enter)
                {
                    if(_creditsMenu.selectedString() == CLOSE_STRING)
                    {
                        _uiOutSound.play();

                        _currentScreen = internal::EScreen::MENU;
                    }
                }
                else if(event.key.code == sf::Keyboard::Escape)
                {
                    _uiOutSound.play();

                    _currentScreen = internal::EScreen::MENU;
                }

                break;
            }
            }
        }
        else if(event.type == sf::Event::MouseButtonPressed)
        {
            switch(_currentScreen)
            {
            case internal::EScreen::MENU:
            {
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    if(_menu.selectedString() == START_GAME_STRING && _menu.selectedGlobalBounds().contains(mouse))
                    {
                        _uiInSound.play();
                    }
                    else if(_menu.selectedString() == SETTINGS_STRING && _menu.selectedGlobalBounds().contains(mouse))
                    {
                        _uiInSound.play();

                        _currentScreen = internal::EScreen::SETTINGS;
                    }
                    else if(_menu.selectedString() == CREDITS_STRING && _menu.selectedGlobalBounds().contains(mouse))
                    {
                        _uiInSound.play();

                        _currentScreen = internal::EScreen::CREDITS;
                    }
                    else if(_menu.selectedString() == EXIT_STRING && _menu.selectedGlobalBounds().contains(mouse))
                    {
                        _gameData->window.close();
                    }
                }

                break;
            }
            case internal::EScreen::SETTINGS:
            {
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    if(_settingsMenu.selectedString() == CLOSE_STRING && _settingsMenu.selectedGlobalBounds().contains(mouse))
                    {
                         _uiOutSound.play();

                        _currentScreen = internal::EScreen::MENU;
                    }
                }

                break;
            }
            case internal::EScreen::CREDITS:
            {
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    if(_creditsMenu.selectedString() == CLOSE_STRING && _creditsMenu.selectedGlobalBounds().contains(mouse))
                    {
                        _uiOutSound.play();

                        _currentScreen = internal::EScreen::MENU;
                    }
                }

                break;
            }
            }
        }
    }
}

void game::states::MainMenuState::update(const double aDelta)
{
    _parallaxBg.update(aDelta);

    const auto& mousePosition = sf::Vector2f(sf::Mouse::getPosition(_gameData->window));

    switch(_currentScreen)
    {
    case internal::EScreen::MENU:
    {
        _menu.update(mousePosition);

        break;
    }
    case internal::EScreen::SETTINGS:
    {
        _settingsMenu.update(mousePosition);

        break;
    }
    case internal::EScreen::CREDITS:
    {
        _creditsMenu.update(mousePosition);

        break;
    }
    }
}

void game::states::MainMenuState::draw()
{
    _gameData->window.clear(sf::Color(10,20,30,255));

    _parallaxBg.draw(_gameData->window);

    _gameData->window.draw(_mainFrame);

    switch(_currentScreen)
    {
    case internal::EScreen::MENU:
    {
        _gameData->window.draw(_menuFrame);
        _gameData->window.draw(_snakeImage);
        _gameData->window.draw(_copyrightText);

        _menu.draw(_gameData->window);

        break;
    }
    case internal::EScreen::SETTINGS:
    {
        _settingsMenu.draw(_gameData->window);

        break;
    }
    case internal::EScreen::CREDITS:
    {
        _creditsMenu.draw(_gameData->window);

        break;
    }
    }

    _gameData->window.display();
}
