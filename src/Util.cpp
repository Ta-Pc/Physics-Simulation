#include "Util.h"
#include <stdexcept> // For std::runtime_error

const float Util::PI()
{
    return 3.141592654f;
} 

sf::Vector2f Util::divide(sf::Vector2f v1, sf::Vector2f v2)
{
    return sf::Vector2f(v1.x / v2.x, v1.y / v2.y);
}

sf::Vector2f Util::add(sf::Vector2f v1, float v)
{
    return sf::Vector2f(v1.x + v, v1.y + v);
}

sf::Vector2f Util::subtract(sf::Vector2f v1, float v)
{
    return sf::Vector2f(v1.x - v, v1.y - v);
}

sf::Vector2f Util::multiply(sf::Vector2f v1, sf::Vector2f v2)
{
    return sf::Vector2f(v1.x * v2.x, v1.y * v2.y);
}

sf::Vector2f Util::componentMagnitude(sf::Vector2f v1)
{
    return sf::Vector2f(abs(v1.x + 1E-30), abs(v1.y + 1E-30));
}

float Util::resultantMagnitude(sf::Vector2f v1)
{
    return sqrt(v1.x * v1.x + v1.y * v1.y);
}

sf::Vector2f Util::normalize(sf::Vector2f v)
{
    if (v.x == 0.f || v.y == 0.f)
        throw std::runtime_error("Cannot normalize vector with a magnitude of 0");
    else
        return divide(v, componentMagnitude(v));
}
