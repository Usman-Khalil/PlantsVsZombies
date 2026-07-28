#ifndef LAWN_H
#define LAWN_H
#include <iostream>
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp" 

using namespace std;
using namespace sf;

class Lawn
{

	Texture lawnTex;
	unique_ptr<Sprite> lawn;


public:

	Lawn();
	void initializeTextureForLawn();
	void draw(RenderWindow&);

};

#endif
#pragma once
