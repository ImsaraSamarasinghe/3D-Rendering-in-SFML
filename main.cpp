#include <SFML/Graphics.hpp>
#include <vector>
#include <utility> // for std::pair
#include <cmath>
#include <iostream>

const int width = 800;  // Window width
const int height = 600; // Window height

// Function to create the rotation matrix
std::vector<std::vector<double>> rotation_matrix(double angle_x, double angle_y, double angle_z) {
    std::vector<std::vector<double>> matrix;
    double cos_x = cos(angle_x), sin_x = sin(angle_x);
    double cos_y = cos(angle_y), sin_y = sin(angle_y);
    double cos_z = cos(angle_z), sin_z = sin(angle_z);

    matrix = {
        {cos_y * cos_z, -cos_y * sin_z, sin_y},
        {sin_x * sin_y * cos_z + cos_x * sin_z, -sin_x * sin_y * sin_z + cos_x * cos_z, -sin_x * cos_y},
        {-cos_x * sin_y * cos_z + sin_x * sin_z, cos_x * sin_y * sin_z + sin_x * cos_z, cos_x * cos_y}
    };

    return matrix;
}

// Function to multiply a matrix by a vector
std::vector<double> multiplyMatrixVector(const std::vector<std::vector<double>>& matrix, const std::vector<double>& vector) {
    std::vector<double> result(3, 0.0); // Initialize result vector with zeros

    // Perform matrix multiplication
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < vector.size(); ++j) {
            result[i] += matrix[i][j] * vector[j];
        }
    }

    return result; // Return the result vector
}

// Perform 3D to 2D projection
sf::Vector2f project_3D_to_2D(const std::vector<double>& point3D, double fov, double viewer_distance) {
    double factor = fov / (viewer_distance + point3D[2]);
    float x = static_cast<float>(point3D[0] * factor + width / 2);
    float y = static_cast<float>(-point3D[1] * factor + height / 2);
    return sf::Vector2f(x, y);
}

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
void draw_square(sf::RenderWindow& window, const std::vector<std::vector<double>>& vertices, double angle_x, double angle_y, double angle_z, double viewer_distance) {
    double fov = 256;
    std::vector<sf::Vector2f> final_vertices;
    std::vector<std::pair<int, int>> edges = _cube_edges();

    for (const auto& vertex : vertices) {
        // Rotate the vertex
        std::vector<double> rotated_vertex = multiplyMatrixVector(rotation_matrix(angle_x, angle_y, angle_z), vertex);
        // Project the rotated vertex to 2D
        final_vertices.push_back(project_3D_to_2D(rotated_vertex, fov, viewer_distance));
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

    // Main loop
    while (window.isOpen()) {
        // Event handling
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window
        window.clear(sf::Color::Black);

        // Increment angles for rotation
        angle_x += 0.01; // Adjust the speed of rotation as needed
        angle_y += 0.02;
        angle_z += 0.03;

        // Draw the rotating square
        draw_square(window, vertices, angle_x, angle_y, angle_z, viewer_distance);

        // Display everything
        window.display();
    }

    return 0;
}
