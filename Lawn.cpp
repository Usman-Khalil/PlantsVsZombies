#include <iostream>
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"  
#include "SFML\Audio.hpp"
#include "Lawn.h"
#include "Plant.h"

using namespace std;
using namespace sf;


Lawn::Lawn() {
	lawn = nullptr;
}

void Lawn::initializeTextureForLawn() {

	// Initialize Background image
	if (!lawnTex.loadFromFile("Images/lawn.png"))
		throw "Could not load bg.jfif from file.";
	
	lawn = make_unique<Sprite>(lawnTex);
	lawn->setScale({ 0.97 , 1.175 });
	lawn->setOrigin({ lawn->getLocalBounds().size.x / 2 , lawn->getLocalBounds().size.y / 2 });
	//lawn->setRotation(degrees(270));
	lawn->setPosition({ lawn->getGlobalBounds().size.x / 2 , lawn->getGlobalBounds().size.y / 2 });

}

void Lawn::draw(RenderWindow& window) {

	window.draw(*lawn);
}

