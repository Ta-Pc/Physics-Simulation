#pragma once
#include "SFML/Graphics.hpp"

//*****************************************
// Drag Class
// Purpose: Provides utility functions for calculating drag forces
//          in physics simulations. 
// Last Edited: Mar 23 2024
// Author singnature: T@Physics
// Author Email: makhosazanaprity33@gmail.com
//*****************************************

class Drag
{
public:
    // celsiusToKelvin: Converts a temperature from Celsius to Kelvin.
    //                  Used in viscosity calculations.
    static float celsiusToKelvin(double celsius);

    // calculateViscosity: Determines the viscosity of a fluid (likely air)
    //                     based on the provided temperature in Celsius.
    static float calculateViscosity(double temperatureCelsius);

    // dragForce: Calculates the drag force acting on a spherical object
    //            based on its radius, velocity, and the viscosity of the medium.            
    static sf::Vector2f dragForce(float sphereRadius, sf::Vector2f velocity, float viscosity);
};
