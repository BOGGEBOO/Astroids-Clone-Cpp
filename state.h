#ifndef STATE_H
#define STATE_H
#include <SFML/Graphics.hpp>
#include "includes.h"


class State : public std::enable_shared_from_this<State>{
  public:
    State();
    virtual ~State();

    virtual void on_key_press(sf::Keyboard::Key key);

    virtual std::shared_ptr<State> update(sf::Time time) = 0;

    virtual void render(sf::RenderWindow &to) = 0;
    static void run(sf::RenderWindow &window, std::shared_ptr<State> state);
};

class Exit_State : public State 
{
  public:
    std::shared_ptr<State> update(sf::Time) { return nullptr; }
    void render(sf::RenderWindow &) {}
};

#endif