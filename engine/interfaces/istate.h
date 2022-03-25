#pragma once

namespace engine::state
{
    class IState
    {
    public:
        IState() = default;
        virtual ~IState() = default;

        IState(IState&& other) = default;
        IState(const IState&) = default;
        IState& operator=(const IState&) = default;
        IState& operator=(IState&&) = default;

        virtual void init() = 0;
        virtual void handleInput() = 0;
        virtual void update(double aDelta) = 0;
        virtual void draw() = 0;

        virtual void pause()
        {
            _paused = true;
        };

        virtual void resume()
        {
            _paused = false;
        };

    private:
        bool _paused = false;
    };
}
