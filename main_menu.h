#ifndef MAIN_MENU_H
#define MAIN_MENU_H
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


class MainMenu
{
	Texture mainTex;
	Texture loadingTex;
	Texture bgTex;
	Font font;

	Music mainMenu;

	unique_ptr<Sprite>main;
	unique_ptr<Sprite>loading;
	unique_ptr<Sprite>bg;
	unique_ptr<Text>startButtonText;

	int loadingTime;

public:

	MainMenu();
	void initializeMainMenuTexture(RenderWindow&);
	void initialize();
	void closeMainMenu(RenderWindow&);
	void stopMusic();
};


#endif
#pragma once
