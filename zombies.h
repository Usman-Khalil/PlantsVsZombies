#ifndef ZOMBIES_H
#define ZOMBIES_H
#include <iostream>
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp" 
#include "Lawn.h"
#include "Plant.h"
#include "game.h"
#include <vector>
#include <string>

using namespace std;
using namespace sf;

class Zombies
{

	Texture zombiesTex;
	unique_ptr<Sprite>zombie;
	vector<Sprite>zombies;
	vector<int>hpOfzombies;

	RectangleShape hpBar;
	vector<RectangleShape>hpBarForAllZombies;

	int zombiesSpawnTime;
	int maxHpOfZombie;

public:

	Zombies();
	void initializeTextureForZombies();
	void drawZombies(RenderWindow&);
	void spawningOfZombies(RenderWindow&);
	vector<Sprite>& getZombies();
	vector<int>& getHpOfZombies();


};


#endif
#pragma once
