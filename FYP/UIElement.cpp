#include "UIElement.h"

UIElement::UIElement(sf::Vector2f p, float angle, bool a, int t)
{

	type = t;

	if (type == 1)
	{
		if (!UITexture.loadFromFile("UI.png"))
		{
			// error...
		}
		UITexture.setSmooth(true);

		UISprite.setTexture(UITexture);
		UISprite.setOrigin(sf::Vector2f(UISprite.getTextureRect().width / 2, UISprite.getTextureRect().height / 2));
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
	}
	
	position = p;

	UISprite.setScale(sf::Vector2f(1.0f, 1.0f));
	
	UISprite.setRotation(angle);
	
	UISprite.setColor(sf::Color(255, 255, 255, 255));

	active = a;

	//UISprite.setPosition(sf::Vector2f((ship->getSprite().getPosition().x - ship->getSprite().getTextureRect().width / 2) + position.x, (ship->getSprite().getPosition().y - ship->getSprite().getTextureRect().height / 2) + position.y));
}

void UIElement::Update()
{
	if (active == false)
	{
		if (type == 4)
		{
			if (ShipManager::GetInstance()->ships.at(0)->missileTimer < 0 && ShipManager::GetInstance()->ships.at(0)->missileFiring == false)
			{
				UISprite.setTexture(UITexture);
				active = true;
			}
		}
		if (type == 5)
		{
			if (ShipManager::GetInstance()->ships.at(0)->shieldTimer < 0 && ShipManager::GetInstance()->ships.at(0)->shieldDuration < 0)
			{
				UISprite.setTexture(UITexture);
				active = true;
			}
		}
	}
	if (active == true)
	{
		if (type == 4)
		{
			if (ShipManager::GetInstance()->ships.at(0)->missileTimer > 0 || ShipManager::GetInstance()->ships.at(0)->missileFiring == true)
			{
				UISprite.setTexture(UIAltTexture);
				active = false;
			}
		}
		if (type == 5)
		{
			if (ShipManager::GetInstance()->ships.at(0)->shieldTimer > 0 && ShipManager::GetInstance()->ships.at(0)->shieldDuration > 0)
			{
				UISprite.setTexture(UIAltTexture);
				active = false;
			}
		}
	}
	//UISprite.setPosition(sf::Vector2f((*ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().x - *ShipManager::GetInstance()->ships.at(0)->getSprite().getTextureRect().width / 2) + position.x, (*ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().y - *ShipManager::GetInstance()->ships.at(0)->getSprite().getTextureRect().height / 2) + position.y));
	UISprite.setPosition(sf::Vector2f(ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().x + position.x * UISprite.getScale().x, ShipManager::GetInstance()->ships.at(0)->getSprite().getPosition().y + position.y  * UISprite.getScale().y));
}

void UIElement::Draw(sf::RenderWindow & window)
{
	window.draw(UISprite);
}