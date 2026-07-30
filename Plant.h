#include <iostream>
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"  
#include "SFML\Audio.hpp"
#include "Lawn.h"
#include <vector>
#ifndef PLANT_H
#define PLANT_H

using namespace std;
using namespace sf;


class Plant 
{
	Texture greenPlantTex;
	Texture bluePlantTex;
	Texture sunFlowerPlantTex;
	Texture priceBarTex;
	Texture amountBarTex;

	unique_ptr<Sprite> greenPlant;
	unique_ptr<Sprite> bluePlant;
	unique_ptr<Sprite> sunFlowerPlant;
	unique_ptr<Sprite> priceBar;
	unique_ptr<Sprite> amountBar;

	int greenShootTime;
	int blueShootTime;
	int sunGlowTime;
	  
	Font font;

	unique_ptr<Text> greenFooter;
	unique_ptr<Text> blueFooter;
	unique_ptr<Text> sunFooter;

public:

	unique_ptr<Text> amount;
	int numOfSunFlower;

	Plant();
	void initializeTextureForPlants();
	void initializeFontsForPlants();
	void drawPlants(RenderWindow&);
	void statusOfPlants(); 
	FloatRect getGreenPlantGlobalBounds();
	FloatRect getBluePlantGlobalBounds();
	FloatRect getSunFlowerPlantGlobalBounds();
	Sprite& getGreenPlant();
	Sprite& getBluePlant();
	Sprite& getSunFlowerPlant();

	Texture getGreenTex();
	Texture& getBlueTex();
	Texture& getSunFlowerTex();

};


#endif
#pragma once
