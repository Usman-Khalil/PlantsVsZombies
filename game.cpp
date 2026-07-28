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
#include "projectiles.h"

using namespace std;
using namespace sf;

Plant plant;
Lawn lawn;
Zombies zombie;
Projectiles projectile;


Game::Game() {

	flower = nullptr;
	flowerSpawnTime = 0;
	greenSpawnTime = 0;
	sunSpawnTime = 0;
	activePlant = nullptr;
	selectedPlant = 'N';
	activeStatus = false;
}

void Game::initializeGame() {

	// Initialize Objects For Window

	lawn.initializeTextureForLawn();
	plant.initializeTextureForPlants();
	plant.initializeFontsForPlants();
	zombie.initializeTextureForZombies();
	projectile.initializeTextureOfProjectiles();
	initializeGameObjects();

	RenderWindow window(VideoMode({ 1300 , 700 }), "Plant_VS_Zombies");
	window.setFramerateLimit(60);

	while (window.isOpen()) {

		while (const optional event = window.pollEvent()) {
			if (event->is<Event::Closed>())
				window.close();
			if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
			{
				if (mousePressed->button == Mouse::Button::Left)
				{
					Vector2f mousePos;
					mousePos.x = Mouse::getPosition().x;
					mousePos.y = Mouse::getPosition().y;
					selectingPlant(mousePos);
				}
			}
		}

		// Updates Everything here
		droppingFlowers(window);
		zombie.spawningOfZombies(window);
		plant.statusOfPlants();
		if (activeStatus)
			previewPlant();

		window.clear();

		//Draw Objects

		lawn.draw(window);
		plant.drawPlants(window);
		zombie.drawZombies(window);

		if (activePlant != nullptr)
			window.draw(*activePlant);
		for (int i = 0; i < flowers.size(); i++) {
			window.draw(flowers[i]);
		}
		for (int i = 0; i < placedPlants.size(); i++) {
			window.draw(placedPlants[i]);
		}
		for (int i = 0; i < greenBullets.size(); i++) {
			window.draw(greenBullets[i]);
		}
		for (int i = 0; i < blueBullets.size(); i++) {
			window.draw(blueBullets[i]);
		}
		for (int i = 0; i < sunFlower.size(); i++) {
			window.draw(sunFlower[i]);
		}

		//

		window.display();
	}
}

void Game::initializeGameObjects() {

	if (!flowerTex.loadFromFile("Images/sun.png"))
		throw "could not load sun.png from the file";

	flower = make_unique<Sprite>(flowerTex);
	flower->setScale({ 0.01 , 0.01 });

}

void Game::droppingFlowers(RenderWindow& window) {

	if (flowerSpawnTime < 600)
		flowerSpawnTime++;
	if (flowerSpawnTime >= 600) {

		flower->setPosition({ 300 + static_cast<float>(rand() % (window.getSize().x - 100)) , 0 });
		flowers.push_back(*flower);
		flowerSpawnTime = 0;

	}
	for (int i = 0; i < flowers.size(); i++) {

		flowers[i].move({ 0,0.5 });
		
		if (flowers[i].getPosition().y > window.getSize().y - 100)
		{
			flowers.erase(flowers.begin() + i);
			break;
		}

	}
}

void Game::selectingPlant(Vector2f pos) {

	if (plant.getBluePlantGlobalBounds().contains(pos) && plant.numOfSunFlower >= 200) {
		activeStatus = true;
		selectedPlant = 'B';
	}
	else if (plant.getGreenPlantGlobalBounds().contains(pos) && plant.numOfSunFlower >= 100) {
		activeStatus = true;
		selectedPlant = 'G';
	}
	else if (plant.getSunFlowerPlantGlobalBounds().contains(pos) && plant.numOfSunFlower >= 50) {
		activeStatus = true;
		selectedPlant = 'S';
	}
	else {
		if (activeStatus)
			placePlants(pos);
		else
			collectFlowers(pos);
	}

	if (selectedPlant == 'B')
	{
		activePlant = make_unique<Sprite>(plant.getBluePlant());
		activePlant->setScale({ 0.09 , 0.09 });
	}
	else if (selectedPlant == 'G')
	{
		activePlant = make_unique<Sprite>(plant.getGreenPlant());
		activePlant->setScale({ 0.06 , 0.06 });
	}
	else if (selectedPlant == 'S')
	{
		activePlant = make_unique<Sprite>(plant.getSunFlowerPlant());
		activePlant->setScale({ 0.055 , 0.055 });
	}
	else
		return;
}

