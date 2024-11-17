#include <SFML/Graphics.hpp>
#include <vector>
#include <utility> // for std::pair
#include <cmath>
#include <iostream>
#include "square.hpp"
#include "floor.hpp"
#include "axis.hpp"
#include "torus.hpp"

const int width = 800;  // Window width
const int height = 600; // Window height

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(width, height), "3D Engine");


    // Torus class object
    Torus torus({0.,150.,0.}, 100., 50., 50, 20);

    // floor class
    Floor floor({0.,0.,0.},300.);

    // axis class
    Axis axis({0.,0.,0.},60.);

    // set window location to the right of the screen during development
    window.setPosition(sf::Vector2i(1450, 200));

    // set frame rate limit - 60 fps
    window.setFramerateLimit(60);

    // Rotation angles
    double angle_x = 0.0;
    double angle_y = 0.0;
    double angle_z = 0.0;
    double viewer_distance = 300.0; // Distance from the viewer

    //rotation check
    bool rotating = false;
    double current_x=0, current_y=0, new_x=0, new_y=0;
    double dx, dy;

    // Main loop
    while (window.isOpen()) {
        // Event handling
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                rotating = true;
                current_x = event.mouseButton.x;
                current_y = event.mouseButton.y;
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left){ // check for release
                rotating=false;
            }

            if (event.type == sf::Event::MouseMoved && rotating){
                new_x = event.mouseMove.x;
                new_y = event.mouseMove.y;
                dx = new_x-current_x;
                dy = new_y-current_y;

                angle_x += dy * 0.01;
                angle_y += dx * 0.01;
                current_x = new_x;
                current_y = new_y;
            }

            if (event.type == sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                viewer_distance = viewer_distance + 1.;
            }
        }
        // Clear the window
        window.clear(sf::Color::White);

        // Draw the floor
        floor.draw_floor(window, angle_x, angle_y, angle_z, viewer_distance, width, height);

        // draw the axis
        axis.draw_axis(window, angle_x, angle_y, angle_z, viewer_distance, width, height);


        torus.draw_torus(window, angle_x, angle_y, angle_z, viewer_distance, width, height);

        // Display everything
        window.display();
    }

    return 0;
}
