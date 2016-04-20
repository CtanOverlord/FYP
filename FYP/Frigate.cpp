#include "Frigate.h"
#include "Turret.h"

static const float SCALE = 30.f;

Frigate::Frigate()
{

}

Frigate::Frigate(b2World& World, sf::Vector2f position, string t, sf::RenderWindow & window)
{
	if (t == "player")
	{
		if (!shipTexture.loadFromFile("Frigate2.png"))
		{
			// error...
		}
	}
	else if (t == "enemy")
	{
		if (!shipTexture.loadFromFile("FrigateEnemy.png"))
		{
			// error...
		}
	}
	else if (t == "ally")
	{
		if (!shipTexture.loadFromFile("FrigateAlly.png"))
		{
			// error...
		}
	}

	missileStep = 0;

	shipType = "Frigate";

	fireCount = 7;

	missileFiring = false;

	shield = false;

	Window = &window;

	destructionTimer = 240;

	delayTimer = 0;

	delay = 19; // or 17

	health = 720;

	maxHealth = 720;

	fuel = 1000;

	maxFuel = 1000;

	soundTimer = 0;

	onlyOnce = false;

	rayCollision = false;

	followPoint = sf::Vector2f(0, 0);

	currentTState = TurnState::FOLLOW;
	currentMState = MoveState::FORWARD;
	currentFState = FireState::NONE3;

	//currentTState = TurnState::NONE;
	//currentMState = MoveState::NONE2;
	//currentFState = FireState::NONE3;

	chooseTimer = 0;

	firing = false;

	targetPos = sf::Vector2f(0, -10000);

	chooseTimer = 120;

	shipTexture.setSmooth(true);

	shipSprite.setTexture(shipTexture);

	shipSprite.setScale(sf::Vector2f(0.5f, 0.5f));

	shipSprite.setPosition(sf::Vector2f(position.x, position.y));

	shipSprite.setOrigin(sf::Vector2f(88, 116));

	if (t == "enemy")
	{
		shipSprite.setRotation(180);
	}

	//sf::IntRect temp = shipSprite.getTextureRect();

	//temp.height = 200;

	//shipSprite.setTextureRect(temp);

	destroyed = false;

	if (!healthBoxTexture.loadFromFile("healthBox2.png"))
	{
		// error...
	}

	healthBoxTexture.setSmooth(true);

	healthBox.setTexture(healthBoxTexture);

	healthBox.setScale(sf::Vector2f(0.2f, 0.2f));

	healthBox.setPosition(sf::Vector2f(position.x, position.y));

	healthBox.setOrigin(sf::Vector2f(300, 58.5f));

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

	if (!bayTexture.loadFromFile("MissileBaysFrigate.png"))
	{
		// error...
	}

	bayTexture.setSmooth(true);

	baySprite.setTexture(bayTexture);

	baySprite.setScale(sf::Vector2f(0.5f, 0.5f));

	baySprite.setPosition(sf::Vector2f(position.x, position.y));

	baySprite.setOrigin(sf::Vector2f(88, 116));

	baySprite.setColor(sf::Color(255, 255, 255, 0));

	if (!boosterTexture.loadFromFile("engineStreamMain.png"))
	{
		// error...
	}

	type = t;

	boosterTexture.setSmooth(true);

	boosterSprite.setTexture(boosterTexture);

	boosterSprite.setScale(sf::Vector2f(0.5f, 0.25f));

	boosterSprite.setPosition(sf::Vector2f(100, 190));

	boosterSprite.setOrigin(sf::Vector2f(38, 1));

	boosterPoint = sf::Vector2f(44, 95);

	if (!boosterTexture2.loadFromFile("engineStreamBoost.png"))
	{
		// error...
	}

	boosterTexture2.setSmooth(true);

	boosterSprite2.setTexture(boosterTexture2);

	boosterSprite2.setScale(sf::Vector2f(0.5f, 0.25f));

	boosterSprite2.setPosition(sf::Vector2f(100, 190));

	boosterSprite2.setOrigin(sf::Vector2f(12, 1));

	boosterSprite2.setColor(sf::Color(255, 255, 255, 0));

	boosterPoint2 = sf::Vector2f(8.5, 105);

	boosterSprite3.setTexture(boosterTexture2);

	boosterSprite3.setScale(sf::Vector2f(0.5f, 0.25f));

	boosterSprite3.setPosition(sf::Vector2f(100, 190));

	boosterSprite3.setOrigin(sf::Vector2f(12, 1));

	boosterPoint3 = sf::Vector2f(79.5, 106);

	boosterSprite3.setColor(sf::Color(255, 255, 255, 0));

	if (!shieldTexture.loadFromFile("shipShield4.png"))
	{
		// error...
	}

	shieldTexture.setSmooth(true);

	shieldSprite.setTexture(shieldTexture);

	shieldSprite.setScale(sf::Vector2f(0.25f, 0.25f));

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
	missilePoints.push_back(new sf::Vector2f(8, 40));
	// right
	missilePoints.push_back(new sf::Vector2f(79, 40));

	// left
	missilePointOrig.push_back(new sf::Vector2f(8, 40));
	// right
	missilePointOrig.push_back(new sf::Vector2f(79, 40));

	wreckPoint.push_back(new sf::Vector2f(20, 20));
	wreckPoint.push_back(new sf::Vector2f(20, 40));

	wreckPointOrig.push_back(new sf::Vector2f(20, 20));
	wreckPointOrig.push_back(new sf::Vector2f(20, 40));

	//TurretManager::GetInstance()->CreateTurret(new Turret(sf::Vector2f(44, 72), *this, type, "Laser", *Window, *world));

	turrets.push_back(new Turret(sf::Vector2f(44, 72), *this, type, "Laser", *Window, *world));

	TurretManager::GetInstance()->CreateTurret(turrets.at(0));

	thrusters.push_back(new Thruster(sf::Vector2f(41.5, 4), 0, false, "front"));
	thrusters.push_back(new Thruster(sf::Vector2f(46.5, 4), 0, false, "front"));


	thrusters.push_back(new Thruster(sf::Vector2f(10, 55), 0, false, "topleft"));
	thrusters.push_back(new Thruster(sf::Vector2f(78, 55), 0, false, "topright"));
	thrusters.push_back(new Thruster(sf::Vector2f(10, 105), 0, false, "botleft"));
	thrusters.push_back(new Thruster(sf::Vector2f(78, 105), 0, false, "botright"));

	//rayPoints.push_back(new sf::Vector2f(5, 50));
	//rayPointOrig.push_back(new sf::Vector2f(50, 50));
	//rayPoints.push_back(new sf::Vector2f(82, 50));
	//rayPointOrig.push_back(new sf::Vector2f(82, 50));

	//// Left (0', 45', 90')
	//rayEndPoints.push_back(new sf::Vector2f(5, 30));
	//rayEndPointOrig.push_back(new sf::Vector2f(5, 30));
	//rayEndPoints.push_back(new sf::Vector2f(-11, 36));
	//rayEndPointOrig.push_back(new sf::Vector2f(-11, 36));
	//rayEndPoints.push_back(new sf::Vector2f(-15, 50));
	//rayEndPointOrig.push_back(new sf::Vector2f(-15, 50));

	//// Right (0', 45', 90')
	//rayEndPoints.push_back(new sf::Vector2f(82, 30));
	//rayEndPointOrig.push_back(new sf::Vector2f(82, 30));
	//rayEndPoints.push_back(new sf::Vector2f(96, 36));
	//rayEndPointOrig.push_back(new sf::Vector2f(96, 36));
	//rayEndPoints.push_back(new sf::Vector2f(106, 50));
	//rayEndPointOrig.push_back(new sf::Vector2f(106, 50));

	rayPoints.push_back(new sf::Vector2f(10, 50));
	rayPointOrig.push_back(new sf::Vector2f(10, 50));
	rayPoints.push_back(new sf::Vector2f(82, 50));
	rayPointOrig.push_back(new sf::Vector2f(82, 50));
	rayPoints.push_back(new sf::Vector2f(10, 110));
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
	rayEndPoints.push_back(new sf::Vector2f(82, 30));
	rayEndPointOrig.push_back(new sf::Vector2f(82, 30));
	rayEndPoints.push_back(new sf::Vector2f(106, 36));
	rayEndPointOrig.push_back(new sf::Vector2f(106, 36));
	rayEndPoints.push_back(new sf::Vector2f(110, 50));
	rayEndPointOrig.push_back(new sf::Vector2f(110, 50));
}

