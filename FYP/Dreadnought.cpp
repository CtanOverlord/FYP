#include "Dreadnought.h"
#include "Turret.h"

static const float SCALE = 30.f;

Dreadnought::Dreadnought()
{

}

Dreadnought::Dreadnought(b2World& World, sf::Vector2f position, string t, sf::RenderWindow & window)
{
	if (t == "player")
	{
		if (!shipTexture.loadFromFile("Ship3.png"))
		{
			// error...
		}
	}
	else if (t == "enemy")
	{
		if (!shipTexture.loadFromFile("ShipEnemy.png"))
		{
			// error...
		}
	}
	else if (t == "ally")
	{
		if (!shipTexture.loadFromFile("ShipAlly.png"))
		{
			// error...
		}
	}

	missileStep = 0;

	shipType = "Dreadnought";

	fireCount = 7;

	missileFiring = false;

	missileTimer = 0;

	shield = false;

	Window = &window;

	destructionTimer = 240;

	delayTimer = 0;

	delay = 19; // or 17

	health = 1000;

	maxHealth = 1000;

	fuel = 1000;

	maxFuel = 1000;

	fuelTimer = 0;

	noFuel = false;

	soundTimer = 0;

	onlyOnce = false;

	shipTexture.setSmooth(true);

	shipSprite.setTexture(shipTexture);

	shipSprite.setScale(sf::Vector2f(0.5f, 0.5f));

	shipSprite.setPosition(sf::Vector2f(position.x, position.y));

	shipSprite.setOrigin(sf::Vector2f(200, 300));

	if (t == "enemy")
	{
		shipSprite.setRotation(180);
	}

	destroyed = false;

	rayCollision = false;

	followPoint = sf::Vector2f(0, 0);

	currentTState = TurnState::FOLLOW;
	currentMState = MoveState::FORWARD;
	currentFState = FireState::NONE3;

	chooseTimer = 0;

	firing = false;

	targetPos = sf::Vector2f(0, -10000);

	if (!healthBoxTexture.loadFromFile("healthBoxShip.png"))
	{
		// error...
	}

	healthBoxTexture.setSmooth(true);

	healthBox.setTexture(healthBoxTexture);

	healthBox.setScale(sf::Vector2f(0.2f, 0.2f));

	healthBox.setPosition(sf::Vector2f(position.x, position.y));

	healthBox.setOrigin(sf::Vector2f(300, 100));

	healthBox.setColor(sf::Color(255, 255, 255, 255));

	if (!healthBarTexture.loadFromFile("healthBarShip.png"))
	{
		// error...
	}

	healthBarTexture.setSmooth(true);

	healthBar.setTexture(healthBarTexture);

	healthBar.setScale(sf::Vector2f(0.2f, 0.2f));

	healthBar.setPosition(sf::Vector2f(position.x, position.y));

	healthBar.setOrigin(sf::Vector2f(0, 29.5));

	healthBar.setColor(sf::Color(255, 255, 255, 255));

	if (!powerTexture.loadFromFile("powerBarShip.png"))
	{
		// error...
	}

	powerTexture.setSmooth(true);

	power.setTexture(powerTexture);

	power.setScale(sf::Vector2f(0.2f, 0.2f));

	power.setPosition(sf::Vector2f(position.x, position.y));

	power.setOrigin(sf::Vector2f(0, 29.5));

	power.setColor(sf::Color(255, 255, 255, 255));

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

	rayCallBackF1 = new RayCastCallBackCustom();
	rayCallBackF2 = new RayCastCallBackCustom();
	rayCallBackL1 = new RayCastCallBackCustom();
	rayCallBackL2 = new RayCastCallBackCustom();
	rayCallBackR1 = new RayCastCallBackCustom();
	rayCallBackR2 = new RayCastCallBackCustom();

	CreateBody();

	if (type == "enemy")
	{
		shipBody->SetTransform(shipBody->GetPosition(), degreeToRadian(180));
	}

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

	rayPoints.push_back(new sf::Vector2f(10, 50));
	rayPointOrig.push_back(new sf::Vector2f(10, 50));
	rayPoints.push_back(new sf::Vector2f(190, 50));
	rayPointOrig.push_back(new sf::Vector2f(190, 50));
	rayPoints.push_back(new sf::Vector2f(10, 50));
	rayPointOrig.push_back(new sf::Vector2f(10, 50));
	rayPoints.push_back(new sf::Vector2f(190, 50));
	rayPointOrig.push_back(new sf::Vector2f(190, 50));
	rayPoints.push_back(new sf::Vector2f(10, 50));
	rayPointOrig.push_back(new sf::Vector2f(10, 50));
	rayPoints.push_back(new sf::Vector2f(190, 50));
	rayPointOrig.push_back(new sf::Vector2f(190, 50));

	// Left (0', 45', 90')
	rayEndPoints.push_back(new sf::Vector2f(10, 30));
	rayEndPointOrig.push_back(new sf::Vector2f(10, 30));
	rayEndPoints.push_back(new sf::Vector2f(-4, 36));
	rayEndPointOrig.push_back(new sf::Vector2f(-4, 36));
	rayEndPoints.push_back(new sf::Vector2f(-10, 50));
	rayEndPointOrig.push_back(new sf::Vector2f(-10, 50));

	// Right (0', 45', 90')
	rayEndPoints.push_back(new sf::Vector2f(190, 30));
	rayEndPointOrig.push_back(new sf::Vector2f(190, 30));
	rayEndPoints.push_back(new sf::Vector2f(204, 36));
	rayEndPointOrig.push_back(new sf::Vector2f(204, 36));
	rayEndPoints.push_back(new sf::Vector2f(210, 50));
	rayEndPointOrig.push_back(new sf::Vector2f(210, 50));

	turrets.push_back(new Turret(sf::Vector2f(75, 80), *this, type, "Plasma", *Window, *world));
	turrets.push_back(new Turret(sf::Vector2f(124, 80), *this, type, "Plasma", *Window, *world));
	turrets.push_back(new Turret(sf::Vector2f(75, 127), *this, type, "Plasma", *Window, *world));
	turrets.push_back(new Turret(sf::Vector2f(124, 127), *this, type, "Plasma", *Window, *world));
	turrets.push_back(new Turret(sf::Vector2f(75, 175), *this, type, "Plasma", *Window, *world));
	turrets.push_back(new Turret(sf::Vector2f(124, 175), *this, type, "Plasma", *Window, *world));

	//turrets.push_back(new Turret(sf::Vector2f(75, 80), *this, type, "Laser", *Window, *world));
	//turrets.push_back(new Turret(sf::Vector2f(124, 80), *this, type, "Laser", *Window, *world));
	//turrets.push_back(new Turret(sf::Vector2f(75, 127), *this, type, "Laser", *Window, *world));
	//turrets.push_back(new Turret(sf::Vector2f(124, 127), *this, type, "Laser", *Window, *world));
	//turrets.push_back(new Turret(sf::Vector2f(75, 175), *this, type, "Laser", *Window, *world));
	//turrets.push_back(new Turret(sf::Vector2f(124, 175), *this, type, "Laser", *Window, *world));

	TurretManager::GetInstance()->CreateTurret(turrets.at(0));
	TurretManager::GetInstance()->CreateTurret(turrets.at(1));
	TurretManager::GetInstance()->CreateTurret(turrets.at(2));
	TurretManager::GetInstance()->CreateTurret(turrets.at(3));
	TurretManager::GetInstance()->CreateTurret(turrets.at(4));
	TurretManager::GetInstance()->CreateTurret(turrets.at(5));

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
}

