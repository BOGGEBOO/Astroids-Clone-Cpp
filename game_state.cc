#include "game_state.h"
#include "menu_state.h"
#include "enemy.h"
#include "player.h"
#include <experimental/random>

Game_State::Game_State(){
    world.add(std::make_shared<Player>(sf::Vector2f{width / 2.0f, height / 2.0f}));
}

std::shared_ptr<State> Game_State::update(sf::Time delta){

    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Q) )
    {
        return std::make_shared<Menu_State>(shared_from_this());
    }
    
    world.update(delta);

    return nullptr;
}

void Game_State::render(sf::RenderWindow &to )
{
    world.render(to);
}