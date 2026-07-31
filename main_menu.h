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
	Font font;

	Music mainMenu;

	unique_ptr<Sprite>main;
	unique_ptr<Text>exitButtonText;
	unique_ptr<Text>startButtonText;

	RectangleShape startButton;
	RectangleShape exitButton;


public:

	MainMenu();
	void initializeMainMenuTexture();
	void initialize();
	void closeMainMenu(RenderWindow&);
	void stopMusic();
};


#endif
#pragma once
