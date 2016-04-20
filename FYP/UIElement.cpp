#include "UIElement.h"

UIElement::UIElement()
{
	type = 1;
}

UIElement::UIElement(sf::Vector2f p, float angle, bool a, int t)
{
	type = t;

	if (!font.loadFromFile("RAZEROBLIQUE.ttf"))
	{
		// error...
	}

	if (type == 1)
	{
		if (!UITexture.loadFromFile("UI2.png"))
		{
			// error...
		}
		UITexture.setSmooth(true);

		UISprite.setTexture(UITexture);
		UISprite.setOrigin(sf::Vector2f(UISprite.getTextureRect().width / 2, UISprite.getTextureRect().height / 2));

		
		// Create a text which uses our font
		blueText.setFont(font);
		blueText.setCharacterSize(15);
		blueText.setStyle(sf::Text::Regular);
		blueText.setPosition(sf::Vector2f(-10000 - 410, -10000 - 340));
		blueText.setString("Blue Points: " + to_string(Globals::GetInstance()->blueScore));
		blueText.setOrigin(0, blueText.getLocalBounds().height);

		redText.setFont(font);
		redText.setCharacterSize(15);
		redText.setStyle(sf::Text::Regular);
		redText.setPosition(sf::Vector2f(-10000 - 410, -10000 - 306));
		redText.setString("Red Points: " + to_string(Globals::GetInstance()->redScore));
		redText.setOrigin(0, redText.getLocalBounds().height);
	}
	if (type == 2)
	{
		if (!UITexture.loadFromFile("healthBar.png"))
		{
			// error...
		}
		UITexture.setSmooth(true);

		UISprite.setTexture(UITexture);
		UISprite.setOrigin(sf::Vector2f(0, UISprite.getTextureRect().height / 2));
	}
	if (type == 3)
	{
		if (!UITexture.loadFromFile("powerBar.png"))
		{
			// error...
		}
		UITexture.setSmooth(true);

		UISprite.setTexture(UITexture);
		UISprite.setOrigin(sf::Vector2f(0, UISprite.getTextureRect().height / 2));
	}
	if (type == 4)
	{
		if (!UITexture.loadFromFile("ability1.png"))
		{
			// error...
		}
		if (!UIAltTexture.loadFromFile("abilityUsed12.png"))
		{
			// error...
		}
		UITexture.setSmooth(true);

		UISprite.setTexture(UITexture);
		UISprite.setOrigin(sf::Vector2f(UISprite.getTextureRect().width / 2, UISprite.getTextureRect().height / 2));

		blueText.setFont(font);
		blueText.setCharacterSize(15);
		blueText.setStyle(sf::Text::Regular);
		blueText.setPosition(sf::Vector2f(-10000 - 165, -10000 - 335));
		blueText.setString("");
		blueText.setOrigin(0, blueText.getLocalBounds().height);
	}
	if (type == 5)
	{
		if (!UITexture.loadFromFile("ability2.png"))
		{
			// error...
		}
		if (!UIAltTexture.loadFromFile("abilityUsed22.png"))
		{
			// error...
		}
		UITexture.setSmooth(true);

		UISprite.setTexture(UITexture);
		UISprite.setOrigin(sf::Vector2f(UISprite.getTextureRect().width / 2, UISprite.getTextureRect().height / 2));

		blueText.setFont(font);
		blueText.setCharacterSize(15);
		blueText.setStyle(sf::Text::Regular);
		blueText.setPosition(sf::Vector2f(-10000 - 65, -10000 - 335));
		blueText.setString("");
		blueText.setOrigin(0, blueText.getLocalBounds().height);
	}
	if (type == 6)
	{
		if (!UITexture.loadFromFile("ability3.png"))
		{
			// error...
		}
		if (!UIAltTexture.loadFromFile("abilityUsed32.png"))
		{
			// error...
		}
		UITexture.setSmooth(true);

		UISprite.setTexture(UITexture);
		UISprite.setOrigin(sf::Vector2f(UISprite.getTextureRect().width / 2, UISprite.getTextureRect().height / 2));

		blueText.setFont(font);
		blueText.setCharacterSize(15);
		blueText.setStyle(sf::Text::Regular);
		blueText.setPosition(sf::Vector2f(-10000 - 165, -10000 - 335));
		blueText.setString("");
		blueText.setOrigin(0, blueText.getLocalBounds().height);
	}
	if (type == 7)
	{
		if (!UITexture.loadFromFile("ability4.png"))
		{
			// error...
		}
		if (!UIAltTexture.loadFromFile("abilityUsed42.png"))
		{
			// error...
		}
		UITexture.setSmooth(true);

		UISprite.setTexture(UITexture);
		UISprite.setOrigin(sf::Vector2f(UISprite.getTextureRect().width / 2, UISprite.getTextureRect().height / 2));

		blueText.setFont(font);
		blueText.setCharacterSize(15);
		blueText.setStyle(sf::Text::Regular);
		blueText.setPosition(sf::Vector2f(-10000 - 65, -10000 - 335));
		blueText.setString("");
		blueText.setOrigin(0, blueText.getLocalBounds().height);
	}
	if (type == 8)
	{
		if (!UITexture.loadFromFile("ability5.png"))
		{
			// error...
		}
		if (!UIAltTexture.loadFromFile("abilityUsed5.png"))
		{
			// error...
		}
		UITexture.setSmooth(true);

		UISprite.setTexture(UITexture);
		UISprite.setOrigin(sf::Vector2f(UISprite.getTextureRect().width / 2, UISprite.getTextureRect().height / 2));

		blueText.setFont(font);
		blueText.setCharacterSize(15);
		blueText.setStyle(sf::Text::Regular);
		blueText.setPosition(sf::Vector2f(-10000 - 165, -10000 - 335));
		blueText.setString("");
		blueText.setOrigin(0, blueText.getLocalBounds().height);
	}
	if (type == 9)
	{
		if (!UITexture.loadFromFile("ability6.png"))
		{
			// error...
		}
		if (!UIAltTexture.loadFromFile("abilityUsed6.png"))
		{
			// error...
		}
		UITexture.setSmooth(true);

		UISprite.setTexture(UITexture);
		UISprite.setOrigin(sf::Vector2f(UISprite.getTextureRect().width / 2, UISprite.getTextureRect().height / 2));

		blueText.setFont(font);
		blueText.setCharacterSize(15);
		blueText.setStyle(sf::Text::Regular);
		blueText.setPosition(sf::Vector2f(-10000 - 65, -10000 - 335));
		blueText.setString("");
		blueText.setOrigin(0, blueText.getLocalBounds().height);
	}
	if (type == 10)
	{
		if (!UITexture.loadFromFile("Lock.png"))
		{
			// error...
		}
		if (!UIAltTexture.loadFromFile("Unlock.png"))
		{
			// error...
		}
		UITexture.setSmooth(true);

		UISprite.setTexture(UITexture);
		UISprite.setOrigin(sf::Vector2f(UISprite.getTextureRect().width / 2, UISprite.getTextureRect().height / 2));
	}
	
	position = p;

	if (type != 10)
	{
		UISprite.setScale(sf::Vector2f(1.0f, 1.0f));
	}
	else
	{
		UISprite.setScale(sf::Vector2f(0.4f, 0.4f));
	}
	
	UISprite.setRotation(angle);
	
	UISprite.setColor(sf::Color(255, 255, 255, 255));

	active = a;

	//UISprite.setPosition(sf::Vector2f((ship->getSprite().getPosition().x - ship->getSprite().getTextureRect().width / 2) + position.x, (ship->getSprite().getPosition().y - ship->getSprite().getTextureRect().height / 2) + position.y));
}

