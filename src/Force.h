#pragma once
#include "SFML/Graphics.hpp"

//*****************************************
// Force Class
// Purpose: Provides utility functions for calculating forces
//          related to basic Newtonian mechanics.
// Last Edited: Mar 24 2024
// Author singnature: T@Physics
// Author Email: makhosazanaprity33@gmail.com
//*****************************************

class Force
{
public:
    // force: Implements Newton's Second Law, calculating the net force acting on an object.  
    //        Formula: F = m * a
    static sf::Vector2f force(float mass, sf::Vector2f acceleration);

    // centripitalForceMagnitude: Calculates the magnitude of the centripetal force required
    //                            to maintain an object's circular motion. 
    //                            Formula: Fc = (m * v^2) / r
    static float centripitalForceMagnitude(float mass, float velocityMagnitude, float circularPathRadius);
};
