#include "game_state.h"
#include "menu_state.h"
#include <cmath>

Game_State::Game_State(){
    player.setSize(sf::Vector2f(50, 100));
    player.setPosition(300, 300);
    player.setOrigin(25, 50);
}

float find_rotation(){
    float rotation{0};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        rotation -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        rotation += 1;
    
    return rotation;
}

std::shared_ptr<State> Game_State::update(sf::Time delta){

    float rotation = find_rotation();

        //auto delta = clock.restart();
        {
            spin = rotation * 250.0f * delta.asSeconds();
            location.x = 250.0*-sin(player.getRotation()*3.14159265/180)*delta.asSeconds();
            location.y = 250.0*cos(player.getRotation()*3.14159265/180)*delta.asSeconds();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            player.move(location);
        }

    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Q) )
    {
        return std::make_shared<Menu_State>(shared_from_this());
    }

    return nullptr;
}

void Game_State::render(sf::RenderWindow &to )
{
    to.clear();
    player.rotate(spin);
    to.draw(player);
    to.display();
}