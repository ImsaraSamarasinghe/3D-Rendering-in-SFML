#include <vector>
#include <cmath>

/**
 * @brief Function to create rotation matrix
 * 
 * @details
 * function to create the rotation matrix. Created by pre-multiplyin the matrices
 * defining rotations around the x, y & z axes.
 * 
 * @param angle_x angle change about the x axis.
 * @param angle_y angle change about the y axis.
 * @param angle_z angle change about the z axis.
 * @return matrix The rotation matrix
 */
std::vector<std::vector<double>> rotation_matrix(double &angle_x, double &angle_y, double &angle_z) {
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

/**
 * @brief Multiply r_matrix and 3D point
 * 
 * Function to preform the matrix multiplication between rotation matrix
 * and a vertex point.
 * 
 * @param matrix rotation matrix 3x3
 * @param vector 3D coordinate of the vertex as a list ex: [1,2,3].
 * @return std::vector<double> result rotated vertex point as a vector.
 */
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

/**
 * @brief project 3D coords to 2D.
 * 
 * @details Converts the rotated 3d coordinates to 2D ones with the correct
 *          field of view for the 3D effect.
 * 
 * @param point3D The vector of the 3D coordinates of a vertex.
 * @param fov The field of view of the user.
 * @param viewer_distance The zoom setting of the user.
 * @param width The width of the screen.
 * @param height The height of the screen.
 * 
 */
sf::Vector2f project_3D_to_2D(const std::vector<double>& point3D, double fov, double viewer_distance, int width, int height) {
    double factor = fov / (viewer_distance + point3D[2]);
    float x = static_cast<float>(point3D[0] * factor + width / 2);
    float y = static_cast<float>(-point3D[1] * factor + height / 2);
    return sf::Vector2f(x, y);
}
