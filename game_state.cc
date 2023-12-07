#include "game_state.h"
#include "menu_state.h"
#include "enemy.h"
#include "player.h"

#include <experimental/random>

Game_State::Game_State(){
    world.add(std::make_shared<Player>(sf::Vector2f{player_x, player_y}));
    levels = {200, 400, 600, 1000, 1500};
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
    bool x_in_middle{rand_x > world.player_pos().x - distance 
    && rand_x < world.player_pos().x + distance};
    bool y_in_middle{rand_y > world.player_pos().y - distance
    && rand_y < world.player_pos().y + distance};
    
    if ( x_in_middle && y_in_middle )  {
        
        while (true) {
            x_in_middle = rand_x > world.player_pos().x - distance
            && rand_x < world.player_pos().x + distance;
            y_in_middle = rand_y > world.player_pos().y - distance 
            && rand_y < world.player_pos().y + distance;

            if ( x_in_middle && y_in_middle ) {

                rand_x = std::experimental::randint(1, int(width));
                rand_y = std::experimental::randint(1, int(height));

            }
            else {
                break;
            }
        }
    }
    sf::Vector2f spawn{rand_x, rand_y};
    random = std::experimental::randint(1, 100);
    
    // first level, spawn only asteroids
    if (world.score <= levels[0]){
        if (random == 10 && world.maxEnemies < 5) {
            world.add(std::make_shared<Asteroid>(spawn, 
            1.0f, "images/asteroid.png"));
            world.maxEnemies++;

        }
    }
    
    // second level, spawn only asteroids
    if (world.score <= levels[1] && world.score > levels[0]){
        if (random == 10 && world.maxEnemies < 8){
            world.add(std::make_shared<Asteroid>(spawn,
            1.0f, "images/asteroid.png"));
            world.maxEnemies++;
        }
    }
    
    // third level, either asteroids or comets
    if (world.score <= levels[2] && world.score > levels[1]){
        if (random == 10 && world.maxEnemies < 10){
            if (std::experimental::randint(1,3) == 1){
                world.add(std::make_shared<Asteroid>(spawn,
                3.0f, "images/comet.png"));
                world.maxEnemies++;
            }
            else{
                world.add(std::make_shared<Asteroid>(spawn,
                1.0f, "images/asteroid.png"));
                world.maxEnemies++;
            }
        }
    }
    
    //third level, either asteroids or comets or missiles
    if (world.score <=levels[3] && world.score > levels[2]){
        if (random == 10 && world.maxEnemies < 15){
            const int choise{std::experimental::randint(1,4)};
            if (choise == 1){
                world.add(std::make_shared<Asteroid>(spawn,
                3.0f, "images/comet.png"));
                world.maxEnemies++;
            }
            else if (choise == 2){
                world.add(std::make_shared<Missile>(spawn, 
                2.0f, "images/comet.png"));
                world.maxEnemies++;
            }
            else{
                world.add(std::make_shared<Asteroid>(spawn,
                1.0f, "images/asteroid.png"));
                world.maxEnemies++;
            }
        }
    }

    if (world.score <=levels[4] && world.score > levels[3]){
        if (random == 10 && world.maxEnemies < 17){
            const int choise{std::experimental::randint(1,5)};
            if (choise == 1){
                world.add(std::make_shared<Asteroid>(spawn,
                3.0f, "images/comet.png"));
                world.maxEnemies++;
            }
            else if (choise == 2){
                world.add(std::make_shared<Missile>(spawn, 
                2.0f, "images/comet.png"));
                world.maxEnemies++;
            }
            else if (choise == 3 && world.ufo_num < 1){
                world.add(std::make_shared<Ufo>(sf::Vector2f{1, 100}, 
                1.0f, "images/player.png"));
                world.ufo_num++;
            }
            else{
                world.add(std::make_shared<Asteroid>(spawn,
                1.0f, "images/asteroid.png"));
                world.maxEnemies++;
            }
        }
    }

    if (world.score >= levels[4]){
        if (random == 10 && world.maxEnemies < 20){
            const int choise{std::experimental::randint(1,5)};
            if (choise == 1){
                world.add(std::make_shared<Asteroid>(spawn,
                3.0f, "images/comet.png"));
                world.maxEnemies++;
            }
            else if (choise == 2){
                world.add(std::make_shared<Missile>(spawn, 
                2.0f, "images/comet.png"));
                world.maxEnemies++;
            }
            else if (choise == 3 && world.ufo_num < 3){
                world.add(std::make_shared<Ufo>(sf::Vector2f{1, 100}, 
                1.0f, "images/player.png"));
                world.ufo_num++;
            }
            else{
                world.add(std::make_shared<Asteroid>(spawn,
                1.0f, "images/asteroid.png"));
                world.maxEnemies++;
            }
        }
    }       
}