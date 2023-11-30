#include <SFML/Graphics.hpp>

const size_t width{1024};
const size_t height{768};

int main()
{
    sf::RenderWindow window{sf:: VideoMode( width, height), "Asteroid"};

    return 0;
}