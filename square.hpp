#include <vector>
#include <SFML/Graphics.hpp>
#include "transforms.hpp"

/**
 * @brief Function to find the coordinates of a cube in 3D
 * 
 * @details Creates the list of coordinates of a cube defined by 
 * the center and a sidelength
 * 
 * @param center Center of the cube
 * @param side_length side length of the cube
 * @returns list of vertices in 3D i.e. {{x, y, z},....}
 */
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
        };// list of vertex coordinates in 3D {{x, y, z},....}
}

/**
 * @brief Creates the list of edges
 * 
 * @param None
 * @returns List of edges
 */
std::vector<std::pair<int, int>> _cube_edges() {
    return {
        {0, 1}, {1, 2}, {2, 3}, {3, 0}, // back face
        {4, 5}, {5, 6}, {6, 7}, {7, 4}, // front face
        {0, 4}, {1, 5}, {2, 6}, {3, 7}  // connecting edges
    };
}

/**
 * @brief function to draw the square
 * 
 * @details Draws the cube based on the vertices and the edges returned from the functions
 * 
 * @param window Display window from SFML
 * @param vertices List of cube vertices from predifned function
 * @param angle_x Angle about x-axis
 * @param angle_y Angle about the y-axis
 * @param angle_z Angle about the z-axis
 * @param viewer_distance Zoom level for display
 */
void draw_square(sf::RenderWindow& window, const std::vector<std::vector<double>>& vertices, double angle_x, double angle_y, double angle_z, double viewer_distance, int width, int height) {
    double fov = 256; // field of view
    std::vector<sf::Vector2f> final_vertices; // final vertices after calculations
    std::vector<std::pair<int, int>> edges = _cube_edges(); // get the cube edges vector

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