void Game::previewPlant() {

	activePlant->setPosition({ static_cast<float>(Mouse::getPosition().x) , static_cast<float>(Mouse::getPosition().y) });
}

void Game::placePlants(Vector2f pos) {
	if (activePlant == nullptr)
		return;

	activePlant->setPosition(pos);
	placedPlants.push_back(*activePlant);
	activePlant = nullptr;
	activeStatus = false;
	if (selectedPlant == 'G')
	{
		plant.numOfSunFlower -= 100;
	}
	else if (selectedPlant == 'B')
	{
		plant.numOfSunFlower -= 200;
	}
	else if (selectedPlant == 'S')
	{
		plant.numOfSunFlower -= 50;
	}
	plant.amount->setString(to_string(plant.numOfSunFlower));
	selectedPlant = 'N';

}

void Game::collectFlowers(Vector2f pos) {
	for (int i = 0; i < flowers.size(); i++) {

		if (flowers[i].getGlobalBounds().contains(pos)) {
			flowers.erase(flowers.begin() + i);
			plant.numOfSunFlower += 25;
			plant.amount->setString(to_string(plant.numOfSunFlower));
			break;
		}

	}
}
void Game::throwGreenBalls() {

	for (int i = 0; i < greenBullets.size(); i++) {
		greenBullets[i].move({ 2 , 0 });
	}

}

void Game::throwBlueBalls() {

	for (int i = 0; i < blueBullets.size(); i++) {
		blueBullets[i].move({ 2 , 0 });
	}

}

void Game::throwSuns() {

	for (int i = 0; i < sunFlower.size(); i++) {
		sunFlower[i].move({ 2 , 0 });
	}

}


//Game
//│
//├── Event System
//├── Grid
//├── PlantManager
//│      ├── Place Plants
//│      ├── Update Plants
//│      └── Draw Plants
//│
//├── ZombieManager
//│      ├── Spawn
//│      ├── Update
//│      └── Draw
//│
//├── BulletManager
//│      ├── Spawn
//│      ├── Update
//│      └── Draw
//│
//├── SunManager
//│      ├── Spawn
//│      ├── Collect
//│      └── Draw
//│
//└── CollisionManager
//├── Bullet ↔ Zombie
//└── Zombie ↔ Plant

//Program Starts
//│
//▼
//Initialize Game
//│
//├── Load Textures
//├── Load Fonts
//├── Create Window
//├── Initialize Lawn
//├── Initialize Plant Menu
//├── Initialize Zombies
//└── Initialize HUD
//│
//▼
//============================ =
//GAME LOOP
//============================ =
//│
//▼
//Handle Events
//│
//├── Window Close
//├── Mouse Click
//├── Keyboard
//└── Plant Selection
//│
//▼
//Update Game
//│
//├── Spawn Suns
//├── Spawn Zombies
//├── Place Plants
//├── Plants Shoot
//├── Move Bullets
//├── Move Zombies
//├── Bullet vs Zombie
//├── Zombie vs Plant
//├── Remove Dead Objects
//├── Update Sun Count
//└── Check Win / Lose
//│
//▼
//Draw Everything
//│
//├── Lawn
//├── Grid
//├── Plants
//├── Zombies
//├── Bullets
//├── Suns
//├── HUD
//└── Preview Plant
//│
//▼
//Display Frame
//│
//▼
//Repeat Until Window Closes