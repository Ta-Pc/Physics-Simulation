#pragma once
#include "SFML/Graphics.hpp"
#include "Particle.h"
#include "Util.h"
#include <stdexcept> 
#include <vector> 

using namespace sf;

//*****************************************
// ProjectileMotion Class
// Purpose: Models the motion of a projectile under the influence of gravity.
//          Includes calculations, trajectory updates, and rendering.
// Last Edited: Mar 25 2024
// Author singnature: T@Physics
// Author Email: makhosazanaprity33@gmail.com
//*****************************************

class ProjectileMotion
{
private:
	Particle* p;                  // Pointer to the Particle object being simulated
	RenderWindow* window;         // Pointer to the SFML window for rendering
	Vector2f initialPositionOfProjectile;
	sf::VertexArray groundLine;   // Line representing the ground
	float gravity;                // Acceleration due to gravity
	float initialVelocityMagnitude;
	float angleOfProjection;      // Launch angle (in radians)
	float groundLevel;            // Y-coordinate representing the ground
	const int INTERVAL = 1;       // Time step (likely in seconds, but could be adjusted)
	float previousTime;
	float Range;                  // Horizontal range of the projectile
	float maximumHeight;
	float timeOfFlight;

	std::vector<sf::CircleShape> trailHistory; // Stores positions for the trail effect
	sf::Color trailColor = sf::Color::Yellow;  // Color of the trail

	// Optional trail configuration (uncomment if using a trail)
	 int maxTrailLength = 10000; 
	 float trailCircleRadius = 2.0f;

public:
	ProjectileMotion(Particle &p, Vector2f initialPositionOfProjectile, float initialVelocityMagnitude, float angleOfProjectionInRadians, float  gravityMagnitude = 9.8, float groundY = 0.f): groundLevel(groundY)
	{
		if (angleOfProjectionInRadians >= 0 && angleOfProjectionInRadians <= Util::PI() / 2)
		{
			this->initialVelocityMagnitude = initialVelocityMagnitude;
			this->initialPositionOfProjectile = initialPositionOfProjectile;
			this->angleOfProjection = angleOfProjectionInRadians;
			p.particle.setPosition(initialPositionOfProjectile);
			this->gravity = gravityMagnitude;
			previousTime = 0;
			this->p = &p;

			// Pre-calculation of important values
            timeOfFlight = 2 * initialVelocityMagnitude * sin(angleOfProjectionInRadians) / gravity;
            Range = initialVelocityMagnitude * initialVelocityMagnitude * sin(2 * angleOfProjection) / gravity;
            maximumHeight = (initialVelocityMagnitude * initialVelocityMagnitude * sin(angleOfProjection)) / (2 * gravity);

			// Set up the ground line for rendering
			groundLine = sf::VertexArray(sf::PrimitiveType::Lines, 2);
			groundLine[0].position = sf::Vector2f(0, groundY);          // Left point
			groundLine[1].position = sf::Vector2f(Range + 2.f, groundY);// Right point
			groundLine[0].color = sf::Color::White;                     // Start color
			groundLine[1].color = sf::Color::White;                     // End color

			// Calculate initial velocity components 
			p.velocity = Vector2f(initialVelocityMagnitude * cos(angleOfProjection), -initialVelocityMagnitude * sin(angleOfProjection));
		}
		else
			throw std::runtime_error("Angle out of domain: [0 radians, PI/2 radians]");
	}

	// update: Advances the simulation by one time step 
	void update(Time dt);

	// calculateAndCreateView: Creates an SFML view tailored to the projectile's motion 
	View calculateAndCreateView(RenderWindow& window) const;

	// draw: Renders the ground line and projectile trail on the window  
	void draw(RenderWindow& window);

};