void Dreadnought::Update()
{
	if (type == "player")
	{
		playerUpdate();
	}
	else if (type == "enemy" || type == "ally")
	{
		enemyUpdate();
	}
}

void Dreadnought::playerUpdate()
{
	if (fuel < 1000 && noFuel == false)
	{
		fuel += 1.0f;
	}

	if (fuel <= 2)
	{
		noFuel = true;
		fuel = 0;
	}

	if (noFuel == true)
	{
		fuelTimer++;
		if (fuelTimer >= 180)
		{
			fuel += 10.0f;
			if (fuel > 1000)
			{
				fuelTimer = 0;
				noFuel = false;
			}
		}
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

			missileTimer = 480;

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
		updateThrusterPoints();
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
		updateThrusterPoints();
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
		shipBody->ApplyLinearImpulse(b2Vec2(-velocity.x * 1.5, -velocity.y * 1.5), shipBody->GetWorldCenter(), false);
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

	if (health < 0)
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
			for (int i = 0; i < wreckPoint.size(); i++)
			{
				WreckManager::GetInstance()->CreateWreck(sf::Vector2f(wreckPoint.at(i)->x, wreckPoint.at(i)->y), shipSprite.getRotation(), i);
			}
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

	/*for (int i = 0; i < turrets.size(); i++)
	{
	turrets.at(i)->Update();
	}*/
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
		if (missileTimer > -1)
		{
			missileTimer--;
		}
	}
}

