#include "Level.h"

Level::Level(sfrm::ResourceManager &resources, sf::Vector2u windowSize, sf::Font &font):
round_(1)
{
	DuckType black;
	black.basePoints=500;
	black.textureName="assets/images/black.png";
	DuckType blue;
	blue.basePoints=1000;
	blue.textureName="assets/images/blue.png";
	DuckType red;
	red.basePoints=1500;
	red.textureName="assets/images/red.png";
	
	types_.push_back(black);
	types_.push_back(blue);
	types_.push_back(red);
	
	font_=font;
	currentRound_=unique_ptr<Round>(new Round(resources, types_, round_, windowSize, 0, font_));
	
	grass_=sf::Sprite(resources.getTexture("assets/images/grass.png"));
	grass_.setPosition(0, windowSize.y-grass_.getGlobalBounds().height);
	
	gameOver_=false;
	finalScore_=0;
}

bool Level::isGameOver()
{
	return gameOver_;
}

int Level::getFinalScore()
{
	return finalScore_;
}

void Level::update(float dt, sf::RenderWindow &window, sfrm::ResourceManager &resources)
{
	if(currentRound_->empty())
	{
		int score=currentRound_->getScore();
		if(currentRound_->getHitsLeft()<=0)
		{
			round_++;
			currentRound_=unique_ptr<Round>(new Round(resources, types_, round_, window.getSize(), score, font_));
		}
		else
		{
			gameOver_=true;
			finalScore_=score;
		}
	}
	else
	{
		currentRound_->update(dt, window);
	}
}

void Level::draw(sf::RenderWindow &window)
{
	currentRound_->draw(window);
	window.draw(grass_);
}