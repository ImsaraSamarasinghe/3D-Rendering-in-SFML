#include <vector>
#include <SFML/Graphics.hpp>
#include "transforms.h"

// Function to return the vertices of a square in 3D
// Define cube vertices (3D)
std::vector<std::vector<double>> _cube_vertices(std::vector<float> center, float side_length) {
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

std::vector<std::pair<int, int>> _cube_edges() {
    return {
        {0, 1}, {1, 2}, {2, 3}, {3, 0}, // back face
        {4, 5}, {5, 6}, {6, 7}, {7, 4}, // front face
        {0, 4}, {1, 5}, {2, 6}, {3, 7}  // connecting edges
    };
}

// Function to draw the rotating square
void draw_square(sf::RenderWindow& window, const std::vector<std::vector<double>>& vertices, double angle_x, double angle_y, double angle_z, double viewer_distance, int width, int height) {
    double fov = 256;
    std::vector<sf::Vector2f> final_vertices;
    std::vector<std::pair<int, int>> edges = _cube_edges();

    for (const auto& vertex : vertices) {
        // Rotate the vertex
        std::vector<double> rotated_vertex = multiplyMatrixVector(rotation_matrix(angle_x, angle_y, angle_z), vertex);
        // Project the rotated vertex to 2D
        final_vertices.push_back(project_3D_to_2D(rotated_vertex, fov, viewer_distance, width, height));
    }

    // Draw edges
    for (const auto& edge : edges) {
        sf::Vertex line[] = {
            sf::Vertex(final_vertices[edge.first], sf::Color::Green),
            sf::Vertex(final_vertices[edge.second], sf::Color::Green)
        };
        window.draw(line, 2, sf::Lines); // Draw line segment
    }
}