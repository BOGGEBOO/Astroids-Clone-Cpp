#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "includes.h"

class World;

class Game_Object
{
    public:
        Game_Object(sf::Vector2f c, float r)
        : center{c}, radius{r}
        {}

        virtual ~Game_Object() = default;

        sf::Vector2f center;

        float radius;

        virtual bool update(sf::Time time, World &world) = 0;

        virtual void render(sf::RenderWindow &window) = 0;
};

class Texture_Obj : public Game_Object
{
    protected:
        sf::RectangleShape shape;
    public:
        Texture_Obj(sf::Vector2f center, const std::string &texture);

        void render(sf::RenderWindow &window) override;
};

#endif