void Dreadnought::enemyUpdate()
{
	healthBox.setPosition(shipSprite.getPosition().x, shipSprite.getPosition().y - 170);
	healthBar.setPosition(shipSprite.getPosition().x - 51, shipSprite.getPosition().y - 178);
	power.setPosition(shipSprite.getPosition().x - 51, shipSprite.getPosition().y - 162);

	float scaleX = health / maxHealth;

	if (scaleX < 0)
	{
		scaleX = 0;
	}
	healthBar.setScale(scaleX / 5, 0.2f);

	scaleX = fuel / maxFuel;

	if (scaleX < 0)
	{
		scaleX = 0;
	}
	power.setScale(scaleX / 5, 0.2f);

	if (fuel < 1000 && noFuel == false)
	{
		fuel += 1.0f;
	}

	if (fuel <= 2)
	{
		noFuel = true;
		fuel = 0;
	}

	if (noFuel == true)
	{
		fuelTimer++;
		if (fuelTimer >= 180)
		{
			fuel += 10.0f;
			if (fuel > 1000)
			{
				fuelTimer = 0;
				noFuel = false;
			}
		}
	}

	if (chooseTimer > 120)
	{
		if (type == "enemy")
		{
			chooseNextAction();
		}
		else if(type == "ally")
		{
			chooseNextActionAlly();
		}
		chooseTimer = 0;
	}

	chooseTimer++;

	shieldSprite.setPosition(shipSprite.getPosition());

	shieldSprite.setRotation(shipSprite.getRotation());

	baySprite.setPosition(shipSprite.getPosition());

	baySprite.setRotation(shipSprite.getRotation());

	updateBoosterPoints();

	updateRayPoints();

	for (int i = 0; i < thrusters.size(); i++)
	{
		thrusters.at(i)->active = false;
	}

	rayCallBackF1->Reset();
	rayCallBackF2->Reset();
	rayCallBackL1->Reset();
	rayCallBackL2->Reset();
	rayCallBackR1->Reset();
	rayCallBackR2->Reset();

	b2Vec2 startPoint;
	startPoint.x = rayPoints.at(0)->x / SCALE;
	startPoint.y = rayPoints.at(0)->y / SCALE;

	b2Vec2 endPoint;

	//Front left
	endPoint.x = (rayPoints.at(0)->x + ((rayEndPoints.at(0)->x - rayPoints.at(0)->x) * 8)) / SCALE;
	endPoint.y = (rayPoints.at(0)->y + ((rayEndPoints.at(0)->y - rayPoints.at(0)->y) * 8)) / SCALE;

	world->RayCast(rayCallBackF1,startPoint, endPoint);

	//Front left 45'
	endPoint.x = (rayPoints.at(0)->x + ((rayEndPoints.at(1)->x - rayPoints.at(0)->x) * 5)) / SCALE;
	endPoint.y = (rayPoints.at(0)->y + ((rayEndPoints.at(1)->y - rayPoints.at(0)->y) * 5)) / SCALE;

	world->RayCast(rayCallBackL1, startPoint, endPoint);

	//Front left 90'
	endPoint.x = (rayPoints.at(0)->x + ((rayEndPoints.at(2)->x - rayPoints.at(0)->x) * 5)) / SCALE;
	endPoint.y = (rayPoints.at(0)->y + ((rayEndPoints.at(2)->y - rayPoints.at(0)->y) * 5)) / SCALE;

	world->RayCast(rayCallBackL2, startPoint, endPoint);

	startPoint.x = rayPoints.at(1)->x / SCALE;
	startPoint.y = rayPoints.at(1)->y / SCALE;

	//Front right
	endPoint.x = (rayPoints.at(1)->x + ((rayEndPoints.at(3)->x - rayPoints.at(1)->x) * 8)) / SCALE;
	endPoint.y = (rayPoints.at(1)->y + ((rayEndPoints.at(3)->y - rayPoints.at(1)->y) * 8)) / SCALE;

	world->RayCast(rayCallBackF2, startPoint, endPoint);

	//Front right 45'
	endPoint.x = (rayPoints.at(1)->x + ((rayEndPoints.at(4)->x - rayPoints.at(1)->x) * 5)) / SCALE;
	endPoint.y = (rayPoints.at(1)->y + ((rayEndPoints.at(4)->y - rayPoints.at(1)->y) * 5)) / SCALE;

	world->RayCast(rayCallBackR1, startPoint, endPoint);

	//Front right90'
	endPoint.x = (rayPoints.at(1)->x + ((rayEndPoints.at(5)->x - rayPoints.at(1)->x) * 5)) / SCALE;
	endPoint.y = (rayPoints.at(1)->y + ((rayEndPoints.at(5)->y - rayPoints.at(1)->y) * 5)) / SCALE;

	world->RayCast(rayCallBackR2, startPoint, endPoint);

	bool hitF1 = false;
	bool hitF2 = false;
	bool hitL1 = false;
	bool hitL2 = false;
	bool hitR1 = false;
	bool hitR2 = false;

	if (rayCallBackF1->objectName == "bound" || rayCallBackF1->objectName == "enemy" || rayCallBackF1->objectName == "ally" || rayCallBackF1->objectName == "player" || rayCallBackF1->objectName == "cap")
	{
		hitF1 = true;
	}
	if (rayCallBackF2->objectName == "bound" || rayCallBackF2->objectName == "enemy" || rayCallBackF2->objectName == "ally" || rayCallBackF2->objectName == "player" || rayCallBackF2->objectName == "cap")
	{
		hitF2 = true;
	}
	if (rayCallBackL1->objectName == "bound" || rayCallBackL1->objectName == "enemy" || rayCallBackL1->objectName == "ally" || rayCallBackL1->objectName == "player" || rayCallBackL1->objectName == "cap")
	{
		hitL1 = true;
	}
	if (rayCallBackL2->objectName == "bound" || rayCallBackL2->objectName == "enemy" || rayCallBackL2->objectName == "ally" || rayCallBackL2->objectName == "player" || rayCallBackL2->objectName == "cap")
	{
		hitL2 = true;
	}
	if (rayCallBackR1->objectName == "bound" || rayCallBackR1->objectName == "enemy" || rayCallBackR1->objectName == "ally" || rayCallBackR1->objectName == "player" || rayCallBackR1->objectName == "cap")
	{
		hitR1 = true;
	}
	if (rayCallBackR2->objectName == "bound" || rayCallBackR2->objectName == "enemy" || rayCallBackR2->objectName == "ally" || rayCallBackR2->objectName == "player" || rayCallBackR2->objectName == "cap")
	{
		hitR2 = true;
	}

	if (hitF1 == true || hitF2 == true || hitL1 == true || hitL2 == true || hitR1 == true || hitR2 == true)
	{
		if (rayCollision == false)
		{
			rayCollision = true;
			previousTState = currentTState;
			previousMState = currentMState;
		}
	}
	else
	{
		if (rayCollision == true)
		{
			rayCollision = false;
			currentTState = previousTState;
			currentMState = previousMState;
		}
	}

	if (hitF1 == true && hitF2 == true)
	{
		currentMState = MoveState::BACKWARDS;
	}

	if (hitF1 == true || hitL1 == true || hitL2 == true)
	{
		currentTState = TurnState::RIGHT;
	}

	if (hitF2 == true || hitR1 == true || hitR2 == true)
	{
		currentTState = TurnState::LEFT;
	}

	switch (currentTState) {

	case(TurnState::LEFT) :
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
		break;
	case(TurnState::RIGHT) :
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
		break;
	case(TurnState::SLEFT) :
		updateThrusterPoints();
		shipBody->ApplyLinearImpulse(b2Vec2(-velocity2.x / 2, -velocity2.y / 2), shipBody->GetWorldCenter(), false);
		for (int i = 0; i < thrusters.size(); i++)
		{
			if (thrusters.at(i)->ori == "topright" || thrusters.at(i)->ori == "botright")
			{
				thrusters.at(i)->active = true;
			}
		}
		break;
	case(TurnState::SRIGHT) :
		updateThrusterPoints();
		shipBody->ApplyLinearImpulse(b2Vec2(velocity2.x / 2, velocity2.y / 2), shipBody->GetWorldCenter(), false);
		for (int i = 0; i < thrusters.size(); i++)
		{
			if (thrusters.at(i)->ori == "topleft" || thrusters.at(i)->ori == "botleft")
			{
				thrusters.at(i)->active = true;
			}
		}
		break;
	case(TurnState::FOLLOW) :
		if (currentTState == TurnState::FOLLOW)
		{
			//float distance = sqrt(((followPoint.x - shipSprite.getPosition().x) * (followPoint.x - shipSprite.getPosition().x)) + ((followPoint.y - shipSprite.getPosition().y) * (followPoint.y - shipSprite.getPosition().y)));

			if (distance(followPoint, shipSprite.getPosition()) < 300)
			{
				if (type == "enemy")
				{
					chooseNextAction();
				}
				else if (type == "ally")
				{
					chooseNextActionAlly();
				}
			}
			/*sf::Vector2i mousePos;
			mousePos = sf::Mouse::getPosition(*Window);

			sf::Vector2f rotPoint = Window->mapPixelToCoords(mousePos);*/

			sf::Vector2i mousePos;
			mousePos = sf::Mouse::getPosition(*Window);

			sf::Vector2f rotPoint = followPoint;

			float bodyAngle = shipBody->GetAngle();
			b2Vec2 toTarget;
			toTarget.x = rotPoint.x - shipBody->GetPosition().x * SCALE;
			toTarget.y = rotPoint.y - shipBody->GetPosition().y * SCALE;

			desiredAngle = atan2f(toTarget.x, -toTarget.y);

			float tempAngle = desiredAngle;

			tempAngle = radiansToDegrees(tempAngle);

			tempAngle = to_positive_angle(tempAngle);

			tempAngle = degreeToRadian(tempAngle);

			desiredAngle = tempAngle;

			float nextAngle = bodyAngle + shipBody->GetAngularVelocity() / 5.0;
			float totalRotation = desiredAngle - nextAngle;
			tempAngle = totalRotation;
			tempAngle = radiansToDegrees(tempAngle);
			if (tempAngle > 180)
			{
				tempAngle -= 360;
				//tempAngle = -tempAngle;
			}
			totalRotation = degreeToRadian(tempAngle);
			while (degreeToRadian(totalRotation < -180)) degreeToRadian(totalRotation += 360);
			while (degreeToRadian(totalRotation > 180)) degreeToRadian(totalRotation -= 360);
			float desiredAngularVelocity = totalRotation * 5;
			float change = degreeToRadian(1); //allow 1 degree rotation per time step
			desiredAngularVelocity = min(change, max(-change, desiredAngularVelocity));
			float impulse = shipBody->GetInertia() * desiredAngularVelocity;
			impulse = impulse / 2;

			shipBody->ApplyAngularImpulse(impulse, false);

			if (impulse < -0.1 && impulse > -3)
			{
				updateThrusterPoints();
				for (int i = 0; i < thrusters.size(); i++)
				{
					if (thrusters.at(i)->ori == "topright" || thrusters.at(i)->ori == "botleft")
					{
						thrusters.at(i)->active = true;
					}
				}
			}
			else if (impulse > 0.1 && impulse < 3)
			{
				updateThrusterPoints();
				for (int i = 0; i < thrusters.size(); i++)
				{
					if (thrusters.at(i)->ori == "topleft" || thrusters.at(i)->ori == "botright")
					{
						thrusters.at(i)->active = true;
					}
				}
			}
			else if (impulse == 0)
			{
				for (int i = 0; i < thrusters.size(); i++)
				{
					thrusters.at(i)->active = false;
				}
			}
		}
		break;
	case(TurnState::NONE) :
		if (type == "enemy")
		{
			chooseNextAction();
		}
		else if (type == "ally")
		{
			chooseNextActionAlly();
		}
		break;
	}

	switch (currentMState) {

	case(MoveState::FORWARD) :
		shipBody->ApplyLinearImpulse(b2Vec2(-velocity.x * 1.5f, -velocity.y * 1.5f), shipBody->GetWorldCenter(), false);
		if (speed < 1)
		{
			speed += 0.01f;
		}
		break;
	case(MoveState::BACKWARDS) :
		updateThrusterPoints();
		shipBody->ApplyLinearImpulse(b2Vec2(velocity.x, velocity.y), shipBody->GetWorldCenter(), false);
		for (int i = 0; i < thrusters.size(); i++)
		{
			if (thrusters.at(i)->ori == "front")
			{
				thrusters.at(i)->active = true;
			}
		}
		if (speed > 0.01f)
		{
			speed -= 0.01f;
		}
		break;
	case(MoveState::NONE2) :
		if (speed > 0.01f)
		{
			speed -= 0.01f;
		}
		break;
	}

	switch (currentFState) {

	case(FireState::FIRING) :
		firing = true;
		targetPos = targetShip->getSprite().getPosition();
		AbilityOne();
		AbilityTwo();
		break;
	case(FireState::NONE3) :
		firing = false;
		break;
	}

	if (health < 0)
	{
		currentTState = TurnState::NONE;
		currentMState = MoveState::NONE2;

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
			for (int i = 0; i < wreckPoint.size(); i++)
			{
				WreckManager::GetInstance()->CreateWreck(sf::Vector2f(wreckPoint.at(i)->x, wreckPoint.at(i)->y), shipSprite.getRotation(), i);
			}
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

	/*for (int i = 0; i < turrets.size(); i++)
	{
	turrets.at(i)->Update();
	}*/
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
			shieldTimer = 800;
			shield = false;
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

				if (type == "enemy")
				{
					ProjectileManager::GetInstance()->CreateMissile(*missilePoints.at(fireCount), worldMousePos, shipSprite.getRotation() - 90, true);

					ProjectileManager::GetInstance()->CreateMissile(*missilePoints.at(fireCount + 8), worldMousePos, shipSprite.getRotation() + 90, true);

					SoundManager::GetInstance()->CreateSound(*missilePoints.at(fireCount + 8), 1);
				}
				else
				{
					ProjectileManager::GetInstance()->CreateMissile(*missilePoints.at(fireCount), worldMousePos, shipSprite.getRotation() - 90, false);

					ProjectileManager::GetInstance()->CreateMissile(*missilePoints.at(fireCount + 8), worldMousePos, shipSprite.getRotation() + 90, false);

					SoundManager::GetInstance()->CreateSound(*missilePoints.at(fireCount + 8), 1);
				}

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
			missileTimer = 700;
			missileFiring = false;
			fireCount = 7;
			missileStep = 0;
		}
	}
	else
	{
		if (missileTimer > -1)
		{
			missileTimer--;
		}
	}
}

