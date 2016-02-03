#include "Turret.h"
#include "Ship.h"

Turret::Turret(sf::Vector2f p, Ship& s, string t, sf::RenderWindow & w)
{
	if (!turretTexture.loadFromFile("Turret5.png"))
	{
		// error...
	}

	turretTexture.setSmooth(true);

	turretSprite.setTexture(turretTexture);

	position = p;

	turretSprite.setScale(sf::Vector2f(0.5f, 0.5f));

	turretSprite.setPosition(sf::Vector2f(position.x, position.y));

	turretSprite.setOrigin(sf::Vector2f(45, 45));

	ship = &s;

	type = t;
	
	window = &w;

	fireTimer = 0;

	turretSprite.setPosition((ship->getSprite().getPosition().x - ship->getSprite().getTextureRect().width / 4) + position.x, (ship->getSprite().getPosition().y - ship->getSprite().getTextureRect().height / 4) + position.y);

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
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (fireTimer < 60 && fireTimer > 45)
			{
				if (fireOnce1 == false)
				{
					ProjectileManager::GetInstance()->CreateProjectile(firePoints.at(0), turretSprite.getPosition(), turretSprite.getRotation());
					AnimationManager::GetInstance()->CreateAnimation(firePoints.at(0), 2, turretSprite.getRotation() + 90);
					SoundManager::GetInstance()->CreateSound(firePoints.at(0), 2);
					fireOnce1 = true;
				}
			}
			if (fireTimer < 45 && fireTimer > 30)
			{
				if (fireOnce2 == false)
				{
					ProjectileManager::GetInstance()->CreateProjectile(firePoints.at(1), turretSprite.getPosition(), turretSprite.getRotation());
					AnimationManager::GetInstance()->CreateAnimation(firePoints.at(1), 2, turretSprite.getRotation() + 90);
					SoundManager::GetInstance()->CreateSound(firePoints.at(1), 2);
					fireOnce2 = true;
				}
			}
			if (fireTimer < 30 && fireTimer > 15)
			{
				if (fireOnce3 == false)
				{
					ProjectileManager::GetInstance()->CreateProjectile(firePoints.at(2), turretSprite.getPosition(), turretSprite.getRotation());
					AnimationManager::GetInstance()->CreateAnimation(firePoints.at(2), 2, turretSprite.getRotation() + 90);
					SoundManager::GetInstance()->CreateSound(firePoints.at(2), 2);
					fireOnce3 = true;
				}
			}
			if (fireTimer < 15 && fireTimer > 0)
			{
				if (fireOnce4 == false)
				{
					ProjectileManager::GetInstance()->CreateProjectile(firePoints.at(3), turretSprite.getPosition(), turretSprite.getRotation());
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
		}
	}
	else if (type == "enemy")
	{

	}
	fireTimer--;

	Move();
}

void Turret::Draw(sf::RenderWindow & window)
{
	window.draw(turretSprite);
}

void Turret::Move() {
	prevRotation = rotation;
	position2 = turretSprite.getPosition();
	sf::Vector2i mousePos;
	if (type == "player")
	{
		mousePos = sf::Mouse::getPosition(*window);
	}
	else if (type == "enemy")
	{
		mousePos = sf::Vector2i(0, -1000);
	}
	sf::Vector2f worldMousePos = window->mapPixelToCoords(mousePos);
	sf::Vector2f wantedVector = worldMousePos - position2;

	float angleBetweenTwo = atan2(worldMousePos.y - position2.y, worldMousePos.x - position2.x);

	rotation = CurveAngle(rotation, angleBetweenTwo, 0.040f);

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