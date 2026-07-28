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
}

void Zombies::drawZombies(RenderWindow& window) {

	for (int i = 0; i < zombies.size(); i++) {
		window.draw(zombies[i]);
	}

}

void Zombies::spawningOfZombies(RenderWindow& window) {

	if (zombiesSpawnTime < 1000)
		zombiesSpawnTime++;
	if (zombiesSpawnTime >= 1000) {
		
		int rowNum = rand() % 5;
		if(rowNum == 0)
			zombie->setPosition({ static_cast<float>(window.getSize().x) , 45 });
		else if (rowNum == 1)
			zombie->setPosition({ static_cast<float>(window.getSize().x) , 165 });
		else if (rowNum == 2)
			zombie->setPosition({ static_cast<float>(window.getSize().x) , 300 });
		else if (rowNum == 3)
			zombie->setPosition({ static_cast<float>(window.getSize().x) , 410 });
		else
			zombie->setPosition({ static_cast<float>(window.getSize().x) , 550 });

		zombies.push_back(*zombie);
		zombiesSpawnTime = 0;

	}

	for (int i = 0; i < zombies.size(); i++) {

		zombies[i].move({ -0.3f,0 });

	}
}