#ifdef _DEBUG
#pragma comment(lib,"sfml-graphics-d.lib")
#pragma comment(lib,"sfml-audio-d.lib")
#pragma comment(lib,"sfml-system-d.lib")
#pragma comment(lib,"sfml-window-d.lib")
#pragma comment(lib,"sfml-network-d.lib")
#else
#pragma comment(lib,"sfml-graphics.lib")
#pragma comment(lib,"sfml-audio.lib")
#pragma comment(lib,"sfml-system.lib")
#pragma comment(lib,"sfml-window.lib")
#pragma comment(lib,"sfml-network.lib")
#endif
#include "SFML/Graphics.hpp"
#include <cmath>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Ship.h"
#include "ProjectileManager.h"

#include "Box2D\Box2D.h"

#include "AnimatedSprite.hpp"

#include "AnimationManager.h"

#include "ContactListener.h"

#include "ShipManager.h"

//doxygen

static const float SCALE = 30.f;

int main()	
{
	b2Vec2 Gravity(0.f, 0);
	b2World World(Gravity);

	ContactListener contactListener;

	World.SetContactListener(&contactListener);

	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 1000;
	settings.majorVersion = 3;
	settings.minorVersion = 0;

	sf::RenderWindow window(sf::VideoMode(1280, 720), "FYP", sf::Style::Default, settings);
	
	window.setFramerateLimit(60);
	
	AnimationManager aniMan = AnimationManager();
	ProjectileManager projMan = ProjectileManager(World, aniMan);
	ShipManager shipMan = ShipManager(World, aniMan, projMan);

	shipMan.CreateShip(sf::Vector2f(300, 300), "player");

	shipMan.CreateShip(sf::Vector2f(700, 300), "enemy");
	
	//Ship ship = Ship(World, sf::Vector2f(300, 300), "player", projMan, aniMan);

	//Ship ship2 = Ship(World, sf::Vector2f(700, 300), "enemy", projMan, aniMan);

	sf::Texture background;

	if (!background.loadFromFile("background.jpg"))
	{
		// error...
	}
	
	background.setSmooth(true);

	sf::Sprite backgroundSprite;

	backgroundSprite.setTexture(background);

	backgroundSprite.setScale(sf::Vector2f(1.5f, 1.5f));

	backgroundSprite.setPosition(sf::Vector2f(0, 0));

	backgroundSprite.setOrigin(sf::Vector2f(1715, 1733));


	sf::View view(sf::FloatRect(shipMan.ships.at(0)->getSprite().getPosition().x, shipMan.ships.at(0)->getSprite().getPosition().y, 1280, 720));

	view.setCenter(sf::Vector2f(shipMan.ships.at(0)->getSprite().getPosition().x, shipMan.ships.at(0)->getSprite().getPosition().y));

	window.setView(view);

	// create a view with its center and size
	//sf::View view2(sf::Vector2f(350, 300), sf::Vector2f(300, 200));

	sf::Event event;

	while (window.isOpen())
	{
		// get global mouse position
		//sf::Vector2i position = sf::Mouse::getPosition();
		// set mouse position relative to a window
		//sf::Mouse::setPosition(sf::Vector2i(100, 200), window)

		World.Step(1 / 60.f, 8, 3);

		view.setCenter(sf::Vector2f(shipMan.ships.at(0)->getSprite().getPosition().x, shipMan.ships.at(0)->getSprite().getPosition().y));

		window.setView(view);

		while (window.pollEvent(event))
		{
				if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
				{
					if (event.type == event.MouseButtonPressed || event.type == event.MouseButtonReleased)
					{

					}
					else if (event.mouseWheelScroll.delta > 0)
					{
						sf::Vector2f size = view.getSize();
						if (size.x > 1280)
						{
							view.zoom(0.9f);
						}
					}
					else if (event.mouseWheelScroll.delta < 0)
					{
						sf::Vector2f size = view.getSize();
						if (size.x < 2560)
						{
							view.zoom(1.1f);
						}
					}
				}
		}

		projMan.Update();
		aniMan.Update();
		shipMan.Update();

		window.clear();
		window.draw(backgroundSprite);
		shipMan.Draw(window);
		projMan.Draw(window);
		aniMan.Draw(window);
		window.display();
	}

	return 0;

}