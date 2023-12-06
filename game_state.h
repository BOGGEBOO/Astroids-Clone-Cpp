#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "state.h"
#include "world.h"

class Game_State : public State 
{
    private:
        World world;
        std::vector<int> levels;
        float player_x{width/2.0f};
        float player_y{height/2.0f};

    public:

        Game_State();

        std::shared_ptr<State> update(sf::Time delta) override;

        void render(sf::RenderWindow &to) override;

};

#endif