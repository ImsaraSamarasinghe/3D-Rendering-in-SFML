#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "square.hpp"
#include "transforms.hpp" // Make sure this is included as needed

// Implementation of the static functions
std::vector<std::vector<double>> Square::_cube_vertices(std::vector<float>& center, float side_length) {
    float half_side = side_length / 2;
    float cx = center[0], cy = center[1], cz = center[2];

    return {
        {cx - half_side, cy - half_side, cz - half_side},
        {cx + half_side, cy - half_side, cz - half_side},
        {cx + half_side, cy + half_side, cz - half_side},
        {cx - half_side, cy + half_side, cz - half_side},
        {cx - half_side, cy - half_side, cz + half_side},
        {cx + half_side, cy - half_side, cz + half_side},
        {cx + half_side, cy + half_side, cz + half_side},
        {cx - half_side, cy + half_side, cz + half_side}, 
    };
}

std::vector<std::pair<int, int>> Square::_cube_edges() {
    return {
        {0, 1}, {1, 2}, {2, 3}, {3, 0}, // back face
        {4, 5}, {5, 6}, {6, 7}, {7, 4}, // front face
        {0, 4}, {1, 5}, {2, 6}, {3, 7}  // connecting edges
    };
}

// Constructor implementation
Square::Square(std::vector<float> c, float l) 
    : vertices(_cube_vertices(c, l)), edges(_cube_edges()) {}

// Draw method implementation
void Square::draw_square(sf::RenderWindow& window, double angle_x, double angle_y, double angle_z, double viewer_distance, int width, int height) {
    double fov = 256; // field of view
    std::vector<sf::Vector2f> final_vertices; // final vertices after calculations

    for (const auto& vertex : vertices) { // loop through vertices vector
        // Rotate the vertex
        std::vector<double> rotated_vertex = multiplyMatrixVector(rotation_matrix(angle_x, angle_y, angle_z), vertex);
        // Project the rotated vertex to 2D
        final_vertices.push_back(project_3D_to_2D(rotated_vertex, fov, viewer_distance, width, height));
    }

    // Draw edges
    for (const auto& edge : edges) {
        sf::Vertex line[] = {
            sf::Vertex(final_vertices[edge.first], sf::Color::Black),
            sf::Vertex(final_vertices[edge.second], sf::Color::Black)
        };
        window.draw(line, 2, sf::Lines); // Draw line segment
    }
}
