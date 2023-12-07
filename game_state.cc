#include "game_state.h"
#include "menu_state.h"
#include "enemy.h"
#include "player.h"

#include <experimental/random>

Game_State::Game_State(){
    world.add(std::make_shared<Player>(sf::Vector2f{player_x, player_y}));
    levels = {200, 500, 750};
}

std::shared_ptr<State> Game_State::update(sf::Time delta) {

    //spawn emenys depending on score
    level_select();

    //pause game
    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Q) )
    {
        return std::make_shared<Menu_State>(shared_from_this(), world.score);
    }

    //check if player died
    if (world.is_dead()){
        return std::make_shared<Menu_State>(nullptr, world.score);
    }
    
    world.update(delta);

    return nullptr;
}

void Game_State::render(sf::RenderWindow &to )
{
    world.render(to);
}

void Game_State::level_select()
{
    // random x- and y-coordinates
    float rand_x = std::experimental::randint(1, int(width));
    float rand_y = std::experimental::randint(1, int(height));

    // Avoid enemy to spawn on player
    // check if rand_x and rand_y is within range of player
    bool x_in_middle{rand_x > player_x - distance && rand_x < player_x + distance};
    bool y_in_middle{rand_y > player_y - distance && rand_y < player_y + distance};
    
    if ( x_in_middle && y_in_middle )  {
        
        while (true) {
            x_in_middle = rand_x > player_x - distance && rand_x < player_x + distance;
            y_in_middle = rand_y > player_y - distance && rand_y < player_y + distance;

            if ( x_in_middle && y_in_middle ) {

                rand_x = std::experimental::randint(1, int(width));
                rand_y = std::experimental::randint(1, int(height));

            }
            else {
                break;
            }
        }
    }

    random = std::experimental::randint(1, 100);
    
    // first level, spawn only asteroids
    if (world.score <= levels[0]){
        if (random == 10 && world.maxEnemies < 5) {
            world.add(std::make_shared<Asteroid>(sf::Vector2f{rand_x, rand_y}));
            world.maxEnemies++;

        }
    }
    
    // second level, spawn only asteroids
    if (world.score <= levels[1] && world.score > levels[0]){
        if (random == 10 && world.maxEnemies < 8){
            world.add(std::make_shared<Asteroid>(sf::Vector2f{rand_x, rand_y}));
            world.maxEnemies++;
        }
    }
    
    // third level, either asteroids or comets
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
    
    //third level, either asteroids or comets
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
}