void Frigate::Update()
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

void Frigate::playerUpdate()
{
	shipSprite.setPosition(shipBody->GetPosition().x * SCALE, shipBody->GetPosition().y * SCALE);

	shipSprite.setRotation(shipBody->GetAngle() * (180.0f / b2_pi));

	if (fuel < 1000)
	{
		fuel += 1.0f;
	}

	//shieldSprite.setPosition(shipSprite.getPosition());

	//shieldSprite.setRotation(shipSprite.getRotation());

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
				shieldDuration = 400;
				shieldTimer = 480;
				SoundManager::GetInstance()->ShieldsOn();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			if (missileTimer < 0 && missileFiring == false)
			{
				missileFiring = true;

				missileTimer = 480;

				sf::Vector2i mousePos;
				mousePos = sf::Mouse::getPosition(*Window);

				worldMousePos = Window->mapPixelToCoords(mousePos);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			updateThrusterPoints();
			shipBody->ApplyAngularImpulse(-0.3, false);
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
			shipBody->ApplyAngularImpulse(0.3, false);
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
			if (speedBoost == true)
			{
				shipBody->ApplyLinearImpulse(b2Vec2((velocity.x  * 2.5f) / 2, (velocity.y * 2.5f) / 2), shipBody->GetWorldCenter(), false);
			}
			else if (speedBoost == false)
			{
				shipBody->ApplyLinearImpulse(b2Vec2(velocity.x / 2, velocity.y / 2), shipBody->GetWorldCenter(), false);
			}
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
			if (speedBoost == true)
			{
				shipBody->ApplyLinearImpulse(b2Vec2(-velocity.x * 2.5f, -velocity.y * 2.5f), shipBody->GetWorldCenter(), false);
			}
			else if (speedBoost == false)
			{
				shipBody->ApplyLinearImpulse(b2Vec2(-velocity.x, -velocity.y), shipBody->GetWorldCenter(), false);
			}

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
					tempX = shipSprite.getPosition().x + rand() % 50 + 1;
					tempY = shipSprite.getPosition().y + rand() % 50 + 1;
				}
				else if (temp == 2)
				{
					tempX = shipSprite.getPosition().x - rand() % 50 + 1;
					tempY = shipSprite.getPosition().y + rand() % 50 + 1;
				}
				else if (temp == 3)
				{
					tempX = shipSprite.getPosition().x + rand() % 50 + 1;
					tempY = shipSprite.getPosition().y - rand() % 50 + 1;
				}
				else if (temp == 4)
				{
					tempX = shipSprite.getPosition().x - rand() % 50 + 1;
					tempY = shipSprite.getPosition().y - rand() % 50 + 1;
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
				WreckManager::GetInstance()->CreateWreck(sf::Vector2f(wreckPoint.at(i)->x, wreckPoint.at(i)->y), shipSprite.getRotation(), i + 4);
			}
		}
	}

	//missileTimer--;

	//speed = sqrt((shipBody->GetLinearVelocity().x * shipBody->GetLinearVelocity().x) + (shipBody->GetLinearVelocity().y * shipBody->GetLinearVelocity().y));


	boosterSprite.setScale(sf::Vector2f(0.5f, speed / 2.5f));
	boosterSprite2.setScale(sf::Vector2f(0.5f, speed / 2.5f));
	boosterSprite3.setScale(sf::Vector2f(0.5f, speed / 2.5f));


	velocity.x = cos((shipSprite.getRotation() + 90) * 0.0174532925);
	velocity.y = sin((shipSprite.getRotation() + 90) * 0.0174532925);

	velocity2.x = cos((shipSprite.getRotation()) * 0.0174532925);
	velocity2.y = sin((shipSprite.getRotation()) * 0.0174532925);

	for (int i = 0; i < thrusters.size(); i++)
	{
		thrusters.at(i)->Update();
	}

	if (shield == true)
	{
		shieldDuration--;

		speedBoost = true;

		if (shieldSprite.getColor().a < 255)
		{
			shieldSprite.setColor(sf::Color(255, 255, 255, shieldSprite.getColor().a + 1));
			boosterSprite2.setColor(sf::Color(255, 255, 255, boosterSprite2.getColor().a + 1));
			boosterSprite3.setColor(sf::Color(255, 255, 255, boosterSprite3.getColor().a + 1));
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
		speedBoost = false;
		if (shieldSprite.getColor().a > 2)
		{
			shieldSprite.setColor(sf::Color(255, 255, 255, shieldSprite.getColor().a - 2));
			boosterSprite2.setColor(sf::Color(255, 255, 255, boosterSprite2.getColor().a - 2));
			boosterSprite3.setColor(sf::Color(255, 255, 255, boosterSprite3.getColor().a - 2));
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
			if (missileStep == 30)
			{
				updateMissilePoints();

				ProjectileManager::GetInstance()->CreateDrain(*missilePoints.at(0), worldMousePos, shipSprite.getRotation(), false);

				ProjectileManager::GetInstance()->CreateDrain(*missilePoints.at(1), worldMousePos, shipSprite.getRotation(), false);

				SoundManager::GetInstance()->CreateSound(*missilePoints.at(1), 1);
			}

			if (missileStep == 60)
			{
				missileStep = 0;

				missileTimer = 480;
				missileFiring = false;
				fireCount = 7;
				missileStep = 0;
			}
		}

		missileStep++;
	}
	else
	{
		if (missileTimer > -1)
		{
			missileTimer--;
		}
	}
}

