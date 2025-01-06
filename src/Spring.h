#pragma once
#include "SFML/Graphics.hpp"
#include "Particle.h"
#include "Util.h" 
using namespace sf;

//*****************************************
// Spring Class
// Purpose: Represents a physical spring object used in simulations. It 
//          calculates forces based on Hooke's Law and can be visually 
//          represented.
// Last Edited: Mar 23 2024
// Author singnature: T@Physics
// Author Email: makhosazanaprity33@gmail.com
//*****************************************

class Spring
{
private:
    float restLengthOfAPointSpring; // The natural length of the spring when no forces are applied
    Particle* firstParticle;         // Pointer to the first particle attached to the spring
    Particle* lastParticle;          // Pointer to the second particle attached to the spring
    float k;                         // The spring constant (how stiff the spring is)

public:
    // Constructor: Initializes a Spring object
    Spring(float k, float restLengthOfAPointSpring, Particle* firstParticle, Particle* lastParticle)
    {
        // Create a graphical representation of the spring (a line)
        line[0].position = firstParticle->position; // First vertex is fixed
        line[0].color = Color::White;
        line[1].position = Vector2f(lastParticle->position.x, lastParticle->position.y - lastParticle->particle.getRadius()); // Second vertex updates with particle position
        line[1].color = Color::White;

        this->firstParticle = firstParticle;
        this->lastParticle = lastParticle;
        this->restLengthOfAPointSpring = restLengthOfAPointSpring;
        this->k = k;
    }

    // Update: Calculates spring force and potentially applies it (not fully implemented here)
    void update(Vector2f force, Time dt);

    // hooksLaw: Implements Hooke's Law, calculating the force exerted by the spring
    Vector2f hooksLaw(Vector2f gravity);

    // Graphical representation (for rendering the spring)
    Vertex line[2];
};
