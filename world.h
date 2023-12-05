#ifndef WORLD_H
#define WORLD_H

#include "includes.h"
#include "game_object.h"

class World {
    public:
        void update(sf::Time delta);

        void render(sf::RenderWindow &to);

        void add(shared_ptr<Game_Object> object);

        std::vector<shared_ptr<Game_Object>> collides_with(Game_Object &me) const;

        bool is_dead();

        int score{0};
        //sf::Text text;
    private:
        std::vector<shared_ptr<Game_Object>> objects;
};

#endif