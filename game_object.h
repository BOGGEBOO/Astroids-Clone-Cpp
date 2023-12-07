#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "includes.h"

class World;

class Game_Object
{
    public:
        Game_Object(const std::string &texture);
        //virtual ~Game_Object() = default;

        sf::RectangleShape shape;

        sf::Vector2f dir;

        virtual bool update(sf::Time time, World &world) = 0;

        void render(sf::RenderWindow &window);
};

// class Texture_Obj : public Game_Object
// {
//     public:
//         Texture_Obj(const std::string &texture);

//         void render(sf::RenderWindow &window) override;
// };

#endif