#include "Sniper.h"
#include "Turret.h"

static const float SCALE = 30.f;

Sniper::Sniper()
{

}

Sniper::Sniper(b2World& World, sf::Vector2f position, string t, sf::RenderWindow & window)
{
	srand(time(NULL));

	if (t == "player")
	{
		if (!shipTexture.loadFromFile("Sniper.png"))
		{
			// error...
		}
	}
	else if (t == "enemy")
	{
		if (!shipTexture.loadFromFile("SniperEnemy.png"))
		{
			// error...
		}
	}
	else if (t == "ally")
	{
		if (!shipTexture.loadFromFile("SniperAlly.png"))
		{
			// error...
		}
	}

	missileStep = 0;

	shipType = "Sniper";

	fireCount = 7;

	missileFiring = false;

	shield = false;

	Window = &window;

	destructionTimer = 240;

	delayTimer = 0;

	delay = 19; // or 17

	health = 650;

	maxHealth = 650;

	fuel = 1000;

	cooldown = false;

	charging = false;

	fireTimer = 350;

	fireTimerMax = 350;

	cooldownTimer = 120;

	soundTimer = 0;

	onlyOnce = false;

	manual = false;

	cloakx = 0;

	cloaky = 0;

	cloakx2 = 199;

	cloaky2 = 574;

	decloakTimer = 0;

	cloakTimer = 0;

	cloakwave = 0;

	cloakwave2 = 0;

	mineCount = 30;

	mineLeft = true;

	rayCollision = false;

	followPoint = sf::Vector2f(0, 0);

	currentTState = TurnState::FOLLOW;
	currentMState = MoveState::FORWARD;
	currentFState = FireState::NONE3;

	chooseTimer = 0;

	firing = false;

	targetPos = sf::Vector2f(0, -10000);

	shipTexture.setSmooth(true);

	shipSprite.setTexture(shipTexture);

	shipSprite.setScale(sf::Vector2f(0.5f, 0.5f));

	shipSprite.setPosition(sf::Vector2f(position.x, position.y));

	shipSprite.setOrigin(sf::Vector2f(100, 287.5f));

	if (t == "enemy")
	{
		shipSprite.setRotation(180);
	}

	if (t == "enemy")
	{
		cloakBase.loadFromFile("SniperEnemy.png");
	}
	else if (t == "ally")
	{
		cloakBase.loadFromFile("SniperAlly.png");
	}
	else
	{
		cloakBase.loadFromFile("Sniper.png");
	}

	cloak.loadFromFile("SniperCloak2.png");

	if (t == "enemy")
	{
		defaultSniper.loadFromFile("SniperEnemy.png");
	}
	else if (t == "ally")
	{
		defaultSniper.loadFromFile("SniperAlly.png");
	}
	else
	{
		defaultSniper.loadFromFile("Sniper.png");
	}

	//firePoint1 = sf::Vector2f(22.5, 0);

	firePointOrig.push_back(sf::Vector2f(50, 200));

	firePoints.push_back(sf::Vector2f(50, 200));

	firePointOrig.push_back(sf::Vector2f(50, 235));

	firePoints.push_back(sf::Vector2f(50, 235));

	for (int i = 0; i < firePoints.size(); i++)
	{
		firePoints.at(i).x = (shipSprite.getPosition().x - shipSprite.getTextureRect().width / 4) + firePointOrig.at(i).x;
		firePoints.at(i).y = (shipSprite.getPosition().y - shipSprite.getTextureRect().height / 4) + firePointOrig.at(i).y;
	}

	for (int i = 0; i < 30; i++)
	{
		zapPointOrig.push_back(sf::Vector2f(50, 6.333333 * i));

		zapPoints.push_back(sf::Vector2f(50, 6.333333 * i));
	}

	for (int i = 0; i < zapPoints.size(); i++)
	{
		zapPoints.at(i).x = (shipSprite.getPosition().x - shipSprite.getTextureRect().width / 4) + zapPointOrig.at(i).x;
		zapPoints.at(i).y = (shipSprite.getPosition().y - shipSprite.getTextureRect().height / 4) + zapPointOrig.at(i).y;
	}

	//sf::IntRect temp = shipSprite.getTextureRect();

	//temp.height = 200;

	//shipSprite.setTextureRect(temp);

	destroyed = false;

	if (!chargeTexture.loadFromFile("ChargeSheet.png"))
	{

	}

	chargeTexture.setSmooth(true);

	charge.setSpriteSheet(chargeTexture);

	for (int i = 0; i < 8; i++)
	{
		charge.addFrame(sf::IntRect(200 * i, 0, 200, 575));
	}

	chargeSprite = AnimatedSprite(sf::seconds(1.0f), true, true);
	chargeSprite.setOrigin(100, 287.5f);
	chargeSprite.setPosition(position);
	chargeSprite.setScale(sf::Vector2f(0.5f, 0.5f));
	chargeSprite.play(charge);
	chargeSprite.setFrame(0, true);
	chargeSprite.pause();

	if (!chargeBuffer.loadFromFile("charge2.ogg"))
	{

	}

	chargeSound.setBuffer(chargeBuffer);
	chargeSound.pause();
	chargeSound.setPosition(sf::Vector3f(shipSprite.getPosition().x, 0, shipSprite.getPosition().y));
	chargeSound.setLoop(false);
	chargeSound.setVolume(30);
	chargeSound.setPitch(0.7);
	chargeSound.setRelativeToListener(false);
	chargeSound.setAttenuation(20);
	chargeSound.setMinDistance(1000);

	if (!powerdownBuffer.loadFromFile("powerdown3.ogg"))
	{

	}

	powerdownSound.setBuffer(powerdownBuffer);
	powerdownSound.pause();
	powerdownSound.setPosition(sf::Vector3f(shipSprite.getPosition().x, 0, shipSprite.getPosition().y));
	powerdownSound.setLoop(false);
	powerdownSound.setVolume(10);
	powerdownSound.setPitch(0.8);
	powerdownSound.setRelativeToListener(false);
	powerdownSound.setAttenuation(20);
	powerdownSound.setMinDistance(1000);

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

	if (!boosterTexture.loadFromFile("sniperEngine.png"))
	{
		// error...
	}

	type = t;

	boosterTexture.setSmooth(true);

	boosterSprite.setTexture(boosterTexture);

	boosterSprite.setScale(sf::Vector2f(0.5f, 0.25f));

	boosterSprite.setPosition(sf::Vector2f(100, 190));

	boosterSprite.setOrigin(sf::Vector2f(58, 1));

	boosterPoint = sf::Vector2f(50, 275);

	if (!boosterTexture2.loadFromFile("escapeEngine.png"))
	{
		// error...
	}

	boosterTexture2.setSmooth(true);

	boosterSprite2.setTexture(boosterTexture2);

	boosterSprite2.setScale(sf::Vector2f(0.5f, 1.0f));

	boosterSprite2.setPosition(sf::Vector2f(10, 220));

	boosterSprite2.setOrigin(sf::Vector2f(9, 49));

	boosterSprite2.setColor(sf::Color(255, 255, 255, 0));

	boosterPoint2 = sf::Vector2f(8, 210);

	boosterSprite3.setTexture(boosterTexture2);

	boosterSprite3.setScale(sf::Vector2f(0.5f, 1.0f));

	boosterSprite3.setPosition(sf::Vector2f(90, 220));

	boosterSprite3.setOrigin(sf::Vector2f(9, 49));

	boosterPoint3 = sf::Vector2f(92, 210);

	boosterSprite3.setColor(sf::Color(255, 255, 255, 0));

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

	wreckPoint.push_back(new sf::Vector2f(50, 237));
	wreckPoint.push_back(new sf::Vector2f(30, 96));
	wreckPoint.push_back(new sf::Vector2f(70, 96));

	wreckPointOrig.push_back(new sf::Vector2f(50, 237));
	wreckPointOrig.push_back(new sf::Vector2f(30, 96));
	wreckPointOrig.push_back(new sf::Vector2f(70, 96));

	rayPoints.push_back(new sf::Vector2f(17, 19));
	rayPointOrig.push_back(new sf::Vector2f(17, 19));
	rayPoints.push_back(new sf::Vector2f(82, 19));
	rayPointOrig.push_back(new sf::Vector2f(82, 19));
	rayPoints.push_back(new sf::Vector2f(10, 50));
	rayPointOrig.push_back(new sf::Vector2f(10, 50));
	rayPoints.push_back(new sf::Vector2f(190, 50));
	rayPointOrig.push_back(new sf::Vector2f(190, 50));
	rayPoints.push_back(new sf::Vector2f(10, 50));
	rayPointOrig.push_back(new sf::Vector2f(10, 50));
	rayPoints.push_back(new sf::Vector2f(190, 50));
	rayPointOrig.push_back(new sf::Vector2f(190, 50));

	// Left (0', 45', 90')
	rayEndPoints.push_back(new sf::Vector2f(17, -1));
	rayEndPointOrig.push_back(new sf::Vector2f(17, -1));
	rayEndPoints.push_back(new sf::Vector2f(3, 5));
	rayEndPointOrig.push_back(new sf::Vector2f(3, 5));
	rayEndPoints.push_back(new sf::Vector2f(-3, 19));
	rayEndPointOrig.push_back(new sf::Vector2f(-3, 19));

	// Right (0', 45', 90')
	rayEndPoints.push_back(new sf::Vector2f(82, -1));
	rayEndPointOrig.push_back(new sf::Vector2f(82, -1));
	rayEndPoints.push_back(new sf::Vector2f(95, 5));
	rayEndPointOrig.push_back(new sf::Vector2f(95, 5));
	rayEndPoints.push_back(new sf::Vector2f(102, 19));
	rayEndPointOrig.push_back(new sf::Vector2f(102, 19));

	thrusters.push_back(new Thruster(sf::Vector2f(27, 10), 0, false, "front"));
	thrusters.push_back(new Thruster(sf::Vector2f(73, 10), 0, false, "front"));

	//thrusters.push_back(new Thruster(sf::Vector2f(37, 2), 0, false, "front"));
	//thrusters.push_back(new Thruster(sf::Vector2f(63, 2), 0, false, "front"));

	thrusters.push_back(new Thruster(sf::Vector2f(20, 32), 0, false, "topleft"));
	thrusters.push_back(new Thruster(sf::Vector2f(80, 32), 0, false, "topright"));

	thrusters.push_back(new Thruster(sf::Vector2f(20, 37), 0, false, "topleft"));
	thrusters.push_back(new Thruster(sf::Vector2f(80, 37), 0, false, "topright"));

	thrusters.push_back(new Thruster(sf::Vector2f(8, 238), 0, false, "botleft"));
	thrusters.push_back(new Thruster(sf::Vector2f(92, 238), 0, false, "botright"));

	thrusters.push_back(new Thruster(sf::Vector2f(8, 243), 0, false, "botleft"));
	thrusters.push_back(new Thruster(sf::Vector2f(92, 243), 0, false, "botright"));
}

