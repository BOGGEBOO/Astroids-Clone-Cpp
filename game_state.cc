#include "game_state.h"
#include "menu_state.h"
#include "enemy.h"
#include "player.h"

#include <experimental/random>

Game_State::Game_State(){
    world.add(std::make_shared<Player>(sf::Vector2f{width / 2.0f, height / 2.0f}));
    levels = {200, 500, 750};
}

std::shared_ptr<State> Game_State::update(sf::Time delta){
    float rand_x = std::experimental::randint(1, int(width));
    float rand_y = std::experimental::randint(1, int(height));

    //check if rand_x is within range of player
    bool x_in_middle{rand_x > (width / 2) - 100 && rand_x < (width / 2) + 100};
    bool y_in_middle{rand_y > (height / 2) - 100 && rand_y < (height / 2) + 100};
    
    if ( x_in_middle && y_in_middle )  {
            while (true)
            {
                x_in_middle = rand_x > (width / 2) - 100 && rand_x < (width / 2) + 100;
                y_in_middle = rand_y > (height / 2) - 100 && rand_y < (height / 2) + 100;
    
                if ( x_in_middle && y_in_middle ) {
                    rand_x = std::experimental::randint(1, int(width));
                    
                    rand_y = std::experimental::randint(1, int(height));
                }
                else{
                    break;
                }
            }
    }

    
    int random = std::experimental::randint(1, 100);
    
    //first level, spawn only asteroids
    if (world.score <= levels[0]){
        if (random == 10 && world.maxEnemies < 5) {
            world.add(std::make_shared<Asteroid>(sf::Vector2f{rand_x, rand_y}));
            world.maxEnemies++;

        }
    }
    //second level, spawn only asteroids
    if (world.score <= levels[1] && world.score > levels[0]){
        if (random == 10 && world.maxEnemies < 8){
            world.add(std::make_shared<Asteroid>(sf::Vector2f{rand_x, rand_y}));
            world.maxEnemies++;
        }
    }
    //third level, either asteroids or comets
    if (world.score <= levels[2] && world.score > levels[1]){
        if (random == 10 && world.maxEnemies < 10){
            if (std::experimental::randint(1,3) == 1){
                world.add(std::make_shared<Comet>(sf::Vector2f{rand_x, rand_y}));
                world.maxEnemies++;
            }
            else{
                world.add(std::make_shared<Asteroid>(sf::Vector2f{rand_x, rand_y}));
                world.maxEnemies++;
            }
        }
    }
    if (world.score > levels[2]){
        if (random == 10 && world.maxEnemies < 15){
            if (std::experimental::randint(1,3) == 1){
                world.add(std::make_shared<Comet>(sf::Vector2f{rand_x, rand_y}));
                world.maxEnemies++;
            }
            else{
                world.add(std::make_shared<Asteroid>(sf::Vector2f{rand_x, rand_y}));
                world.maxEnemies++;
            }
        }
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