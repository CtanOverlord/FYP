#include "AnimationManager.h"

AnimationManager::AnimationManager()
{

	srand(time(NULL));

	if (!largeExplosionTexture.loadFromFile("explosionSheet3.png"))
	{

	}

	largeExplosionTexture.setSmooth(true);

	for (int i = 0; i < 9; i++)
	{
		largeExplosion.addFrame(sf::IntRect(0, 100 * i, 100, 100));
		largeExplosion.addFrame(sf::IntRect(100, 100 * i, 100, 100));
		largeExplosion.addFrame(sf::IntRect(200, 100 * i, 100, 100));
		largeExplosion.addFrame(sf::IntRect(300, 100 * i, 100, 100));
		largeExplosion.addFrame(sf::IntRect(400, 100 * i, 100, 100));
		largeExplosion.addFrame(sf::IntRect(500, 100 * i, 100, 100));
		largeExplosion.addFrame(sf::IntRect(600, 100 * i, 100, 100));
		largeExplosion.addFrame(sf::IntRect(700, 100 * i, 100, 100));
		largeExplosion.addFrame(sf::IntRect(800, 100 * i, 100, 100));
	}

	largeExplosion.setSpriteSheet(largeExplosionTexture);
	//largeExplosion.addFrame(sf::IntRect(0, 0, 64, 64));
	//largeExplosion.addFrame(sf::IntRect(64, 0, 64, 64));
	//largeExplosion.addFrame(sf::IntRect(128, 0, 64, 64));
	//largeExplosion.addFrame(sf::IntRect(192, 0, 64, 64));
	//largeExplosion.addFrame(sf::IntRect(256, 0, 64, 64));
	//largeExplosion.addFrame(sf::IntRect(0, 64, 64, 64));
	//largeExplosion.addFrame(sf::IntRect(64, 64, 64, 64));
	//largeExplosion.addFrame(sf::IntRect(128, 64, 64, 64));
	//largeExplosion.addFrame(sf::IntRect(192, 64, 64, 64));
	//largeExplosion.addFrame(sf::IntRect(256, 64, 64, 64));
	//largeExplosion.addFrame(sf::IntRect(0, 128, 64, 64));
	//largeExplosion.addFrame(sf::IntRect(64, 128, 64, 64));
	//largeExplosion.addFrame(sf::IntRect(128, 128, 64, 64));
	//largeExplosion.addFrame(sf::IntRect(192, 128, 64, 64));
	//largeExplosion.addFrame(sf::IntRect(256, 128, 64, 64));
	//largeExplosion.addFrame(sf::IntRect(0, 192, 64, 64));
	//largeExplosion.addFrame(sf::IntRect(64, 192, 64, 64));
	//largeExplosion.addFrame(sf::IntRect(128, 192, 64, 64));
	//largeExplosion.addFrame(sf::IntRect(192, 192, 64, 64));
	//largeExplosion.addFrame(sf::IntRect(256, 192, 64, 64));
	//largeExplosion.addFrame(sf::IntRect(0, 256, 64, 64));
	//largeExplosion.addFrame(sf::IntRect(64, 256, 64, 64));
	//largeExplosion.addFrame(sf::IntRect(128, 256, 64, 64));
	//largeExplosion.addFrame(sf::IntRect(192, 256, 64, 64));
	//largeExplosion.addFrame(sf::IntRect(256, 256, 64, 64));

	if (!smallExplosionTexture.loadFromFile("explosionSheet3.png"))
	{

	}

	smallExplosionTexture.setSmooth(true);

	smallExplosion.setSpriteSheet(smallExplosionTexture);

	for (int i = 0; i < 9;  i++)
	{
		smallExplosion.addFrame(sf::IntRect(0, 100 * i, 100, 100));
		smallExplosion.addFrame(sf::IntRect(100, 100 * i, 100, 100));
		smallExplosion.addFrame(sf::IntRect(200, 100 * i, 100, 100));
		smallExplosion.addFrame(sf::IntRect(300, 100 * i, 100, 100));
		smallExplosion.addFrame(sf::IntRect(400, 100 * i, 100, 100));
		smallExplosion.addFrame(sf::IntRect(500, 100 * i, 100, 100));
		smallExplosion.addFrame(sf::IntRect(600, 100 * i, 100, 100));
		smallExplosion.addFrame(sf::IntRect(700, 100 * i, 100, 100));
		smallExplosion.addFrame(sf::IntRect(800, 100 * i, 100, 100));


		/*smallExplosion.addFrame(sf::IntRect(0, 0, 64, 64));
		smallExplosion.addFrame(sf::IntRect(64, 0, 64, 64));
		smallExplosion.addFrame(sf::IntRect(128, 0, 64, 64));
		smallExplosion.addFrame(sf::IntRect(192, 0, 64, 64));
		smallExplosion.addFrame(sf::IntRect(256, 0, 64, 64));
		smallExplosion.addFrame(sf::IntRect(0, 64, 64, 64));
		smallExplosion.addFrame(sf::IntRect(64, 64, 64, 64));
		smallExplosion.addFrame(sf::IntRect(128, 64, 64, 64));
		smallExplosion.addFrame(sf::IntRect(192, 64, 64, 64));
		smallExplosion.addFrame(sf::IntRect(256, 64, 64, 64));
		smallExplosion.addFrame(sf::IntRect(0, 128, 64, 64));
		smallExplosion.addFrame(sf::IntRect(64, 128, 64, 64));
		smallExplosion.addFrame(sf::IntRect(128, 128, 64, 64));
		smallExplosion.addFrame(sf::IntRect(192, 128, 64, 64));
		smallExplosion.addFrame(sf::IntRect(256, 128, 64, 64));
		smallExplosion.addFrame(sf::IntRect(0, 192, 64, 64));
		smallExplosion.addFrame(sf::IntRect(64, 192, 64, 64));
		smallExplosion.addFrame(sf::IntRect(128, 192, 64, 64));
		smallExplosion.addFrame(sf::IntRect(192, 192, 64, 64));
		smallExplosion.addFrame(sf::IntRect(256, 192, 64, 64));
		smallExplosion.addFrame(sf::IntRect(0, 256, 64, 64));
		smallExplosion.addFrame(sf::IntRect(64, 256, 64, 64));
		smallExplosion.addFrame(sf::IntRect(128, 256, 64, 64));
		smallExplosion.addFrame(sf::IntRect(192, 256, 64, 64));
		smallExplosion.addFrame(sf::IntRect(256, 256, 64, 64));*/
	}

	if (!explosionTexture.loadFromFile("explosionSheet.png"))
	{

	}

	explosionTexture.setSmooth(true);

	explosion.setSpriteSheet(explosionTexture);
	explosion.addFrame(sf::IntRect(0, 0, 64, 64));
	explosion.addFrame(sf::IntRect(64, 0, 64, 64));
	explosion.addFrame(sf::IntRect(128, 0, 64, 64));
	explosion.addFrame(sf::IntRect(192, 0, 64, 64));
	explosion.addFrame(sf::IntRect(256, 0, 64, 64));
	explosion.addFrame(sf::IntRect(0, 64, 64, 64));
	explosion.addFrame(sf::IntRect(64, 64, 64, 64));
	explosion.addFrame(sf::IntRect(128, 64, 64, 64));
	explosion.addFrame(sf::IntRect(192, 64, 64, 64));
	explosion.addFrame(sf::IntRect(256, 64, 64, 64));
	explosion.addFrame(sf::IntRect(0, 128, 64, 64));
	explosion.addFrame(sf::IntRect(64, 128, 64, 64));
	explosion.addFrame(sf::IntRect(128, 128, 64, 64));
	explosion.addFrame(sf::IntRect(192, 128, 64, 64));
	explosion.addFrame(sf::IntRect(256, 128, 64, 64));
	explosion.addFrame(sf::IntRect(0, 192, 64, 64));
	explosion.addFrame(sf::IntRect(64, 192, 64, 64));
	explosion.addFrame(sf::IntRect(128, 192, 64, 64));
	explosion.addFrame(sf::IntRect(192, 192, 64, 64));
	explosion.addFrame(sf::IntRect(256, 192, 64, 64));
	explosion.addFrame(sf::IntRect(0, 256, 64, 64));
	explosion.addFrame(sf::IntRect(64, 256, 64, 64));
	explosion.addFrame(sf::IntRect(128, 256, 64, 64));
	explosion.addFrame(sf::IntRect(192, 256, 64, 64));
	explosion.addFrame(sf::IntRect(256, 256, 64, 64));

	if (!fireEffectTexture.loadFromFile("fireStrip3.png"))
	{

	}

	fireEffectTexture.setSmooth(true);
	
	fireEffect.setSpriteSheet(fireEffectTexture);
	fireEffect.addFrame(sf::IntRect(0, 0, 182, 62));
	fireEffect.addFrame(sf::IntRect(91 * 2, 0, 182, 62));
	fireEffect.addFrame(sf::IntRect(182 * 2, 0, 182, 62));
	fireEffect.addFrame(sf::IntRect(273 * 2, 0, 182, 62));
	fireEffect.addFrame(sf::IntRect(364 * 2, 0, 182, 62));
	fireEffect.addFrame(sf::IntRect(455 * 2, 0, 182, 62));
	fireEffect.addFrame(sf::IntRect(546 * 2, 0, 182, 62));
	fireEffect.addFrame(sf::IntRect(637 * 2, 0, 182, 62));
	fireEffect.addFrame(sf::IntRect(728 * 2, 0, 182, 62));
	fireEffect.addFrame(sf::IntRect(819 * 2, 0, 182, 62));
	fireEffect.addFrame(sf::IntRect(910 * 2, 0, 182, 62));
	fireEffect.addFrame(sf::IntRect(1001 * 2, 0, 182, 62));


}

