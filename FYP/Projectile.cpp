#include "Projectile.h"

static const float SCALE = 30.f;

Projectile::Projectile(b2World& World, sf::Vector2f position, sf::Vector2f pos2, float a, string t)
{
	type = t;

	vel = 0;

	prevRotation = a;

	rotation = a;

	target = pos2;

	if (type == "plasma" || type == "plasmaE")
	{
		if (!projTexture.loadFromFile("Plasma.png"))
		{
			// error...
		}

		angle = a;

		projTexture.setSmooth(true);

		projSprite.setTexture(projTexture);

		projSprite.setScale(sf::Vector2f(0.5f, 0.5f));

		sf::Vector2f temp = sf::Vector2f(21.5f, 22);

		projSprite.setPosition((position));// +pos2) - temp);

		projSprite.setOrigin(sf::Vector2f(5.5f, 0));

		projSprite.setRotation(angle);
	}
	else if (type == "missile" || type == "missileE")
	{
		if (!projTexture.loadFromFile("Missile2.png"))
		{
			// error...
		}

		angle = a;

		projTexture.setSmooth(true);

		projSprite.setTexture(projTexture);

		projSprite.setScale(sf::Vector2f(0.5f, 0.5f));

		projSprite.setPosition(position);

		projSprite.setOrigin(sf::Vector2f(10, 10));

		projSprite.setRotation(angle);
	}
	else if (type == "drain" || type == "drainE")
	{
		if (!projTexture.loadFromFile("Missile3.png"))
		{
			// error...
		}

		angle = a;

		projTexture.setSmooth(true);

		projSprite.setTexture(projTexture);

		projSprite.setScale(sf::Vector2f(0.5f, 0.5f));

		projSprite.setPosition(position);

		projSprite.setOrigin(sf::Vector2f(10, 10));

		projSprite.setRotation(angle);
	}
	else if (type == "slug" || type == "slugE")
	{
		if (!projTexture.loadFromFile("Slug2.png"))
		{
			// error...
		}

		angle = a;

		projTexture.setSmooth(true);

		projSprite.setTexture(projTexture);

		projSprite.setScale(sf::Vector2f(0.5f, 0.5f));

		sf::Vector2f temp = sf::Vector2f(21.5f, 22);

		projSprite.setPosition((position));// +pos2) - temp);

		projSprite.setOrigin(sf::Vector2f(11, 0));

		projSprite.setRotation(angle);
	}
	else if (type == "mine" || type == "mineE")
	{
		if (!mineTexture.loadFromFile("MineSheet.png"))
		{

		}

		mineTexture.setSmooth(true);

		mine.setSpriteSheet(mineTexture);

		for (int i = 0; i < 2; i++)
		{
			mine.addFrame(sf::IntRect(300 * i, 0, 300, 300));
		}

		angle = a;

		mineSprite = AnimatedSprite(sf::seconds(0.5f), false, true);
		mineSprite.setOrigin(150, 150);
		mineSprite.setPosition(position);
		mineSprite.setScale(sf::Vector2f(0.06f, 0.06f));
		mineSprite.setRotation(angle);
		mineSprite.play(mine);

		//if (!projTexture.loadFromFile("Mine.png"))
		//{
		//	// error...
		//}

		//angle = a;

		//projTexture.setSmooth(true);

		//projSprite.setTexture(projTexture);

		//projSprite.setScale(sf::Vector2f(0.06f, 0.06f));

		//sf::Vector2f temp = sf::Vector2f(21.5f, 22);

		//projSprite.setPosition((position));// +pos2) - temp);

		//projSprite.setOrigin(sf::Vector2f(150, 150));

		//projSprite.setRotation(angle);
	}

	//projSprite.setColor(sf::Color(255, 255, 255, 100));

	world = &World;

	CreateBody();

	if (type == "mine" || type == "mineE")
	{
		projBody->SetTransform(b2Vec2(mineSprite.getPosition().x / SCALE, mineSprite.getPosition().y / SCALE), (mineSprite.getRotation()) / (180.0f / b2_pi));
	}
	else
	{
		projBody->SetTransform(b2Vec2(projSprite.getPosition().x / SCALE, projSprite.getPosition().y / SCALE), (projSprite.getRotation()) / (180.0f / b2_pi));
	}

	transform.rotate(angle, pos2);

	if (type == "missile" || type == "drain" || type == "missileE" || type == "drainE")
	{
		float scale1 = (rand() % 10 + 1) + 400;

		ttl = scale1;

	}

	if (type == "plasma" || type == "plasmaE")
	{
		float scale1 = (rand() % 5 + 1) + 60;

		ttl = scale1;
	}

	if (type == "slug" || type == "slugE")
	{
		float scale1 = (rand() % 5 + 1) + 400;

		ttl = scale1;
	}

	if (type == "mine" || type == "mineE")
	{
		float scale1 = (rand() % 100 + 1) + 1150;

		ttl = scale1;

		velocity.x = cos((mineSprite.getRotation() + 90) / (180.0f / b2_pi));
		velocity.y = sin((mineSprite.getRotation() + 90) / (180.0f / b2_pi));

		float scaler = rand() % 65 + 15;
		/*if (scaler <= 10)
		{
			scaler = 1;
		}
		else if (scaler <= 20)
		{
			scaler = 2;
		}
		else if (scaler <= 30)
		{
			scaler = 3;
		}*/

		scaler = scaler /= 10;

		projBody->ApplyLinearImpulse(b2Vec2(-velocity.x * scaler, -velocity.y * scaler), projBody->GetWorldCenter(), false);

		float tempAngle = rand() % 100 + 1;

		float temp = rand() % 10 + 1;

		if (temp > 5)
		{
			projBody->ApplyAngularImpulse(tempAngle, false);
		}
		else
		{
			projBody->ApplyAngularImpulse(-tempAngle, false);
		}
	}


	//projBody->SetTransform(projBody->GetPosition(), angle * 0.0174532925);
}

