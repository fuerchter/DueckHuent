#ifndef LEVEL
#define LEVEL

#include <memory>
using namespace std;

#include "ResourceManager.h"

#include "Round.h"

class Level
{
public:
	Level(sfrm::ResourceManager &resources, sf::Vector2u windowSize, sf::Font &font);
	bool isGameOver();
	int getFinalScore();
	void update(float dt, sf::RenderWindow &window, sfrm::ResourceManager &resources);
	void draw(sf::RenderWindow &window);
private:
	int round_;
	vector<DuckType> types_;
	sf::Font font_;
	unique_ptr<Round> currentRound_;
	sf::Sprite grass_;
	bool gameOver_;
	int finalScore_;
};

#endif