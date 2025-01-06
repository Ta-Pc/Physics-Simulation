#include "UniformCircularMotion.h"
#include <iostream>

void UniformCircularMotion::update(sf::Time period)
{
	theta = angularVelocity * period.asSeconds();
	p->position = Vector2f(circularMotionRadius * cos(theta) + center.x, circularMotionRadius * sin((3/2 * Util::PI()) + theta) + center.y);

	// For every second
	if((period.asSeconds() - previousTime) >= INTERVAL)
	{
		// Changes in all the variables
		angularVelocity = theta / period.asSeconds();
		float velocityMagnitude = angularVelocity * circularMotionRadius;
		velocity = Vector2f(velocityMagnitude * cos(theta), velocityMagnitude * sin(theta));
		float centripetalAccelerationMagnitude = (velocityMagnitude * velocityMagnitude) / circularMotionRadius;
		centripetalAcceleration = Vector2f(centripetalAccelerationMagnitude * cos(theta), centripetalAccelerationMagnitude * sin(theta));
		centripetalForce = p->mass * centripetalAcceleration;

		// Print out the anaylisis
		std::cout << "Motion Analysis: @ t = " << period.asSeconds() << "\n";
		std::cout << "Centripetal Force: " << "(" << centripetalForce.x << "; " << centripetalForce.y << ") " << "-> " << Util::resultantMagnitude(centripetalForce) << " N" << std::endl;
		std::cout << "Centripetal Acceleration: " << "(" << centripetalAcceleration.x << "; " << centripetalAcceleration.y << ") " << "-> " << Util::resultantMagnitude(centripetalAcceleration) << " m/s^2" << std::endl;
		std::cout << "Velocity: " << "(" << velocity.x << "; " << velocity.y << ")" << ") " << "-> " << Util::resultantMagnitude(velocity) << " m/s" << std::endl;
		std::cout << "Position: " << "(" << p->position.x << "; " << p->position.y << ") " << "-> " << Util::resultantMagnitude(p->position - center) << " m" << std::endl;
		std::cout << "Angular Velocity: " << angularVelocity << " rad/s" << std::endl;
		std::cout << "Period: " << fullCyclePeriod << " s" << std::endl;
		std::cout << "Frequency: " << 1.f / fullCyclePeriod << " Hz" << std::endl;
		std::cout << "Angular Position: " << angularVelocity * period.asSeconds() << " rad" << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;

		previousTime = period.asSeconds();
	}
}

View UniformCircularMotion::calculateAndCreateView(RenderWindow& window) const
{
		View view = View(window.getView()); // Start with existing view

		float margin = 0.15f;

		// Finding the appropriate area
		float diameter = circularMotionRadius * 2;
		float zoomX =  (diameter * (1 + margin)) / window.getSize().x;
		float zoomY =  (diameter * (1 + margin)) / window.getSize().y;

		// Prioritize fitting the entire circle 
		float zoomFactor = std::min(zoomX, zoomY);

		// Avoid excessive zoom out if circle is small
		zoomFactor = std::max(zoomFactor, 0.7f);

		// Center the view on the circular motion
		Vector2f viewCenter(center);

		view.zoom(zoomFactor);
		view.setCenter(viewCenter);
		return view;

}

void UniformCircularMotion::draw(RenderWindow& window) const
{
	window.draw(path);
	window.draw(centerDot);
}
