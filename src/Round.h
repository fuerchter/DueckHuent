#ifndef ROUND
#define ROUND

#include <cstdlib>

#include <string>
#include <queue>
using namespace std;

#include "SFML/Graphics.hpp"

#include "ResourceManager.h"

#include "Duck.h"
#include "RoundStats.h"
#include "DuckType.h"

class Round
{
public:
	Round(sfrm::ResourceManager &resources, vector<DuckType> types, int round, sf::Vector2u windowSize, int score, sf::Font &font);
	bool empty();
	int getHitsLeft();
	int getScore();
	void update(float dt, sf::RenderWindow &window);
	void draw(sf::RenderWindow &window);
private:
	void nextDuck();
	void handleCollision(sf::FloatRect duckBounds, sf::Vector2u windowSize);

	vector<DuckType> types_;
	int round_;
	int maxDucks_;
	queue<Duck> ducks_;
	int hitsLeft_;
	int maxAmmo_;
	int ammo_;
	bool pressedPreviously_;
	float scoreMultiplicator_;
	int score_;
	
	sf::Text roundText_;
	sf::Text ammoText_;
	sf::Text advanceText_;
	sf::Text scoreText_;
	
	sf::Sound shotSound_;
};

#endif