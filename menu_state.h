#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "state.h"
#include <functional>
#include <vector>

class Menu_State : public State 
{
    public:

        Menu_State(std::shared_ptr<State> resume = nullptr, int score = 0);

        void on_key_press(sf::Keyboard::Key key) override;

        std::shared_ptr<State> update(sf::Time time) override;

        void render(sf::RenderWindow &draw) override;

    private:
        using Action = std::function<std::shared_ptr<State>()>;
        struct Entry{
            sf::Text text;
            float state;
            Action action;
        };

        std::vector<Entry> entries;

        size_t selected;

        sf::Font font;

        bool enter_pressed;

        sf::Time delay;

        std::shared_ptr<State> background;

        void add(const std::string &text, Action action);

        int score;

        sf::Text scoretext;
        sf::Text titletext;

};

#endif