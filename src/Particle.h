#pragma once
#include "SFML/Graphics.hpp"
#include "Util.h" 

using namespace sf;

//*****************************************
// Particle Class
// Purpose: Represents a physical particle with properties such as 
//          position, velocity, and mass. Provides functionality
//          for updating and rendering the particle in simulations.
// Last Edited: Mar 23 2024
// Author singnature: T@Physics
// Author Email: makhosazanaprity33@gmail.com
//*****************************************

class Particle
{
public:
    float mass;               // Mass of the particle
    Vector2f position;        // Current position (x, y coordinates)
    Vector2f velocity;        // Current velocity (x and y components)
    Vector2f acceleration;    // Current acceleration (x and y components)
    CircleShape particle;     // SFML shape used to graphically represent the particle

    // Constructor: Initializes a Particle object
    Particle(float mass, Vector2f& position, Vector2f velocity = Vector2f(0.f, 0.f), Vector2f acceleration = Vector2f(0.f, 0.f))
    {
        this->mass = mass;
        this->position = position;
        this->velocity = velocity;
        this->acceleration = acceleration;

        // Configure the graphical representation
        particle.setPosition(position);
        particle.setRadius(10.f * mass);          // Radius scales with mass
        particle.setOrigin(Vector2f(particle.getRadius(), particle.getRadius())); // Center origin
        particle.setFillColor(Color::Blue);
        particle.setOutlineThickness(4.f);
        particle.setOutlineColor(Color::White);
    }

    // update: Updates the particle's position based on its motion 
    //         and syncs it with the graphical representation.  
    void update()
    {
        particle.setPosition(position);
    }
};
