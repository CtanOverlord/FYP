#include "Ship.h"
#include "Turret.h"

static const float SCALE = 30.f;

Ship::Ship()
{

}

Ship::Ship(b2World& World, sf::Vector2f position, string t, sf::RenderWindow & window)
{
	if (!shipTexture.loadFromFile("Ship3.png"))
	{
		// error...
	}

	missileStep = 0;

	fireCount = 7;

	missileFiring = false;

	shield = false;

	Window = &window;

	destructionTimer = 240;

	delayTimer = 0;

	delay = 19; // or 17

	health = 1000;

	fuel = 1000;

	soundTimer = 0;

	onlyOnce = false;

	shipTexture.setSmooth(true);

	shipSprite.setTexture(shipTexture);

	shipSprite.setScale(sf::Vector2f(0.5f, 0.5f));

	shipSprite.setPosition(sf::Vector2f(position.x, position.y));

	shipSprite.setOrigin(sf::Vector2f(200, 300));

	destroyed = false;

	if (!bayTexture.loadFromFile("bayLights.png"))
	{
		// error...
	}
	
	bayTexture.setSmooth(true);

	baySprite.setTexture(bayTexture);

	baySprite.setScale(sf::Vector2f(0.5f, 0.5f));

	baySprite.setPosition(sf::Vector2f(position.x, position.y));

	baySprite.setOrigin(sf::Vector2f(200, 300));

	baySprite.setColor(sf::Color(255, 255, 255, 0));

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

	if (!shieldTexture.loadFromFile("shipShield4.png"))
	{
		// error...
	}

	shieldTexture.setSmooth(true);

	shieldSprite.setTexture(shieldTexture);

	shieldSprite.setScale(sf::Vector2f(0.55f, 0.55f));

	//shieldSprite.setScale(sf::Vector2f(0.5f, 0.5f));

	shieldSprite.setPosition(sf::Vector2f(100, 290));

	shieldSprite.setOrigin(sf::Vector2f(shieldSprite.getTextureRect().width / 2, (shieldSprite.getTextureRect().height / 2) - 25));

	shieldSprite.setColor(sf::Color(255, 255, 255, 0));

	velocity = sf::Vector2f(0, 0);

	world = &World;

	speed = 0.010f;

	CreateBody();

	// left
	missilePoints.push_back(new sf::Vector2f(31 / 2, 150 / 2));
	missilePoints.push_back(new sf::Vector2f(31 / 2, 203 / 2));
	missilePoints.push_back(new sf::Vector2f(31 / 2, 256 / 2));
	missilePoints.push_back(new sf::Vector2f(31 / 2, 309 / 2));
	missilePoints.push_back(new sf::Vector2f(31 / 2, 362 / 2));
	missilePoints.push_back(new sf::Vector2f(31 / 2, 415 / 2));
	missilePoints.push_back(new sf::Vector2f(31 / 2, 468 / 2));
	missilePoints.push_back(new sf::Vector2f(31 / 2, 521 / 2));
	// right
	missilePoints.push_back(new sf::Vector2f(368 / 2, 150 / 2));
	missilePoints.push_back(new sf::Vector2f(368 / 2, 203 / 2));
	missilePoints.push_back(new sf::Vector2f(368 / 2, 256 / 2));
	missilePoints.push_back(new sf::Vector2f(368 / 2, 309 / 2));
	missilePoints.push_back(new sf::Vector2f(368 / 2, 362 / 2));
	missilePoints.push_back(new sf::Vector2f(368 / 2, 415 / 2));
	missilePoints.push_back(new sf::Vector2f(368 / 2, 468 / 2));
	missilePoints.push_back(new sf::Vector2f(368 / 2, 521 / 2));

	// left
	missilePointOrig.push_back(new sf::Vector2f(31 / 2, 150 / 2));
	missilePointOrig.push_back(new sf::Vector2f(31 / 2, 203 / 2));
	missilePointOrig.push_back(new sf::Vector2f(31 / 2, 256 / 2));
	missilePointOrig.push_back(new sf::Vector2f(31 / 2, 309 / 2));
	missilePointOrig.push_back(new sf::Vector2f(31 / 2, 362 / 2));
	missilePointOrig.push_back(new sf::Vector2f(31 / 2, 415 / 2));
	missilePointOrig.push_back(new sf::Vector2f(31 / 2, 468 / 2));
	missilePointOrig.push_back(new sf::Vector2f(31 / 2, 521 / 2));
	// right
	missilePointOrig.push_back(new sf::Vector2f(368 / 2, 150 / 2));
	missilePointOrig.push_back(new sf::Vector2f(368 / 2, 203 / 2));
	missilePointOrig.push_back(new sf::Vector2f(368 / 2, 256 / 2));
	missilePointOrig.push_back(new sf::Vector2f(368 / 2, 309 / 2));
	missilePointOrig.push_back(new sf::Vector2f(368 / 2, 362 / 2));
	missilePointOrig.push_back(new sf::Vector2f(368 / 2, 415 / 2));
	missilePointOrig.push_back(new sf::Vector2f(368 / 2, 468 / 2));
	missilePointOrig.push_back(new sf::Vector2f(368 / 2, 521 / 2));

	wreckPoint.push_back(new sf::Vector2f(51, 91));
	wreckPoint.push_back(new sf::Vector2f(55, 229));
	wreckPoint.push_back(new sf::Vector2f(148, 91));
	wreckPoint.push_back(new sf::Vector2f(145, 223));

	wreckPointOrig.push_back(new sf::Vector2f(51, 91));
	wreckPointOrig.push_back(new sf::Vector2f(55, 229));
	wreckPointOrig.push_back(new sf::Vector2f(148, 91));
	wreckPointOrig.push_back(new sf::Vector2f(145, 223));

	TurretManager::GetInstance()->CreateTurret(new Turret(sf::Vector2f(75, 80), *this, type, "Plasma", *Window, *world));
	TurretManager::GetInstance()->CreateTurret(new Turret(sf::Vector2f(124, 80), *this, type, "Plasma", *Window, *world));
	TurretManager::GetInstance()->CreateTurret(new Turret(sf::Vector2f(75, 127), *this, type, "Plasma", *Window, *world));
	TurretManager::GetInstance()->CreateTurret(new Turret(sf::Vector2f(124, 127), *this, type, "Plasma", *Window, *world));
	TurretManager::GetInstance()->CreateTurret(new Turret(sf::Vector2f(75, 175), *this, type, "Plasma", *Window, *world));
	TurretManager::GetInstance()->CreateTurret(new Turret(sf::Vector2f(124, 175), *this, type, "Plasma", *Window, *world));

	//turrets.push_back(new Turret(sf::Vector2f(75, 80), *this, type, "Plasma", *Window, *world));
	//turrets.push_back(new Turret(sf::Vector2f(124, 80), *this, type, "Plasma", *Window, *world));
	//turrets.push_back(new Turret(sf::Vector2f(75, 127), *this, type, "Plasma", *Window, *world));
	//turrets.push_back(new Turret(sf::Vector2f(124, 127), *this, type, "Plasma", *Window, *world));
	//turrets.push_back(new Turret(sf::Vector2f(75, 175), *this, type, "Plasma", *Window, *world));
	//turrets.push_back(new Turret(sf::Vector2f(124, 175), *this, type, "Plasma", *Window, *world));

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
	if (fuel < 1000)
	{
		fuel += 1.0f;
	}

	shieldSprite.setPosition(shipSprite.getPosition());
	
	shieldSprite.setRotation(shipSprite.getRotation());
	
	baySprite.setPosition(shipSprite.getPosition());
	
	baySprite.setRotation(shipSprite.getRotation());

	updateBoosterPoints();

	for (int i = 0; i < thrusters.size(); i++)
	{
		thrusters.at(i)->active = false;
	}

	if (type == "player" && health > 0)
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			if (shieldTimer < 0 && shieldDuration < 0)
			{
				shield = true;
				shieldDuration = 600;
				shieldTimer = 480;
				SoundManager::GetInstance()->ShieldsOn();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			if (missileTimer < 0 && missileFiring == false)
			{
				missileFiring = true;

				sf::Vector2i mousePos;
				mousePos = sf::Mouse::getPosition(*Window);

				worldMousePos = Window->mapPixelToCoords(mousePos);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			updateThrusterPoints();
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
			updateThrusterPoints();
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
			updateThrusterPoints();
			shipBody->ApplyLinearImpulse(b2Vec2(velocity2.x / 2, velocity2.y / 2), shipBody->GetWorldCenter(), false);
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
			updateThrusterPoints();
			shipBody->ApplyLinearImpulse(b2Vec2(-velocity2.x / 2, -velocity2.y / 2), shipBody->GetWorldCenter(), false);
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
			updateThrusterPoints();
			shipBody->ApplyLinearImpulse(b2Vec2(velocity.x / 2, velocity.y / 2), shipBody->GetWorldCenter(), false);
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
		if (onlyOnce == false)
		{
			SoundManager::GetInstance()->CreateSound(shipSprite.getPosition(), 4);
			onlyOnce = true;
		}
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

				AnimationManager::GetInstance()->CreateAnimation(sf::Vector2f(tempX, tempY), 4, 0);

				if (soundTimer == 2)
				{
					SoundManager::GetInstance()->CreateSound(sf::Vector2f(tempX, tempY), 3);
					soundTimer = 0;
				}

				soundTimer++;

				delay--;

				delayTimer = delay;
			}

			delayTimer--;
		}
		else
		{
			destroyed = true;
			updateWreckPoints();
		}
	}

	//missileTimer--;

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
	for (int i = 0; i < thrusters.size(); i++)
	{
		thrusters.at(i)->Update();
	}

	if (shield == true)
	{
		shieldDuration--;

		if (shieldSprite.getColor().a < 255)
		{
			shieldSprite.setColor(sf::Color(255, 255, 255, shieldSprite.getColor().a + 1));
		}
		if (shieldDuration < 0)
		{
			shieldTimer = 480;
			shield = false;
			SoundManager::GetInstance()->ShieldsOff();
		}
	}
	else if (shield == false)
	{
		shieldTimer--;
		if (shieldSprite.getColor().a > 2)
		{
			shieldSprite.setColor(sf::Color(255, 255, 255, shieldSprite.getColor().a - 2));
		}
	}

	if (missileFiring == true)
	{
		if (baySprite.getColor().a < 255)
		{
			float trans = baySprite.getColor().a + 10;
			if (trans > 255)
			{
				trans = 255;
			}
			baySprite.setColor(sf::Color(255, 255, 255, trans));
		}
	}
	else if (missileFiring == false)
	{
		float trans = baySprite.getColor().a - 10;
		if (trans < 0)
		{
			trans = 0;
		}
		baySprite.setColor(sf::Color(255, 255, 255, trans));
	}

	if (missileFiring == true)
	{
		if (fireCount > -1)
		{
			if (missileStep == 10)
			{
				updateMissilePoints();

				ProjectileManager::GetInstance()->CreateMissile(*missilePoints.at(fireCount), worldMousePos, shipSprite.getRotation() - 90, false);

				ProjectileManager::GetInstance()->CreateMissile(*missilePoints.at(fireCount + 8), worldMousePos, shipSprite.getRotation() + 90, false);

				SoundManager::GetInstance()->CreateSound(*missilePoints.at(fireCount + 8), 1);

				fireCount--;

				missileStep = 0;
			}
		}
		else if (fireCount > -41)
		{
			fireCount--;
		}


		missileStep++;

		if (fireCount == -40)
		{
			missileTimer = 480;
			missileFiring = false;
			fireCount = 7;
			missileStep = 0;
		}
	}
	else
	{
		missileTimer--;
	}
}

