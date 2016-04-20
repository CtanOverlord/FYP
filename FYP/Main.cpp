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

#include "Menu.h"

#include "CapPoint.h"

#include "Level.h"

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
	ShipManager::GetInstance()->prepare();
	Level::GetInstance()->setWorld(World);
	Level::GetInstance()->setWindow(window);
	Level::GetInstance()->createWorld();
	SoundManager::GetInstance()->ShieldsOff();

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

	sf::Texture background1;

	if (!background1.loadFromFile("loading.png"))
	{
		// error...
	}

	background1.setSmooth(true);

	sf::Sprite backgroundSprite1;

	backgroundSprite1.setTexture(background1);

	backgroundSprite1.setScale(sf::Vector2f(1.0f, 1.0f));

	backgroundSprite1.setPosition(sf::Vector2f(-10000, -10000));

	backgroundSprite1.setOrigin(sf::Vector2f(640, 360));

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

	UIElement uiLock = UIElement(sf::Vector2f(-295, 310), 0, true, 10);

	UIElement* uiAbility1;

	UIElement* uiAbility2;

	uiAbility1 = new UIElement(sf::Vector2f(-148, -325), 0, true, 4);

	uiAbility2 = new UIElement(sf::Vector2f(-50, -324), 0, true, 5);

	sf::View view(sf::FloatRect(0, 0, 1280, 720));

	view.setCenter(sf::Vector2f(0, 0));

	window.setView(view);

	//create a view with its center and size
	sf::View view2(sf::Vector2f(-10000, -10000), sf::Vector2f(1280, 720));

	sf::Event event;

	Menu menu = Menu(window);

	bool firstLaunch = false;

	bool respawnLoad = false;

	int loadTimer = 30;

	while (window.isOpen())
	{
		while (myClock.now() - timeOfLastTick >= timePerTick)
		{
			timeOfLastTick = myClock.now();

			World.Step(1 / 60.f, 8, 3);

			switch (menu.currentState) {

			case(menu.State::SPLASH) :
				view.setCenter(sf::Vector2f(0, 0));
				window.setView(view);
			   break;

			case(menu.State::MAIN) :
				view.setCenter(sf::Vector2f(0, 0));
				window.setView(view);
				break;

			case(menu.State::OPTIONS) :
				view.setCenter(sf::Vector2f(0, 0));
				window.setView(view);
				break;
			case(menu.State::GAME) :

				if (firstLaunch == false)
				{
					ShipManager::GetInstance()->CreateShip(sf::Vector2f(-500, 2200), "player", menu.shipType);


					ShipManager::GetInstance()->CreateShip(sf::Vector2f(500, 2200), "ally", "Sniper");

					ShipManager::GetInstance()->CreateShip(sf::Vector2f(1250, 2200), "ally", "Frigate");

					ShipManager::GetInstance()->CreateShip(sf::Vector2f(1800, 2200), "ally", "Dreadnought");

					//ShipManager::GetInstance()->CreateShip(sf::Vector2f(-500, 2200), "ally", "Dreadnought");

					ShipManager::GetInstance()->CreateShip(sf::Vector2f(-1250, 2200), "ally", "Sniper");

					ShipManager::GetInstance()->CreateShip(sf::Vector2f(-1800, 2200), "ally", "Frigate");


					ShipManager::GetInstance()->CreateShip(sf::Vector2f(500, -2200), "enemy", "Sniper");

					ShipManager::GetInstance()->CreateShip(sf::Vector2f(1250, -2200), "enemy", "Frigate");

					ShipManager::GetInstance()->CreateShip(sf::Vector2f(1800, -2200), "enemy", "Dreadnought");

					ShipManager::GetInstance()->CreateShip(sf::Vector2f(-500, -2200), "enemy", "Frigate");

					ShipManager::GetInstance()->CreateShip(sf::Vector2f(-1250, -2200), "enemy", "Sniper");

					ShipManager::GetInstance()->CreateShip(sf::Vector2f(-1800, -2200), "enemy", "Frigate");


					if (ShipManager::GetInstance()->ships.at(0)->shipType == "Dreadnought")
					{
						uiAbility1 = new UIElement(sf::Vector2f(-148, -325), 0, true, 4);

						uiAbility2 = new UIElement(sf::Vector2f(-50, -324), 0, true, 5);
					}
					else if (ShipManager::GetInstance()->ships.at(0)->shipType == "Frigate")
					{
						uiAbility1 = new UIElement(sf::Vector2f(-148, -325), 0, true, 6);

						uiAbility2 = new UIElement(sf::Vector2f(-50, -324), 0, true, 7);
					}

					else if (ShipManager::GetInstance()->ships.at(0)->shipType == "Sniper")
					{
						uiAbility1 = new UIElement(sf::Vector2f(-148, -325), 0, true, 8);

						uiAbility2 = new UIElement(sf::Vector2f(-50, -324), 0, true, 9);
					}

					firstLaunch = true;
				}

								   if (respawnLoad == true)
								   {
									   delete uiAbility1;
									   delete uiAbility2;

									   if (ShipManager::GetInstance()->ships.at(0)->shipType == "Dreadnought")
									   {
										   uiAbility1 = new UIElement(sf::Vector2f(-148, -325), 0, true, 4);

										   uiAbility2 = new UIElement(sf::Vector2f(-50, -324), 0, true, 5);
									   }
									   else if (ShipManager::GetInstance()->ships.at(0)->shipType == "Frigate")
									   {
										   uiAbility1 = new UIElement(sf::Vector2f(-148, -325), 0, true, 6);

										   uiAbility2 = new UIElement(sf::Vector2f(-50, -324), 0, true, 7);
									   }

									   else if (ShipManager::GetInstance()->ships.at(0)->shipType == "Sniper")
									   {
										   uiAbility1 = new UIElement(sf::Vector2f(-148, -325), 0, true, 8);

										   uiAbility2 = new UIElement(sf::Vector2f(-50, -324), 0, true, 9);
									   }
									   respawnLoad = false;
								   }


				view.setCenter(sf::Vector2f(ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().x, ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().y));

				SoundManager::GetInstance()->setShipPos(sf::Vector2f(ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().x, ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().y));

				ui.Update();
				uiHealth.Update();
				uiPower.Update();
				uiLock.Update();
				uiAbility1->Update();
				uiAbility2->Update();

				window.setView(view);

				if (ShipManager::GetInstance()->ships.at(0)->destroyed == true)
				{
					menu.respawnState();
				}

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
								//ui.UISprite.setScale(tempX, tempY);
								//uiHealth.UISprite.setScale(tempX, tempY);
								//uiPower.UISprite.setScale(tempX, tempY);
								//uiAbility1->UISprite.setScale(tempX, tempY);
								//uiAbility2->UISprite.setScale(tempX, tempY);
								cursorSprite.setScale(tempX / 3, tempY / 3);
								/*ui.UISprite.setScale(sf::Vector2f(ui.UISprite.getScale().x * 0.9, ui.UISprite.getScale().y * 0.9));
								uiHealth.UISprite.setScale(sf::Vector2f(uiHealth.UISprite.getScale().x * 0.9, uiHealth.UISprite.getScale().y * 0.9));
								uiPower.UISprite.setScale(sf::Vector2f(uiPower.UISprite.getScale().x * 0.9, uiPower.UISprite.getScale().y * 0.9));*/
							}
						}
						else if (event.mouseWheelScroll.delta < 0)
						{
							sf::Vector2f size = view.getSize();
							if (size.x < 2560 && ShipManager::GetInstance()->ships.at(0)->shipType != "Sniper" || size.x < 6000 && ShipManager::GetInstance()->ships.at(0)->shipType == "Sniper")
							{
								view.zoom(1.1f);
								float tempX = view.getSize().x / 1280;
								float tempY = view.getSize().y / 720;
								//ui.UISprite.setScale(tempX, tempY);
								//uiHealth.UISprite.setScale(tempX, tempY);
								//uiPower.UISprite.setScale(tempX, tempY);
								//uiAbility1->UISprite.setScale(tempX, tempY);
								//uiAbility2->UISprite.setScale(tempX, tempY);
								cursorSprite.setScale(tempX / 3, tempY / 3);
								/*ui.UISprite.setScale(sf::Vector2f(ui.UISprite.getScale().x * 1.1, ui.UISprite.getScale().y * 1.1));
								uiHealth.UISprite.setScale(sf::Vector2f(uiHealth.UISprite.getScale().x * 1.1, uiHealth.UISprite.getScale().y * 1.1));
								uiPower.UISprite.setScale(sf::Vector2f(uiPower.UISprite.getScale().x * 1.1, uiPower.UISprite.getScale().y * 1.1));*/
							}
						}
					}
				}

				loadTimer--;

				//backgroundSprite1.setPosition(sf::Vector2f(ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().x, ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().y));

				ProjectileManager::GetInstance()->Update();
				AnimationManager::GetInstance()->Update();
				ShipManager::GetInstance()->Update();
				WreckManager::GetInstance()->Update();
				SoundManager::GetInstance()->Update();
				TurretManager::GetInstance()->Update();
				Level::GetInstance()->Update();

				break;
			case(menu.State::INGAME) :
				menu.BGISprite.setPosition(sf::Vector2f(ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().x, ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().y));
				menu.playIG->UISprite.setPosition(sf::Vector2f(ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().x, ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().y - 130));
				menu.optionsIG->UISprite.setPosition(sf::Vector2f(ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().x, ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().y));
				menu.quitIG->UISprite.setPosition(sf::Vector2f(ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().x, ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().y + 130));
				menu.playIG->text.setPosition(sf::Vector2f(ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().x, ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().y - 130));
				menu.optionsIG->text.setPosition(sf::Vector2f(ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().x, ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().y));
				menu.quitIG->text.setPosition(sf::Vector2f(ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().x, ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().y + 130));

				while (window.pollEvent(event))
				{
					if (event.type == sf::Event::MouseButtonReleased)
					{
						if (event.mouseButton.button == sf::Mouse::Left)
						{
							menu.released = true;
						}
					}
				}

				break;
			case(menu.State::RESPAWN) :
				menu.BGRSprite.setPosition(sf::Vector2f(ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().x, ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().y));
				menu.shipR1->UISprite.setPosition(sf::Vector2f(ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().x - 300, ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().y));
				menu.shipR2->UISprite.setPosition(sf::Vector2f(ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().x, ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().y));
				menu.shipR3->UISprite.setPosition(sf::Vector2f(ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().x + 300, ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().y));
				menu.shipR1->text.setPosition(sf::Vector2f(ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().x - 300, ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().y + 130));
				menu.shipR2->text.setPosition(sf::Vector2f(ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().x, ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().y + 130));
				menu.shipR3->text.setPosition(sf::Vector2f(ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().x + 300, ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().y + 130));

				respawnLoad = true;

				while (window.pollEvent(event))
				{
					if (event.type == sf::Event::MouseButtonReleased)
					{
						if (event.mouseButton.button == sf::Mouse::Left)
						{
							menu.released = true;
						}
					}
				}

				break;
			case(menu.State::OPTIONSIG) :
				menu.BGISprite.setPosition(sf::Vector2f(ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().x, ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().y));
				menu.optionsBack->UISprite.setPosition(sf::Vector2f(ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().x - 305, ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().y - 210));

				break;

			case(menu.State::ENDGAME) :
				view.reset(sf::FloatRect(0, 0, 1280, 720));
				view.setCenter(0, 0);
				menu.BGISprite.setPosition(sf::Vector2f(ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().x, ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().y));
				menu.optionsBack->UISprite.setPosition(sf::Vector2f(ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().x - 305, ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().y - 210));

				break;

			case(menu.State::QUIT) :
				window.close();
				break;
			}

			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::MouseButtonReleased)
				{
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						menu.released = true;
					}
				}
			}

			sf::Vector2i mousePos;
			mousePos = sf::Mouse::getPosition(window);
			sf::Vector2f worldMousePos = window.mapPixelToCoords(mousePos);

			cursorSprite.setPosition(worldMousePos);

			menu.Update();
		}

		window.clear();

		switch (menu.currentState) {

		case(menu.State::SPLASH) :
			break;

		case(menu.State::MAIN) :

			break;

		case(menu.State::OPTIONS) :

			break;
		case(menu.State::OPTIONSIG) :
			window.setView(view);
			window.draw(backgroundSprite);
			Level::GetInstance()->Draw();
			WreckManager::GetInstance()->Draw(window);
			AnimationManager::GetInstance()->Draw2(window);
			ProjectileManager::GetInstance()->Draw2(window);
			ShipManager::GetInstance()->Draw(window);
			AnimationManager::GetInstance()->Draw3(window);
			TurretManager::GetInstance()->Draw(window);
			TurretManager::GetInstance()->Draw2(window);
			ShipManager::GetInstance()->Draw2(window);
			ProjectileManager::GetInstance()->Draw(window);
			AnimationManager::GetInstance()->Draw(window);
			window.setView(view2);
			ui.Draw(window);
			uiHealth.Draw(window);
			uiPower.Draw(window);
			uiLock.Draw(window);
			uiAbility1->Draw(window);
			uiAbility2->Draw(window);
			break;
		case(menu.State::RESPAWN) :
			window.setView(view);
			window.draw(backgroundSprite);
			Level::GetInstance()->Draw();
			WreckManager::GetInstance()->Draw(window);
			AnimationManager::GetInstance()->Draw2(window);
			ProjectileManager::GetInstance()->Draw2(window);
			ShipManager::GetInstance()->Draw(window);
			AnimationManager::GetInstance()->Draw3(window);
			TurretManager::GetInstance()->Draw(window);
			TurretManager::GetInstance()->Draw2(window);
			ShipManager::GetInstance()->Draw2(window);
			ProjectileManager::GetInstance()->Draw(window);
			AnimationManager::GetInstance()->Draw(window);
			window.setView(view2);
			ui.Draw(window);
			uiHealth.Draw(window);
			uiPower.Draw(window);
			uiLock.Draw(window);
			uiAbility1->Draw(window);
			uiAbility2->Draw(window);
			break;
		case(menu.State::GAME) :
			window.setView(view);
			window.draw(backgroundSprite);
			Level::GetInstance()->Draw();
			WreckManager::GetInstance()->Draw(window);
			AnimationManager::GetInstance()->Draw2(window);
			ProjectileManager::GetInstance()->Draw2(window);
			ShipManager::GetInstance()->Draw(window);
			AnimationManager::GetInstance()->Draw3(window);
			TurretManager::GetInstance()->Draw(window);
			TurretManager::GetInstance()->Draw2(window);
			ShipManager::GetInstance()->Draw2(window);
			ProjectileManager::GetInstance()->Draw(window);
			AnimationManager::GetInstance()->Draw(window);
			window.setView(view2);
			ui.Draw(window);
			uiHealth.Draw(window);
			uiPower.Draw(window);
			uiLock.Draw(window);
			uiAbility1->Draw(window);
			uiAbility2->Draw(window);

			if (loadTimer > 0)
			{
				window.draw(backgroundSprite1);
			}

			break;
		case(menu.State::INGAME) :
			window.setView(view);
			window.draw(backgroundSprite);
			Level::GetInstance()->Draw();
			WreckManager::GetInstance()->Draw(window);
			AnimationManager::GetInstance()->Draw2(window);
			ProjectileManager::GetInstance()->Draw2(window);
			ShipManager::GetInstance()->Draw(window);
			AnimationManager::GetInstance()->Draw3(window);
			TurretManager::GetInstance()->Draw(window);
			TurretManager::GetInstance()->Draw2(window);
			ShipManager::GetInstance()->Draw2(window);
			ProjectileManager::GetInstance()->Draw(window);
			AnimationManager::GetInstance()->Draw(window);
			window.setView(view2);
			ui.Draw(window);
			uiHealth.Draw(window);
			uiPower.Draw(window);
			uiLock.Draw(window);
			uiAbility1->Draw(window);
			uiAbility2->Draw(window);
			break;
		case(menu.State::ENDGAME) :
			break;
		}

		window.setView(view);
		menu.Draw();

		window.draw(cursorSprite);
		window.display();
	}

	return 0;

}