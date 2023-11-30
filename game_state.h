#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "state.h"

class Game_State : public State 
{
    public:

        Game_State();

        std::shared_ptr<State> update(sf::Time delta) override;

        void render(sf::RenderWindow &to) override;

        sf::RectangleShape player;
        
        sf::Vector2f location{300, 300};
        
        float spin{};
};

#endif