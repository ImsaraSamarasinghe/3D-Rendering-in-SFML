#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>

class Floor{
    private:
        const std::vector<std::vector<double>> vertices;
        const std::vector<std::pair<int, int>> edges;

        static std::vector<std::vector<double>> _floor_vertices(std::vector<float> center, float side_length);
        static std::vector<std::pair<int, int>> _floor_edges();

    public:
        Floor(std::vector<float> c, float l); // class constructor

        void draw_floor(sf::RenderWindow& window, double angle_x, double angle_y, double angle_z, double viewer_distance, int width, int height);

};