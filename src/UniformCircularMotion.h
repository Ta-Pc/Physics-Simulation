#pragma once
#include "SFML/Graphics.hpp"
#include "Particle.h"
#include "Util.h"

//*****************************************
// UniformCircularMotion Class
// Purpose: Represents and simulates the motion of an object 
//          undergoing uniform circular motion (constant speed, 
//          circular path). Handles updates, calculations, and rendering.
//*****************************************

class UniformCircularMotion
{
private:
	Particle* p;                  // Pointer to the Particle in motion
	Vector2f centripetalAcceleration;
	Vector2f centripetalForce;
	Vector2f velocity;
	Vector2f center;              // Center of the circular path
	sf::CircleShape centerDot;    // Visual representation of the center
	sf::CircleShape path;         // Visual representation of the path
	float circularMotionRadius;
	float angularVelocity;
	float theta;                  // Current angle of the particle 
	float fullCyclePeriod;        // Time to complete one full circle
	const int INTERVAL = 1;       // (Likely a time step in seconds)
	float previousTime;

public:
	// Constructor 1: Initializes with Centripetal Force 
	UniformCircularMotion(float circularMotionRadius, sf::Vector2f center, Particle& p, sf::Vector2f centripetalForce = sf::Vector2f(0.f, 0.f))
	{
		this->circularMotionRadius = circularMotionRadius;
		this->center = center;
		this->p = &p;
		p.particle.setRadius(circularMotionRadius / 4.f);
		p.particle.setOrigin(sf::Vector2f(p.particle.getRadius(), p.particle.getRadius()));
		p.position = Vector2f(center.x + circularMotionRadius, center.y + center.y);

		// Draw the center centerDot
		this->centerDot.setRadius(2.f);
		this->centerDot.setOrigin(sf::Vector2f(centerDot.getRadius(), centerDot.getRadius()));
		this->centerDot.setFillColor(Color::White);
		this->centerDot.setPosition(center);

		// Draw path
		this->path.setPointCount(300);
		this->path.setRadius(circularMotionRadius);
		this->path.setOrigin(sf::Vector2f(path.getRadius(), path.getRadius()));
		this->path.setFillColor(Color::Transparent);
		this->path.setOutlineColor(Color::White);
		this->path.setOutlineThickness(2.f);
		this->path.setPosition(center);

		// Previous time
		previousTime = 0.f;

		// Important initial calculations:
		this->centripetalForce = centripetalForce;
		this->centripetalAcceleration = centripetalForce / p.mass;
		this->theta = acos(centripetalForce.x / circularMotionRadius); // Assuming standard angle conventions

		// Velocity, Angular Velocity, Period
		float velocityMagnitude = sqrt(Util::resultantMagnitude(centripetalAcceleration) * circularMotionRadius);
		this->velocity = Vector2f(velocityMagnitude * cos(theta), velocityMagnitude * sin(theta));
		this->angularVelocity = velocityMagnitude / circularMotionRadius;
		this->fullCyclePeriod = (2 * Util::PI() * circularMotionRadius) / velocityMagnitude;
	}

	// Constructor 2: Initializes with Centripetal Force Magnitude
	UniformCircularMotion(float circularMotionRadius, sf::Vector2f center, Particle& p, float centripetalForceMagnitude)
	{
		this->circularMotionRadius = circularMotionRadius;
		this->center = center;
		this->p = &p;
		p.particle.setRadius(circularMotionRadius / 4.f);
		p.particle.setOrigin(sf::Vector2f(p.particle.getRadius(), p.particle.getRadius()));
		p.position = Vector2f(circularMotionRadius + center.x, center.y);

		// Draw the center centerDot
		this->centerDot.setRadius(2.f);
		this->centerDot.setOrigin(sf::Vector2f(centerDot.getRadius(), centerDot.getRadius()));
		this->centerDot.setFillColor(Color::White);
		this->centerDot.setPosition(center);

		// Draw path
		this->path.setRadius(circularMotionRadius);
		this->path.setOrigin(sf::Vector2f(path.getRadius(), path.getRadius()));
		this->path.setFillColor(Color::Transparent);
		this->path.setOutlineColor(Color::White);
		this->path.setOutlineThickness(2.f);
		this->path.setPosition(center);

		// Previous time
		previousTime = 0.f;

		// Initial calculations (notice how they start from force magnitude)
		this->theta = acos((p.position.x - center.x) / circularMotionRadius);

		// Calculations cascade to find centripetalForce, centripetalAcceleration, velocity, angularVelocity and Period.
		this->centripetalForce = Vector2f(centripetalForceMagnitude * cos(theta), centripetalForceMagnitude * sin(theta));
		this->centripetalAcceleration = centripetalForce / p.mass; // Same direction as centripetal force
		float velocityMagnitude = sqrt(Util::resultantMagnitude(centripetalAcceleration) * circularMotionRadius);
		this->velocity = Vector2f(velocityMagnitude * cos(theta), velocityMagnitude * sin(theta));
		this->angularVelocity = velocityMagnitude / circularMotionRadius; 
		this->fullCyclePeriod = (2 * 3.141592654f * circularMotionRadius) / velocityMagnitude;
	}

	// update: Advances the simulation by a time step
	void update(sf::Time period);

	// calculateAndCreateView: Creates an SFML View suitable for the circular motion
	View calculateAndCreateView(RenderWindow& window) const;

	// draw: Renders the visual components of the simulation
	void draw(RenderWindow& window) const;
};

