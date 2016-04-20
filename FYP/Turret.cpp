#include "Turret.h"
#include "Ship.h"

static const float SCALE = 30.f;

Turret::Turret(sf::Vector2f p, Ship& s, string t, string w1, sf::RenderWindow & w, b2World& wrld)
{
	type = t;

	world = &wrld;

	weaponType = w1;

	prevImpact = sf::Vector2f(0, 0);

	if (weaponType == "Plasma")
	{
		if (!turretTexture.loadFromFile("Turret5.png"))
		{
			// error...
		}
	}
	if (weaponType == "Laser")
	{
		if (!turretTexture.loadFromFile("LaserTurret3.png"))
		{
			// error...
		}
	}

	if (!laserSound.loadFromFile("laser.ogg"))
	{

	}

	laser.setBuffer(laserSound);
	laser.pause();
	laser.setPosition(sf::Vector3f(turretSprite.getPosition().x, 0, turretSprite.getPosition().y));
	laser.setLoop(true);
	laser.setVolume(40);
	laser.setRelativeToListener(false);
	laser.setAttenuation(20);
	laser.setMinDistance(1000);
	laser.setPitch(1.1);

	if (!steamSound.loadFromFile("ventSound.ogg"))
	{

	}

	steam.setBuffer(steamSound);
	steam.pause();
	steam.setPosition(sf::Vector3f(turretSprite.getPosition().x, 0, turretSprite.getPosition().y));
	steam.setLoop(false);
	steam.setVolume(80);
	steam.setRelativeToListener(false);
	steam.setAttenuation(20);
	steam.setMinDistance(1000);
	steam.setPitch(0.6);

	turretTexture.setSmooth(true);

	turretSprite.setTexture(turretTexture);

	position = p;

	turretSprite.setScale(sf::Vector2f(0.5f, 0.5f));

	turretSprite.setPosition(sf::Vector2f(position.x, position.y));

	turretSprite.setOrigin(sf::Vector2f(45, 45));

	if (!laserTexture.loadFromFile("Laser2.png"))
	{
		// error...
	}

	laserTexture.setSmooth(true);

	laserBeam.setTexture(laserTexture);

	laserBeam.setScale(sf::Vector2f(0.5f, 0.5f));

	laserBeam.setPosition(sf::Vector2f(position.x, position.y));

	laserBeam.setOrigin(sf::Vector2f(5, 0));

	laserBeam.setColor(sf::Color(255, 255, 255, 0));

	if (!impactTexture.loadFromFile("Impact.png"))
	{
		// error...
	}

	impactTexture.setSmooth(true);

	impact.setTexture(impactTexture);

	impact.setScale(sf::Vector2f(0.2f, 0.2f));

	impact.setPosition(sf::Vector2f(position.x, position.y));

	impact.setOrigin(sf::Vector2f(70, 100));

	impact.setColor(sf::Color(255, 255, 255, 0));

	if (!heatTexture.loadFromFile("TurretHeat.png"))
	{
		// error...
	}

	heatTexture.setSmooth(true);

	heat.setTexture(heatTexture);

	heat.setScale(sf::Vector2f(0.5f, 0.5f));

	heat.setPosition(sf::Vector2f(position.x, position.y));

	heat.setOrigin(sf::Vector2f(45, 45));

	heat.setColor(sf::Color(255, 255, 255, 0));

	if (!ventTexture.loadFromFile("Vent.png"))
	{
		// error...
	}

	ventTexture.setSmooth(true);

	vent.setTexture(ventTexture);

	vent.setScale(sf::Vector2f(0.5f, 0.5f));

	vent.setPosition(sf::Vector2f(position.x, position.y));

	vent.setOrigin(sf::Vector2f(50, 50));

	vent.setColor(sf::Color(255, 255, 255, 0));

	ship = &s;
	
	window = &w;

	overheated = false;

	heatTimer = 70;

	fireTimer = 0;

	rayCallBack = new RayCastCallBackCustom();

	turretSprite.setPosition((ship->getSprite().getPosition().x - ship->getSprite().getTextureRect().width / 4) + position.x, (ship->getSprite().getPosition().y - ship->getSprite().getTextureRect().height / 4) + position.y);

	if (weaponType == "Plasma")
	{
		firePoint1 = sf::Vector2f(11, 2);
		firePoint2 = sf::Vector2f(18, 0);
		firePoint3 = sf::Vector2f(27, 0);
		firePoint4 = sf::Vector2f(34, 2);

		firePointOrig.push_back(firePoint1);
		firePointOrig.push_back(firePoint2);
		firePointOrig.push_back(firePoint3);
		firePointOrig.push_back(firePoint4);

		firePoints.push_back(sf::Vector2f(11, 2));
		firePoints.push_back(sf::Vector2f(18, 0));
		firePoints.push_back(sf::Vector2f(27, 0));
		firePoints.push_back(sf::Vector2f(34, 2));
	}
	if (weaponType == "Laser")
	{
		firePoint1 = sf::Vector2f(22.5, 0);

		firePointOrig.push_back(firePoint1);

		firePoints.push_back(sf::Vector2f(22.5, 0));
	}

	for (int i = 0; i < firePoints.size(); i++)
	{
		firePoints.at(i).x = (turretSprite.getPosition().x - turretSprite.getTextureRect().width / 4) + firePointOrig.at(i).x;
		firePoints.at(i).y = (turretSprite.getPosition().y - turretSprite.getTextureRect().height / 4) + firePointOrig.at(i).y;
	}

	//turretSprite.setRotation(45);

	/*
		11, 2
		18, 0
		27, 0
		34, 2

		22, 5
		37, 0
		54, 0
		69, 5
	*/
}

