#include <SFML/Graphics.hpp>
#include "menu_state.h"

const size_t width{1024};
const size_t height{768};

int main()
{
    sf::RenderWindow window{sf:: VideoMode( width, height), "Asteroid"};

    State::run(window, std::make_shared<Menu_State>(nullptr));

    return 0;
}