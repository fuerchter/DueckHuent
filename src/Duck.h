#ifndef DUCK
#define DUCK

#include <cstdlib>
#include <cmath>

#include <iostream>
using namespace std;

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"

#include "ResourceManager.h"

#include "RoundStats.h"
#include "DuckType.h"

class Duck
{
public:
	Duck(sfrm::ResourceManager &resources, RoundStats roundStats, DuckType type, sf::Vector2u windowSize);
	void generateDirection(sf::Vector2i collision);
	sf::FloatRect getGlobalBounds();
	float getTimeLeft();
	void timeLeftZero();
	int getBasePoints();
	bool isShot();
	void shot();
	void update(float dt);
	void draw(sf::RenderWindow &window);
private:
	float speed_;
	float timeLeft_;
	sf::Vector2f direction_;
	int basePoints_;
	sf::Sprite sprite_;
	bool shot_;
	float fallSpeed_;
};

#endif