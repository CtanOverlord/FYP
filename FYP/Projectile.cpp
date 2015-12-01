#include "Projectile.h"

static const float SCALE = 30.f;

Projectile::Projectile(b2World& World, sf::Vector2f position, sf::Vector2f pos2, float a)
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

	projSprite.setOrigin(sf::Vector2f(5.5f, 22));

	projSprite.setRotation(angle);

	//projSprite.setColor(sf::Color(255, 255, 255, 100));

	world = &World;

	CreateBody();

	transform.rotate(angle, pos2);

	float scale1 = (rand() % 3 + 1) + 55;

	ttl = scale1;

	//projBody->SetTransform(projBody->GetPosition(), angle * 0.0174532925);
}

void Projectile::Update()
{
	velocity.x = cos((angle + 90) * 0.0174532925);
	velocity.y = sin((angle + 90) * 0.0174532925);

	projSprite.setPosition(projSprite.getPosition().x - velocity.x * 10, projSprite.getPosition().y - velocity.y * 10);
	projBody->SetTransform(b2Vec2(projSprite.getPosition().x / SCALE, projSprite.getPosition().y / SCALE), angle);

	ttl--;
}

void Projectile::Draw(sf::RenderWindow & window)
{
	//if (onlyOnce == false)
	//{
	window.draw(projSprite);// , transform);
		//onlyOnce = true;
	//}
	//else
	//{
		//window.draw(projSprite);
	//}
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
	BodyDef.position = b2Vec2(projSprite.getPosition().x / SCALE, projSprite.getPosition().y / SCALE);
	BodyDef.type = b2_dynamicBody;
	BodyDef.userData = this;
	b2Body* Body = world->CreateBody(&BodyDef);
	Body->SetFixedRotation(false);
	Body->SetSleepingAllowed(false);

	b2PolygonShape Shape;
	Shape.SetAsBox(((projSprite.getTextureRect().width * projSprite.getScale().x) / 2) / SCALE, ((projSprite.getTextureRect().height * projSprite.getScale().x) / 2) / SCALE);
	Shape.SetAsBox((5.5 / 2) / SCALE, (22 / 2) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 1.0f;
	FixtureDef.friction = 0.0f;
	FixtureDef.shape = &Shape;
	FixtureDef.userData = "projectile";
	FixtureDef.isSensor = true;
	Body->CreateFixture(&FixtureDef);
	
	projBody = Body;
}