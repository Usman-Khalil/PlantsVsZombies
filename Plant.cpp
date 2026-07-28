#include <iostream>
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp" 
#include "Lawn.h"
#include <vector>
#include "Plant.h"

using namespace std;
using namespace sf;


Plant::Plant() {

	greenPlant = nullptr;
	bluePlant = nullptr;
	sunFlowerPlant = nullptr;
	priceBar = nullptr;
	greenFooter = nullptr;
	blueFooter = nullptr;
	sunFooter = nullptr;
	amountBar = nullptr;

	greenShootTime = 0;
	blueShootTime = 0;
	sunGlowTime = 0;
	numOfSunFlower = 50;

}

void Plant::initializeTextureForPlants() {

	//Green

	if (!greenPlantTex.loadFromFile("Images/green.png"))
		throw "could not load green.png from file";

	greenPlant = make_unique<Sprite>(greenPlantTex);
	greenPlant->setScale({ 0.05 , 0.05 });
	greenPlant->setPosition({ 5,5 });
	greenPlant->setColor(Color(255, 255, 255, 150));

	//Blue

	if (!bluePlantTex.loadFromFile("Images/blue.png"))
		throw "could not load blue.png from file";

	bluePlant = make_unique<Sprite>(bluePlantTex);
	bluePlant->setScale({ 0.08 , 0.08 });
	bluePlant->setPosition({ greenPlant->getPosition().x + greenPlant->getGlobalBounds().size.x + 5 ,5});
	bluePlant->setColor(Color(255, 255, 255, 150));

	//sunFlower

	if (!sunFlowerPlantTex.loadFromFile("Images/sun_flower.png"))
		throw "could not load sun_flower.png from file";

	sunFlowerPlant = make_unique<Sprite>(sunFlowerPlantTex);
	sunFlowerPlant->setScale({ 0.05 , 0.045 });
	sunFlowerPlant->setPosition({ bluePlant->getPosition().x + bluePlant->getGlobalBounds().size.x + 5,5 });
	sunFlowerPlant->setColor(Color(255, 255, 255, 150));

	//PriceBar

	if (!priceBarTex.loadFromFile("Images/price_bar.png"))
		throw "could not load price_bar.jfif from file";

	priceBar = make_unique<Sprite>(priceBarTex);
	priceBar->setScale({ 0.45 , 0.25 });
	priceBar->setPosition({ greenPlant->getPosition().x + 8 ,greenPlant->getPosition().y + greenPlant->getGlobalBounds().size.y + 3 });

	//AmountBar

	amountBar = make_unique<Sprite>(priceBarTex);
	amountBar->setScale({ 0.10 , 0.20 });
	amountBar->setPosition({ greenPlant->getPosition().x + 20 , priceBar->getPosition().y + priceBar->getGlobalBounds().size.y + 22 });

}

void Plant::initializeFontsForPlants() {

	if (!font.openFromFile("Fonts/Ubuntu-Medium.ttf"))
		throw "could not load font from the file.";

	//Green

	greenFooter = make_unique<Text>(font, "100", 20);
	greenFooter->setPosition({ greenPlant->getPosition().x + 20 , greenPlant->getPosition().y + greenPlant->getGlobalBounds().size.y + 22});
	greenFooter->setFillColor(Color::Black);

	//Blue

	blueFooter = make_unique<Text>(font, "200", 20);
	blueFooter->setPosition({ bluePlant->getPosition().x + 20 , greenPlant->getPosition().y + greenPlant->getGlobalBounds().size.y + 22 });
	blueFooter->setFillColor(Color::Black);

	//Sun

	sunFooter = make_unique<Text>(font, "50", 20);
	sunFooter->setPosition({ sunFlowerPlant->getPosition().x + 20 , greenPlant->getPosition().y + greenPlant->getGlobalBounds().size.y + 22 });
	sunFooter->setFillColor(Color::Black);

	//Amount

	amount = make_unique<Text>(font, to_string(numOfSunFlower) , 20);
	amount->setPosition({ greenPlant->getPosition().x + 25 , priceBar->getPosition().y + priceBar->getGlobalBounds().size.y + 32 });
	amount->setFillColor(Color::Black);

}

void Plant::statusOfPlants() {

	//Sun Flower

	if (numOfSunFlower >= 50)
		sunFlowerPlant->setColor(Color(255, 255, 255, 255));
	else
		sunFlowerPlant->setColor(Color(255, 255, 255, 100));

	//Green Plant

	if (numOfSunFlower >= 100)
		greenPlant->setColor(Color(255, 255, 255, 255));
	else
		greenPlant->setColor(Color(255, 255, 255, 100));

	//Blue Plant

	if (numOfSunFlower >= 200)
		bluePlant->setColor(Color(255, 255, 255, 255));
	else
		bluePlant->setColor(Color(255, 255, 255, 100));

}  

FloatRect Plant::getGreenPlantGlobalBounds() {

	return greenPlant->getGlobalBounds();

}

FloatRect Plant::getBluePlantGlobalBounds() {

	return bluePlant->getGlobalBounds();

}

FloatRect Plant::getSunFlowerPlantGlobalBounds() {

	return sunFlowerPlant->getGlobalBounds();

}

Sprite& Plant::getGreenPlant() {
	return *greenPlant;
}

Sprite& Plant::getBluePlant() {
	return *bluePlant;
}

Sprite& Plant::getSunFlowerPlant() {
	return *sunFlowerPlant;
}

Texture Plant::getGreenTex() {
	return greenPlant->getTexture();
}

Texture& Plant::getBlueTex() {
	return bluePlantTex;
}

Texture& Plant::getSunFlowerTex() {
	return sunFlowerPlantTex;
}

void Plant::drawPlants(RenderWindow& window) {

	window.draw(*greenPlant);
	window.draw(*bluePlant);
	window.draw(*sunFlowerPlant);
	window.draw(*priceBar);
	window.draw(*greenFooter);
	window.draw(*blueFooter);
	window.draw(*sunFooter);
	window.draw(*amountBar);
	window.draw(*amount); 
}