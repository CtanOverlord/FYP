#include "Ship.h"
#include "Turret.h"

static const float SCALE = 30.f;

Ship::Ship(b2World& World, sf::Vector2f position, string t, ProjectileManager & projManager, AnimationManager& a)
{
	if (!shipTexture.loadFromFile("Ship.png"))
	{
		// error...
	}

	destructionTimer = 240;

	delayTimer = 0;

	delay = 19; // or 17

	health = 1;

	shipTexture.setSmooth(true);

	shipSprite.setTexture(shipTexture);

	shipSprite.setScale(sf::Vector2f(0.5f, 0.5f));

	shipSprite.setPosition(sf::Vector2f(position.x, position.y));

	shipSprite.setOrigin(sf::Vector2f(200, 300));

	destroyed = false;

	if (!boosterTexture.loadFromFile("Boosters4.png"))
	{
		// error...
	}

	type = t;

	boosterTexture.setSmooth(true);

	boosterSprite.setTexture(boosterTexture);

	boosterSprite.setScale(sf::Vector2f(0.5f, 0.25f));

	boosterSprite.setPosition(sf::Vector2f(100, 290));

	boosterSprite.setOrigin(sf::Vector2f(140, 1));

	boosterPoint = sf::Vector2f(100, 290);

	velocity = sf::Vector2f(0, 0);

	world = &World;

	projMan = & projManager;

	aniMan = &a;

	speed = 0.010f;

	CreateBody();

	turrets.push_back(new Turret(sf::Vector2f(75, 80), *this, type, *projMan, *aniMan));
	turrets.push_back(new Turret(sf::Vector2f(124, 80), *this, type, *projMan, *aniMan));
	turrets.push_back(new Turret(sf::Vector2f(75, 127), *this, type, *projMan, *aniMan));
	turrets.push_back(new Turret(sf::Vector2f(124, 127), *this, type, *projMan, *aniMan));
	turrets.push_back(new Turret(sf::Vector2f(75, 175), *this, type, *projMan, *aniMan));
	turrets.push_back(new Turret(sf::Vector2f(124, 175), *this, type, *projMan, *aniMan));

	thrusters.push_back(new Thruster(sf::Vector2f(70, 4), 0, false, "front"));
	thrusters.push_back(new Thruster(sf::Vector2f(75, 4), 0, false, "front"));
	thrusters.push_back(new Thruster(sf::Vector2f(130, 4), 0, false, "front"));
	thrusters.push_back(new Thruster(sf::Vector2f(125, 4), 0, false, "front"));
	thrusters.push_back(new Thruster(sf::Vector2f(80, 4), 0, false, "front"));
	thrusters.push_back(new Thruster(sf::Vector2f(120, 4), 0, false, "front"));

	thrusters.push_back(new Thruster(sf::Vector2f(10, 70), 0, false, "topleft"));
	thrusters.push_back(new Thruster(sf::Vector2f(190, 70), 0, false, "topright"));
	thrusters.push_back(new Thruster(sf::Vector2f(10, 80), 0, false, "topleft"));
	thrusters.push_back(new Thruster(sf::Vector2f(190, 80), 0, false, "topright"));
	thrusters.push_back(new Thruster(sf::Vector2f(10, 75), 0, false, "topleft"));
	thrusters.push_back(new Thruster(sf::Vector2f(190, 75), 0, false, "topright"));
	thrusters.push_back(new Thruster(sf::Vector2f(10, 260), 0, false, "botleft"));
	thrusters.push_back(new Thruster(sf::Vector2f(190, 260), 0, false, "botright"));
	thrusters.push_back(new Thruster(sf::Vector2f(10, 250), 0, false, "botleft"));
	thrusters.push_back(new Thruster(sf::Vector2f(190, 250), 0, false, "botright"));
	thrusters.push_back(new Thruster(sf::Vector2f(10, 255), 0, false, "botleft"));
	thrusters.push_back(new Thruster(sf::Vector2f(190, 255), 0, false, "botright"));



	/*70, 4
		130,4
		10, 70
		190, 70
		10, 230
		190, 230

	*/

	/*150, 160
		249, 160
		150, 255
		249, 255
		150, 350
		249, 350

		1 / 2 scale:

	75, 80
		124, 80
		75, 127
		124, 127
		75, 175
		124, 175*/
}