void Turret::Update()
{
	laser.setPosition(sf::Vector3f(turretSprite.getPosition().x, 0, turretSprite.getPosition().y));

	steam.setPosition(sf::Vector3f(turretSprite.getPosition().x, 0, turretSprite.getPosition().y));

	turretSprite.setPosition((ship->getSprite().getPosition().x - ship->getSprite().getTextureRect().width / 4) + position.x, (ship->getSprite().getPosition().y - ship->getSprite().getTextureRect().height / 4) + position.y);

	float s = sin(ship->getSprite().getRotation() * 0.0174532925);
	float c = cos(ship->getSprite().getRotation() * 0.0174532925);

	// translate point back to origin:
	turretSprite.setPosition(turretSprite.getPosition().x - ship->getSprite().getPosition().x, turretSprite.getPosition().y - ship->getSprite().getPosition().y);

	// rotate point
	float xnew = turretSprite.getPosition().x * c - turretSprite.getPosition().y * s;
	float ynew = turretSprite.getPosition().x * s + turretSprite.getPosition().y * c;

	// translate point back:
	turretSprite.setPosition(xnew + ship->getSprite().getPosition().x, ynew + ship->getSprite().getPosition().y);

	for (int i = 0; i < firePoints.size(); i++)
	{
		firePoints.at(i).x = (turretSprite.getPosition().x - turretSprite.getTextureRect().width / 4) + firePointOrig.at(i).x;
		firePoints.at(i).y = (turretSprite.getPosition().y - turretSprite.getTextureRect().height / 4) + firePointOrig.at(i).y;

		float s1 = sin(turretSprite.getRotation() * 0.0174532925);
		float c1 = cos(turretSprite.getRotation() * 0.0174532925);

		// translate point back to origin:
		firePoints.at(i) = sf::Vector2f(firePoints.at(i).x - turretSprite.getPosition().x, firePoints.at(i).y - turretSprite.getPosition().y);
		// rotate point
		float xnew1 = firePoints.at(i).x * c1 - firePoints.at(i).y * s1;
		float ynew1 = firePoints.at(i).x * s1 + firePoints.at(i).y * c1;

		// translate point back:
		firePoints.at(i) = sf::Vector2f(xnew1 + turretSprite.getPosition().x, ynew1 + turretSprite.getPosition().y);
	}

	if (type == "player")
	{
		laserBeam.setColor(sf::Color(255, 255, 255, 0));

		impact.setColor(sf::Color(255, 255, 255, 0));

		if (weaponType == "Plasma")
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (ship->getFuel() > 1 && ship->noFuel == false)
				{
					if (fireTimer < 60 && fireTimer > 45)
					{
						if (fireOnce1 == false)
						{
							ProjectileManager::GetInstance()->CreateProjectile(firePoints.at(0), turretSprite.getPosition(), turretSprite.getRotation(), false);
							AnimationManager::GetInstance()->CreateAnimation(firePoints.at(0), 2, turretSprite.getRotation() + 90);
							SoundManager::GetInstance()->CreateSound(firePoints.at(0), 2);
							fireOnce1 = true;
						}
					}
					if (fireTimer < 45 && fireTimer > 30)
					{
						if (fireOnce2 == false)
						{
							ProjectileManager::GetInstance()->CreateProjectile(firePoints.at(1), turretSprite.getPosition(), turretSprite.getRotation(), false);
							AnimationManager::GetInstance()->CreateAnimation(firePoints.at(1), 2, turretSprite.getRotation() + 90);
							SoundManager::GetInstance()->CreateSound(firePoints.at(1), 2);
							fireOnce2 = true;
						}
					}
					if (fireTimer < 30 && fireTimer > 15)
					{
						if (fireOnce3 == false)
						{
							ProjectileManager::GetInstance()->CreateProjectile(firePoints.at(2), turretSprite.getPosition(), turretSprite.getRotation(), false);
							AnimationManager::GetInstance()->CreateAnimation(firePoints.at(2), 2, turretSprite.getRotation() + 90);
							SoundManager::GetInstance()->CreateSound(firePoints.at(2), 2);
							fireOnce3 = true;
						}
					}
					if (fireTimer < 15 && fireTimer > 0)
					{
						if (fireOnce4 == false)
						{
							ProjectileManager::GetInstance()->CreateProjectile(firePoints.at(3), turretSprite.getPosition(), turretSprite.getRotation(), false);
							AnimationManager::GetInstance()->CreateAnimation(firePoints.at(3), 2, turretSprite.getRotation() + 90);
							SoundManager::GetInstance()->CreateSound(firePoints.at(3), 2);
							fireOnce4 = true;
						}
						//for (int i = 0; i < firePoints.size(); i++)
						//{
						//	ProjectileManager::GetInstance()->CreateProjectile(firePoints.at(i), turretSprite.getPosition(), turretSprite.getRotation());
						//}
					}
					if (fireTimer < 0)
					{
						fireTimer = 60;
						fireOnce1 = false;
						fireOnce2 = false;
						fireOnce3 = false;
						fireOnce4 = false;
					}
					ship->setFuel(ship->getFuel() - 0.5f);
				}
			}
		}
		if (weaponType == "Laser")
		{
			if (laserActive == false)
			{
				if (laser.getVolume() > 0)
				{
					laser.setVolume(laser.getVolume() - 2);
				}
				if (laser.getVolume() <= 5)
				{
					laser.pause();
				}
			}
			else if (laserActive == true)
			{
				if (laser.getVolume() < 40)
				{
					laser.setVolume(laser.getVolume() + 2);
				}
			}

			heat.setPosition(turretSprite.getPosition());
			heat.setRotation(turretSprite.getRotation());

			vent.setPosition(turretSprite.getPosition());
			vent.setRotation(turretSprite.getRotation());

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && overheated == false)
			{
				if (ship->getFuel() > 1)
				{
					//ProjectileManager::GetInstance()->CreateProjectile(firePoints.at(0), turretSprite.getPosition(), turretSprite.getRotation());
					//AnimationManager::GetInstance()->CreateAnimation(firePoints.at(0), 2, turretSprite.getRotation() + 90);
					//SoundManager::GetInstance()->CreateSound(firePoints.at(0), 2);

					rayCallBack->Reset();

					b2Vec2 startPoint;
					startPoint.x = turretSprite.getPosition().x / SCALE;
					startPoint.y = turretSprite.getPosition().y / SCALE;
					b2Vec2 endPoint;
					endPoint.x = (turretSprite.getPosition().x + ((firePoints.at(0).x - turretSprite.getPosition().x) * 25)) / SCALE;
					endPoint.y = (turretSprite.getPosition().y + ((firePoints.at(0).y - turretSprite.getPosition().y) * 25)) / SCALE;

					world->RayCast(rayCallBack, startPoint, endPoint);

					bool hit = false;

					if (rayCallBack->objectName == "bound")
					{
						hit = true;
					}
					if (rayCallBack->objectName == "enemy")
					{
						static_cast<Ship*>(rayCallBack->data)->setHealth(static_cast<Ship*>(rayCallBack->data)->getHealth() - 2);
						hit = true;
					}
					if (rayCallBack->objectName == "wreck")
					{
						static_cast<Wreck*>(rayCallBack->data)->setTTL(static_cast<Wreck*>(rayCallBack->data)->getTTL() - 5);
						hit = true;
					}
					if (hit == true)
					{
						beamImpact.x = (rayCallBack->m_point.x * SCALE) + (firePoints.at(0).x - turretSprite.getPosition().x);
						beamImpact.y = (rayCallBack->m_point.y * SCALE) + (firePoints.at(0).y - turretSprite.getPosition().y);
						laserBeam.setPosition(firePoints.at(0));
						laserBeam.setRotation(turretSprite.getRotation() - 180);
						laserBeam.setColor(sf::Color(255, 255, 255, 255));
						sf::IntRect temp = laserBeam.getTextureRect();
						temp.height = (sqrt(((firePoints.at(0).x - beamImpact.x) * (firePoints.at(0).x - beamImpact.x)) + ((firePoints.at(0).y - beamImpact.y) * (firePoints.at(0).y - beamImpact.y))) * 2);
						laserBeam.setTextureRect(temp);

						impact.setRotation(turretSprite.getRotation() - 180);
						impact.setColor(sf::Color(255, 255, 255, 255));
						impact.setPosition(beamImpact);

						if (laser.getPitch() < 1.853)
						{
							laser.setPitch(laser.getPitch() + 0.003f);
						}
						if (laser.getPitch() > 1.853)
						{
							laser.setPitch(1.85300529f);
						}

						if (heat.getColor().a < 255)
						{
							heat.setColor(sf::Color(255, 255, 255, heat.getColor().a + 1));
						}
						if (heat.getColor().a > 250)
						{
							heat.setColor(sf::Color(255, 255, 255, 255));
							overheated = true;
							steam.play();
						}

						rayCallBack->Reset();

						if (released == true)
						{
							prevImpact = beamImpact;
							released = false;
							//SoundManager::GetInstance()->LaserOn();
							laser.play();
							laserActive = true;
						}

						if (timer <= 0)
						{
							if (distance(beamImpact, prevImpact) > 100)
							{
								prevImpact = beamImpact;
							}
							AnimationManager::GetInstance()->AddBurn(prevImpact, beamImpact);
							prevImpact = beamImpact;
							timer = 3;
						}

						timer--;
					}
					else
					{
						laserBeam.setPosition(firePoints.at(0));
						laserBeam.setRotation(turretSprite.getRotation() - 180);
						laserBeam.setColor(sf::Color(255, 255, 255, 255));
						sf::IntRect temp = laserBeam.getTextureRect();
						temp.height = 1100;// (sqrt(((firePoints.at(0).x - beamImpact.x) * (firePoints.at(0).x - beamImpact.x)) + ((firePoints.at(0).y - beamImpact.y) * (firePoints.at(0).y - beamImpact.y))) * 2);
						laserBeam.setTextureRect(temp);

						if (released2 == true)
						{
							released2 = false;
							laser.play();
							laserActive = true;
							//SoundManager::GetInstance()->LaserOn();
						}

						if (laser.getPitch() < 1.853)
						{
							laser.setPitch(laser.getPitch() + 0.003f);
						}
						if (laser.getPitch() > 1.853)
						{
							laser.setPitch(1.85300529f);
						}

						if (heat.getColor().a < 255)
						{
							heat.setColor(sf::Color(255, 255, 255, heat.getColor().a + 1));
						}
						if (heat.getColor().a > 250)
						{
							heat.setColor(sf::Color(255, 255, 255, 255));
							overheated = true;
							steam.play();
						}

						//impact.setRotation(turretSprite.getRotation() - 180);
						//impact.setColor(sf::Color(255, 255, 255, 255));
						//impact.setPosition(sf::Vector2f((firePoints.at(0).x - turretSprite.getPosition().x) * 25, (firePoints.at(0).y - turretSprite.getPosition().y) * 25));
					}



					//ship->setFuel(ship->getFuel() - 0.5f);
				}
			}
			else
			{
				released = true;
				released2 = true;
				//SoundManager::GetInstance()->LaserOff();
				//laser.pause();
				laserActive = false;

				if (laser.getPitch() > 1.1)
				{
					laser.setPitch(laser.getPitch() - 0.003f);
				}
				else if (laser.getPitch() < 1.1)
				{
					laser.setPitch(1.1f);
				}

				if (overheated == false)
				{
					if (heat.getColor().a > 2)
					{
						heat.setColor(sf::Color(255, 255, 255, heat.getColor().a - 2));
					}
					if (heat.getColor().a <= 2)
					{
						heat.setColor(sf::Color(255, 255, 255, 0));
						overheated = false;
					}
					if (vent.getColor().a > 22)
					{
						vent.setColor(sf::Color(255, 255, 255, vent.getColor().a - 5));
					}
					if (vent.getColor().a <= 2)
					{
						vent.setColor(sf::Color(255, 255, 255, 0));
					}
				}
				else if (overheated == true)
				{
					if (vent.getColor().a < 255)
					{
						vent.setColor(sf::Color(255, 255, 255, vent.getColor().a + 5));
					}
					if (vent.getColor().a > 255)
					{
						vent.setColor(sf::Color(255, 255, 255, 255));
					}
					if (heatTimer <= 0)
					{
						if (heat.getColor().a > 2)
						{
							heat.setColor(sf::Color(255, 255, 255, heat.getColor().a - 2));
						}
						if (heat.getColor().a <= 2)
						{
							heat.setColor(sf::Color(255, 255, 255, 0));
							overheated = false;
							heatTimer = 70;
						}
					}
					heatTimer--;
				}
			}
		}
	}
	else if (type == "enemy" || type == "ally")
	{
		laserBeam.setColor(sf::Color(255, 255, 255, 0));

		impact.setColor(sf::Color(255, 255, 255, 0));

		if (weaponType == "Plasma")
		{
			if (ship->firing == true &&  ship->noFuel == false)
			{
				if (ship->getFuel() > 1)
				{
					if (fireTimer < 60 && fireTimer > 45)
					{
						if (fireOnce1 == false)
						{
							if (type == "enemy")
							{
								ProjectileManager::GetInstance()->CreateProjectile(firePoints.at(0), turretSprite.getPosition(), turretSprite.getRotation(), true);
							}
							else
							{
								ProjectileManager::GetInstance()->CreateProjectile(firePoints.at(0), turretSprite.getPosition(), turretSprite.getRotation(), false);
							}
							AnimationManager::GetInstance()->CreateAnimation(firePoints.at(0), 2, turretSprite.getRotation() + 90);
							SoundManager::GetInstance()->CreateSound(firePoints.at(0), 2);
							fireOnce1 = true;
						}
					}
					if (fireTimer < 45 && fireTimer > 30)
					{
						if (fireOnce2 == false)
						{
							if (type == "enemy")
							{
								ProjectileManager::GetInstance()->CreateProjectile(firePoints.at(1), turretSprite.getPosition(), turretSprite.getRotation(), true);
							}
							else
							{
								ProjectileManager::GetInstance()->CreateProjectile(firePoints.at(1), turretSprite.getPosition(), turretSprite.getRotation(), false);
							}
							AnimationManager::GetInstance()->CreateAnimation(firePoints.at(1), 2, turretSprite.getRotation() + 90);
							SoundManager::GetInstance()->CreateSound(firePoints.at(1), 2);
							fireOnce2 = true;
						}
					}
					if (fireTimer < 30 && fireTimer > 15)
					{
						if (fireOnce3 == false)
						{
							if (type == "enemy")
							{
								ProjectileManager::GetInstance()->CreateProjectile(firePoints.at(2), turretSprite.getPosition(), turretSprite.getRotation(), true);
							}
							else
							{
								ProjectileManager::GetInstance()->CreateProjectile(firePoints.at(2), turretSprite.getPosition(), turretSprite.getRotation(), false);
							}
							AnimationManager::GetInstance()->CreateAnimation(firePoints.at(2), 2, turretSprite.getRotation() + 90);
							SoundManager::GetInstance()->CreateSound(firePoints.at(2), 2);
							fireOnce3 = true;
						}
					}
					if (fireTimer < 15 && fireTimer > 0)
					{
						if (fireOnce4 == false)
						{
							if (type == "enemy")
							{
								ProjectileManager::GetInstance()->CreateProjectile(firePoints.at(3), turretSprite.getPosition(), turretSprite.getRotation(), true);
							}
							else
							{
								ProjectileManager::GetInstance()->CreateProjectile(firePoints.at(3), turretSprite.getPosition(), turretSprite.getRotation(), false);
							}
							AnimationManager::GetInstance()->CreateAnimation(firePoints.at(3), 2, turretSprite.getRotation() + 90);
							SoundManager::GetInstance()->CreateSound(firePoints.at(3), 2);
							fireOnce4 = true;
						}
						//for (int i = 0; i < firePoints.size(); i++)
						//{
						//	ProjectileManager::GetInstance()->CreateProjectile(firePoints.at(i), turretSprite.getPosition(), turretSprite.getRotation());
						//}
					}
					if (fireTimer < 0)
					{
						fireTimer = 60;
						fireOnce1 = false;
						fireOnce2 = false;
						fireOnce3 = false;
						fireOnce4 = false;
					}
					ship->setFuel(ship->getFuel() - 0.5f);
				}
			}
		}
		if (weaponType == "Laser")
		{
			if (laserActive == false)
			{
				if (laser.getVolume() > 0)
				{
					laser.setVolume(laser.getVolume() - 2);
				}
				if (laser.getVolume() <= 5)
				{
					laser.pause();
				}
			}
			else if (laserActive == true)
			{
				if (laser.getVolume() < 40)
				{
					laser.setVolume(laser.getVolume() + 2);
				}
			}

			heat.setPosition(turretSprite.getPosition());
			heat.setRotation(turretSprite.getRotation());

			vent.setPosition(turretSprite.getPosition());
			vent.setRotation(turretSprite.getRotation());

			if (ship->firing == true && overheated == false)
			{
				if (ship->getFuel() > 1)
				{
					//ProjectileManager::GetInstance()->CreateProjectile(firePoints.at(0), turretSprite.getPosition(), turretSprite.getRotation());
					//AnimationManager::GetInstance()->CreateAnimation(firePoints.at(0), 2, turretSprite.getRotation() + 90);
					//SoundManager::GetInstance()->CreateSound(firePoints.at(0), 2);

					rayCallBack->Reset();

					b2Vec2 startPoint;
					startPoint.x = turretSprite.getPosition().x / SCALE;
					startPoint.y = turretSprite.getPosition().y / SCALE;
					b2Vec2 endPoint;
					endPoint.x = (turretSprite.getPosition().x + ((firePoints.at(0).x - turretSprite.getPosition().x) * 25)) / SCALE;
					endPoint.y = (turretSprite.getPosition().y + ((firePoints.at(0).y - turretSprite.getPosition().y) * 25)) / SCALE;

					world->RayCast(rayCallBack, startPoint, endPoint);

					bool hit = false;

					if (rayCallBack->objectName == "bound")
					{
						hit = true;
					}
					if (type == "enemy")
					{
						if (rayCallBack->objectName == "player")
						{
							static_cast<Ship*>(rayCallBack->data)->setHealth(static_cast<Ship*>(rayCallBack->data)->getHealth() - 2);
							hit = true;
						}
						if (rayCallBack->objectName == "ally")
						{
							static_cast<Ship*>(rayCallBack->data)->setHealth(static_cast<Ship*>(rayCallBack->data)->getHealth() - 2);
							hit = true;
						}
					}
					else
					{
						if (rayCallBack->objectName == "enemy")
						{
							static_cast<Ship*>(rayCallBack->data)->setHealth(static_cast<Ship*>(rayCallBack->data)->getHealth() - 2);
							hit = true;
						}
					}
					if (rayCallBack->objectName == "wreck")
					{
						static_cast<Wreck*>(rayCallBack->data)->setTTL(static_cast<Wreck*>(rayCallBack->data)->getTTL() - 5);
						hit = true;
					}

					if (hit == true)
					{
						beamImpact.x = (rayCallBack->m_point.x * SCALE) + (firePoints.at(0).x - turretSprite.getPosition().x);
						beamImpact.y = (rayCallBack->m_point.y * SCALE) + (firePoints.at(0).y - turretSprite.getPosition().y);
						laserBeam.setPosition(firePoints.at(0));
						laserBeam.setRotation(turretSprite.getRotation() - 180);
						laserBeam.setColor(sf::Color(255, 255, 255, 255));
						sf::IntRect temp = laserBeam.getTextureRect();
						temp.height = (sqrt(((firePoints.at(0).x - beamImpact.x) * (firePoints.at(0).x - beamImpact.x)) + ((firePoints.at(0).y - beamImpact.y) * (firePoints.at(0).y - beamImpact.y))) * 2);
						laserBeam.setTextureRect(temp);

						impact.setRotation(turretSprite.getRotation() - 180);
						impact.setColor(sf::Color(255, 255, 255, 255));
						impact.setPosition(beamImpact);

						if (laser.getPitch() < 1.853)
						{
							laser.setPitch(laser.getPitch() + 0.003f);
						}
						if (laser.getPitch() > 1.853)
						{
							laser.setPitch(1.85300529f);
						}

						if (heat.getColor().a < 255)
						{
							heat.setColor(sf::Color(255, 255, 255, heat.getColor().a + 1));
						}
						if (heat.getColor().a > 250)
						{
							heat.setColor(sf::Color(255, 255, 255, 255));
							overheated = true;
							steam.play();
						}

						rayCallBack->Reset();

						if (released == true)
						{
							prevImpact = beamImpact;
							released = false;
							//SoundManager::GetInstance()->LaserOn();
							laser.play();
							laserActive = true;
						}

						if (timer <= 0)
						{
							if (distance(beamImpact, prevImpact) > 100)
							{
								prevImpact = beamImpact;
							}
							AnimationManager::GetInstance()->AddBurn(prevImpact, beamImpact);
							prevImpact = beamImpact;
							timer = 3;
						}

						timer--;
					}
					else
					{
						laserBeam.setPosition(firePoints.at(0));
						laserBeam.setRotation(turretSprite.getRotation() - 180);
						laserBeam.setColor(sf::Color(255, 255, 255, 255));
						sf::IntRect temp = laserBeam.getTextureRect();
						temp.height = 1100;// (sqrt(((firePoints.at(0).x - beamImpact.x) * (firePoints.at(0).x - beamImpact.x)) + ((firePoints.at(0).y - beamImpact.y) * (firePoints.at(0).y - beamImpact.y))) * 2);
						laserBeam.setTextureRect(temp);

						if (released2 == true)
						{
							released2 = false;
							laser.play();
							laserActive = true;
							//SoundManager::GetInstance()->LaserOn();
						}

						if (laser.getPitch() < 1.853)
						{
							laser.setPitch(laser.getPitch() + 0.003f);
						}
						if (laser.getPitch() > 1.853)
						{
							laser.setPitch(1.85300529f);
						}

						if (heat.getColor().a < 255)
						{
							heat.setColor(sf::Color(255, 255, 255, heat.getColor().a + 1));
						}
						if (heat.getColor().a > 250)
						{
							heat.setColor(sf::Color(255, 255, 255, 255));
							overheated = true;
							steam.play();
						}

						//impact.setRotation(turretSprite.getRotation() - 180);
						//impact.setColor(sf::Color(255, 255, 255, 255));
						//impact.setPosition(sf::Vector2f((firePoints.at(0).x - turretSprite.getPosition().x) * 25, (firePoints.at(0).y - turretSprite.getPosition().y) * 25));
					}



					//ship->setFuel(ship->getFuel() - 0.5f);
				}
			}
			else
			{
				released = true;
				released2 = true;
				//SoundManager::GetInstance()->LaserOff();
				//laser.pause();
				laserActive = false;

				if (laser.getPitch() > 1.1)
				{
					laser.setPitch(laser.getPitch() - 0.003f);
				}
				else if (laser.getPitch() < 1.1)
				{
					laser.setPitch(1.1f);
				}

				if (overheated == false)
				{
					if (heat.getColor().a > 2)
					{
						heat.setColor(sf::Color(255, 255, 255, heat.getColor().a - 2));
					}
					if (heat.getColor().a <= 2)
					{
						heat.setColor(sf::Color(255, 255, 255, 0));
						overheated = false;
					}
					if (vent.getColor().a > 22)
					{
						vent.setColor(sf::Color(255, 255, 255, vent.getColor().a - 5));
					}
					if (vent.getColor().a <= 2)
					{
						vent.setColor(sf::Color(255, 255, 255, 0));
					}
				}
				else if (overheated == true)
				{
					if (vent.getColor().a < 255)
					{
						vent.setColor(sf::Color(255, 255, 255, vent.getColor().a + 5));
					}
					if (vent.getColor().a > 255)
					{
						vent.setColor(sf::Color(255, 255, 255, 255));
					}
					if (heatTimer <= 0)
					{
						if (heat.getColor().a > 2)
						{
							heat.setColor(sf::Color(255, 255, 255, heat.getColor().a - 2));
						}
						if (heat.getColor().a <= 2)
						{
							heat.setColor(sf::Color(255, 255, 255, 0));
							overheated = false;
							heatTimer = 70;
						}
					}
					heatTimer--;
				}
			}
		}
	}
	fireTimer--;

	Move();
}

