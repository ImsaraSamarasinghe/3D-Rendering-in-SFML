#ifndef TORUS_HPP
#define TORUS_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>

class Torus {
    private:
        const std::vector<std::vector<double>> vertices;
        const std::vector<std::pair<int, int>> edges;

        static std::vector<std::vector<double>> _torus_vertices(std::vector<float> c, float R, float r, int seg_u, int seg_v);
        static std::vector<std::pair<int, int>> _torus_edges(int seg_u, int seg_v);
    public:
        Torus(std::vector<float> center, float Radius, float radius, int segments_u, int segments_v);

        void draw_torus(sf::RenderWindow& window, double angle_x, double angle_y, double angle_z, double viewer_distance, int width, int height);
};

#endif