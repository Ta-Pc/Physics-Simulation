#include "Drag.h"
#include "cmath"
// Function to convert Celsius to Kelvin
float Drag::celsiusToKelvin(double celsius)
{
	return celsius + 273.15;
}

// Function to calculate air viscosity
float Drag::calculateViscosity(double temperatureCelsius)
{
	// Constants
	const double b = 1.458e-6;
	const double S = 110.4;

	double temperatureKelvin = celsiusToKelvin(temperatureCelsius);
	double u = (b * std::pow(temperatureKelvin, 1.5)) / (temperatureKelvin + S);
	return u;
}

// Function to calculate drag force of air
sf::Vector2f Drag::dragForce(float sphereRadius, sf::Vector2f velocity, float viscosity)
{
	// Constant
	const float Cd = 6.f * 3.141592654f;
	sf::Vector2f drag = -Cd * viscosity * sphereRadius * velocity;
	return drag;
}
