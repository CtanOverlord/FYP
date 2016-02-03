#include "Thruster.h"

Thruster::Thruster(sf::Vector2f p, float angle, bool a, string o)
{
	if (!turretTexture.loadFromFile("Thruster2.png"))
	{
		// error...
	}

	turretTexture.setSmooth(true);

	turretSprite.setTexture(turretTexture);

	position = p;

	ori = o;

	turretSprite.setScale(sf::Vector2f(0.25f, 0.25f));

	turretSprite.setRotation(angle);

	turretSprite.setColor(sf::Color(255, 255, 255, 255));

	active = a;

	speed = 0;

	turretSprite.setPosition(sf::Vector2f(p.x, p.y));

	turretSprite.setOrigin(sf::Vector2f(10, 100));
}

void Thruster::Update()
{
	if (active == true)
	{
		if (speed < 0.6)
		{
			speed += 0.1f;
			if (speed > 0.3 && speed < 0.4)
			{
				SoundManager::GetInstance()->CreateSound(turretSprite.getPosition(), 8);
			}
		}
	}
	else
	{
		if (speed > 0.0f)
		{
			speed -= 0.2f;
		}
		if (speed < 0)
		{
			speed = 0;
		}
	}
	
	turretSprite.setScale(sf::Vector2f(0.15f, speed / 2));
}

void Thruster::Draw(sf::RenderWindow & window)
{
	//if (active == true)
	//{
		window.draw(turretSprite);
	//}
}