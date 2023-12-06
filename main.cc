#include <SFML/Graphics.hpp>
#include "menu_state.h"
#include "includes.h"

const size_t width{1920};
const size_t height{1080};

int main()
{
    sf::RenderWindow window{sf:: VideoMode( width, height), "Asteroid"};

    State::run(window, std::make_shared<Menu_State>(nullptr));

    return 0;
}