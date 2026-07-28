#ifndef GAME_H
#define GAME_H
#include <iostream>
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp" 
#include "Lawn.h"
#include "Plant.h"
#include <vector>

using namespace std;
using namespace sf;

class Game
{
	Texture flowerTex;
	Texture activePlantTex;

	unique_ptr<Sprite>flower;
	unique_ptr<Sprite>activePlant;

	vector<Sprite>flowers;
	vector<Sprite>placedPlants;
	vector<Sprite>greenBullets;
	vector<Sprite>blueBullets;
	vector<Sprite>sunFlower;

	Vector2f greenBallPos;
	Vector2f blueBallPos;
	Vector2f sunPos;

	int flowerSpawnTime;
	int greenSpawnTime;
	int blueSpawnTime;
	int sunSpawnTime;
	bool activeStatus;
	char selectedPlant;

public:

	Game();
	void droppingFlowers(RenderWindow&);
	void collectFlowers(Vector2f);
	void initializeGame();
	void initializeGameObjects();
	void selectingPlant(Vector2f);
	void previewPlant();
	void placePlants(Vector2f);
	void firing();
	void throwGreenBalls();
	void throwBlueBalls();
	void throwSuns();
};

#endif
#pragma once