void UIElement::Update()
{
	if (active == false)
	{
		if (type == 4 || type == 6 || type == 8)
		{
			if (ShipManager::GetInstance()->ships.at(0)->missileTimer < 0 && ShipManager::GetInstance()->ships.at(0)->missileFiring == false)
			{
				UISprite.setTexture(UITexture);
				active = true;
			}

			blueText.setString(to_string((int)(ShipManager::GetInstance()->ships.at(0)->missileTimer)));
		}
		if (type == 5 || type == 7 || type == 9)
		{
			if (ShipManager::GetInstance()->ships.at(0)->shieldTimer < 0 && ShipManager::GetInstance()->ships.at(0)->shieldDuration < 0)
			{
				UISprite.setTexture(UITexture);
				active = true;
			}

			blueText.setString(to_string((int)(ShipManager::GetInstance()->ships.at(0)->shieldTimer)));
		}
	}
	if (active == true)
	{
		if (type == 4 || type == 6 || type == 8)
		{
			if (ShipManager::GetInstance()->ships.at(0)->missileTimer > 0 || ShipManager::GetInstance()->ships.at(0)->missileFiring == true)
			{
				UISprite.setTexture(UIAltTexture);
				active = false;
			}
			blueText.setString("");
		}
		if (type == 5 || type == 7 || type == 9)
		{
			if (ShipManager::GetInstance()->ships.at(0)->shieldTimer > 0 && ShipManager::GetInstance()->ships.at(0)->shieldDuration > 0)
			{
				UISprite.setTexture(UIAltTexture);
				active = false;
			}
			blueText.setString("");
		}
	}
	if (type == 1)
	{
		blueText.setString("Blue Points: " + to_string((int)Globals::GetInstance()->blueScore));
		redText.setString("Red Points: " + to_string((int)Globals::GetInstance()->redScore));
	}
	if (type == 2)
	{
		float scaleX = ShipManager::GetInstance()->ships.at(0)->health / ShipManager::GetInstance()->ships.at(0)->maxHealth;

		if (scaleX < 0)
		{
			scaleX = 0;
		}
		UISprite.setScale(scaleX, 1.0);
	}
	if (type == 3)
	{
		float scaleX = ShipManager::GetInstance()->ships.at(0)->fuel / ShipManager::GetInstance()->ships.at(0)->maxFuel;

		if (scaleX < 0)
		{
			scaleX = 0;
		}
		UISprite.setScale(scaleX, 1.0);
	}
	if (type == 10)
	{
		if (ShipManager::GetInstance()->ships.at(0)->shipType == "Sniper" && ShipManager::GetInstance()->ships.at(0)->manual == true)
		{
			UISprite.setTexture(UITexture);
			active = true;
		}
		else
		{
			UISprite.setTexture(UIAltTexture);
			active = false;
		}

		blueText.setString(to_string((int)(ShipManager::GetInstance()->ships.at(0)->shieldTimer)));
	}
	//UISprite.setPosition(sf::Vector2f((*ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().x - *ShipManager::GetInstance()->ships.at(0)->getSprite().getTextureRect().width / 2) + position.x, (*ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().y - *ShipManager::GetInstance()->ships.at(0)->getSprite().getTextureRect().height / 2) + position.y));
	//UISprite.setPosition(sf::Vector2f(ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().x + position.x * UISprite.getScale().x, ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().y + position.y  * UISprite.getScale().y));
	UISprite.setPosition(sf::Vector2f(-10000 + position.x, -10000 + position.y));
}

void UIElement::Draw(sf::RenderWindow & window)
{
	if (type == 1)
	{
		window.draw(UISprite);
		window.draw(blueText);
		window.draw(redText);
	}
	else if (type == 10)
	{
		if (ShipManager::GetInstance()->ships.size() > 0)
		{
			if (ShipManager::GetInstance()->ships.at(0)->shipType == "Sniper")
			{
				window.draw(UISprite);
			}
		}
	}
	else if (type != 2 || type != 3)
	{
		window.draw(UISprite);
		window.draw(blueText);
	}
	else
	{
		window.draw(UISprite);
	}
}