#pragma once

#include <memory>
#include <vector>

#include "engine/interfaces/istate.h"

namespace engine::manager
{
    class StateManager final
    {
    public:
        StateManager() = default;

        void addState(std::unique_ptr<engine::state::IState> aNewState, bool aReplace = true) noexcept
        {
            if(!_stack.empty())
            {
                aReplace ? _stack.pop_back() : _stack.back()->pause();
            }

            _stack.emplace_back(std::move(aNewState));

            _stack.back()->init();
        };

        void removeState() noexcept
        {
            if(!_stack.empty())
            {
                _stack.pop_back();

                if(!_stack.empty())
                {
                    _stack.back()->resume();
                }
            }
        };

        [[nodiscard]] std::unique_ptr<engine::state::IState>& getActiveState()
        {
            return _stack.back();
        };

    private:
        std::vector<std::unique_ptr<engine::state::IState>> _stack;
    };
}
