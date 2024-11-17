#ifndef SQUARE_HPP 
#define SQUARE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <utility> // For std::pair

class Square {
private:
    const std::vector<std::vector<double>> vertices; // Vertices variable for the class
    const std::vector<std::pair<int, int>> edges;    // Edges variable for the class

    // Helper functions to create vertices and edges for the square
    static std::vector<std::vector<double>> _cube_vertices(std::vector<float>& center, float side_length);
    static std::vector<std::pair<int, int>> _cube_edges();

public:
    // Constructor
    Square(std::vector<float> c, float l);

    // Method to draw the square
    void draw_square(sf::RenderWindow& window, double angle_x, double angle_y, double angle_z,
                     double viewer_distance, int width, int height);
};

#endif