void Sniper::Update()
{
	chargeSound.setPosition(sf::Vector3f(shipSprite.getPosition().x, 0, shipSprite.getPosition().y));
	powerdownSound.setPosition(sf::Vector3f(shipSprite.getPosition().x, 0, shipSprite.getPosition().y));
	if (type == "player")
	{
		playerUpdate();
	}
	else if (type == "enemy" || type == "ally")
	{
		enemyUpdate();
	}
}

void Sniper::playerUpdate()
{
	shipSprite.setPosition(shipBody->GetPosition().x * SCALE, shipBody->GetPosition().y * SCALE);

	shipSprite.setRotation(shipBody->GetAngle() * (180.0f / b2_pi));

	if (fuel < 1000)
	{
		fuel += 1.0f;
	}

	for (int i = 0; i < firePoints.size(); i++)
	{
		firePoints.at(i).x = (shipSprite.getPosition().x - shipSprite.getTextureRect().width / 4) + firePointOrig.at(i).x;
		firePoints.at(i).y = (shipSprite.getPosition().y - shipSprite.getTextureRect().height / 4) + firePointOrig.at(i).y;

		float s1 = sin(shipSprite.getRotation() * 0.0174532925);
		float c1 = cos(shipSprite.getRotation() * 0.0174532925);

		// translate point back to origin:
		firePoints.at(i) = sf::Vector2f(firePoints.at(i).x - shipSprite.getPosition().x, firePoints.at(i).y - shipSprite.getPosition().y);
		// rotate point
		float xnew1 = firePoints.at(i).x * c1 - firePoints.at(i).y * s1;
		float ynew1 = firePoints.at(i).x * s1 + firePoints.at(i).y * c1;

		// translate point back:
		firePoints.at(i) = sf::Vector2f(xnew1 + shipSprite.getPosition().x, ynew1 + shipSprite.getPosition().y);
	}

	for (int i = 0; i < zapPoints.size(); i++)
	{
		zapPoints.at(i).x = (shipSprite.getPosition().x - shipSprite.getTextureRect().width / 4) + zapPointOrig.at(i).x;
		zapPoints.at(i).y = (shipSprite.getPosition().y - shipSprite.getTextureRect().height / 4) + zapPointOrig.at(i).y;

		float s1 = sin(shipSprite.getRotation() * 0.0174532925);
		float c1 = cos(shipSprite.getRotation() * 0.0174532925);

		// translate point back to origin:
		zapPoints.at(i) = sf::Vector2f(zapPoints.at(i).x - shipSprite.getPosition().x, zapPoints.at(i).y - shipSprite.getPosition().y);
		// rotate point
		float xnew1 = zapPoints.at(i).x * c1 - zapPoints.at(i).y * s1;
		float ynew1 = zapPoints.at(i).x * s1 + zapPoints.at(i).y * c1;

		// translate point back:
		zapPoints.at(i) = sf::Vector2f(xnew1 + shipSprite.getPosition().x, ynew1 + shipSprite.getPosition().y);
	}

	if (fireTimer < 350 && fireTimer > 306.5f)
	{
		chargeSprite.setFrame(0, true);
	}
	else if (fireTimer < 306.25 && fireTimer > 262.5f)
	{
		chargeSprite.setFrame(1, true);
	}
	else if (fireTimer < 262.5 && fireTimer > 218.75)
	{
		chargeSprite.setFrame(2, true);
	}
	else if (fireTimer < 218.75 && fireTimer > 175)
	{
		chargeSprite.setFrame(3, true);
	}
	else if (fireTimer < 175 && fireTimer > 131.25)
	{
		chargeSprite.setFrame(4, true);
	}
	else if (fireTimer < 131.25 && fireTimer > 87.5)
	{
		chargeSprite.setFrame(5, true);
	}
	else if (fireTimer < 87.5 && fireTimer > 43.75)
	{
		chargeSprite.setFrame(6, true);
	}
	else if (fireTimer < 43.75)
	{
		chargeSprite.setFrame(7, true);
	}

	chargeSprite.setPosition(shipSprite.getPosition());

	chargeSprite.setRotation(shipSprite.getRotation());

	updateBoosterPoints();

	for (int i = 0; i < thrusters.size(); i++)
	{
		thrusters.at(i)->active = false;
	}

	if (type == "player" && health > 0)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (cooldown == false)
			{
				if (shield == true)
				{
					shieldDuration = -1;
					shieldTimer = 480;
					shield = false;
					cloakx = 0;
					cloaky = 0;
					cloakx2 = 199;
					cloaky2 = 574;
					cloakwave = 0;
					cloakwave2 = 0;
					decloakTimer = 500;
					SoundManager::GetInstance()->CreateSound(shipSprite.getPosition(), 10);
				}

				float randZap = rand() % 29 + 1;

				AnimationManager::GetInstance()->CreateAnimation(zapPoints.at(30 - randZap), 14, shipSprite.getRotation() + 90);

				charging = true;

				powerdown = false;

				powerdownSound.stop();

				if (chargeSound.getStatus() == sf::Sound::Paused || chargeSound.getStatus() == sf::Sound::Stopped)
				{
					chargeSound.play();
					chargeSound.setVolume(30);
				}

				fireTimer--;

				if (fireTimer <= 0)
				{
					ProjectileManager::GetInstance()->CreateSlug(firePoints.at(0), shipSprite.getPosition(), shipSprite.getRotation(), false);
					SoundManager::GetInstance()->CreateSound(firePoints.at(0), 6);
					cooldown = true;
					powerdown = true;
				}
			}
			else
			{
				if (powerdown == false)
				{
					if (powerdownSound.getStatus() == sf::Sound::Paused || powerdownSound.getStatus() == sf::Sound::Stopped)
					{
						powerdownSound.play();
						powerdown = true;
					}
				}

				if (chargeSound.getVolume() > 0)
				{
					chargeSound.setVolume(chargeSound.getVolume() - 1);
				}
				if (chargeSound.getVolume() <= 3)
				{
					chargeSound.stop();
				}
				if (fireTimer < 350)
				{
					fireTimer += 2;
				}
				if (fireTimer >= 350)
				{
					cooldown = false;
				}
				else
				{
					cooldown = true;
				}
			}
		}
		else
		{
			if (powerdown == false)
			{
				if (powerdownSound.getStatus() == sf::Sound::Paused || powerdownSound.getStatus() == sf::Sound::Stopped)
				{
					powerdownSound.play();
					powerdown = true;
				}
			}

			if (chargeSound.getVolume() > 0)
			{
				chargeSound.setVolume(chargeSound.getVolume() - 1);
			}
			if (chargeSound.getVolume() <= 3)
			{
				chargeSound.stop();
			}
			if (fireTimer < 350)
			{
				fireTimer += 2;
			}

			if (fireTimer >= 350)
			{
				cooldown = false;
			}
			else
			{
				cooldown = true;
			}
		}

		if (manual == false)
		{
			sf::Vector2i mousePos;
			mousePos = sf::Mouse::getPosition(*Window);

			sf::Vector2f rotPoint = Window->mapPixelToCoords(mousePos);

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
			if (fireTimer < 350 && cooldown == false)
			{
				impulse = impulse / 4;
			}
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
		{
			manual = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		{
			manual = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			if (shieldTimer <= 0 && shieldDuration <= 0)
			{
				shield = true;
				shieldDuration = 1600;
				shieldTimer = 480;
				cloakTimer = 500;
				cloakBase.loadFromFile("Sniper.png");
				SoundManager::GetInstance()->CreateSound(shipSprite.getPosition(), 9);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			if (missileTimer < 0 && missileFiring == false)
			{
				missileFiring = true;

				missileTimer = 480;

				mineCount = 30;

				if (shield == true)
				{
					shieldDuration = -1;
					shieldTimer = 480;
					shield = false;
					cloakx = 0;
					cloaky = 0;
					cloakx2 = 199;
					cloaky2 = 574;
					cloakwave = 0;
					cloakwave2 = 0;
					decloakTimer = 500;
					SoundManager::GetInstance()->CreateSound(shipSprite.getPosition(), 10);
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			updateThrusterPoints();
			if (fireTimer < 350 && cooldown == false)
			{
				shipBody->ApplyAngularImpulse(-2.6 / 4, false);
			}
			else
			{
				shipBody->ApplyAngularImpulse(-2.86, false);
			}
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
			if (fireTimer < 350 && cooldown == false)
			{
				shipBody->ApplyAngularImpulse(2.86 / 4, false);
			}
			else
			{
				shipBody->ApplyAngularImpulse(2.86, false);
			}
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

			if (shield == true)
			{
				shieldDuration = -1;
				shieldTimer = 480;
				shield = false;
				cloakx = 0;
				cloaky = 0;
				cloakx2 = 199;
				cloaky2 = 574;
				cloakwave = 0;
				cloakwave2 = 0;
				decloakTimer = 500;
				SoundManager::GetInstance()->CreateSound(shipSprite.getPosition(), 10);
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
			shipBody->ApplyLinearImpulse(b2Vec2(-velocity.x, -velocity.y), shipBody->GetWorldCenter(), false);

			if (shield == true)
			{
				shieldDuration = -1;
				shieldTimer = 480;
				shield = false;
				cloakx = 0;
				cloaky = 0;
				cloakx2 = 199;
				cloaky2 = 574;
				cloakwave = 0;
				cloakwave2 = 0;
				decloakTimer = 500;
				SoundManager::GetInstance()->CreateSound(shipSprite.getPosition(), 10);
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
				WreckManager::GetInstance()->CreateWreck(sf::Vector2f(wreckPoint.at(i)->x, wreckPoint.at(i)->y), shipSprite.getRotation(), i + 6);
			}
		}
	}

	//missileTimer--;

	//speed = sqrt((shipBody->GetLinearVelocity().x * shipBody->GetLinearVelocity().x) + (shipBody->GetLinearVelocity().y * shipBody->GetLinearVelocity().y));


	boosterSprite.setScale(sf::Vector2f(0.5f, speed / 2.5f));

	sf::Time frameTime = frameClock.restart();

	chargeSprite.update(frameTime);

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

		if (cloakTimer > 0)
		{
			for (int i = 0; i < 4000; i++)
			{
				float tempx = rand() % 200;
				float tempy = rand() % 575;

				cloakBase.setPixel(tempx, tempy, cloak.getPixel(tempx, tempy));

				cloakx++;

				if (cloakx > 199)
				{
					cloakx = 0;
					cloaky++;
				}

				if (cloaky > 574)
				{
					cloaky = 0;
				}
			}

			/*for (int i = 0; i < 4000; i++)
			{
			float tempx = rand() % 200;
			float tempy;

			if (cloakwave == 0)
			{
			tempy = 0;
			}
			else
			{
			tempy = rand() % cloakwave + cloakwave2;
			}

			cloakBase.setPixel(tempx, tempy, cloak.getPixel(tempx, tempy));
			}

			cloakwave++;

			if (cloakwave > 74)
			{
			cloakwave = 74;
			}

			cloakwave2 = cloakwave2 + 4;

			if (cloakwave2 > 500)
			{
			cloakwave2 = 500;
			}

			for (int i = 0; i < 700; i++)
			{
			cloakBase.setPixel(cloakx, cloaky, cloak.getPixel(cloakx, cloaky));

			cloakx++;

			if (cloakx > 199)
			{
			cloakx = 0;
			cloaky++;
			}

			if (cloaky > 574)
			{
			cloaky = 0;
			}
			}*/

			/*for (int i = 0; i < 800; i++)
			{
			cloakBase.setPixel(cloakx, cloaky, cloak.getPixel(cloakx, cloaky));

			cloakx++;

			if (cloakx > 199)
			{
			cloakx = 0;
			cloaky++;
			}

			if (cloaky > 574)
			{
			cloaky = 0;
			}
			}*/

			//for (int i = 0; i < 800; i++)
			//{
			//	cloakBase.setPixel(cloakx2, cloaky2, cloak.getPixel(cloakx2, cloaky2));
			//	//	}
			//	//}
			//	cloakx2--;

			//	if (cloakx2 < 0)
			//	{
			//		cloakx2 = 199;
			//		cloaky2--;
			//	}

			//	if (cloaky2 < 0)
			//	{
			//		cloaky2 = 574;
			//	}
			//}

			shipTexture.update(cloakBase, 0, 0);

			if (boosterSprite.getColor().a > 0)
			{
				boosterSprite.setColor(sf::Color(255, 255, 255, boosterSprite.getColor().a - 3));
			}

			if (boosterSprite2.getColor().a > 0)
			{
				boosterSprite2.setColor(sf::Color(255, 255, 255, boosterSprite2.getColor().a - 3));
			}

			if (boosterSprite3.getColor().a > 0)
			{
				boosterSprite3.setColor(sf::Color(255, 255, 255, boosterSprite3.getColor().a - 3));
			}

			for (int i = 0; i < thrusters.size(); i++)
			{
				if (thrusters.at(i)->turretSprite.getColor().a > 0)
				{
					thrusters.at(i)->turretSprite.setColor(sf::Color(255, 255, 255, thrusters.at(i)->turretSprite.getColor().a - 3));
				}
			}

			cloakTimer--;
		}

		if (shieldDuration <= 0)
		{
			shieldDuration = -1;
			shieldTimer = 480;
			shield = false;
			SoundManager::GetInstance()->ShieldsOff();
			cloakx = 0;
			cloaky = 0;
			cloakx2 = 199;
			cloaky2 = 574;
			cloakwave = 0;
			cloakwave2 = 0;
			decloakTimer = 500;
			SoundManager::GetInstance()->CreateSound(shipSprite.getPosition(), 10);
		}
	}
	else if (shield == false)
	{
		shieldTimer--;
		speedBoost = false;

		if (decloakTimer > 0)
		{
			for (int i = 0; i < 4000; i++)
			{
				float tempx = rand() % 200;
				float tempy = rand() % 575;

				cloakBase.setPixel(tempx, tempy, defaultSniper.getPixel(tempx, tempy));

				cloakx++;

				if (cloakx > 199)
				{
					cloakx = 0;
					cloaky++;
				}

				if (cloaky > 574)
				{
					cloaky = 0;
				}
			}

			//for (int i = 0; i < 800; i++)
			//{
			//	cloakBase.setPixel(cloakx, cloaky, defaultSniper.getPixel(cloakx, cloaky));
			//	//	}
			//	//}
			//	cloakx++;

			//	if (cloakx > 199)
			//	{
			//		cloakx = 0;
			//		cloaky++;
			//	}

			//	if (cloaky > 574)
			//	{
			//		cloaky = 0;
			//	}
			//}

			shipTexture.update(cloakBase, 0, 0);

			if (boosterSprite.getColor().a < 255)
			{
				boosterSprite.setColor(sf::Color(255, 255, 255, boosterSprite.getColor().a + 3));
			}

			if (boosterSprite2.getColor().a < 255)
			{
				boosterSprite2.setColor(sf::Color(255, 255, 255, boosterSprite2.getColor().a + 3));
			}

			if (boosterSprite3.getColor().a < 255)
			{
				boosterSprite3.setColor(sf::Color(255, 255, 255, boosterSprite3.getColor().a + 3));
			}

			for (int i = 0; i < thrusters.size(); i++)
			{
				if (thrusters.at(i)->turretSprite.getColor().a < 255)
				{
					thrusters.at(i)->turretSprite.setColor(sf::Color(255, 255, 255, thrusters.at(i)->turretSprite.getColor().a + 3));
				}
			}

			decloakTimer--;
		}

		//if (shieldSprite.getColor().a > 2)
		//{
		//	shieldSprite.setColor(sf::Color(255, 255, 255, shieldSprite.getColor().a - 2));
		//	//boosterSprite2.setColor(sf::Color(255, 255, 255, boosterSprite2.getColor().a - 2));
		//	//boosterSprite3.setColor(sf::Color(255, 255, 255, boosterSprite3.getColor().a - 2));
		//}
	}

	if (missileFiring == true)
	{

		if (mineCount > 0)
		{
			float tempAngle = rand() % 60 + 20;

			if (mineLeft == true)
			{
				tempAngle = -tempAngle;
				mineLeft = false;
			}
			else
			{
				mineLeft = true;
			}

			ProjectileManager::GetInstance()->CreateMine(firePoints.at(1), shipSprite.getPosition(), shipSprite.getRotation() + tempAngle, false);

			mineCount--;
		}

		if (boosterSprite2.getColor().a < 255)
		{
			float trans = boosterSprite2.getColor().a + 10;
			if (trans > 255)
			{
				trans = 255;
			}
			boosterSprite2.setColor(sf::Color(255, 255, 255, trans));
			boosterSprite3.setColor(sf::Color(255, 255, 255, trans));
		}

		shipBody->ApplyLinearImpulse(b2Vec2((velocity.x  * 7.0f), (velocity.y * 7.0f)), shipBody->GetWorldCenter(), false);

		missileStep++;

		if (missileStep == 120)
		{
			missileTimer = 480;
			missileFiring = false;
			missileStep = 0;
		}
	}
	else if (missileFiring == false)
	{
		float trans = boosterSprite2.getColor().a - 10;
		if (trans < 0)
		{
			trans = 0;
		}
		boosterSprite2.setColor(sf::Color(255, 255, 255, trans));
		boosterSprite3.setColor(sf::Color(255, 255, 255, trans));
	}

	if (missileFiring == false)
	{
		if (missileTimer > -1)
		{
			missileTimer--;
		}
	}
}

void Sniper::enemyUpdate()
{
	healthBox.setPosition(shipSprite.getPosition().x, shipSprite.getPosition().y - 170);
	healthBar.setPosition(shipSprite.getPosition().x - 51, shipSprite.getPosition().y - 170);

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

	for (int i = 0; i < firePoints.size(); i++)
	{
		firePoints.at(i).x = (shipSprite.getPosition().x - shipSprite.getTextureRect().width / 4) + firePointOrig.at(i).x;
		firePoints.at(i).y = (shipSprite.getPosition().y - shipSprite.getTextureRect().height / 4) + firePointOrig.at(i).y;

		float s1 = sin(shipSprite.getRotation() * 0.0174532925);
		float c1 = cos(shipSprite.getRotation() * 0.0174532925);

		// translate point back to origin:
		firePoints.at(i) = sf::Vector2f(firePoints.at(i).x - shipSprite.getPosition().x, firePoints.at(i).y - shipSprite.getPosition().y);
		// rotate point
		float xnew1 = firePoints.at(i).x * c1 - firePoints.at(i).y * s1;
		float ynew1 = firePoints.at(i).x * s1 + firePoints.at(i).y * c1;

		// translate point back:
		firePoints.at(i) = sf::Vector2f(xnew1 + shipSprite.getPosition().x, ynew1 + shipSprite.getPosition().y);
	}

	for (int i = 0; i < zapPoints.size(); i++)
	{
		zapPoints.at(i).x = (shipSprite.getPosition().x - shipSprite.getTextureRect().width / 4) + zapPointOrig.at(i).x;
		zapPoints.at(i).y = (shipSprite.getPosition().y - shipSprite.getTextureRect().height / 4) + zapPointOrig.at(i).y;

		float s1 = sin(shipSprite.getRotation() * 0.0174532925);
		float c1 = cos(shipSprite.getRotation() * 0.0174532925);

		// translate point back to origin:
		zapPoints.at(i) = sf::Vector2f(zapPoints.at(i).x - shipSprite.getPosition().x, zapPoints.at(i).y - shipSprite.getPosition().y);
		// rotate point
		float xnew1 = zapPoints.at(i).x * c1 - zapPoints.at(i).y * s1;
		float ynew1 = zapPoints.at(i).x * s1 + zapPoints.at(i).y * c1;

		// translate point back:
		zapPoints.at(i) = sf::Vector2f(xnew1 + shipSprite.getPosition().x, ynew1 + shipSprite.getPosition().y);
	}

	if (fireTimer < 350 && fireTimer > 306.5f)
	{
		chargeSprite.setFrame(0, true);
	}
	else if (fireTimer < 306.25 && fireTimer > 262.5f)
	{
		chargeSprite.setFrame(1, true);
	}
	else if (fireTimer < 262.5 && fireTimer > 218.75)
	{
		chargeSprite.setFrame(2, true);
	}
	else if (fireTimer < 218.75 && fireTimer > 175)
	{
		chargeSprite.setFrame(3, true);
	}
	else if (fireTimer < 175 && fireTimer > 131.25)
	{
		chargeSprite.setFrame(4, true);
	}
	else if (fireTimer < 131.25 && fireTimer > 87.5)
	{
		chargeSprite.setFrame(5, true);
	}
	else if (fireTimer < 87.5 && fireTimer > 43.75)
	{
		chargeSprite.setFrame(6, true);
	}
	else if (fireTimer < 43.75)
	{
		chargeSprite.setFrame(7, true);
	}

	chargeSprite.setPosition(shipSprite.getPosition());

	chargeSprite.setRotation(shipSprite.getRotation());

	updateBoosterPoints();

	updateRayPoints();

	for (int i = 0; i < thrusters.size(); i++)
	{
		thrusters.at(i)->active = false;
	}

	if (firing == false)
	{
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
			if (fireTimer < 350 && cooldown == false)
			{
				impulse = impulse / 2;
			}

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
		shipBody->ApplyLinearImpulse(b2Vec2(-velocity.x, -velocity.y), shipBody->GetWorldCenter(), false);

		if (shield == true)
		{
			shieldDuration = -1;
			shieldTimer = 700;
			shield = false;
			cloakx = 0;
			cloaky = 0;
			cloakx2 = 199;
			cloaky2 = 574;
			cloakwave = 0;
			cloakwave2 = 0;
			decloakTimer = 500;
			SoundManager::GetInstance()->CreateSound(shipSprite.getPosition(), 10);
		}

		if (speed < 1)
		{
			speed += 0.01f;
		}
		break;
	case(MoveState::BACKWARDS) :
		updateThrusterPoints();
		shipBody->ApplyLinearImpulse(b2Vec2(velocity.x / 2, velocity.y / 2), shipBody->GetWorldCenter(), false);

		if (shield == true)
		{
			shieldDuration = -1;
			shieldTimer = 700;
			shield = false;
			cloakx = 0;
			cloaky = 0;
			cloakx2 = 199;
			cloaky2 = 574;
			cloakwave = 0;
			cloakwave2 = 0;
			decloakTimer = 500;
			SoundManager::GetInstance()->CreateSound(shipSprite.getPosition(), 10);
		}

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
		followPoint = targetShip->getSprite().getPosition();
		//AbilityOne();
		//AbilityTwo();
		break;
	case(FireState::NONE3) :
		firing = false;
		break;
	}

	if (health > 0)
	{
		if (firing == true && shield == false)
		{
			if (cooldown == false)
			{
				if (shield == true)
				{
					shieldDuration = -1;
					shieldTimer = 700;
					shield = false;
					cloakx = 0;
					cloaky = 0;
					cloakx2 = 199;
					cloaky2 = 574;
					cloakwave = 0;
					cloakwave2 = 0;
					decloakTimer = 500;
					SoundManager::GetInstance()->CreateSound(shipSprite.getPosition(), 10);
				}

				float randZap = rand() % 29 + 1;

				AnimationManager::GetInstance()->CreateAnimation(zapPoints.at(30 - randZap), 14, shipSprite.getRotation() + 90);

				charging = true;

				powerdown = false;

				powerdownSound.stop();

				if (chargeSound.getStatus() == sf::Sound::Paused || chargeSound.getStatus() == sf::Sound::Stopped)
				{
					chargeSound.play();
					chargeSound.setVolume(30);
				}

				fireTimer--;

				if (fireTimer <= 0)
				{
					if (type == "enemy")
					{
						ProjectileManager::GetInstance()->CreateSlug(firePoints.at(0), shipSprite.getPosition(), shipSprite.getRotation(), true);
					}
					else
					{
						ProjectileManager::GetInstance()->CreateSlug(firePoints.at(0), shipSprite.getPosition(), shipSprite.getRotation(), false);
					}
					SoundManager::GetInstance()->CreateSound(firePoints.at(0), 6);
					cooldown = true;
					powerdown = true;
				}
			}
			else
			{
				if (powerdown == false)
				{
					if (powerdownSound.getStatus() == sf::Sound::Paused || powerdownSound.getStatus() == sf::Sound::Stopped)
					{
						powerdownSound.play();
						powerdown = true;
					}
				}

				if (chargeSound.getVolume() > 0)
				{
					chargeSound.setVolume(chargeSound.getVolume() - 1);
				}
				if (chargeSound.getVolume() <= 3)
				{
					chargeSound.stop();
				}
				if (fireTimer < 350)
				{
					fireTimer += 2;
				}
				if (fireTimer >= 350)
				{
					cooldown = false;
				}
				else
				{
					cooldown = true;
				}
			}
		}
		else
		{
			if (powerdown == false)
			{
				if (powerdownSound.getStatus() == sf::Sound::Paused || powerdownSound.getStatus() == sf::Sound::Stopped)
				{
					powerdownSound.play();
					powerdown = true;
				}
			}

			if (chargeSound.getVolume() > 0)
			{
				chargeSound.setVolume(chargeSound.getVolume() - 1);
			}
			if (chargeSound.getVolume() <= 3)
			{
				chargeSound.stop();
			}
			if (fireTimer < 350)
			{
				fireTimer += 2;
			}

			if (fireTimer >= 350)
			{
				cooldown = false;
			}
			else
			{
				cooldown = true;
			}
		}
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
					tempX = shipSprite.getPosition().x + rand() % 60 + 1;
					tempY = shipSprite.getPosition().y + rand() % 60 + 1;
				}
				else if (temp == 2)
				{
					tempX = shipSprite.getPosition().x - rand() % 60 + 1;
					tempY = shipSprite.getPosition().y + rand() % 60 + 1;
				}
				else if (temp == 3)
				{
					tempX = shipSprite.getPosition().x + rand() % 60 + 1;
					tempY = shipSprite.getPosition().y - rand() % 70 + 1;
				}
				else if (temp == 4)
				{
					tempX = shipSprite.getPosition().x - rand() % 60 + 1;
					tempY = shipSprite.getPosition().y - rand() % 60 + 1;
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
				WreckManager::GetInstance()->CreateWreck(sf::Vector2f(wreckPoint.at(i)->x, wreckPoint.at(i)->y), shipSprite.getRotation(), i + 6);
			}
		}
	}

	boosterSprite.setScale(sf::Vector2f(0.5f, speed / 2.5f));

	sf::Time frameTime = frameClock.restart();

	chargeSprite.update(frameTime);

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
		if (shipSprite.getColor().a > 3)
		{
			shipSprite.setColor(sf::Color(255, 255, 255, shipSprite.getColor().a - 2));
			healthBox.setColor(sf::Color(255, 255, 255, healthBox.getColor().a - 2));
			healthBar.setColor(sf::Color(255, 255, 255, healthBar.getColor().a - 2));
		}
		if (shipSprite.getColor().a < 3)
		{
			shipSprite.setColor(sf::Color(255, 255, 255, 0));
			healthBox.setColor(sf::Color(255, 255, 255, 0));
			healthBar.setColor(sf::Color(255, 255, 255, 0));
		}

		shieldDuration--;

		speedBoost = true;

		if (cloakTimer > 0)
		{
			for (int i = 0; i < 4000; i++)
			{
				float tempx = rand() % 200;
				float tempy = rand() % 575;

				cloakBase.setPixel(tempx, tempy, cloak.getPixel(tempx, tempy));

				cloakx++;

				if (cloakx > 199)
				{
					cloakx = 0;
					cloaky++;
				}

				if (cloaky > 574)
				{
					cloaky = 0;
				}
			}

			shipTexture.update(cloakBase, 0, 0);

			if (boosterSprite.getColor().a > 0)
			{
				boosterSprite.setColor(sf::Color(255, 255, 255, boosterSprite.getColor().a - 3));
			}

			if (boosterSprite2.getColor().a > 0)
			{
				boosterSprite2.setColor(sf::Color(255, 255, 255, boosterSprite2.getColor().a - 3));
			}

			if (boosterSprite3.getColor().a > 0)
			{
				boosterSprite3.setColor(sf::Color(255, 255, 255, boosterSprite3.getColor().a - 3));
			}

			for (int i = 0; i < thrusters.size(); i++)
			{
				if (thrusters.at(i)->turretSprite.getColor().a > 0)
				{
					thrusters.at(i)->turretSprite.setColor(sf::Color(255, 255, 255, thrusters.at(i)->turretSprite.getColor().a - 3));
				}
			}

			cloakTimer--;
		}

		if (shieldDuration <= 0)
		{
			shieldDuration = -1;
			shieldTimer = 700;
			shield = false;
			SoundManager::GetInstance()->ShieldsOff();
			cloakx = 0;
			cloaky = 0;
			cloakx2 = 199;
			cloaky2 = 574;
			cloakwave = 0;
			cloakwave2 = 0;
			decloakTimer = 500;
			SoundManager::GetInstance()->CreateSound(shipSprite.getPosition(), 10);
		}
	}
	else if (shield == false)
	{
		if (shipSprite.getColor().a < 255)
		{
			shipSprite.setColor(sf::Color(255, 255, 255, shipSprite.getColor().a + 2));
			healthBox.setColor(sf::Color(255, 255, 255, healthBox.getColor().a + 2));
			healthBar.setColor(sf::Color(255, 255, 255, healthBar.getColor().a + 2));
		}
		if (shipSprite.getColor().a > 250)
		{
			shipSprite.setColor(sf::Color(255, 255, 255, 255));
			healthBox.setColor(sf::Color(255, 255, 255, 255));
			healthBar.setColor(sf::Color(255, 255, 255, 255));
		}

		shieldTimer--;
		speedBoost = false;

		if (decloakTimer > 0)
		{
			for (int i = 0; i < 4000; i++)
			{
				float tempx = rand() % 200;
				float tempy = rand() % 575;

				cloakBase.setPixel(tempx, tempy, defaultSniper.getPixel(tempx, tempy));

				cloakx++;

				if (cloakx > 199)
				{
					cloakx = 0;
					cloaky++;
				}

				if (cloaky > 574)
				{
					cloaky = 0;
				}
			}

			shipTexture.update(cloakBase, 0, 0);

			if (boosterSprite.getColor().a < 255)
			{
				boosterSprite.setColor(sf::Color(255, 255, 255, boosterSprite.getColor().a + 3));
			}

			if (boosterSprite2.getColor().a < 255)
			{
				boosterSprite2.setColor(sf::Color(255, 255, 255, boosterSprite2.getColor().a + 3));
			}

			if (boosterSprite3.getColor().a < 255)
			{
				boosterSprite3.setColor(sf::Color(255, 255, 255, boosterSprite3.getColor().a + 3));
			}

			for (int i = 0; i < thrusters.size(); i++)
			{
				if (thrusters.at(i)->turretSprite.getColor().a < 255)
				{
					thrusters.at(i)->turretSprite.setColor(sf::Color(255, 255, 255, thrusters.at(i)->turretSprite.getColor().a + 3));
				}
			}

			decloakTimer--;
		}
	}

	if (missileFiring == true)
	{

		if (mineCount > 0)
		{
			float tempAngle = rand() % 60 + 20;

			if (mineLeft == true)
			{
				tempAngle = -tempAngle;
				mineLeft = false;
			}
			else
			{
				mineLeft = true;
			}

			if (type == "enemy")
			{
				ProjectileManager::GetInstance()->CreateMine(firePoints.at(1), shipSprite.getPosition(), shipSprite.getRotation() + tempAngle, true);
			}
			else if(type == "ally")
			{
				ProjectileManager::GetInstance()->CreateMine(firePoints.at(1), shipSprite.getPosition(), shipSprite.getRotation() + tempAngle, false);
			}

			mineCount--;
		}

		if (boosterSprite2.getColor().a < 255)
		{
			float trans = boosterSprite2.getColor().a + 10;
			if (trans > 255)
			{
				trans = 255;
			}
			boosterSprite2.setColor(sf::Color(255, 255, 255, trans));
			boosterSprite3.setColor(sf::Color(255, 255, 255, trans));
		}

		shipBody->ApplyLinearImpulse(b2Vec2((velocity.x  * 7.0f), (velocity.y * 7.0f)), shipBody->GetWorldCenter(), false);

		missileStep++;

		if (missileStep == 120)
		{
			missileTimer = 1200;
			missileFiring = false;
			missileStep = 0;
		}
	}
	else if (missileFiring == false)
	{
		float trans = boosterSprite2.getColor().a - 10;
		if (trans < 0)
		{
			trans = 0;
		}
		boosterSprite2.setColor(sf::Color(255, 255, 255, trans));
		boosterSprite3.setColor(sf::Color(255, 255, 255, trans));
	}

	if (missileFiring == false)
	{
		if (missileTimer > -1)
		{
			missileTimer--;
		}
	}
}

