#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "floor.hpp"
#include "transforms.hpp"

std::vector<std::vector<double>> Floor::_floor_vertices(std::vector<float> center, float side_length){
    float half_side = side_length / 2;
    float cx = center[0], cz = center[2];

    return {{cx-half_side,0.,cz-half_side},
            {cx+half_side,0.,cz-half_side},
            {cx+half_side,0.,cz+half_side},
            {cx-half_side,0.,cz+half_side}
            };
}

std::vector<std::pair<int, int>> Floor::_floor_edges(){
    return {{0,1},
            {1,2},
            {2,3},
            {3,0}};
}

// Constructor implementation
Floor::Floor(std::vector<float> c, float l) 
    : vertices(_floor_vertices(c, l)), edges(_floor_edges()) {}

void Floor::draw_floor(sf::RenderWindow& window, double angle_x, double angle_y, double angle_z, double viewer_distance, int width, int height){
    double fov = 256;
    std::vector<sf::Vector2f> final_vertices;
    sf:: VertexArray quad(sf::Quads, 4);

    int count = 0;
    for (const auto& vertex : vertices){
        std::vector<double> rotated_vertex = multiplyMatrixVector(rotation_matrix(angle_x, angle_y, angle_z), vertex);
        //final_vertices.push_back(project_3D_to_2D(rotated_vertex, fov, viewer_distance, width, height)); 
        quad[count].position = project_3D_to_2D(rotated_vertex, fov, viewer_distance, width, height);
        quad[count].color = sf::Color{128, 128, 128, 128};
        count++;
    }
    window.draw(quad);
}
