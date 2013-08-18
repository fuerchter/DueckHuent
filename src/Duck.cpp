#include "Duck.h"

Duck::Duck(sfrm::ResourceManager &resources, RoundStats roundStats, DuckType type, sf::Vector2u windowSize):
speed_(roundStats.getSpeed()), timeLeft_(roundStats.getFlyAwayTime())
{
	generateDirection(sf::Vector2i());
	
	basePoints_=type.basePoints;
	sprite_=sf::Sprite(resources.getTexture(type.textureName));
	sprite_.setOrigin(sprite_.getLocalBounds().width/2, sprite_.getLocalBounds().height/2);
	int xPosition=rand()%(windowSize.x-(int)sprite_.getGlobalBounds().width)+sprite_.getGlobalBounds().width/2;
	sprite_.setPosition(xPosition, windowSize.y-sprite_.getGlobalBounds().height/2);
	shot_=false;
	fallSpeed_=150;
}

void Duck::generateDirection(sf::Vector2i collision)
{
	//random x and y between -1.00 and 1.00, then normalized
	direction_.x=(float)(rand()%200-100)/100;
	direction_.y=(float)(rand()%200-100)/100;
	float length=sqrt(direction_.x*direction_.x+direction_.y*direction_.y);
	direction_/=length;
	
	if(collision.x!=0)
	{
		direction_.x=abs(direction_.x)*-collision.x;
	}
	if(collision.y!=0)
	{
		//Example: top collision will make collision.y==-1, the new y direction then becomes positive
		direction_.y=abs(direction_.y)*-collision.y;
	}
	//cout << "New direction: " << direction_.x << " " << direction_.y << endl;
}

sf::FloatRect Duck::getGlobalBounds()
{
	return sprite_.getGlobalBounds();
}

float Duck::getTimeLeft()
{
	return timeLeft_;
}

void Duck::timeLeftZero()
{
	timeLeft_=0;
}

int Duck::getBasePoints()
{
	return basePoints_;
}

bool Duck::isShot()
{
	return shot_;
}

void Duck::shot()
{
	shot_=true;
}

void Duck::update(float dt)
{
	if(shot_)
	{
		sprite_.move(0, fallSpeed_*dt);
	}
	else
	{
		//cout << timeLeft_ << endl;
		if(timeLeft_>0)
		{
			timeLeft_-=dt;
		}
		
		sprite_.move(direction_*speed_*dt);
	}
}

void Duck::draw(sf::RenderWindow &window)
{
	window.draw(sprite_);
}