#include "Ship.h"
#include "Turret.h"

static const float SCALE = 30.f;

Ship::Ship(b2World& World, ProjectileManager & projManager, AnimationManager& a)
{
	if (!shipTexture.loadFromFile("Ship.png"))
	{
		// error...
	}

	shipTexture.setSmooth(true);

	shipSprite.setTexture(shipTexture);

	shipSprite.setScale(sf::Vector2f(0.5f, 0.5f));

	shipSprite.setPosition(sf::Vector2f(300, 300));

	shipSprite.setOrigin(sf::Vector2f(200, 300));

	if (!boosterTexture.loadFromFile("Boosters4.png"))
	{
		// error...
	}

	boosterTexture.setSmooth(true);

	boosterSprite.setTexture(boosterTexture);

	boosterSprite.setScale(sf::Vector2f(0.5f, 0.25f));

	boosterSprite.setPosition(sf::Vector2f(300, 500));

	boosterSprite.setOrigin(sf::Vector2f(140, 1));

	boosterPoint = sf::Vector2f(100, 290);

	velocity = sf::Vector2f(0, 0);

	world = &World;

	projMan = & projManager;

	aniMan = &a;

	speed = 0.010f;

	CreateBody();

	turrets.push_back(new Turret(sf::Vector2f(75, 80), *this, *projMan, *aniMan));
	turrets.push_back(new Turret(sf::Vector2f(124, 80), *this, *projMan, *aniMan));
	turrets.push_back(new Turret(sf::Vector2f(75, 127), *this, *projMan, *aniMan));
	turrets.push_back(new Turret(sf::Vector2f(124, 127), *this, *projMan, *aniMan));
	turrets.push_back(new Turret(sf::Vector2f(75, 175), *this, *projMan, *aniMan));
	turrets.push_back(new Turret(sf::Vector2f(124, 175), *this, *projMan, *aniMan));

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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		shipBody->ApplyAngularImpulse(-200, false);
		//shipSprite.setRotation(shipSprite.getRotation() - 0.002);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		shipBody->ApplyAngularImpulse(200, false);
		//shipSprite.setRotation(shipSprite.getRotation() + 0.002);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		shipBody->ApplyLinearImpulse(b2Vec2(velocity2.x, velocity2.y), shipBody->GetWorldCenter(), false);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		shipBody->ApplyLinearImpulse(b2Vec2(-velocity2.x, -velocity2.y), shipBody->GetWorldCenter(), false);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		shipBody->ApplyLinearImpulse(b2Vec2(velocity.x, velocity.y), shipBody->GetWorldCenter(), false);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		shipBody->ApplyLinearImpulse(b2Vec2(-velocity.x, -velocity.y), shipBody->GetWorldCenter(), false);
		//boosterSprite.setColor(sf::Color(255, 255, 255, 255));
	}
	else
	{
		//boosterSprite.setColor(sf::Color(255, 255, 255, 0));
	}

	float speed = sqrt((shipBody->GetLinearVelocity().x * shipBody->GetLinearVelocity().x) + (shipBody->GetLinearVelocity().y * shipBody->GetLinearVelocity().y));

	boosterSprite.setScale(sf::Vector2f(0.5f, speed / 2));

	velocity.x = cos((shipSprite.getRotation() + 90) * 0.0174532925);
	velocity.y = sin((shipSprite.getRotation() + 90) * 0.0174532925);

	velocity2.x = cos((shipSprite.getRotation()) * 0.0174532925);
	velocity2.y = sin((shipSprite.getRotation()) * 0.0174532925);

	shipSprite.setPosition(shipBody->GetPosition().x * SCALE, shipBody->GetPosition().y * SCALE);
	shipSprite.setRotation(shipBody->GetAngle());

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
	FixtureDef.userData = "Ship";
	Body->CreateFixture(&FixtureDef);

	shipBody = Body;
}

//void Ship::Move(sf::Vector2f targetPos) {
//	prevRotation = rotation;
//	position = sprite.getPosition();
//	sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);
//	sf::Vector2f wantedVector = mousePos - position;
//
//	float angleBetweenTwo = atan2(mousePos.y - position.y, mousePos.x - position.x);
//
//	rotation = CurveAngle(rotation, angleBetweenTwo, 0.0006f);
//
//	//error check, rotation was crashing every so often, this is a loose fix
//	if (isnan(rotation))
//		rotation = prevRotation;
//
//	//rotation = rotation;
//	direction = sf::Vector2f(cos(rotation), sin(rotation));
//	normalize(direction);
//	direction *= speed;
//
//	////if space is held down, will fly forwards
//	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
//	//	position += direction;
//
//	sprite.setRotation(radiansToDegrees(rotation) + 90);
//	sprite.setPosition(position);
//}
//
////these are the code from the gods that fix the rotation loop around 2 pi
//float CurveAngle(float from, float to, float step)
//{
//	if (step == 0)
//		return from;
//	if (from == to || step == 1)
//		return to;
//
//	sf::Vector2f fromVector = sf::Vector2f((float)cos(from), (float)sin(from));
//	sf::Vector2f toVector = sf::Vector2f((float)cos(to), (float)sin(to));
//
//	sf::Vector2f currentVector = Slerp(fromVector, toVector, step);
//
//	return (float)atan2(currentVector.y, currentVector.x);
//}
//
//sf::Vector2f Slerp(sf::Vector2f from, sf::Vector2f to, float step)
//{
//	if (step == 0) return from;
//	if (from == to || step == 1) return to;
//
//	double theta = acos(dotProduct(from, to));
//	if (theta == 0) return to;
//
//	double sinTheta = sin(theta);
//	return (float)(sin((1 - step) * theta) / sinTheta) * from + (float)(sin(step * theta) / sinTheta) * to;
//}
//
//sf::Vector2f normalize(sf::Vector2f source)
//{
//	float length = sqrt((source.x * source.x) + (source.y * source.y));
//	if (length != 0)
//		return sf::Vector2f(source.x / length, source.y / length);
//	else
//		return source;
//}
//
//float degreeToRadian(float angle)
//{
//	float pi = 3.14159265358979323846;
//	return  pi * angle / 180.0;
//}
//
//float radiansToDegrees(float angle)
//{
//	float pi = 3.14159265358979323846;
//	return angle * (180.0 / pi);
//}
//
//float dotProduct(sf::Vector2f v1, sf::Vector2f v2)
//{
//	v1 = normalize(v1);
//	v2 = normalize(v2);
//	return (v1.x * v2.x) + (v1.y * v2.y);
//}


