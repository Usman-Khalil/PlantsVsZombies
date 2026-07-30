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

	Font font;

	unique_ptr<Sprite>flower;
	unique_ptr<Sprite>activePlant;
	unique_ptr<Text>gameOverText;

	vector<Sprite>flowers;
	vector<Sprite>placedPlants;
	vector<char>genreOfPlacedPlants;
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
	bool playerStatus;
	int noOfZombiesDie;

public:

	Game();
	void droppingFlowers(RenderWindow&);
	void collectFlowers(Vector2f);
	void initializeGame(RenderWindow&);
	void initializeGameObjects();
	void selectingPlant(Vector2f);
	void previewPlant();
	void placePlants(Vector2f);
	void throwGreenBalls(RenderWindow&);
	void throwBlueBalls(RenderWindow&);
	void throwSuns(RenderWindow&);
	void zombiesVsPlants();
	void zombiesVsGreenBullets();
	void zombiesVsBlueBullets();
	void isPlayerAlive();
	void updateZombiesSpawnTime();
};

#endif
#pragma once
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            