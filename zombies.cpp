#include <iostream>
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp" 
#include "Lawn.h"
#include "Plant.h"
#include "game.h"
#include <vector>
#include <string>
#include "zombies.h"

using namespace std;
using namespace sf;

Game game;

Zombies::Zombies() {

	zombie = nullptr;
	zombiesSpawnTime = 0;
	maxHpOfZombie = 50;

}

void Zombies::initializeTextureForZombies() {

	if (!zombiesTex.loadFromFile("Images/zombie.png"))
		throw "could not load zombie.png from file";

	zombie = make_unique<Sprite>(zombiesTex);
	zombie->setScale({ 0.075 , 0.075 });

	hpBar.setSize({ (float)(2 * maxHpOfZombie) , 10 });
	hpBar.setFillColor(Color::Red);
}

void Zombies::drawZombies(RenderWindow& window) {

	for (int i = 0; i < zombies.size(); i++) {
		window.draw(zombies[i]);
	}
	for (int i = 0; i < hpBarForAllZombies.size(); i++)
		window.draw(hpBarForAllZombies[i]);

}

void Zombies::spawningOfZombies(RenderWindow& window) {

	if (zombiesSpawnTime < (1000 - (2 * game.getNumberOfDieZombies())))
		zombiesSpawnTime++;
	if (zombiesSpawnTime >= (1000 - (2 * game.getNumberOfDieZombies()))) {
		
		int rowNum = rand() % 5;
		if(rowNum == 0)
			zombie->setPosition({ static_cast<float>(window.getSize().x) , 40 });
		else if (rowNum == 1)
			zombie->setPosition({ static_cast<float>(window.getSize().x) , 160 });
		else if (rowNum == 2)
			zombie->setPosition({ static_cast<float>(window.getSize().x) , 295 });
		else if (rowNum == 3)
			zombie->setPosition({ static_cast<float>(window.getSize().x) , 400 });
		else
			zombie->setPosition({ static_cast<float>(window.getSize().x) , 545 });
		
		hpBar.setPosition({ zombie->getPosition().x , zombie->getPosition().y - 10 });
		hpBarForAllZombies.push_back(hpBar);
		zombies.push_back(*zombie);
		hpOfzombies.push_back(maxHpOfZombie);
		zombiesSpawnTime = 0;

	}

	for (int i = 0; i < zombies.size(); i++) {

		zombies[i].move({ -0.3f,0 });

	}
}

vector<Sprite>& Zombies::getZombies() {

	return zombies;
}

vector<int>& Zombies::getHpOfZombies() {

	return hpOfzombies;
}