#include <cstdlib>
#include <ctime>

#include <fstream>
#include <string>
#include <memory>
using namespace std;

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "ResourceManager.h"

#include "Level.h"

int main (int argc, const char * argv[])
{
	//Seeding for Duck
	srand(time(NULL));
	
	sfrm::ResourceManager resources;

	sf::RenderWindow window(sf::VideoMode(1024, 896), "DueckHuent", sf::Style::Close);
	
	int score=0;
	
	string line;
	ifstream myfile ("score.txt");
	if (myfile.is_open())
	{
		getline (myfile,line);
		score=stoi(line);
		myfile.close();
	}
	else
	{
		ofstream myfile ("score.txt");
		if (myfile.is_open())
		{
			myfile << "0";
			myfile.close();
		}
	}
	
	sf::Font font;
	font.loadFromFile("assets/fonts/Romulus.ttf");
	sf::Text dueckHuent("DueckHuent", font, 180);
	dueckHuent.setPosition(100, 0);
	sf::Text start("Press ENTER to start!", font, 80);
	start.setPosition(150, 400);
	sf::Text topScore("TOP SCORE = " +to_string(score), font, 80);
	topScore.setPosition(150, 675);
	sf::Text credits("2013 fuerchter font by Hewett Tsoi", font, 50);
	credits.setPosition(150, 800);
	
	shared_ptr<Level> level;
	bool ingame=false;
	
	sf::Clock clock;
	sf::Time previousTick=clock.getElapsedTime();
	sf::Time deltaTime;
	
	sf::Time counter=clock.getElapsedTime();
	int fps=0;
	
	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			switch(event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}
		}
		
		deltaTime=clock.getElapsedTime()-previousTick;
		previousTick=clock.getElapsedTime();
		
		fps++;
		counter+=deltaTime;
		if(counter.asSeconds()>=1)
		{
			//cout << fps << endl;
			fps=0;
			counter=sf::Time::Zero;
		}
		
		//UPDATE SECTION
		if(ingame)
		{
			level->update(deltaTime.asSeconds(), window, resources);
			if(level->isGameOver())
			{
				ingame=false;
				if(level->getFinalScore()>score)
				{
					score=level->getFinalScore();
					topScore.setString("TOP SCORE = " +to_string(score));
					
					ofstream myfile ("score.txt");
					if (myfile.is_open())
					{
						myfile << to_string(score);
						myfile.close();
					}
				}
			}
		}
		else
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				ingame=true;
				level=make_shared<Level>(resources, window.getSize(), font);
			}
		}
		//UPDATE SECTION
		
		
		
		//DRAW SECTION
		if(ingame)
		{
			window.clear(sf::Color(60, 188, 252));
			level->draw(window);
		}
		else
		{
			window.clear();
			window.draw(dueckHuent);
			window.draw(start);
			window.draw(topScore);
			window.draw(credits);
		}
		//DRAW SECTION
		
		window.display();
	}
}