#include "textmenu.h"

engine::menu::TextMenu::TextMenu(const sf::Vector2u &aWindowSize, const std::vector<std::string>& aStrings)
    : _windowSize(aWindowSize)
{
    _text.reserve(aStrings.size());

    for(const auto& s : aStrings)
    {
        _text.emplace_back(sf::Text(s, sf::Font(), 1));
    }
}

void engine::menu::TextMenu::setOptions(const game::types::MenuOptions& aOptions)
{
    _options = aOptions;

    for(auto& t : _text)
    {
        t.setFont(_options.font);
        t.setCharacterSize(_options.characterSize);
    }

    reposition();

    _selected = &_text.front();

    select(*_selected, false);
}

void engine::menu::TextMenu::change(engine::enums::EMoveDirection aDirection)
{
    if(_selected == nullptr)
    {
        select(_text.front());

        return;
    }

    size_t index = 0;

    for(auto& text : _text)
    {
        if(_selected == &text)
        {
            switch(aDirection)
            {
            case engine::enums::EMoveDirection::DOWN:
            {
                &text == &_text.back() ? select(_text.front()) : select(_text[index + 1]);

                break;
            }
            case engine::enums::EMoveDirection::UP:
            {
                &text == &_text.front() ? select(_text.back()) : select(_text[index - 1]);

                break;
            }
            default:
            {
            }
            }

            return;
        }

        index++;
    }
}

void engine::menu::TextMenu::update(const sf::Vector2f& aMousePosition)
{
    static sf::Vector2f previousMousePosition = aMousePosition;

    if(_selected != nullptr && !_selected->getGlobalBounds().contains(aMousePosition) && previousMousePosition != aMousePosition)
    {
        deselect();
    }
    if(_selected == nullptr)
    {
        for(auto& text : _text)
        {
            if(text.getGlobalBounds().contains(aMousePosition))
            {
                select(text);

                break;
            }
        }
    }

    previousMousePosition = aMousePosition;
}

void engine::menu::TextMenu::draw(sf::RenderWindow &aWindow)
{
    for(const auto& t : _text)
    {
        aWindow.draw(t);
    }
}

std::string engine::menu::TextMenu::selectedString() const noexcept
{
    return _text.empty() || !_selected ? "" : _selected->getString();
}

sf::FloatRect engine::menu::TextMenu::selectedGlobalBounds() const noexcept
{
    return _text.empty() || !_selected ? sf::FloatRect() : _selected->getGlobalBounds();
}

void engine::menu::TextMenu::reposition()
{
    // Calculate menu height
    auto menuHeight = _options.itemSpacing * _text.size() - _options.itemSpacing;

    for(auto& text : _text)
    {
        menuHeight += text.getGlobalBounds().height;
    }

    // Position text
    const auto& window_X_center = _windowSize.x / 2;
    const auto& window_Y_center = _windowSize.y / 2;

    auto Y_pos = window_Y_center - (menuHeight / 2);

    for(auto& text : _text)
    {
        auto X_Pos = 0;

        switch(_options.alignment)
        {
        case engine::enums::ETextAlignment::CENTER:
        {
            X_Pos = window_X_center - (text.getGlobalBounds().width / 2) + _options.indentation.x;

            break;
        }
        case engine::enums::ETextAlignment::LEFT:
        {
            X_Pos = _options.indentation.x;

            break;
        }
        case engine::enums::ETextAlignment::RIGHT:
        {
            X_Pos = _windowSize.x - text.getGlobalBounds().width + _options.indentation.x;

            break;
        }
        }

        text.setPosition(X_Pos, Y_pos + _options.indentation.y);

        Y_pos += text.getGlobalBounds().height + _options.itemSpacing;
    }
}

void engine::menu::TextMenu::select(sf::Text& aSelect, bool aPlaySound)
{
    if(aPlaySound)
    {
        _options.hoverSound.play();
    }

    if(_selected != nullptr)
    {
        _selected->setFillColor(_options.normalTextColor);
    }

    _selected = &aSelect;

    _selected->setFillColor(_options.hoveringTextColor);
}

void engine::menu::TextMenu::deselect()
{
    _selected->setFillColor(_options.normalTextColor);

    _selected = nullptr;
}

