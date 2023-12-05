#include "game_state.h"
#include "menu_state.h"
#include "enemy.h"
#include "player.h"

#include <experimental/random>

Game_State::Game_State(){
    world.add(std::make_shared<Player>(sf::Vector2f{width / 2.0f, height / 2.0f}));
    count = 0;
}

std::shared_ptr<State> Game_State::update(sf::Time delta){

    int random = std::experimental::randint(1, 50);
    if (random == 10 && count < 5){
        float rand_x = std::experimental::randint(1, int(width));
        float rand_y = std::experimental::randint(1, int(height));

        world.add(std::make_shared<Asteroid>(sf::Vector2f{rand_x, rand_y}));
        count++;
    }

    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Q) )
    {
        return std::make_shared<Menu_State>(shared_from_this());
    }

    if (world.is_dead()){
        return std::make_shared<Menu_State>(shared_from_this());
    }
    
    world.update(delta);

    return nullptr;
}

void Game_State::render(sf::RenderWindow &to )
{
    world.render(to);
}