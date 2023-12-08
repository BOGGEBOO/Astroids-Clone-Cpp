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

        int get_score();
        int get_maxEnemies();
        int get_ufo_num();

        void add_score(int s);
        void add_maxEnemies(int m);
        void add_ufo_num(int u);

        

        
    private:
        std::vector<shared_ptr<Game_Object>> objects;

        sf::Text text;
        sf::Font font;

        int score{0};
        int maxEnemies{0};
        int ufo_num;
};

#endif