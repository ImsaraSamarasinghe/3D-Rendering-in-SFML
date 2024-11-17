#include <SFML/Graphics.hpp>
#include <utility>
#include <vector>

class Axis{
    private:
    std::vector<std::vector<double>> vertices;
    std::vector<std::pair<int, int>> edges;

    static std::vector<std::vector<double>> _axis_vertices(std::vector<float> center, float side_length);
    static std::vector<std::pair<int, int>> _axis_edges();

    public:
    Axis(std::vector<float> c, float l); // class constructor

    void draw_axis(sf::RenderWindow& window, double angle_x, double angle_y, double angle_z, double viewer_distance, int width, int height);// draw function
};