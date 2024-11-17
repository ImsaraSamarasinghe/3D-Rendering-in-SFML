#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include <cmath>
#include "torus.hpp"
#include "transforms.hpp"

std::vector<std::vector<double>> Torus::_torus_vertices(std::vector<float> c, float R, float r, int seg_u, int seg_v){
    float cx = c[0], cy = c[1], cz = c[2];
    std::vector<std::vector<double>> vertices;
    float u=0, v=0, x=0, y=0, z=0;

    for (int i = 0; i < seg_u; ++i ){
        for (int j = 0; j < seg_v; ++j) {
            
            u = (static_cast<float>(i) / static_cast<float>(seg_u)) * 2. * M_PI;
            v = (static_cast<float>(j) / static_cast<float>(seg_v)) * 2. * M_PI;
            x = (R + r * cos(v)) * cos(u);
            y = (R + r * cos(v)) * sin(u);
            z = r * sin(v);
            
            vertices.push_back({cx + x, cy + y, cz + z}); 
        }
    }

    return vertices;
}

std::vector<std::pair<int, int>> Torus::_torus_edges(int seg_u, int seg_v){
    std::vector<std::pair<int, int>> edges;
    int current, next_u, next_v;

    for (int i = 0; i < seg_u; i++ ){
        for (int j = 0; j < seg_v; j++) {
            current = i * seg_v + j;
            next_u = ((i + 1) % seg_u) * seg_v +j;
            next_v = i * seg_v + ((j + 1) % seg_v);

            edges.push_back({current, next_u});
            edges.push_back({current, next_v});
        }
    }
    return edges;
}

Torus::Torus(std::vector<float> center, float Radius, float radius, int segments_u, int segments_v)
        : vertices(_torus_vertices(center, Radius, radius, segments_u, segments_v)) , 
            edges(_torus_edges(segments_u, segments_v)) {}

void Torus::draw_torus(sf::RenderWindow& window, double angle_x, double angle_y, double angle_z, double viewer_distance, int width, int height){
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
        window.draw(line, 2, sf::Lines);
    }
}