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

#include <chrono>

#include "Ship.h"
#include "ProjectileManager.h"

#include "Box2D\Box2D.h"

#include "AnimatedSprite.hpp"

#include "AnimationManager.h"

#include "ContactListener.h"

#include "ShipManager.h"

#include "WreckManager.h"

#include "UIElement.h"

#include "Globals.h"

#include "SoundManager.h"

//doxygen

static const float SCALE = 30.f;

int main()
{
	std::chrono::steady_clock myClock;
	const auto timePerTick = std::chrono::milliseconds(16);
	auto timeOfLastTick = myClock.now();

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

	window.setMouseCursorVisible(false);

	ProjectileManager::GetInstance()->setWorld(World);
	WreckManager::GetInstance()->setWorld(World);
	ShipManager::GetInstance()->setWorld(World);
	ShipManager::GetInstance()->setWindow(window);

	ShipManager::GetInstance()->CreateShip(sf::Vector2f(300, 300), "player");

	ShipManager::GetInstance()->CreateShip(sf::Vector2f(700, 300), "enemy");

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

	sf::Texture cursor;

	if (!cursor.loadFromFile("Cursor2.png"))
	{
		// error...
	}

	cursor.setSmooth(true);

	sf::Sprite cursorSprite;

	cursorSprite.setTexture(cursor);

	cursorSprite.setScale(sf::Vector2f(0.35f, 0.35f));

	cursorSprite.setPosition(sf::Vector2f(0, 0));

	cursorSprite.setOrigin(sf::Vector2f(50, 50));

	UIElement ui = UIElement(sf::Vector2f(0, 0), 0, true, 1);

	UIElement uiHealth = UIElement(sf::Vector2f(-197, 310), 0, true, 2);

	UIElement uiPower = UIElement(sf::Vector2f(-197, 343), 0, true, 3);

	UIElement uiAbility1 = UIElement(sf::Vector2f(-148, -325), 0, true, 4);

	UIElement uiAbility2 = UIElement(sf::Vector2f(-50, -324), 0, true, 5);

	sf::View view(sf::FloatRect(ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().x, ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().y, 1280, 720));

	view.setCenter(sf::Vector2f(ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().x, ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().y));

	window.setView(view);

	 //create a view with its center and size
	sf::View view2(sf::Vector2f(350, 300), sf::Vector2f(300, 200));

	sf::Event event;

	while (window.isOpen())
	{
		while (myClock.now() - timeOfLastTick >= timePerTick) 
		{
			timeOfLastTick = myClock.now();

			World.Step(1 / 60.f, 8, 3);

			view.setCenter(sf::Vector2f(ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().x, ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().y));

			ui.Update();
			uiHealth.Update();
			uiPower.Update();
			uiAbility1.Update();
			uiAbility2.Update();

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
							float tempX = view.getSize().x / 1280;
							float tempY = view.getSize().y / 720;
							ui.UISprite.setScale(tempX, tempY);
							uiHealth.UISprite.setScale(tempX, tempY);
							uiPower.UISprite.setScale(tempX, tempY);
							uiAbility1.UISprite.setScale(tempX, tempY);
							uiAbility2.UISprite.setScale(tempX, tempY);
							cursorSprite.setScale(tempX / 3, tempY / 3);
							/*ui.UISprite.setScale(sf::Vector2f(ui.UISprite.getScale().x * 0.9, ui.UISprite.getScale().y * 0.9));
							uiHealth.UISprite.setScale(sf::Vector2f(uiHealth.UISprite.getScale().x * 0.9, uiHealth.UISprite.getScale().y * 0.9));
							uiPower.UISprite.setScale(sf::Vector2f(uiPower.UISprite.getScale().x * 0.9, uiPower.UISprite.getScale().y * 0.9));*/
						}
					}
					else if (event.mouseWheelScroll.delta < 0)
					{
						sf::Vector2f size = view.getSize();
						if (size.x < 2560)
						{
							view.zoom(1.1f);
							float tempX = view.getSize().x / 1280;
							float tempY = view.getSize().y / 720;
							ui.UISprite.setScale(tempX, tempY);
							uiHealth.UISprite.setScale(tempX, tempY);
							uiPower.UISprite.setScale(tempX, tempY);
							uiAbility1.UISprite.setScale(tempX, tempY);
							uiAbility2.UISprite.setScale(tempX, tempY);
							cursorSprite.setScale(tempX / 3, tempY / 3);
							/*ui.UISprite.setScale(sf::Vector2f(ui.UISprite.getScale().x * 1.1, ui.UISprite.getScale().y * 1.1));
							uiHealth.UISprite.setScale(sf::Vector2f(uiHealth.UISprite.getScale().x * 1.1, uiHealth.UISprite.getScale().y * 1.1));
							uiPower.UISprite.setScale(sf::Vector2f(uiPower.UISprite.getScale().x * 1.1, uiPower.UISprite.getScale().y * 1.1));*/
						}
					}
				}
			}

			sf::Vector2i mousePos;
			mousePos = sf::Mouse::getPosition(window);
			sf::Vector2f worldMousePos = window.mapPixelToCoords(mousePos);

			cursorSprite.setPosition(worldMousePos);

			ProjectileManager::GetInstance()->Update();
			AnimationManager::GetInstance()->Update();
			ShipManager::GetInstance()->Update();
			WreckManager::GetInstance()->Update();
			SoundManager::GetInstance()->Update();

		}
		
		window.clear();
		window.draw(backgroundSprite);
		WreckManager::GetInstance()->Draw(window);
		AnimationManager::GetInstance()->Draw2(window);
		ProjectileManager::GetInstance()->Draw2(window);
		ShipManager::GetInstance()->Draw(window);
		ProjectileManager::GetInstance()->Draw(window);
		AnimationManager::GetInstance()->Draw(window);
		ui.Draw(window);
		uiHealth.Draw(window);
		uiPower.Draw(window);
		uiAbility1.Draw(window);
		uiAbility2.Draw(window);
		window.draw(cursorSprite);
		window.display();
	}

	return 0;

}