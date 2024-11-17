#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include "axis.hpp"
#include "transforms.hpp"

std::vector<std::vector<double>> Axis::_axis_vertices(std::vector<float> center, float side_length){
    float half_side = side_length / 2;
    float cx = center[0], cy = center[1], cz = center[2];

    return {{cx,cy,cz},{cx+half_side,cy,cz},{cx,cy+half_side,cz},{cx,cy,cz+half_side}};
}

std::vector<std::pair<int, int>> Axis::_axis_edges(){
    return {{0,1},{0,2},{0,3}};
}

Axis::Axis(std::vector<float> c, float l) : vertices(_axis_vertices(c, l)), edges(_axis_edges()) {}

void Axis::draw_axis(sf::RenderWindow& window, double angle_x, double angle_y, double angle_z, double viewer_distance, int width, int height){
    double fov = 256;
    std::vector<sf::Vector2f> final_vertices;
    std::vector<sf::Color> colors = {sf::Color::Red, sf::Color::Green, sf::Color::Blue}; // color vector for different axes colors
    int count = 0;

    for (const auto& vertex : vertices){
        std::vector<double> rotated_matrix = multiplyMatrixVector(rotation_matrix(angle_x, angle_y, angle_z), vertex);
        final_vertices.push_back(project_3D_to_2D(rotated_matrix, fov, viewer_distance, width, height));
    }

    /*
    * Possible way of doing it smoothly??
    for (auto const [i, edge] : std::views::enumerate(edges)){
        sf::Vertex line[] = {
            sf::Vertex(final_vertices[edge.first], colors[i]),
            sf::Vertex(final_vertices[edge.second], colors[i])
        };
        window.draw(line, 2, sf::Lines);
    }
    */

    for (const auto& edge: edges){
        sf::Vertex line[] = {
            sf::Vertex(final_vertices[edge.first], colors[count]),
            sf::Vertex(final_vertices[edge.second], colors[count])
        };
        window.draw(line, 2, sf::Lines);
        count++;
    }
}
