#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "includes.h"

class World;

class Game_Object
{
    public:
        Game_Object(float r)
        :radius{r}
        {}

        virtual ~Game_Object() = default;

        //sf::Vector2f center;

        float radius;

        sf::RectangleShape shape;

        virtual bool update(sf::Time time, World &world) = 0;

        virtual void render(sf::RenderWindow &window) = 0;
};

class Texture_Obj : public Game_Object
{
    public:
        Texture_Obj(const std::string &texture);

        void render(sf::RenderWindow &window) override;
};

#endif