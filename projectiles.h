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
#ifndef PROJETILES_H
#define PROJECTILES_H

using namespace std;
using namespace sf;

class Projectiles
{
	Texture greenBulletTex;
	Texture blueBulletTex;
	Texture sunFlowerTex;

	unique_ptr<Sprite>greenBullet;
	unique_ptr<Sprite>blueBullet;
	unique_ptr<Sprite>sunFlower;

public:

	Projectiles();
	void initializeTextureOfProjectiles();
	void drawProjectiles(RenderWindow&);
	Sprite& getGreenBullet();
	Sprite& getBlueBullet();
	Sprite& getSunFlower();
};

#endif
#pragma once
