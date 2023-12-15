#include "state.h"

/**
 * Default constructor for State
*/
State::State() {}

/**
 * Default destructor for State
*/
State::~State() {}

/**
 * Function to be overwritten by menu_state
*/
void State::on_key_press(sf::Keyboard::Key) {}

/**
 * Function for keeping the game running. Closes gmae if requested
*/
void State::run(sf::RenderWindow &window, std::shared_ptr<State> state) 
{
    sf::Clock clock;

    while (state){
        sf::Event event;
        while (window.pollEvent(event)){
            switch (event.type)
            {
            case sf::Event::Closed:
                return;
            case sf::Event::KeyPressed:
                state->on_key_press(event.key.code);
                break;
            default:
                break;
            }
        }
    

        window.clear();
        if ( auto new_state = state->update(clock.restart()) )
        {
            if ( std::dynamic_pointer_cast<Exit_State>(new_state) )
            {
                return;
            } else {
                state = new_state;
            }
            continue;
        }
        state->render(window),
        window.display();
    }
}