float Turret::distance(sf::Vector2f d1, sf::Vector2f d2)
{
	float d = sqrt(((d1.x - d2.x) * (d1.x - d2.x)) + ((d1.y - d2.y) * (d1.y - d2.y)));

	return d;
}

void Turret::Draw(sf::RenderWindow & window)
{
	window.draw(turretSprite);
	window.draw(laserBeam);
	window.draw(impact);
}

void Turret::Draw2(sf::RenderWindow & window)
{
	window.draw(laserBeam);
	window.draw(impact);
	window.draw(heat);
	window.draw(vent);
}

void Turret::Move() {
	prevRotation = rotation;
	position2 = turretSprite.getPosition();
	sf::Vector2i mousePos;
	sf::Vector2f worldMousePos;
	sf::Vector2f wantedVector;
	if (type == "player")
	{
		mousePos = sf::Mouse::getPosition(*window);
		worldMousePos = window->mapPixelToCoords(mousePos);
		wantedVector = worldMousePos - position2;
	}
	else if (type == "enemy" || type == "ally")
	{
		mousePos = sf::Vector2i(ship->targetPos.x, ship->targetPos.y);
		worldMousePos = sf::Vector2f(mousePos.x, mousePos.y);
		wantedVector = worldMousePos - position2;
	}

	float angleBetweenTwo = atan2(worldMousePos.y - position2.y, worldMousePos.x - position2.x);

	if (weaponType == "Laser")
	{
		if (type == "enemy" || type == "ally")
		{
			rotation = CurveAngle(rotation, angleBetweenTwo, 0.080f);
		}
		else
		{
			rotation = CurveAngle(rotation, angleBetweenTwo, 0.030f);
		}
	}
	else
	{
		rotation = CurveAngle(rotation, angleBetweenTwo, 0.040f);
	}

	//error check, rotation was crashing every so often, this is a loose fix
	if (isnan(rotation))
		rotation = prevRotation;

	//rotation = rotation;
	direction = sf::Vector2f(cos(rotation), sin(rotation));
	normalize(direction);
	direction *= speed;

	turretSprite.setRotation(radiansToDegrees(rotation) + 90);
}

