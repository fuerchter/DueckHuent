#include "Round.h"

Round::Round(sfrm::ResourceManager &resources, vector<DuckType> types, int round, sf::Vector2u windowSize, int score, sf::Font &font):
types_(types), round_(round)
{
	RoundStats roundStats(round, maxDucks_);
	//cout << "Round " << round << endl;
	//roundStats.printOut();
	maxDucks_=10;
	for(int i=1; i<=maxDucks_; i++)
	{
		ducks_.push(Duck(resources, roundStats, types[rand()%types.size()], windowSize));
	}
	hitsLeft_=roundStats.getHitsToAdvance();
	maxAmmo_=3;
	ammo_=maxAmmo_;
	pressedPreviously_=true;
	scoreMultiplicator_=roundStats.getScoreMultiplicator();
	score_=score;
	
	roundText_=sf::Text("R="+to_string(round_), font);
	roundText_.setPosition(100, 0);
	ammoText_=sf::Text("SHOT " +to_string(ammo_), font);
	ammoText_.setPosition(200, 0);
	advanceText_=sf::Text("DUECKS TO ADVANCE " +to_string(hitsLeft_), font);
	advanceText_.setPosition(400, 0);
	scoreText_=sf::Text("SCORE " +to_string(score_), font);
	scoreText_.setPosition(750, 0);
	
	shotSound_=sf::Sound(resources.getSoundBuffer("assets/sounds/shot.wav"));
}

bool Round::empty()
{
	return ducks_.empty();
}

int Round::getHitsLeft()
{
	return hitsLeft_;
}

int Round::getScore()
{
	return score_;
}

void Round::update(float dt, sf::RenderWindow &window)
{
	ducks_.front().update(dt);
	
	sf::FloatRect duckBounds=ducks_.front().getGlobalBounds();
	
	if(!ducks_.front().isShot())
	{
		handleCollision(duckBounds, window.getSize());
		
		//Mouse released
		if(pressedPreviously_ && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			pressedPreviously_=false;
		}
		//Mouse pressed
		if(!pressedPreviously_ && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			pressedPreviously_=true;
			
			//Shot
			if(ammo_>0)
			{
				shotSound_.play();
				ammo_--;
				if(duckBounds.contains(sf::Vector2f(sf::Mouse::getPosition(window))))
				{
					//Killed duck
					score_+=ducks_.front().getBasePoints()*scoreMultiplicator_;
					hitsLeft_--;
					ducks_.front().shot();
				}
				else
				{
					if(ammo_<=0)
					{
						ducks_.front().timeLeftZero();
					}
				}
				//cout << "Shot at " << sf::Mouse::getPosition(window).x << " " << sf::Mouse::getPosition(window).y << "! Ammo: " << ammo_ << "! Hits left: " << hitsLeft_ << "! Score: " << score_ << "! BasePoints/Multiplicator:" << ducks_.front().getBasePoints() << " " << scoreMultiplicator_ << endl;
			}
		}
	}
	
	sf::FloatRect windowRect(0, 0, window.getSize().x, window.getSize().y);
	
	//Duck flew off or hit ground
	if(!duckBounds.intersects(windowRect))
	{
		nextDuck();
	}
	
	ammoText_.setString("SHOT " +to_string(ammo_));
	scoreText_.setString("SCORE " +to_string(score_));
}

void Round::draw(sf::RenderWindow &window)
{
	if(!empty())
	{
		ducks_.front().draw(window);
	}
	window.draw(roundText_);
	window.draw(ammoText_);
	window.draw(advanceText_);
	window.draw(scoreText_);
}

void Round::nextDuck()
{
	ammo_=maxAmmo_;
	ducks_.pop();
}

void Round::handleCollision(sf::FloatRect duckBounds, sf::Vector2u windowSize)
{
	if(ducks_.front().getTimeLeft()>0)
	{
		//collision holds which screen edge we collided with
		sf::Vector2i collision;
		if(duckBounds.top<0)
		{
			collision.y--;
		}
		if(duckBounds.top+duckBounds.height>windowSize.y)
		{
			collision.y++;
		}
		if(duckBounds.left<0)
		{
			collision.x--;
		}
		if(duckBounds.left+duckBounds.width>windowSize.x)
		{
			collision.x++;
		}
		
		if(collision.x!=0 || collision.y!=0)
		{
			ducks_.front().generateDirection(collision);
		}
	}
}