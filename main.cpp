#include <SFML/Graphics.hpp>
#include <vector>
#include <utility> // for std::pair
#include <cmath>
#include <iostream>
#include "square.h"

const int width = 800;  // Window width
const int height = 600; // Window height

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(width, height), "Rotating Square Example");

    // Define vertices of the square in 3D
    std::vector<std::vector<double>> vertices = _cube_vertices({0.,0.,0.},100.);

    // Rotation angles
    double angle_x = 0.0;
    double angle_y = 0.0;
    double angle_z = 0.0;
    double viewer_distance = 500.0; // Distance from the viewer

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

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right){
                rotating = true;
                current_x = event.mouseButton.x;
                current_y = event.mouseButton.y;
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right){
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
        }

        // Clear the window
        window.clear(sf::Color::Black);

        // Draw the rotating square
        draw_square(window, vertices, angle_x, angle_y, angle_z, viewer_distance, width, height);

        // Display everything
        window.display();
    }

    return 0;
}