void AnimationManager::Update()
{
	sf::Time frameTime = frameClock.restart();

	for (int i = 0; i < animations.size(); i++)
	{
		animations.at(i)->update(frameTime);
	}

	DeleteExpired();
}

void AnimationManager::Draw(sf::RenderWindow & window)
{
	for (int i = 0; i < animations.size(); i++)
	{
		window.draw(*animations.at(i));
	}
}

void AnimationManager::CreateAnimation(sf::Vector2f position, float type, float angle)
{
	if (type == 1)
	{
		animations.push_back(new AnimatedSprite(sf::seconds(0.015), true, false));
		animations.at(animations.size() - 1)->setOrigin(32, 32);
		animations.at(animations.size() - 1)->setPosition(position);
		float scale1 = (rand() % 2 + 1) + 4;
		animations.at(animations.size() - 1)->setScale(sf::Vector2f(scale1 / 10, scale1 / 10));
		//animations.at(animations.size() - 1)->setColor(sf::Color(255, 255, 255, 200));
		animations.at(animations.size() - 1)->setRotation(rand() % 360 + 1);
		animations.at(animations.size() - 1)->play(explosion);
	}
	if (type == 2)
	{
		animations.push_back(new AnimatedSprite(sf::seconds(0.04), true, false));
		animations.at(animations.size() - 1)->setOrigin(162, 31);
		animations.at(animations.size() - 1)->setPosition(position);
		//float scale1 = (rand() % 1 + 0) + 2;
		//animations.at(animations.size() - 1)->setScale(sf::Vector2f(scale1 / 10, scale1 / 10));
		animations.at(animations.size() - 1)->setScale(sf::Vector2f(0.20f, 0.20f));
		animations.at(animations.size() - 1)->setColor(sf::Color(255, 255, 255, 200));
		animations.at(animations.size() - 1)->setRotation(angle);
		animations.at(animations.size() - 1)->play(fireEffect);
	}
	if (type == 3)
	{
		animations.push_back(new AnimatedSprite(sf::seconds(0.050), true, false));
		animations.at(animations.size() - 1)->setOrigin(50, 50);
		animations.at(animations.size() - 1)->setPosition(position);
		//float scale1 = (rand() % 40 + 40) + 4;
		animations.at(animations.size() - 1)->setScale(sf::Vector2f(50 / 10, 50 / 10));
		//animations.at(animations.size() - 1)->setColor(sf::Color(255, 255, 255, 200));
		animations.at(animations.size() - 1)->setRotation(rand() % 360 + 1);
		animations.at(animations.size() - 1)->play(largeExplosion);
	}
	if (type == 4)
	{
		animations.push_back(new AnimatedSprite(sf::seconds(0.050), true, false));
		animations.at(animations.size() - 1)->setOrigin(50, 50);
		animations.at(animations.size() - 1)->setPosition(position);
		float scale1 = (rand() % 2 + 1) + 1.5;
		animations.at(animations.size() - 1)->setScale(sf::Vector2f(scale1 / 10, scale1 / 10));
		//animations.at(animations.size() - 1)->setColor(sf::Color(255, 255, 255, 200));
		animations.at(animations.size() - 1)->setRotation(rand() % 360 + 1);
		animations.at(animations.size() - 1)->play(smallExplosion);
	}

	DeleteExpired();
}

void AnimationManager::DeleteExpired()
{
	vector<AnimatedSprite*>::iterator iter;
	vector<AnimatedSprite*>::iterator endIter;

	iter = animations.begin();
	endIter = animations.end();

	for (; iter != endIter; ++iter)
	{
		if ((*iter)->isPlaying() == false)
		{
			if (animations.size() == 1)
			{
				animations.clear();
				break;
			}
			else
			{
				iter = animations.erase(iter);
				iter = animations.begin();
				endIter = animations.end();
			}
		}
	}
}