void Projectile::Update()
{
	if (type == "missile" || type == "missileE")
	{
		if (vel < 6)
		{
			vel = vel + 0.15f;
		}
		else
		{
			Move();
		}
		velocity.x = cos((projSprite.getRotation() + 90) / (180.0f / b2_pi));
		velocity.y = sin((projSprite.getRotation() + 90) / (180.0f / b2_pi));

		projSprite.setPosition(projSprite.getPosition().x - velocity.x * vel, projSprite.getPosition().y - velocity.y * vel);
		projSprite.setRotation(projBody->GetAngle() * (180.0f / b2_pi));
		projBody->SetTransform(b2Vec2(projSprite.getPosition().x / SCALE, projSprite.getPosition().y / SCALE), projBody->GetAngle()); // (projSprite.getRotation() + 90) / (180.0f / b2_pi));
		//projSprite.setRotation(projSprite.getRotation() + 0.5);
	}
	else if (type == "plasma" || type == "plasmaE")
	{
		velocity.x = cos((angle + 90) / (180.0f / b2_pi));
		velocity.y = sin((angle + 90) / (180.0f / b2_pi));

		projSprite.setPosition(projSprite.getPosition().x - velocity.x * 10, projSprite.getPosition().y - velocity.y * 10);
		projBody->SetTransform(b2Vec2(projSprite.getPosition().x / SCALE, projSprite.getPosition().y / SCALE), (projSprite.getRotation() + 90) / (180.0f / b2_pi));
	}
	else if (type == "slug" || type == "slugE")
	{
		velocity.x = cos((angle + 90) / (180.0f / b2_pi));
		velocity.y = sin((angle + 90) / (180.0f / b2_pi));

		projSprite.setPosition(projSprite.getPosition().x - velocity.x * 30, projSprite.getPosition().y - velocity.y * 30);
		projBody->SetTransform(b2Vec2(projSprite.getPosition().x / SCALE, projSprite.getPosition().y / SCALE), (projSprite.getRotation() + 90) / (180.0f / b2_pi));
	}
	else if (type == "drain" || type == "drainE")
	{

		if (vel < 6)
		{
			vel = vel + 0.15f;
		}

		velocity.x = cos((angle + 90) / (180.0f / b2_pi));
		velocity.y = sin((angle + 90) / (180.0f / b2_pi));

		projSprite.setPosition(projSprite.getPosition().x - velocity.x * vel, projSprite.getPosition().y - velocity.y * vel);
		projBody->SetTransform(b2Vec2(projSprite.getPosition().x / SCALE, projSprite.getPosition().y / SCALE), (projSprite.getRotation() + 90) / (180.0f / b2_pi));
	}
	else if (type == "mine" || type == "mineE")
	{
		//projSprite.setPosition(projSprite.getPosition().x - velocity.x * vel, projSprite.getPosition().y - velocity.y * vel);
		//projBody->SetTransform(b2Vec2(projSprite.getPosition().x / SCALE, projSprite.getPosition().y / SCALE), (projSprite.getRotation() + 90) / (180.0f / b2_pi));
		mineSprite.setPosition(projBody->GetPosition().x * SCALE, projBody->GetPosition().y * SCALE);
		mineSprite.setRotation(projBody->GetAngle());

		sf::Time frameTime = frameClock.restart();

		mineSprite.update(frameTime);
	}

	ttl--;
}