//these are the code from the gods that fix the rotation loop around 2 pi
float Turret::CurveAngle(float from, float to, float step)
{
	if (step == 0)
		return from;
	if (from == to || step == 1)
		return to;

	sf::Vector2f fromVector = sf::Vector2f((float)cos(from), (float)sin(from));
	sf::Vector2f toVector = sf::Vector2f((float)cos(to), (float)sin(to));

	sf::Vector2f currentVector = Slerp(fromVector, toVector, step);

	return (float)atan2(currentVector.y, currentVector.x);
}

sf::Vector2f Turret::Slerp(sf::Vector2f from, sf::Vector2f to, float step)
{
	if (step == 0) return from;
	if (from == to || step == 1) return to;

	double theta = acos(dotProduct(from, to));
	if (theta == 0) return to;

	double sinTheta = sin(theta);
	return (float)(sin((1 - step) * theta) / sinTheta) * from + (float)(sin(step * theta) / sinTheta) * to;
}

sf::Vector2f Turret::normalize(sf::Vector2f source)
{
	float length = sqrt((source.x * source.x) + (source.y * source.y));
	if (length != 0)
		return sf::Vector2f(source.x / length, source.y / length);
	else
		return source;
}

float Turret::degreeToRadian(float angle)
{
	float pi = 3.14159265358979323846;
	return  pi * angle / 180.0;
}

float Turret::radiansToDegrees(float angle)
{
	float pi = 3.14159265358979323846;
	return angle * (180.0 / pi);
}

float Turret::dotProduct(sf::Vector2f v1, sf::Vector2f v2)
{
	v1 = normalize(v1);
	v2 = normalize(v2);
	return (v1.x * v2.x) + (v1.y * v2.y);
}