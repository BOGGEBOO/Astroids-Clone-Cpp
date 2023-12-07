#ifndef WORLD_H
#define WORLD_H

#include "includes.h"
#include "game_object.h"

class World {
    public:
        World();

        void update(sf::Time delta);

        void render(sf::RenderWindow &to);

        void add(shared_ptr<Game_Object> object);

        std::vector<shared_ptr<Game_Object>> collides_with(Game_Object &me) const;

        bool is_dead() const;

        sf::Vector2f player_pos() const;

        int score{0};
        int maxEnemies{0};
        int ufo_num;

        
    private:
        std::vector<shared_ptr<Game_Object>> objects;

        sf::Text text;
        sf::Font font;
};

#endif