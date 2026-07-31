#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"  
#include "SFML/Audio.hpp"
#include "Lawn.h"
#include "Plant.h"
#include "game.h"
#include <vector>
#include <string>
#include "zombies.h"
#include "projectiles.h"

using namespace std;
using namespace sf;

Projectiles::Projectiles() {

	greenBullet = nullptr;
	blueBullet = nullptr;
	sunFlower = nullptr;

}

void Projectiles::initializeTextureOfProjectiles() {

	if (!greenBulletTex.loadFromFile("Images/green_ball2.png"))
		throw "could not load green_ball.png from the file";

	greenBullet = make_unique<Sprite>(greenBulletTex);
	greenBullet->setScale({ 0.35 , 0.35 });

	if (!blueBulletTex.loadFromFile("Images/blue_ball.png"))
		throw "could not load blue_ball.png from the file";

	blueBullet = make_unique<Sprite>(blueBulletTex);
	blueBullet->setScale({ 0.4 , 0.4 });

	if (!sunFlowerTex.loadFromFile("Images/sun.png"))
		throw "could not load sun.png from the file";

	sunFlower = make_unique<Sprite>(sunFlowerTex);
	sunFlower->setScale({ 0.6 , 0.6 }); 

}

Sprite& Projectiles::getGreenBullet() {
	return *greenBullet;
}

Sprite& Projectiles::getBlueBullet() {
	return *blueBullet;
}

Sprite& Projectiles::getSunFlower() {
	return *sunFlower;
}