void Dreadnought::chooseNextAction()
{
	bool capturePointFree = false;
	bool enemyNearby = false;
	bool capturingPoint = false;
	float shortestDist = 999999999999;


	for (int i = 0; i < Level::GetInstance()->capPoints.size(); i++) //1
	{
		if (Level::GetInstance()->capPoints.at(i)->owner != "Red") //2
		{
			assert(Level::GetInstance()->capPoints.at(i)->owner == "Blue" || Level::GetInstance()->capPoints.at(i)->owner == "Nuetral");
			float dist = distance(shipSprite.getPosition(), Level::GetInstance()->capPoints.at(i)->getSprite().getPosition()); //3

			if ( dist < shortestDist) //4
			{
				assert(dist < shortestDist);
				targetCapPoint = Level::GetInstance()->capPoints.at(i); //5
				capturePointFree = true; //6
				shortestDist = dist;// 7
			}
		}
	} // 8

	if (shortestDist < 300) //9
	{
		assert(shortestDist < 300);
		capturingPoint = true; //10
		currentTState = NONE; //11
		currentMState = NONE2; //12
		capturePointFree = false; //13
	}
	else if (capturePointFree == true) //13
	{
		assert(capturePointFree == true);
		followPoint = targetCapPoint->getSprite().getPosition(); //14
		capturingPoint = false; //15
		currentTState = FOLLOW; //16
		currentMState = FORWARD; //17
	}
	else if (shortestDist == 999999999999) //18
	{
		assert(shortestDist == 999999999999);
		followPoint.x = (rand() % 4000) - 2000; //19
		followPoint.y = (rand() % 4000) - 2000; //20
		currentTState = FOLLOW; //21
		currentMState = FORWARD; //22
	}

	shortestDist = 99999999999;
	for (int i = 0; i < ShipManager::GetInstance()->ships.size(); i++) //5
	{
		if (ShipManager::GetInstance()->ships.at(i)->type == "player" || ShipManager::GetInstance()->ships.at(i)->type == "ally")
		{
			if ((ShipManager::GetInstance()->ships.at(i)->shipType == "Sniper" && ShipManager::GetInstance()->ships.at(i)->shield == true))
			{

			}
			else
			{
				float dist = distance(ShipManager::GetInstance()->ships.at(i)->getSprite().getPosition(), shipSprite.getPosition());
				if (dist < 800)
				{
					if (dist < shortestDist)
					{
						shortestDist = dist;
						targetShip = ShipManager::GetInstance()->ships.at(i);
						enemyNearby = true;
					}
				}
			}
		}
	}

	if (enemyNearby == true) //6
	{
		currentFState = FIRING;
		firing = true;
		targetPos = targetShip->getSprite().getPosition();
	}
	else //7
	{
		currentFState = NONE3;
		firing = false;
		targetPos = sf::Vector2f(0, -10000);
	}
}

