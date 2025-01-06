#pragma once
#include "cmath"
#include "SFML/Graphics.hpp"

//*****************************************
// Util Class
// Purpose: Provides a collection of utility functions 
//          for vector calculations commonly used in physics simulations.
//*****************************************

class Util
{
    public:
        static const float PI();
        // Returns the mathematical constant Pi (approximately 3.14159)

        static sf::Vector2f multiply(sf::Vector2f v1, sf::Vector2f v2);
        // Performs component-wise multiplication of two vectors.
        // Example: multiply(Vector2f(2, 3), Vector2f(4, 5)) would return Vector2f(8, 15)

        static sf::Vector2f divide(sf::Vector2f v1, sf::Vector2f v2);
        // Performs component-wise division of two vectors.

        static sf::Vector2f add(sf::Vector2f v1, float v);
        // Adds a scalar value to each component of a vector.

        static sf::Vector2f subtract(sf::Vector2f v1, float v);
        // Subtracts a scalar value from each component of a vector.

        static sf::Vector2f componentMagnitude(sf::Vector2f v1);
        // Returns a vector with x, y components representing the absolute values
        // of the original vector's components.

        static float resultantMagnitude(sf::Vector2f v1);
        // Calculates the magnitude (length) of a vector using the Pythagorean theorem. 

        static sf::Vector2f normalize(sf::Vector2f v);
        // Returns a unit vector (magnitude 1) pointing in the same direction as the original vector.
};