void Frigate::enemyUpdate()
{
	healthBox.setPosition(shipSprite.getPosition().x, shipSprite.getPosition().y - 90);
	healthBar.setPosition(shipSprite.getPosition().x - 51, shipSprite.getPosition().y - 90);

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

	shipSprite.setPosition(shipBody->GetPosition().x * SCALE, shipBody->GetPosition().y * SCALE);

	shipSprite.setRotation(shipBody->GetAngle() * (180.0f / b2_pi));

	if (fuel < 1000)
	{
		fuel += 1.0f;
	}

	if (chooseTimer > 120)
	{
		if (type == "enemy")
		{
			chooseNextAction();
		}
		else if (type == "ally")
		{
			chooseNextActionAlly();
		}
		chooseTimer = 0;
	}

	chooseTimer++;

	//shieldSprite.setPosition(shipSprite.getPosition());

	//shieldSprite.setRotation(shipSprite.getRotation());

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

	world->RayCast(rayCallBackF1, startPoint, endPoint);

	//Front left 45'
	endPoint.x = (rayPoints.at(0)->x + ((rayEndPoints.at(1)->x - rayPoints.at(0)->x) * 2)) / SCALE;
	endPoint.y = (rayPoints.at(0)->y + ((rayEndPoints.at(1)->y - rayPoints.at(0)->y) * 2)) / SCALE;

	world->RayCast(rayCallBackL1, startPoint, endPoint);

	//Front left 90'
	endPoint.x = (rayPoints.at(0)->x + ((rayEndPoints.at(2)->x - rayPoints.at(0)->x) * 2)) / SCALE;
	endPoint.y = (rayPoints.at(0)->y + ((rayEndPoints.at(2)->y - rayPoints.at(0)->y) * 2)) / SCALE;

	world->RayCast(rayCallBackL2, startPoint, endPoint);

	startPoint.x = rayPoints.at(1)->x / SCALE;
	startPoint.y = rayPoints.at(1)->y / SCALE;

	//Front right
	endPoint.x = (rayPoints.at(1)->x + ((rayEndPoints.at(3)->x - rayPoints.at(1)->x) * 8)) / SCALE;
	endPoint.y = (rayPoints.at(1)->y + ((rayEndPoints.at(3)->y - rayPoints.at(1)->y) * 8)) / SCALE;

	world->RayCast(rayCallBackF2, startPoint, endPoint);

	//Front right 45'
	endPoint.x = (rayPoints.at(1)->x + ((rayEndPoints.at(4)->x - rayPoints.at(1)->x) * 2)) / SCALE;
	endPoint.y = (rayPoints.at(1)->y + ((rayEndPoints.at(4)->y - rayPoints.at(1)->y) * 2)) / SCALE;

	world->RayCast(rayCallBackR1, startPoint, endPoint);

	//Front right90'
	endPoint.x = (rayPoints.at(1)->x + ((rayEndPoints.at(5)->x - rayPoints.at(1)->x) * 2)) / SCALE;
	endPoint.y = (rayPoints.at(1)->y + ((rayEndPoints.at(5)->y - rayPoints.at(1)->y) * 2)) / SCALE;

	world->RayCast(rayCallBackR2, startPoint, endPoint);

	bool hitF1 = false;
	bool hitF2 = false;
	bool hitL1 = false;
	bool hitL2 = false;
	bool hitR1 = false;
	bool hitR2 = false;;

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
		shipBody->ApplyAngularImpulse(-2, false);
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
		shipBody->ApplyAngularImpulse(2, false);
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
			impulse = impulse * 4;

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
		//AbilityTwo();
		if (speedBoost == true)
		{
			shipBody->ApplyLinearImpulse(b2Vec2((-velocity.x * 2.5f) * 2.5f, (-velocity.y * 3.5f) * 2.5f), shipBody->GetWorldCenter(), false);
		}
		else if (speedBoost == false)
		{
			shipBody->ApplyLinearImpulse(b2Vec2((-velocity.x  * 2.5f), (-velocity.y  * 3.5f)), shipBody->GetWorldCenter(), false);
		}
		//shipBody->ApplyLinearImpulse(b2Vec2(-velocity.x * 1.5f, -velocity.y * 1.5f), shipBody->GetWorldCenter(), false);
		if (speed < 1)
		{
			speed += 0.01f;
		}
		break;
	case(MoveState::BACKWARDS) :
		updateThrusterPoints();
		if (speedBoost == true)
		{
			shipBody->ApplyLinearImpulse(b2Vec2(((velocity.x * 2.5f)  * 2.5f) / 2, ((velocity.y * 3.5f) * 2.5f) / 2), shipBody->GetWorldCenter(), false);
		}
		else if (speedBoost == false)
		{
			shipBody->ApplyLinearImpulse(b2Vec2((velocity.x  * 2.5f) / 2, (velocity.y  * 3.5f) / 2), shipBody->GetWorldCenter(), false);
		}
		//shipBody->ApplyLinearImpulse(b2Vec2(velocity.x, velocity.y), shipBody->GetWorldCenter(), false);
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
		//AbilityTwo();
		break;
	case(FireState::NONE3) :
		firing = false;
		break;
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
					tempX = shipSprite.getPosition().x + rand() % 50 + 1;
					tempY = shipSprite.getPosition().y + rand() % 50 + 1;
				}
				else if (temp == 2)
				{
					tempX = shipSprite.getPosition().x - rand() % 50 + 1;
					tempY = shipSprite.getPosition().y + rand() % 50 + 1;
				}
				else if (temp == 3)
				{
					tempX = shipSprite.getPosition().x + rand() % 50 + 1;
					tempY = shipSprite.getPosition().y - rand() % 50 + 1;
				}
				else if (temp == 4)
				{
					tempX = shipSprite.getPosition().x - rand() % 50 + 1;
					tempY = shipSprite.getPosition().y - rand() % 50 + 1;
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
				WreckManager::GetInstance()->CreateWreck(sf::Vector2f(wreckPoint.at(i)->x, wreckPoint.at(i)->y), shipSprite.getRotation(), i + 4);
			}
		}
	}

	//missileTimer--;

	//speed = sqrt((shipBody->GetLinearVelocity().x * shipBody->GetLinearVelocity().x) + (shipBody->GetLinearVelocity().y * shipBody->GetLinearVelocity().y));


	boosterSprite.setScale(sf::Vector2f(0.5f, speed / 2.5f));
	boosterSprite2.setScale(sf::Vector2f(0.5f, speed / 2.5f));
	boosterSprite3.setScale(sf::Vector2f(0.5f, speed / 2.5f));


	velocity.x = cos((shipSprite.getRotation() + 90) * 0.0174532925);
	velocity.y = sin((shipSprite.getRotation() + 90) * 0.0174532925);

	velocity2.x = cos((shipSprite.getRotation()) * 0.0174532925);
	velocity2.y = sin((shipSprite.getRotation()) * 0.0174532925);

	for (int i = 0; i < thrusters.size(); i++)
	{
		thrusters.at(i)->Update();
	}

	if (shield == true)
	{
		shieldDuration--;

		speedBoost = true;

		if (shieldSprite.getColor().a < 255)
		{
			shieldSprite.setColor(sf::Color(255, 255, 255, shieldSprite.getColor().a + 1));
			boosterSprite2.setColor(sf::Color(255, 255, 255, boosterSprite2.getColor().a + 1));
			boosterSprite3.setColor(sf::Color(255, 255, 255, boosterSprite3.getColor().a + 1));
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
		speedBoost = false;
		if (shieldSprite.getColor().a > 2)
		{
			shieldSprite.setColor(sf::Color(255, 255, 255, shieldSprite.getColor().a - 2));
			boosterSprite2.setColor(sf::Color(255, 255, 255, boosterSprite2.getColor().a - 2));
			boosterSprite3.setColor(sf::Color(255, 255, 255, boosterSprite3.getColor().a - 2));
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
			if (missileStep == 30)
			{
				updateMissilePoints();

				if (type == "enemy")
				{
					ProjectileManager::GetInstance()->CreateDrain(*missilePoints.at(0), worldMousePos, shipSprite.getRotation(), true);

					ProjectileManager::GetInstance()->CreateDrain(*missilePoints.at(1), worldMousePos, shipSprite.getRotation(), true);
				}
				else if (type == "ally")
				{
					ProjectileManager::GetInstance()->CreateDrain(*missilePoints.at(0), worldMousePos, shipSprite.getRotation(), false);

					ProjectileManager::GetInstance()->CreateDrain(*missilePoints.at(1), worldMousePos, shipSprite.getRotation(), false);
				}

				SoundManager::GetInstance()->CreateSound(*missilePoints.at(1), 1);
			}

			if (missileStep == 60)
			{
				missileStep = 0;

				missileTimer = 480;
				missileFiring = false;
				fireCount = 7;
				missileStep = 0;
			}
		}

		missileStep++;
	}
	else
	{
		if (missileTimer > -1)
		{
			missileTimer--;
		}
	}
}