void Sniper::chooseNextAction()
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
				if (dist < 2000)
				{
					if (dist < shortestDist)
					{
						currentTState = FOLLOW;
						currentMState = NONE2;
						shortestDist = dist;
						targetShip = ShipManager::GetInstance()->ships.at(i);
						targetPos = targetShip->getSprite().getPosition();
						followPoint = targetShip->getSprite().getPosition();
						enemyNearby = true;
					}
				}
			}
		}
	}

	if (shortestDist < 1000)
	{
		if (shieldTimer <= 0 && shieldDuration <= 0)
		{
			currentTState = NONE;
			currentMState = NONE2;
			AbilityTwo();
		}
	}

	if (shortestDist < 300)
	{
		AbilityOne();
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

void Sniper::chooseNextActionAlly()
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
				if (dist < 2000)
				{
					if (dist < shortestDist)
					{
						currentTState = FOLLOW;
						currentMState = NONE2;
						shortestDist = dist;
						targetShip = ShipManager::GetInstance()->ships.at(i);
						targetPos = targetShip->getSprite().getPosition();
						followPoint = targetShip->getSprite().getPosition();
						enemyNearby = true;
					}
				}
			}
		}
	}

	if (shortestDist < 1000)
	{
		if (shieldTimer <= 0 && shieldDuration <= 0)
		{
			currentTState = NONE;
			currentMState = NONE2;
			AbilityTwo();
		}
	}

	if (shortestDist < 300)
	{
		AbilityOne();
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

void Sniper::AbilityOne()
{
	if (missileTimer < 0 && missileFiring == false)
	{
		missileFiring = true;

		missileTimer = 1200;

		mineCount = 30;

		if (shield == true)
		{
			shieldDuration = -1;
			shieldTimer = 700;
			shield = false;
			cloakx = 0;
			cloaky = 0;
			cloakx2 = 199;
			cloaky2 = 574;
			cloakwave = 0;
			cloakwave2 = 0;
			decloakTimer = 500;
			SoundManager::GetInstance()->CreateSound(shipSprite.getPosition(), 10);
		}
	}
}

void Sniper::AbilityTwo()
{
	if (shieldTimer <= 0 && shieldDuration <= 0)
	{
		shield = true;
		shieldDuration = 1600;
		shieldTimer = 700;
		cloakTimer = 500;

		SoundManager::GetInstance()->CreateSound(shipSprite.getPosition(), 9);

		if (type == "enemy")
		{
			cloakBase.loadFromFile("SniperEnemy.png");
		}
		else if (type == "ally")
		{
			cloakBase.loadFromFile("SniperAlly.png");
		}
	}
}

void Sniper::setHealth(float h)
{
	health = h;

	if (shield == true)
	{
		shieldDuration = -1;
		shieldTimer = 700;
		shield = false;
		cloakx = 0;
		cloaky = 0;
		cloakx2 = 199;
		cloaky2 = 574;
		cloakwave = 0;
		cloakwave2 = 0;
		decloakTimer = 500;
	}
}

void Sniper::Draw(sf::RenderWindow & window)
{
	for (int i = 0; i < thrusters.size(); i++)
	{
		thrusters.at(i)->Draw(window);
	}

	window.draw(boosterSprite);
	window.draw(boosterSprite2);
	window.draw(boosterSprite3);
	window.draw(shipSprite);

	if (fireTimer < 350)
	{
		window.draw(chargeSprite);
	}

	if (type == "enemy" || type == "ally")
	{
		window.draw(healthBox);
		window.draw(healthBar);
	}
}

void Sniper::CreateBody()
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

void Sniper::updateMissilePoints()
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

void Sniper::updateRayPoints()
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

void Sniper::updateThrusterPoints()
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

void Sniper::updateWreckPoints()
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

void Sniper::updateBoosterPoints()
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

void Sniper::DeleteAll()
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