void Ship::Update()
{
	boosterSprite.setPosition((shipSprite.getPosition().x - shipSprite.getTextureRect().width / 4) + boosterPoint.x, (shipSprite.getPosition().y - shipSprite.getTextureRect().height / 4) + boosterPoint.y);

	float s = sin(shipSprite.getRotation() * 0.0174532925);
	float c = cos(shipSprite.getRotation() * 0.0174532925);

	// translate point back to origin:
	boosterSprite.setPosition(boosterSprite.getPosition().x - shipSprite.getPosition().x, boosterSprite.getPosition().y - shipSprite.getPosition().y);

	// rotate point
	float xnew = boosterSprite.getPosition().x * c - boosterSprite.getPosition().y * s;
	float ynew = boosterSprite.getPosition().x * s + boosterSprite.getPosition().y * c;

	// translate point back:
	boosterSprite.setPosition(xnew + shipSprite.getPosition().x, ynew + shipSprite.getPosition().y);

	boosterSprite.setRotation(shipSprite.getRotation());

	for (int i = 0; i < thrusters.size(); i++)
	{
		thrusters.at(i)->turretSprite.setPosition(((shipSprite.getPosition().x - shipSprite.getTextureRect().width / 4) + thrusters.at(i)->position.x), ((shipSprite.getPosition().y - shipSprite.getTextureRect().height / 4) + thrusters.at(i)->position.y));
		//thrusters.at(i).y = ((shipSprite.getPosition().y - shipSprite.getTextureRect().height / 4) + thrusters.at(i)->position.y);

		float s1 = sin(shipSprite.getRotation() * 0.0174532925);
		float c1 = cos(shipSprite.getRotation() * 0.0174532925);

		// translate point back to origin:
		thrusters.at(i)->turretSprite.setPosition(sf::Vector2f(thrusters.at(i)->turretSprite.getPosition().x - shipSprite.getPosition().x, thrusters.at(i)->turretSprite.getPosition().y - shipSprite.getPosition().y));
		// rotate point
		float xnew1 = thrusters.at(i)->turretSprite.getPosition().x * c1 - thrusters.at(i)->turretSprite.getPosition().y * s1;
		float ynew1 = thrusters.at(i)->turretSprite.getPosition().x * s1 + thrusters.at(i)->turretSprite.getPosition().y * c1;

		// translate point back:
		thrusters.at(i)->turretSprite.setPosition(sf::Vector2f(xnew1 + shipSprite.getPosition().x, ynew1 + shipSprite.getPosition().y));

		if (thrusters.at(i)->ori == "front")
		{
			thrusters.at(i)->turretSprite.setRotation(shipSprite.getRotation());
		}
		else if (thrusters.at(i)->ori == "topleft" || thrusters.at(i)->ori == "botleft")
		{
			thrusters.at(i)->turretSprite.setRotation(shipSprite.getRotation() - 90);
		}
		else if (thrusters.at(i)->ori == "topright" || thrusters.at(i)->ori == "botright")
		{
			thrusters.at(i)->turretSprite.setRotation(shipSprite.getRotation() + 90);
		}
	}

	for (int i = 0; i < thrusters.size(); i++)
	{
		thrusters.at(i)->active = false;
	}

	if (type == "player" && health > 0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			shipBody->ApplyAngularImpulse(-5, false);
			//shipSprite.setRotation(shipSprite.getRotation() - 0.002);
			for (int i = 0; i < thrusters.size(); i++)
			{
				if (thrusters.at(i)->ori == "topright" || thrusters.at(i)->ori == "botleft")
				{
					thrusters.at(i)->active = true;
				}
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			shipBody->ApplyAngularImpulse(5, false);
			//shipSprite.setRotation(shipSprite.getRotation() + 0.002);
			for (int i = 0; i < thrusters.size(); i++)
			{
				if (thrusters.at(i)->ori == "topleft" || thrusters.at(i)->ori == "botright")
				{
					thrusters.at(i)->active = true;
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			shipBody->ApplyLinearImpulse(b2Vec2(velocity2.x, velocity2.y), shipBody->GetWorldCenter(), false);
			for (int i = 0; i < thrusters.size(); i++)
			{
				if (thrusters.at(i)->ori == "topleft" || thrusters.at(i)->ori == "botleft")
				{
					thrusters.at(i)->active = true;
				}
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			shipBody->ApplyLinearImpulse(b2Vec2(-velocity2.x, -velocity2.y), shipBody->GetWorldCenter(), false);
			for (int i = 0; i < thrusters.size(); i++)
			{
				if (thrusters.at(i)->ori == "topright" || thrusters.at(i)->ori == "botright")
				{
					thrusters.at(i)->active = true;
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			shipBody->ApplyLinearImpulse(b2Vec2(velocity.x, velocity.y), shipBody->GetWorldCenter(), false);
			for (int i = 0; i < thrusters.size(); i++)
			{
				if (thrusters.at(i)->ori == "front")
				{
					thrusters.at(i)->active = true;
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			shipBody->ApplyLinearImpulse(b2Vec2(-velocity.x, -velocity.y), shipBody->GetWorldCenter(), false);
			if (speed < 1)
			{
				speed += 0.01f;
			}
		}
		else
		{
			if (speed > 0.01f)
			{
				speed -= 0.01f;
			}
			//boosterSprite.setColor(sf::Color(255, 255, 255, 0));
		}
	}
	else
	{

	}
	
	if (type == "enemy" && health > 0)
	{

	}
	else if (type == "enemy" && health < 0)
	{
		destructionTimer--;
		if (destructionTimer > 0)
		{
			if (delayTimer < 0)
			{
				float temp = rand() % 4 + 1;
				float tempX;
				float tempY;
				if (temp == 1)
				{
					tempX = shipSprite.getPosition().x + rand() % 100 + 1;
					tempY = shipSprite.getPosition().y + rand() % 100 + 1;
				}
				else if (temp == 2)
				{
					tempX = shipSprite.getPosition().x - rand() % 100 + 1;
					tempY = shipSprite.getPosition().y + rand() % 100 + 1;
				}
				else if (temp == 3)
				{
					tempX = shipSprite.getPosition().x + rand() % 100 + 1;
					tempY = shipSprite.getPosition().y - rand() % 100 + 1;
				}
				else if (temp == 4)
				{
					tempX = shipSprite.getPosition().x - rand() % 100 + 1;
					tempY = shipSprite.getPosition().y - rand() % 100 + 1;
				}

				aniMan->CreateAnimation(sf::Vector2f(tempX, tempY), 4, 0);

				delay--;

				delayTimer = delay;
			}

			delayTimer--;
		}
		else
		{
			destroyed = true;
		}
	}

	//speed = sqrt((shipBody->GetLinearVelocity().x * shipBody->GetLinearVelocity().x) + (shipBody->GetLinearVelocity().y * shipBody->GetLinearVelocity().y));

	boosterSprite.setScale(sf::Vector2f(0.5f, speed / 2));

	velocity.x = cos((shipSprite.getRotation() + 90) * 0.0174532925);
	velocity.y = sin((shipSprite.getRotation() + 90) * 0.0174532925);

	velocity2.x = cos((shipSprite.getRotation()) * 0.0174532925);
	velocity2.y = sin((shipSprite.getRotation()) * 0.0174532925);

	shipSprite.setPosition(shipBody->GetPosition().x * SCALE, shipBody->GetPosition().y * SCALE);

	shipSprite.setRotation(shipBody->GetAngle() * (180.0f / b2_pi));

	for (int i = 0; i < turrets.size(); i++)
	{
		turrets.at(i)->Update();
	}

}

void Ship::Draw(sf::RenderWindow & window)
{
	window.draw(boosterSprite);
	window.draw(shipSprite);
	for (int i = 0; i < turrets.size(); i++)
	{
		turrets.at(i)->Draw(window);
	}
	for (int i = 0; i < thrusters.size(); i++)
	{
		thrusters.at(i)->Update();
		thrusters.at(i)->Draw(window);
	}
}

float Ship::to_positive_angle(float angle)
{
	angle = fmod(angle, 360);
	while (angle < 0) {
		angle += 360.0;
	}

	return angle;
}

sf::Sprite Ship::getSprite()
{
	return shipSprite;
}

float Ship::getHealth()
{
	return health;
}

void Ship::setHealth(float h)
{
	health = h;
}

b2Body* Ship::getBody()
{
	return shipBody;
}

void Ship::CreateBody()
{
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(shipSprite.getPosition().x / SCALE, shipSprite.getPosition().y / SCALE);
	BodyDef.type = b2_dynamicBody;
	BodyDef.userData = this; 
	b2Body* Body = world->CreateBody(&BodyDef);
	Body->SetFixedRotation(false);
	Body->SetSleepingAllowed(false);
	Body->SetGravityScale(3.0f);
	Body->SetLinearDamping(1);
	Body->SetAngularDamping(1.0f);

	b2PolygonShape Shape;
	Shape.SetAsBox(((shipSprite.getTextureRect().width * shipSprite.getScale().x) / 2) / SCALE, ((shipSprite.getTextureRect().height * shipSprite.getScale().x) / 2) / SCALE);
	Shape.SetAsBox((200 / 2) / SCALE, (300 / 2) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 1.0f;
	FixtureDef.friction = 0.7f;
	FixtureDef.shape = &Shape;
	if (type == "player")
	{
		FixtureDef.userData = "player";
	}
	else if (type == "enemy")
	{
		FixtureDef.userData = "enemy";
	}
	Body->CreateFixture(&FixtureDef);

	shipBody = Body;
}