void Ship::Draw(sf::RenderWindow & window)
{
	for (int i = 0; i < thrusters.size(); i++)
	{
		thrusters.at(i)->Draw(window);
	}
	
	window.draw(boosterSprite);
	window.draw(shipSprite);

	window.draw(baySprite);

	for (int i = 0; i < turrets.size(); i++)
	{
		turrets.at(i)->Draw(window);
	}
}

void Ship::Draw2(sf::RenderWindow & window)
{
	if (shipType == "Dreadnought")
	{
		window.draw(shieldSprite);
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

float Ship::distance(sf::Vector2f d1, sf::Vector2f d2)
{
	float d = sqrt(((d1.x - d2.x) * (d1.x - d2.x)) + ((d1.y - d2.y) * (d1.y - d2.y)));

	return d;
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

float Ship::getFuel()
{
	return fuel;
}

void Ship::setFuel(float f)
{
	fuel = f;
}

b2Body* Ship::getBody()
{
	return shipBody;
}

sf::Vector2f Ship::normalize(sf::Vector2f source)
{
	float length = sqrt((source.x * source.x) + (source.y * source.y));
	if (length != 0)
		return sf::Vector2f(source.x / length, source.y / length);
	else
		return source;
}

float Ship::degreeToRadian(float angle)
{
	float pi = 3.14159265358979323846;
	return  pi * angle / 180.0;
}

float Ship::radiansToDegrees(float angle)
{
	float pi = 3.14159265358979323846;
	return angle * (180.0 / pi);
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
	Shape.SetAsBox((185 / 2) / SCALE, (292 / 2) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 1.0f;
	FixtureDef.friction = 0.7f;
	FixtureDef.shape = &Shape;

	if (type == "player")
	{
		FixtureDef.filter.categoryBits = 0x0001;
		FixtureDef.filter.maskBits = 0x0010 | 0x0002 | 0x0004 | 0x0008;
		FixtureDef.userData = "player";
	}
	else if (type == "enemy")
	{
		FixtureDef.filter.categoryBits = 0x0002;
		FixtureDef.filter.maskBits = 0x0010 | 0x0001 | 0x0004 | 0x0008;
		FixtureDef.userData = "enemy";
	}
	Body->CreateFixture(&FixtureDef);

	shipBody = Body;
}

void Ship::updateMissilePoints()
{
	for (int i = 0; i < missilePoints.size(); i++)
	{
		missilePoints.at(i) = new sf::Vector2f(((shipSprite.getPosition().x - shipSprite.getTextureRect().width / 4) + missilePointOrig.at(i)->x), ((shipSprite.getPosition().y - shipSprite.getTextureRect().height / 4) + missilePointOrig.at(i)->y));
		//thrusters.at(i).y = ((shipSprite.getPosition().y - shipSprite.getTextureRect().height / 4) + thrusters.at(i)->position.y);

		float s1 = sin(shipSprite.getRotation() * 0.0174532925);
		float c1 = cos(shipSprite.getRotation() * 0.0174532925);

		// translate point back to origin:
		missilePoints.at(i) = new sf::Vector2f(missilePoints.at(i)->x - shipSprite.getPosition().x, missilePoints.at(i)->y - shipSprite.getPosition().y);
		// rotate point
		float xnew1 = missilePoints.at(i)->x * c1 - missilePoints.at(i)->y * s1;
		float ynew1 = missilePoints.at(i)->x * s1 + missilePoints.at(i)->y * c1;

		// translate point back:
		missilePoints.at(i) = new sf::Vector2f(xnew1 + shipSprite.getPosition().x, ynew1 + shipSprite.getPosition().y);
	}
}

void Ship::updateThrusterPoints()
{
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
}

void Ship::updateWreckPoints()
{
	for (int i = 0; i < wreckPoint.size(); i++)
	{
		wreckPoint.at(i) = new sf::Vector2f(((shipSprite.getPosition().x - shipSprite.getTextureRect().width / 4) + wreckPointOrig.at(i)->x), ((shipSprite.getPosition().y - shipSprite.getTextureRect().height / 4) + wreckPointOrig.at(i)->y));
		//thrusters.at(i).y = ((shipSprite.getPosition().y - shipSprite.getTextureRect().height / 4) + thrusters.at(i)->position.y);

		float s1 = sin(shipSprite.getRotation() * 0.0174532925);
		float c1 = cos(shipSprite.getRotation() * 0.0174532925);

		// translate point back to origin:
		wreckPoint.at(i) = new sf::Vector2f(wreckPoint.at(i)->x - shipSprite.getPosition().x, wreckPoint.at(i)->y - shipSprite.getPosition().y);
		// rotate point
		float xnew1 = wreckPoint.at(i)->x * c1 - wreckPoint.at(i)->y * s1;
		float ynew1 = wreckPoint.at(i)->x * s1 + wreckPoint.at(i)->y * c1;

		// translate point back:
		wreckPoint.at(i) = new sf::Vector2f(xnew1 + shipSprite.getPosition().x, ynew1 + shipSprite.getPosition().y);
	}
}

void Ship::updateBoosterPoints()
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
}

void Ship::DeleteAll()
{
	for (int i = 0; i < thrusters.size(); i++)
	{
		delete thrusters.at(i);
	}
	for (int i = 0; i < wreckPointOrig.size(); i++)
	{
		delete wreckPointOrig.at(i);
	}
	for (int i = 0; i < wreckPoint.size(); i++)
	{
		delete wreckPoint.at(i);
	}
	for (int i = 0; i < missilePoints.size(); i++)
	{
		delete missilePoints.at(i);
	}
	for (int i = 0; i < missilePointOrig.size(); i++)
	{
		delete missilePointOrig.at(i);
	}
	for (int i = 0; i < turrets.size(); i++)
	{
		delete turrets.at(i);
	}
}