void Projectile::Draw(sf::RenderWindow & window)
{
	if (type == "mine" || type == "mineE")
	{
		window.draw(mineSprite);
	}
	else
	{
		window.draw(projSprite);
	}
}

sf::Sprite Projectile::getSprite()
{
	return projSprite;
}

float Projectile::getTTL()
{
	return ttl;
}

void Projectile::setTTL(float t)
{
	ttl = t;
}

b2Body* Projectile::getBody()
{
	return projBody;
}

void Projectile::CreateBody()
{
	b2BodyDef BodyDef;
	if (type == "mine" || type == "mineE")
	{
		BodyDef.position = b2Vec2(mineSprite.getPosition().x / SCALE, mineSprite.getPosition().y / SCALE);
	}
	else
	{
		BodyDef.position = b2Vec2(projSprite.getPosition().x / SCALE, projSprite.getPosition().y / SCALE);
	}
	BodyDef.type = b2_dynamicBody;
	BodyDef.userData = this;
	b2Body* Body = world->CreateBody(&BodyDef);
	Body->SetFixedRotation(false);
	Body->SetSleepingAllowed(false);

	b2PolygonShape Shape;
	if (type == "mine" || type == "mineE")
	{
		Shape.SetAsBox((18 / 2) / SCALE, (18 / 2) / SCALE);
	}
	else
	{
		Shape.SetAsBox(((projSprite.getTextureRect().width * projSprite.getScale().x) / 2) / SCALE, ((projSprite.getTextureRect().height * projSprite.getScale().x) / 2) / SCALE);
	}
	//Shape.SetAsBox((5.5 / 2) / SCALE, (22 / 2) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 1.0f;
	FixtureDef.friction = 0.0f;
	FixtureDef.shape = &Shape;

	if (type == "plasma")
	{
		FixtureDef.filter.categoryBits = 0x0004;
		FixtureDef.filter.maskBits = 0x0010 | 0x0002;
		FixtureDef.userData = "plasma";
	}
	if (type == "plasmaE")
	{
		FixtureDef.filter.categoryBits = 0x0004;
		FixtureDef.filter.maskBits = 0x0010 | 0x0001;
		FixtureDef.userData = "plasmaE";
	}
	else if (type == "missile")
	{
		FixtureDef.filter.categoryBits = 0x0008;
		FixtureDef.filter.maskBits = 0x0010 | 0x0002;
		FixtureDef.userData = "missile";
	}
	else if (type == "missileE")
	{
		FixtureDef.filter.categoryBits = 0x0008;
		FixtureDef.filter.maskBits = 0x0010 | 0x0001;
		FixtureDef.userData = "missileE";
	}
	else if (type == "drain")
	{
		FixtureDef.filter.categoryBits = 0x0008;
		FixtureDef.filter.maskBits = 0x0010 | 0x0002;
		FixtureDef.userData = "drain";
	}
	else if (type == "drainE")
	{
		FixtureDef.filter.categoryBits = 0x0008;
		FixtureDef.filter.maskBits = 0x0010 | 0x0001;
		FixtureDef.userData = "drainE";
	}
	else if (type == "slug")
	{
		FixtureDef.filter.categoryBits = 0x0008;
		FixtureDef.filter.maskBits = 0x0010 | 0x0002;
		FixtureDef.userData = "slug";
	}
	else if (type == "slugE")
	{
		FixtureDef.filter.categoryBits = 0x0008;
		FixtureDef.filter.maskBits = 0x0010 | 0x0001;
		FixtureDef.userData = "slugE";
	}
	else if (type == "mine")
	{
		FixtureDef.filter.categoryBits = 0x0008;
		FixtureDef.filter.maskBits = 0x0010 | 0x0002;
		FixtureDef.userData = "mine";
		Body->SetLinearDamping(1.0);
	}
	else if (type == "mineE")
	{
		FixtureDef.filter.categoryBits = 0x0008;
		FixtureDef.filter.maskBits = 0x0010 | 0x0001;
		FixtureDef.userData = "mineE";
		Body->SetLinearDamping(1.0);
	}

	FixtureDef.isSensor = true;

	Body->CreateFixture(&FixtureDef);
	
	projBody = Body;
}