void Dreadnought::chooseNextActionAlly()
{
	bool capturePointFree = false;
	bool enemyNearby = false;
	bool capturingPoint = false;
	float shortestDist = 999999999999;

	for (int i = 0; i < Level::GetInstance()->capPoints.size(); i++)
	{
		if (Level::GetInstance()->capPoints.at(i)->owner != "Blue")
		{
			float dist = distance(shipSprite.getPosition(), Level::GetInstance()->capPoints.at(i)->getSprite().getPosition());

			if (dist < shortestDist)
			{
				targetCapPoint = Level::GetInstance()->capPoints.at(i);
				capturePointFree = true;
				shortestDist = dist;
			}
		}
	}

	if (shortestDist < 300)
	{
		capturingPoint = true;
		currentTState = NONE;
		currentMState = NONE2;
		capturePointFree = false;
	}
	else if (capturePointFree == true)
	{
		followPoint = targetCapPoint->getSprite().getPosition();
		capturingPoint = false;
		currentTState = FOLLOW;
		currentMState = FORWARD;
	}
	else if (shortestDist == 999999999999)
	{
		followPoint.x = (rand() % 4000) - 2000;
		followPoint.y = (rand() % 4000) - 2000;
		currentTState = FOLLOW;
		currentMState = FORWARD;
	}

	shortestDist = 99999999999;
	for (int i = 0; i < ShipManager::GetInstance()->ships.size(); i++)
	{
		if (ShipManager::GetInstance()->ships.at(i)->type == "enemy")
		{
			if ((ShipManager::GetInstance()->ships.at(i)->shipType == "Sniper" && ShipManager::GetInstance()->ships.at(i)->shield == true))
			{

			}
			else
			{
				float dist = distance(ShipManager::GetInstance()->ships.at(i)->getSprite().getPosition(), shipSprite.getPosition());
				if (dist < 800)
				{
					if (dist < shortestDist)
					{
						shortestDist = dist;
						targetShip = ShipManager::GetInstance()->ships.at(i);
						enemyNearby = true;
					}
				}
			}
		}
	}

	if (enemyNearby == true)
	{
		currentFState = FIRING;
		firing = true;
		targetPos = targetShip->getSprite().getPosition();
	}
	else
	{
		currentFState = NONE3;
		firing = false;
		targetPos = sf::Vector2f(0, -10000);
	}
}