void Frigate::chooseNextAction()
{
	bool capturePointFree = false;
	bool enemyNearby = false;
	bool capturingPoint = false;
	float shortestDist = 999999999999;

	for (int i = 0; i < Level::GetInstance()->capPoints.size(); i++)
	{
		if (Level::GetInstance()->capPoints.at(i)->owner != "Red")
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
		if (ShipManager::GetInstance()->ships.at(i)->type == "player" || ShipManager::GetInstance()->ships.at(i)->type == "ally")
		{
			if ((ShipManager::GetInstance()->ships.at(i)->shipType == "Sniper" && ShipManager::GetInstance()->ships.at(i)->shield == true))
			{

			}
			else
			{
				float dist = distance(ShipManager::GetInstance()->ships.at(i)->getSprite().getPosition(), shipSprite.getPosition());
				if (dist < 700)
				{
					if (dist < shortestDist)
					{
						currentTState = FOLLOW;
						currentMState = FORWARD;
						shortestDist = dist;
						targetShip = ShipManager::GetInstance()->ships.at(i);
						followPoint = targetShip->getSprite().getPosition();
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

void Frigate::chooseNextActionAlly()
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
				if (dist < 700)
				{
					if (dist < shortestDist)
					{
						currentTState = FOLLOW;
						currentMState = FORWARD;
						shortestDist = dist;
						targetShip = ShipManager::GetInstance()->ships.at(i);
						followPoint = targetShip->getSprite().getPosition();
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

void Frigate::AbilityOne()
{
	if (missileTimer < 0 && missileFiring == false)
	{
		missileFiring = true;

		missileTimer = 480;

		sf::Vector2i mousePos;
		mousePos = sf::Mouse::getPosition(*Window);

		worldMousePos = Window->mapPixelToCoords(mousePos);
	}
}

void Frigate::AbilityTwo()
{
	if (shieldTimer < 0 && shieldDuration < 0)
	{
		shield = true;
		shieldDuration = 400;
		shieldTimer = 480;
	}
}

void Frigate::Draw(sf::RenderWindow & window)
{
	for (int i = 0; i < thrusters.size(); i++)
	{
		thrusters.at(i)->Draw(window);
	}

	window.draw(boosterSprite);
	window.draw(boosterSprite2);
	window.draw(boosterSprite3);
	window.draw(shipSprite);

	window.draw(baySprite);

	if (type == "enemy" || type == "ally")
	{
		window.draw(healthBox);
		window.draw(healthBar);
	}
}

void Frigate::CreateBody()
{
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(shipSprite.getPosition().x / SCALE, shipSprite.getPosition().y / SCALE);
	BodyDef.type = b2_dynamicBody;
	BodyDef.userData = this;
	b2Body* Body = world->CreateBody(&BodyDef);
	Body->SetFixedRotation(false);
	Body->SetSleepingAllowed(false);
	Body->SetGravityScale(3.0f);
	if (type == "enemy" || type == "ally")
	{
		Body->SetLinearDamping(3);
		Body->SetAngularDamping(3.0f);
	}
	else
	{
		Body->SetLinearDamping(1);
		Body->SetAngularDamping(1.0f);
	}

	b2PolygonShape Shape;
	Shape.SetAsBox(((shipSprite.getTextureRect().width * shipSprite.getScale().x) / 2) / SCALE, ((shipSprite.getTextureRect().height * shipSprite.getScale().x) / 2) / SCALE);
	//Shape.SetAsBox((88 / 2) / SCALE, (116 / 2) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 0.6f;
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

void Frigate::updateMissilePoints()
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
void Frigate::updateRayPoints()
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


void Frigate::updateThrusterPoints()
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

void Frigate::updateWreckPoints()
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

void Frigate::updateBoosterPoints()
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

	boosterSprite2.setPosition((shipSprite.getPosition().x - shipSprite.getTextureRect().width / 4) + boosterPoint2.x, (shipSprite.getPosition().y - shipSprite.getTextureRect().height / 4) + boosterPoint2.y);

	s = sin(shipSprite.getRotation() * 0.0174532925);
	c = cos(shipSprite.getRotation() * 0.0174532925);

	// translate point back to origin:
	boosterSprite2.setPosition(boosterSprite2.getPosition().x - shipSprite.getPosition().x, boosterSprite2.getPosition().y - shipSprite.getPosition().y);

	// rotate point
	xnew = boosterSprite2.getPosition().x * c - boosterSprite2.getPosition().y * s;
	ynew = boosterSprite2.getPosition().x * s + boosterSprite2.getPosition().y * c;

	// translate point back:
	boosterSprite2.setPosition(xnew + shipSprite.getPosition().x, ynew + shipSprite.getPosition().y);

	boosterSprite2.setRotation(shipSprite.getRotation());

	boosterSprite3.setPosition((shipSprite.getPosition().x - shipSprite.getTextureRect().width / 4) + boosterPoint3.x, (shipSprite.getPosition().y - shipSprite.getTextureRect().height / 4) + boosterPoint3.y);

	s = sin(shipSprite.getRotation() * 0.0174532925);
	c = cos(shipSprite.getRotation() * 0.0174532925);

	// translate point back to origin:
	boosterSprite3.setPosition(boosterSprite3.getPosition().x - shipSprite.getPosition().x, boosterSprite3.getPosition().y - shipSprite.getPosition().y);

	// rotate point
	xnew = boosterSprite3.getPosition().x * c - boosterSprite3.getPosition().y * s;
	ynew = boosterSprite3.getPosition().x * s + boosterSprite3.getPosition().y * c;

	// translate point back:
	boosterSprite3.setPosition(xnew + shipSprite.getPosition().x, ynew + shipSprite.getPosition().y);

	boosterSprite3.setRotation(shipSprite.getRotation());
}

void Frigate::DeleteAll()
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


