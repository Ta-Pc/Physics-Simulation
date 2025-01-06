#include "Force.h"

sf::Vector2f Force::force(float mass, sf::Vector2f acceleration)
{
    return mass * acceleration;
}

float Force::centripitalForceMagnitude(float mass, float velocityMagnitude, float circularPathRadius)
{
    return mass * (velocityMagnitude * velocityMagnitude) / circularPathRadius;
}
