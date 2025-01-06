#include "Spring.h"

void Spring::update(Vector2f force, Time dt)
{
	// Update the lines position
	sf::VertexArray lines(sf::PrimitiveType::Lines, 2);
	lines[0] = sf::Vertex{(firstParticle->position), sf::Color::White};
	lines[1] = sf::Vertex{(lastParticle->position), sf::Color::White};

	// Find the acceleration caused by the force
	Vector2f acceleration = force / lastParticle->mass;

	///float acc = Util::resultantMagnitude(acceleration);

	// Use the acceleration to change the velocity of the ball
	lastParticle->velocity += acceleration * dt.asSeconds(); // Assuming that time is 1 second per frame

	///float vel = Util::resultantMagnitude(velocity);

	// Use velocity to change the position of the ball
	lastParticle->position += lastParticle->velocity * dt.asSeconds(); // Assuming that time is 1 second per frame

	// Add some friction to the velocity
	// Find the direction of the net force

	Vector2f directionOfForce = Util::normalize(force);

	// Friction
	Vector2f friction = -1.f * directionOfForce;
	lastParticle->velocity = lastParticle->velocity * 0.099f;
}

Vector2f Spring::hooksLaw(Vector2f gravity)
{
	// Find the displacement vector
	Vector2f displacement = line[1].position - line[0].position;
	float stretchLengthOfTheSpring = Util::resultantMagnitude(displacement);
	// Finding the displacement caused by the weight of the object
	float dymass = (lastParticle->mass * gravity.y) / k;
	float restLengthOfTheMassedSpring = dymass + restLengthOfAPointSpring;

	// The true displacement
	float dy = stretchLengthOfTheSpring - restLengthOfTheMassedSpring;

	// Finding Net force on the ball
	/// All forces act in the direction of the displacement
	Vector2f direction = Util::normalize(displacement);
	// Fnet
	Vector2f forceSpring = -k * dy * direction;
	Vector2f forceGravity = lastParticle->mass * gravity;
	Vector2f forceNet = forceSpring + forceGravity;

	return forceNet;
}