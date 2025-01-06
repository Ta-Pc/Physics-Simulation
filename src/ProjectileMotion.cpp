#include "ProjectileMotion.h"
#include <iostream>

void ProjectileMotion::update(Time period)
{
	// Calculation of change of objects position through time
	// Finding the chhange in position of the y component
	p->position.y = initialPositionOfProjectile.y + (p->velocity.y * period.asSeconds()) + (1 / 2.f * gravity * period.asSeconds() * period.asSeconds()); /// Down is taken as positive
	p->position.x = initialPositionOfProjectile.x + (p->velocity.x * period.asSeconds());

    // Draw trail as the ball moves
    sf::CircleShape trailCircle(trailCircleRadius);
    trailCircle.setFillColor(trailColor);
    trailCircle.setPosition(p->position);
    trailCircle.setOrigin(Vector2(trailCircleRadius, trailCircleRadius)); // Center the circle
    trailHistory.push_back(trailCircle);
    if (trailHistory.size() > maxTrailLength) 
    {
        trailHistory.erase(trailHistory.begin()); // Remove oldest if too long
    }

    // Ground Collision
    if (p->position.y >= groundLevel) {
        p->position.y = groundLevel;  // Stick the particle to the ground
        p->velocity.x -= p->velocity.x * 0.01f; // Simulate energy loss on bounce
        if (p->velocity.x < 0.01f)
            window->close();
    }

    // Motion Anylisis
	// For every second
	if ((period.asSeconds() - previousTime) >= INTERVAL)
	{
		// Changes in all the variables

		// Print out the anaylisis
		std::cout << "Motion Analysis: @ t = " << period.asSeconds() << "\n";
		std::cout << "Gravitational Force: " << gravity * p->mass << " N" << std::endl;
		std::cout << "Gravitational Acceleration: " << gravity << " m/s^2" << std::endl;
		std::cout << "Velocity: " << "(" << initialVelocityMagnitude << "; " << p->velocity.y + gravity * period.asSeconds() << ")" << ") " << "-> " << Util::resultantMagnitude(Vector2f(initialVelocityMagnitude, p->velocity.y + gravity * period.asSeconds())) << " m/s" << std::endl;
		std::cout << "Position: " << "(" << p->position.x - initialPositionOfProjectile.x << "; " << p->position.y - initialPositionOfProjectile.y << ") " << "-> " << Util::resultantMagnitude(p->position) << " m" << std::endl;
		std::cout << "Time of flight: " << timeOfFlight << " s" << std::endl;
		std::cout << "Maximum height: " << maximumHeight << " m" << std::endl;
		std::cout << "Range of motion: " << Range << " m" << std::endl;
		std::cout << "Angle of projection in radians: " << angleOfProjection << " rad" << std::endl;
		std::cout << "Angle of projection in degrees: " << 180/Util::PI() * angleOfProjection << " deg" << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;

		previousTime = period.asSeconds();
	}
}

View ProjectileMotion::calculateAndCreateView(RenderWindow& window) const
{
	View view = View(window.getView());

	// Increased Margin
	float margin = 0.2f; // Adjust this value as needed

	float zoomX = ((Range + 20.f) * (1 + margin)) / window.getSize().x;
	float zoomY = (maximumHeight * (1 + margin)) / window.getSize().y;
	float zoomFactor = 1.f;

	// Case 1: Motion bigger than screen (with margin)
	if (zoomX > 1.0f && zoomY > 1.0f)
	{
		zoomFactor = std::min(zoomX, zoomY);
		view.zoom(zoomFactor);
	}
	// Case 2: Motion is smaller than screen
	else
	{
		// Prioritize fitting width if it's the more extreme dimension
		if (zoomX < zoomY)
		{
			view.zoom(zoomX * 5);
		}
		else
		{
			view.zoom(zoomY * 5);
		}
	}

	Vector2f viewCenter(Range / 2, (window.getSize().y - maximumHeight) / 2);

	view.zoom(zoomFactor);
	view.setCenter(viewCenter);
	return view;
}

void ProjectileMotion::draw(RenderWindow& window)
{
	// Draw all fading trail circles
	for (int i = 0; i < trailHistory.size(); i++) {
		float opacityFactor = 1.0f - (i / float(trailHistory.size()));
		trailHistory[i].setFillColor(sf::Color(
			trailColor.r, trailColor.g, trailColor.b, opacityFactor * 255));
		window.draw(trailHistory[i]);
	}
	window.draw(groundLine);
}