void Dreadnought::AbilityOne()
{
	if (missileTimer < 0 && missileFiring == false)
	{
		missileFiring = true;

		missileTimer = 700;

		worldMousePos = targetPos;
	}
}

void Dreadnought::AbilityTwo()
{
	if (shieldTimer < 0 && shieldDuration < 0)
	{
		shield = true;
		shieldDuration = 600;
		shieldTimer = 800;
	}
}

void Dreadnought::setFuel(float f)
{
	fuel = f;
}

void Dreadnought::Draw(sf::RenderWindow & window)
{
	for (int i = 0; i < thrusters.size(); i++)
	{
		thrusters.at(i)->Draw(window);
	}

	window.draw(boosterSprite);
	window.draw(shipSprite);

	window.draw(baySprite);

	/*for (int i = 0; i < turrets.size(); i++)
	{
		turrets.at(i)->Draw(window);
	}*/

	if (type == "enemy" || type == "ally")
	{
		window.draw(healthBox);
		window.draw(healthBar);
		window.draw(power);
	}
}

void Dreadnought::CreateBody()
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

	float width = ((shipSprite.getTextureRect().width * shipSprite.getScale().x) / 2);
	float height = ((shipSprite.getTextureRect().height * shipSprite.getScale().x) / 2);

	b2PolygonShape Shape;
		b2Vec2 vertices[7];
		vertices[6].Set((9 - width) / SCALE, (49 - height) / SCALE);
		vertices[5].Set((55 - width) / SCALE, (4 - height) / SCALE);
		vertices[4].Set((145 - width) / SCALE, (4 - height) / SCALE);
		vertices[3].Set((190 - width) / SCALE, (49 - height) / SCALE);
		vertices[2].Set((190 - width) / SCALE, (280 - height) / SCALE);
		vertices[1].Set((25 - width) / SCALE, (280 - height) / SCALE);
		vertices[0].Set((9 - width) / SCALE, (280 - height) / SCALE);

	Shape.Set(vertices, 7);

	//Shape.SetAsBox(((shipSprite.getTextureRect().width * shipSprite.getScale().x) / 2) / SCALE, ((shipSprite.getTextureRect().height * shipSprite.getScale().x) / 2) / SCALE);
	//Shape.SetAsBox((185 / 2) / SCALE, (292 / 2) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 1.0f;
	FixtureDef.friction = 0.7f;
	FixtureDef.shape = &Shape;

	if (type == "player")
	{
		FixtureDef.filter.categoryBits = 0x0001;
		FixtureDef.filter.maskBits = 0x0010 | 0x0002 | 0x0001 | 0x0004 | 0x0008;
		FixtureDef.userData = "player";
	}
	else if (type == "enemy")
	{
		FixtureDef.filter.categoryBits = 0x0002;
		FixtureDef.filter.maskBits = 0x0010 | 0x0001 | 0x0002 | 0x0004 | 0x0008;
		FixtureDef.userData = "enemy";
	}
	else if (type == "ally")
	{
		FixtureDef.filter.categoryBits = 0x0001;
		FixtureDef.filter.maskBits = 0x0010 | 0x0002 | 0x0001 | 0x0004 | 0x0008;
		FixtureDef.userData = "ally";
	}
	Body->CreateFixture(&FixtureDef);

	shipBody = Body;
}

