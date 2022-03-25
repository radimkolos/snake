#pragma once

#include <string>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace engine::manager
{
    template<typename T>
    class ResourceManager
    {
    public:
        T& loadFromFile(const std::string& aFileName)
        requires(std::is_member_function_pointer_v<decltype(&T::loadFromFile)>)
        {
            T asset;

            if(_assets.count(aFileName) == 0)
            {
                if(asset.loadFromFile(aFileName))
                {
                    _assets[aFileName] = std::move(asset);

                    return _assets[aFileName];
                }
            }

            return _assets[aFileName];
        };

        [[nodiscard]] T& getAsset(const std::string& aFileName) noexcept
        {
            return _assets[aFileName];
        };

    private:
        std::map<std::string, T> _assets;
    };
}
