#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"  
#include "SFML/Audio.hpp"
#include "Lawn.h"
#include "Plant.h"
#include "game.h"
#include <vector>
#include <string>
#include "zombies.h"

using namespace std;
using namespace sf;


Zombies::Zombies() {

	zombie = nullptr;
	zombiesSpawnTime = 0;
	maxHpOfZombie = 50;
	maxSpawnTime = 1000;
	musicPlayed = false;
}

void Zombies::initializeTextureForZombies() {

	if (!zombiesTex.loadFromFile("Images/zombie.png"))
		throw "could not load zombie.png from file";

	zombie = make_unique<Sprite>(zombiesTex);
	zombie->setScale({ 0.075 , 0.075 });

	hpBar.setSize({ (float)(1.1 * maxHpOfZombie) , 10 });
	hpBar.setFillColor(Color::Red);

	if (!grassStep.openFromFile("Music/zombiesComing.ogg"))
		throw "could not open zombiesComing.ogg from the file";
}

void Zombies::drawZombies(RenderWindow& window) {

	for (int i = 0; i < zombies.size(); i++) {
		window.draw(zombies[i]);
	}
	for (int i = 0; i < hpBarForAllZombies.size(); i++)
		window.draw(hpBarForAllZombies[i]);

}

void Zombies::spawningOfZombies(RenderWindow& window) {

	if (zombiesSpawnTime < maxSpawnTime)
		zombiesSpawnTime++;
	if (zombiesSpawnTime >= maxSpawnTime) {
		
		int rowNum = rand() % 5;
		if(rowNum == 0)
			zombie->setPosition({ static_cast<float>(window.getSize().x) , 20 });
		else if (rowNum == 1)
			zombie->setPosition({ static_cast<float>(window.getSize().x) , 160 });
		else if (rowNum == 2)
			zombie->setPosition({ static_cast<float>(window.getSize().x) , 300 });
		else if (rowNum == 3)
			zombie->setPosition({ static_cast<float>(window.getSize().x) , 440 });
		else
			zombie->setPosition({ static_cast<float>(window.getSize().x) , 580 });
		
		if (!musicPlayed) {
			grassStep.play();
			musicPlayed = true;
		}
		hpBar.setPosition({ zombie->getPosition().x , zombie->getPosition().y - 15 });
		hpBarForAllZombies.push_back(hpBar);
		zombies.push_back(*zombie);
		hpOfzombies.push_back(maxHpOfZombie);
		zombiesSpawnTime = 0;

	}

	for (int i = 0; i < zombies.size(); i++) {

		zombies[i].move({ -0.3f,0 });
		hpBarForAllZombies[i].move({ -0.3f , 0 });

	}
}

vector<Sprite>& Zombies::getZombies() {

	return zombies;
}

vector<int>& Zombies::getHpOfZombies() {

	return hpOfzombies;
}             

vector<RectangleShape>& Zombies::getHpBarOfZombies() {
	return hpBarForAllZombies;
}

int& Zombies::getZombieSpawntime() {
	return maxSpawnTime;
}