void Projectile::Move() {

	projBody->SetAngularVelocity(0);

	float bodyAngle = projBody->GetAngle();
	b2Vec2 toTarget;
	toTarget.x = target.x / SCALE - projBody->GetPosition().x;
	toTarget.y = target.y / SCALE - projBody->GetPosition().y;

	float desiredAngle = atan2f(toTarget.x, -toTarget.y);

	float totalRotation = desiredAngle - bodyAngle;
	while (totalRotation < -180 / (180.0f / b2_pi)) totalRotation += 360 / (180.0f / b2_pi);
	while (totalRotation >  180 / (180.0f / b2_pi)) totalRotation -= 360 / (180.0f / b2_pi);
	float change = 3 / (180.0f / b2_pi); //allow 1 degree rotation per time step
	float newAngle = bodyAngle + min(change, max(-change, totalRotation));
	projBody->SetTransform(projBody->GetPosition(), newAngle);
}

//these are the code from the gods that fix the rotation loop around 2 pi
float Projectile::CurveAngle(float from, float to, float step)
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

sf::Vector2f Projectile::Slerp(sf::Vector2f from, sf::Vector2f to, float step)
{
	if (step == 0) return from;
	if (from == to || step == 1) return to;

	double theta = acos(dotProduct(from, to));
	if (theta == 0) return to;

	double sinTheta = sin(theta);
	return (float)(sin((1 - step) * theta) / sinTheta) * from + (float)(sin(step * theta) / sinTheta) * to;
}

sf::Vector2f Projectile::normalize(sf::Vector2f source)
{
	float length = sqrt((source.x * source.x) + (source.y * source.y));
	if (length != 0)
		return sf::Vector2f(source.x / length, source.y / length);
	else
		return source;
}

float Projectile::degreeToRadian(float angle)
{
	float pi = 3.14159265358979323846;
	return  pi * angle / 180.0;
}

float Projectile::radiansToDegrees(float angle)
{
	float pi = 3.14159265358979323846;
	return angle * (180.0 / pi);
}

float Projectile::dotProduct(sf::Vector2f v1, sf::Vector2f v2)
{
	v1 = normalize(v1);
	v2 = normalize(v2);
	return (v1.x * v2.x) + (v1.y * v2.y);
}