void Dreadnought::setHealth(float h)
{
	if (shield == false)
	{
		health = h;
	}
}

void Dreadnought::updateMissilePoints()
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

void Dreadnought::updateRayPoints()
{
	for (int i = 0; i < rayPoints.size(); i++)
	{
		rayPoints.at(i) = new sf::Vector2f(((shipSprite.getPosition().x - shipSprite.getTextureRect().width / 4) + rayPointOrig.at(i)->x), ((shipSprite.getPosition().y - shipSprite.getTextureRect().height / 4) + rayPointOrig.at(i)->y));
		//thrusters.at(i).y = ((shipSprite.getPosition().y - shipSprite.getTextureRect().height / 4) + thrusters.at(i)->position.y);

		float s1 = sin(shipSprite.getRotation() * 0.0174532925);
		float c1 = cos(shipSprite.getRotation() * 0.0174532925);

		// translate point back to origin:
		rayPoints.at(i) = new sf::Vector2f(rayPoints.at(i)->x - shipSprite.getPosition().x, rayPoints.at(i)->y - shipSprite.getPosition().y);
		// rotate point
		float xnew1 = rayPoints.at(i)->x * c1 - rayPoints.at(i)->y * s1;
		float ynew1 = rayPoints.at(i)->x * s1 + rayPoints.at(i)->y * c1;

		// translate point back:
		rayPoints.at(i) = new sf::Vector2f(xnew1 + shipSprite.getPosition().x, ynew1 + shipSprite.getPosition().y);
	}

	for (int i = 0; i < rayEndPoints.size(); i++)
	{
		rayEndPoints.at(i) = new sf::Vector2f(((shipSprite.getPosition().x - shipSprite.getTextureRect().width / 4) + rayEndPointOrig.at(i)->x), ((shipSprite.getPosition().y - shipSprite.getTextureRect().height / 4) + rayEndPointOrig.at(i)->y));
		//thrusters.at(i).y = ((shipSprite.getPosition().y - shipSprite.getTextureRect().height / 4) + thrusters.at(i)->position.y);

		float s1 = sin(shipSprite.getRotation() * 0.0174532925);
		float c1 = cos(shipSprite.getRotation() * 0.0174532925);

		// translate point back to origin:
		rayEndPoints.at(i) = new sf::Vector2f(rayEndPoints.at(i)->x - shipSprite.getPosition().x, rayEndPoints.at(i)->y - shipSprite.getPosition().y);
		// rotate point
		float xnew1 = rayEndPoints.at(i)->x * c1 - rayEndPoints.at(i)->y * s1;
		float ynew1 = rayEndPoints.at(i)->x * s1 + rayEndPoints.at(i)->y * c1;

		// translate point back:
		rayEndPoints.at(i) = new sf::Vector2f(xnew1 + shipSprite.getPosition().x, ynew1 + shipSprite.getPosition().y);
	}
}

void Dreadnought::updateThrusterPoints()
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

void Dreadnought::updateWreckPoints()
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

void Dreadnought::updateBoosterPoints()
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

void Dreadnought::DeleteAll()
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
		turrets.at(i)->destroyed = true;
	}
}


