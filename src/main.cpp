#include "SFML/Graphics.hpp"
#include "Particle.h"
#include "Spring.h"
#include "Force.h"
#include "ProjectileMotion.h"
#include "UniformCircularMotion.h"

using namespace sf;

//*****************************************
// Header: Physics Simulation
// Purpose: Provides a framework for various physics simulations, 
//          including basic particle movement, projectile motion,
//          and uniform circular motion.
//*****************************************

//*****************************************
// Simulation Configuration
//*****************************************

float simulationTimeLimit = 120; // Simulation duration in seconds

//*****************************************
// Main Program
//*****************************************

int main()
{
	//*****************************************
	// Window and World Setup
	//*****************************************

	const float SCREEN_WIDTH = 1920.f;
	const float SCREEN_HEIGHT = 1080.f;
	RenderWindow window(VideoMode(Vector2u(SCREEN_WIDTH, SCREEN_HEIGHT)), "Physics Simulation Window");
	window.setFramerateLimit(600.f);

	Vector2f gravity(0.0f, 9.8f); // Downward acceleration due to gravity
	float temperature = 25.f;     // Ambient temperature (degrees Celsius)
	Clock simulationTime;         // Tracks elapsed simulation time
	Clock frameTime;              // Tracks time per frame
	int frame = 0;                // Frame counter

	// Panning setup
	Vector2f originalMousePosition;
	bool isPanning = false;
	View view = window.getDefaultView();

	// Particle dragging setup
	bool isDragingParticle = false;

	// Zoom setup
	float zoomFactor = 1.0f;
	const float ZOOM_SPEED = 0.05f;

	//*****************************************
	// Simulation Objects and Setup
	//*****************************************

	// Particle setup
	Vector2f position(0.f, SCREEN_HEIGHT);
	Vector2f velocity(0.f, -9.f);
	float mass = 2;
	Particle p(mass, position, velocity, Vector2f(2, 5));

	// Motion setup (Choose one type for the simulation)
	float initialVelocity = 500.f;
	float angleOfProjection = Util::PI() / 2.5;
	float gravityMagnitude = 9.5;
	float groundY = SCREEN_HEIGHT;

	//ProjectileMotion motion(p, p.position, initialVelocity, angleOfProjection, window, gravityMagnitude, groundY); 
	UniformCircularMotion motion(149, Vector2f(SCREEN_HEIGHT/2, 0.f), p, 100);

	//*****************************************
	// Main Simulation Loop
	//*****************************************	
	simulationTime.restart();
	// Main loop
	while (window.isOpen())
	{

		// Handle events
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();

			if (event->is<sf::Event::MouseButtonPressed>() && event->getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left)
			{
				const sf::Vector2i mouse_position_i = event->getIf<sf::Event::MouseButtonPressed>()->position;
				const sf::Vector2f mouse_position_f = window.mapPixelToCoords(mouse_position_i);
				float distance = Util::resultantMagnitude(mouse_position_f - p.position);
				if (distance < p.particle.getRadius())
					isDragingParticle = true;
			}

			if (event->is<sf::Event::MouseButtonReleased>() && event->getIf<sf::Event::MouseButtonReleased>()->button == sf::Mouse::Button::Left)
			{
				isDragingParticle = false;
			}

			// Pan Controls
			if (event->is<sf::Event::MouseButtonPressed>() && event->getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Right)
			{
				originalMousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
				isPanning = true;
			}

			if (event->is<sf::Event::MouseButtonReleased>() && event->getIf<sf::Event::MouseButtonReleased>()->button == sf::Mouse::Button::Right)
			{
				isPanning = false;
			}

			// Zoom Controls 
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::PageUp))
			{
				zoomFactor += ZOOM_SPEED;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::PageDown))
			{
				zoomFactor -= ZOOM_SPEED;
				zoomFactor = std::max(zoomFactor, 0.1f); // Prevent zooming out too far
			}
		}

		// Simulation Time Check
		if (simulationTime.getElapsedTime().asSeconds() >= simulationTimeLimit)
		{
			window.close();
		}

		// Particle Dragging
		if (isDragingParticle)
		{
			p.velocity = Vector2f(0.f, 0.f);
			p.position = Vector2f(Mouse::getPosition(window));
			
		}
		else
		{
			/// SIMULATION UPDATE
			motion.update(simulationTime.getElapsedTime());
			p.update();
		}
		

		// Set the new line position

		// Draw and render
		window.clear(Color::Black);

		// Apply zoom using an SFML View
		View view = window.getDefaultView();
		view.zoom(zoomFactor);

		// Apply Panning using SFML
		if (isPanning)
		{
			Vector2f newMousePosition = Vector2f(Mouse::getPosition(window));
			Vector2f delta = originalMousePosition - newMousePosition;
			view.move(delta);
			window.setView(view);
		}

		// Setup view
		window.setView(view);
		window.setView(motion.calculateAndCreateView(window));

		/// SIMULATION RENDERING
		// Draw all the fading trail circles
		motion.draw(window);
		window.draw(p.particle);
		
		/// SIMULATION RENDERING END

		// Display Renderd objects
		window.display();

		frameTime.restart();
	}

	return 0;

}

