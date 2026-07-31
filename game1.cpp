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
#include "main_menu.h"

using namespace std;
using namespace sf;

Plant plant;
Lawn lawn;
Zombies zombie;
Projectiles projectile;
MainMenu main_menu;


Game::Game() {

	flower = nullptr;
	flowerSpawnTime = 0;
	greenSpawnTime = 0;
	blueSpawnTime = 0;
	sunSpawnTime = 0;
	activePlant = nullptr;
	selectedPlant = 'N';
	playerStatus = true;
	noOfZombiesDie = 0;
	gameOverText = nullptr;
	activeStatus = false;
	musicPlayed = false;
	playerDeadTime = 0;
}

void Game::initializeGame(RenderWindow& window1) {

	main_menu.closeMainMenu(window1);

	// Initialize Objects For Window

	lawn.initializeTextureForLawn();
	plant.initializeTextureForPlants();
	plant.initializeFontsForPlants();
	zombie.initializeTextureForZombies();
	projectile.initializeTextureOfProjectiles();
	initializeGameObjects();
	loadMusicFromFIle();

	RenderWindow window(VideoMode({ 1300 , 700 }), "Plant_VS_Zombies");
	window.setFramerateLimit(60);

	bgMusic.play();
	while (window.isOpen()) {

		while (const optional event = window.pollEvent()) {
			if (event->is<Event::Closed>())
				window.close();
			if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
			{
				if (mousePressed->button == Mouse::Button::Left)
				{
					Vector2f mousePos;
					mousePos.x = Mouse::getPosition().x;
					mousePos.y = Mouse::getPosition().y;
					selectingPlant(mousePos);
				}
			}
		}
		if (playerStatus) {

			// Updates Everything here

			droppingFlowers(window);
			zombie.spawningOfZombies(window);
			plant.statusOfPlants();
			if (activeStatus)
				previewPlant();
			throwGreenBalls(window);
			throwBlueBalls(window);
			throwSuns(window);
			zombiesVsPlants();
			zombiesVsBlueBullets();
			zombiesVsGreenBullets();
			isPlayerAlive();
			updateZombiesSpawnTime();

			window.clear();

			//Draw Objects

			lawn.draw(window);
			plant.drawPlants(window);
			zombie.drawZombies(window);

			if (activePlant != nullptr)
				window.draw(*activePlant);
			for (int i = 0; i < flowers.size(); i++) {
				window.draw(flowers[i]);
			}
			for (int i = 0; i < placedPlants.size(); i++) {
				window.draw(placedPlants[i]);
			}
			for (int i = 0; i < greenBullets.size(); i++) {
				window.draw(greenBullets[i]);
			}
			for (int i = 0; i < blueBullets.size(); i++) {
				window.draw(blueBullets[i]);
			}
			for (int i = 0; i < sunFlower.size(); i++) {
				window.draw(sunFlower[i]);
			}

			//

		}
		else {
			if (playerDeadTime <= 180) {
				if (!musicPlayed) {
					deadMusic.play();
					musicPlayed = true;
				}
				gameOverText->setPosition({ static_cast<float>(window.getSize().x / 2) , static_cast<float>(window.getSize().y / 2) });
				window.draw(*gameOverText);
				playerDeadTime++;
				if (playerDeadTime > 180)
					musicPlayed = false;
			}
			else {
				window.clear();
				if (!musicPlayed) {
					looseMusic.play();
					musicPlayed = true;
				}
				menu->setPosition({ static_cast<float>(window.getSize().x / 2) , static_cast<float>(window.getSize().y / 2) });
				backToMenuText->setPosition({ static_cast<float>(window.getSize().x / 2) - 100 , 500 });
				window.draw(*menu);
				window.draw(*backToMenuText);
				if (Mouse::isButtonPressed(Mouse::Button::Left)) {
					Vector2f pos;
					pos.x = Mouse::getPosition().x;
					pos.y = Mouse::getPosition().y;
					if (backToMenuText->getGlobalBounds().contains(pos)) {
						bgMusic.stop();
						window.close();
						main_menu.initialize();
					}
				}
			}
		}
		window.display();
	}
}
void Game::initializeGameObjects() {

	if (!flowerTex.loadFromFile("Images/sun.png"))
		throw "could not load sun.png from the file";

	flower = make_unique<Sprite>(flowerTex);
	flower->setScale({ 0.5 , 0.5 });

	if (!font.openFromFile("Fonts/Magnificent Nightmare.ttf"))
		throw "could not load font from the file";

	gameOverText = make_unique<Text>(font, "THE  ZOMBIES \n    ATE YOUR \n     BRAINS!" , 80);
	gameOverText->setFillColor(Color(225,0, 0 , 255));
	gameOverText->setOrigin({ gameOverText->getLocalBounds().size.x / 2 , gameOverText->getLocalBounds().size.y / 2 });

	if (!menuTex.loadFromFile("Images/main.png"))
		throw "could not load main.png from the file";

	menu = make_unique<Sprite>(menuTex);
	menu->setOrigin({ menu->getLocalBounds().size.x / 2 , menu->getLocalBounds().size.y / 2 });

	backToMenuText = make_unique<Text>(font, "Back To Menu", 20);
	backToMenuText->setFillColor(Color(225, 0, 0, 255));

}

void Game::loadMusicFromFIle() {


	if (!placePlantMusic.openFromFile("Music/placePlant.ogg"))
		throw "could not open placePlant.ogg from the file";

	if (!zombieVsPlantMusic.openFromFile("Music/zombieVsPlant.ogg"))
		throw "could not open zombieVsPlant.ogg from the file";

	if (!shootMusic.openFromFile("Music/shoot.mp3"))
		throw "could not open shoot.mp3 from the file";

	if (!zombieVsProjectileMusic.openFromFile("Music/zombieVsProjectile.ogg"))
		throw "could not open zombieVsProjectile.ogg from the file";

	if (!collectFlowersMusic.openFromFile("Music/collectFlowers.ogg"))
		throw "could not open collectFlowers.ogg from the file";

	if (!produceFlowersMusic.openFromFile("Music/produceSun.ogg"))
		throw "could not open produceSun.ogg from the file";

	if (!looseMusic.openFromFile("Music/losemusic.ogg"))
		throw "could not open losemusic.ogg from the file";

	if (!deadMusic.openFromFile("Music/playerDead.ogg"))
		throw "could not open playerDead.ogg from the file";

	if (!bgMusic.openFromFile("Music/bg_2.flac"))
		throw "could not open bg_2.flac from the file";

	if (!zombieDeadMusic.openFromFile("Music/zombieDead.mp3"))
		throw "could not open zombieDead.mp3 from the file";

	bgMusic.setLooping(10);
	bgMusic.setVolume(10);
}

void Game::droppingFlowers(RenderWindow& window) {

	if (flowerSpawnTime < 400)
		flowerSpawnTime++;
	if (flowerSpawnTime >= 400) {

		flower->setPosition({ 300 + static_cast<float>(rand() % (window.getSize().x - 100)) , 0 });
		flowers.push_back(*flower);
		flowerSpawnTime = 0;

	}
	for (int i = 0; i < flowers.size(); i++) {

		flowers[i].move({ 0,0.5 });

		if (flowers[i].getPosition().y > window.getSize().y - 100)
		{
			flowers.erase(flowers.begin() + i);
			break;
		}

	}
}

void Game::selectingPlant(Vector2f pos) {

	if (plant.getBluePlantGlobalBounds().contains(pos) && plant.numOfSunFlower >= 200) {
		activeStatus = true;
		selectedPlant = 'B';
	}
	else if (plant.getGreenPlantGlobalBounds().contains(pos) && plant.numOfSunFlower >= 100) {
		activeStatus = true;
		selectedPlant = 'G';
	}
	else if (plant.getSunFlowerPlantGlobalBounds().contains(pos) && plant.numOfSunFlower >= 50) {
		activeStatus = true;
		selectedPlant = 'S';
	}
	else {
		if (activeStatus)
			placePlants(pos);
		else
			collectFlowers(pos);
	}

	if (selectedPlant == 'B')
	{
		activePlant = make_unique<Sprite>(plant.getBluePlant());
		activePlant->setScale({ 0.09 , 0.09 });
	}
	else if (selectedPlant == 'G')
	{
		activePlant = make_unique<Sprite>(plant.getGreenPlant());
		activePlant->setScale({ 0.06 , 0.06 });
	}
	else if (selectedPlant == 'S')
	{
		activePlant = make_unique<Sprite>(plant.getSunFlowerPlant());
		activePlant->setScale({ 0.055 , 0.055 });
	}
	else
		return;
}

void Game::previewPlant() {

	activePlant->setPosition({ static_cast<float>(Mouse::getPosition().x) , static_cast<float>(Mouse::getPosition().y) });
}

void Game::placePlants(Vector2f pos) {
	if (activePlant == nullptr)
		return;

	placePlantMusic.play();
	activePlant->setPosition(pos);
	placedPlants.push_back(*activePlant);
	genreOfPlacedPlants.push_back(selectedPlant);
	activePlant = nullptr;
	activeStatus = false;
	if (selectedPlant == 'G')
	{
		plant.numOfSunFlower -= 100;
	}
	else if (selectedPlant == 'B')
	{
		plant.numOfSunFlower -= 200;
	}
	else if (selectedPlant == 'S')
	{
		plant.numOfSunFlower -= 50;
	}
	plant.amount->setString(to_string(plant.numOfSunFlower));
	selectedPlant = 'N';
}

void Game::collectFlowers(Vector2f pos) {
	for (int i = 0; i < flowers.size(); i++) {

		if (flowers[i].getGlobalBounds().contains(pos)) {
			collectFlowersMusic.play();
			flowers.erase(flowers.begin() + i);
			plant.numOfSunFlower += 25;
			plant.amount->setString(to_string(plant.numOfSunFlower));
			break;
		}

	}
}
void Game::throwGreenBalls(RenderWindow& window) {

	if (greenSpawnTime < 100)
		greenSpawnTime++;
	if (greenSpawnTime >= 100)
	{
		for (int i = 0; i < placedPlants.size(); i++) {
			if (genreOfPlacedPlants[i] == 'G')
			{
				shootMusic.play();
				projectile.getGreenBullet().setPosition({ placedPlants[i].getPosition().x + 40 , placedPlants[i].getPosition().y });
				greenBullets.push_back(projectile.getGreenBullet());
			}
		}
		greenSpawnTime = 0;
	}

	for (int i = 0; i < greenBullets.size(); i++) {
		greenBullets[i].move({ 2 , 0 });

		if (greenBullets[i].getPosition().x < window.getPosition().x - 400)
			greenBullets.erase(greenBullets.begin() + i);
	}

}

void Game::throwBlueBalls(RenderWindow& window) {
	if (blueSpawnTime < 100)
		blueSpawnTime++;
	if (blueSpawnTime >= 100)
	{
		for (int i = 0; i < placedPlants.size(); i++) {
			if (genreOfPlacedPlants[i] == 'B')
			{
				shootMusic.play();
				projectile.getBlueBullet().setPosition({ placedPlants[i].getPosition().x + 40 , placedPlants[i].getPosition().y });
				blueBullets.push_back(projectile.getBlueBullet());
			}
		}
		blueSpawnTime = 0;
	}
	for (int i = 0; i < blueBullets.size(); i++) {
		blueBullets[i].move({ 2 , 0 });

		if (blueBullets[i].getPosition().x < window.getPosition().x - 400)
			blueBullets.erase(blueBullets.begin() + i);
	}

}

void Game::throwSuns(RenderWindow& window) {
	if (sunSpawnTime < 1000)
		sunSpawnTime++;
	if (sunSpawnTime >= 1000)
	{
		for (int i = 0; i < placedPlants.size(); i++) {
			if (genreOfPlacedPlants[i] == 'S')
			{
				produceFlowersMusic.play();
				projectile.getSunFlower().setPosition({ placedPlants[i].getPosition().x + 65 , placedPlants[i].getPosition().y + 30 });
				sunFlower.push_back(projectile.getSunFlower());
			}
		}
		sunSpawnTime = 0;
	}
	for (int i = 0; i < sunFlower.size(); i++) {

		if (Mouse::isButtonPressed(Mouse::Button::Left)) {
			Vector2f pos;
			pos.x = Mouse::getPosition().x;
			pos.y = Mouse::getPosition().y;
			if (sunFlower[i].getGlobalBounds().contains(pos)) {
				collectFlowersMusic.play();
				sunFlower.erase(sunFlower.begin() + i);
				plant.numOfSunFlower += 25;
				plant.amount->setString(to_string(plant.numOfSunFlower));
				break;
			}
		}
	}
}

void Game::zombiesVsPlants() {

	for (int i = 0; i < placedPlants.size(); i++) {
		for (int j = 0; j < zombie.getZombies().size(); j++) {
			if (placedPlants[i].getGlobalBounds().findIntersection(zombie.getZombies()[j].getGlobalBounds())) {
				zombieVsPlantMusic.play();
				placedPlants.erase(placedPlants.begin() + i);
				genreOfPlacedPlants.erase(genreOfPlacedPlants.begin() + i);
				break;
			}
		}
	}
}

void Game::zombiesVsGreenBullets() {

	for (int i = 0; i < greenBullets.size(); i++) {
		for (int j = 0; j < zombie.getZombies().size(); j++) {
			if (greenBullets[i].getGlobalBounds().findIntersection(zombie.getZombies()[j].getGlobalBounds()))
			{
				zombieVsProjectileMusic.play();
				zombie.getHpOfZombies()[j] -= 5;
				zombie.getHpBarOfZombies()[j].setSize({ 1.1f * zombie.getHpOfZombies()[j]  , 10 });
				greenBullets.erase(greenBullets.begin() + i);
				if (zombie.getHpOfZombies()[j] <= 0)
				{
					zombieDeadMusic.play();
					zombie.getZombies().erase(zombie.getZombies().begin() + j);
					zombie.getHpOfZombies().erase(zombie.getHpOfZombies().begin() + j);
					zombie.getHpBarOfZombies().erase(zombie.getHpBarOfZombies().begin() + j);
					noOfZombiesDie++;
				}
				break;
			}
		}
	}
}

void Game::zombiesVsBlueBullets() {

	for (int i = 0; i < blueBullets.size(); i++) {
		for (int j = 0; j < zombie.getZombies().size(); j++) {
			if (blueBullets[i].getGlobalBounds().findIntersection(zombie.getZombies()[j].getGlobalBounds()))
			{
				zombieVsProjectileMusic.play();
				zombie.getHpOfZombies()[j] -= 10;
				zombie.getHpBarOfZombies()[j].setSize({ 1.1f * zombie.getHpOfZombies()[j]  , 10 });
				blueBullets.erase(blueBullets.begin() + i);
				if (zombie.getHpOfZombies()[j] <= 0)
				{
					zombieDeadMusic.play();
					zombie.getHpBarOfZombies().erase(zombie.getHpBarOfZombies().begin() + j);
					zombie.getZombies().erase(zombie.getZombies().begin() + j);
					zombie.getHpOfZombies().erase(zombie.getHpOfZombies().begin() + j);
					noOfZombiesDie++;
				}
				break;
			}
		}
	}
}

void Game::isPlayerAlive() {

	for (int i = 0; i < zombie.getZombies().size(); i++) {
		if (zombie.getZombies()[i].getPosition().x < 200) {
			playerStatus = false;
			bgMusic.stop();
		}
	}
}

void Game::updateZombiesSpawnTime() {
	if (noOfZombiesDie == 20)
		zombie.getZombieSpawntime() -= 10;
	else if (noOfZombiesDie == 40)
		zombie.getZombieSpawntime() -= 40;
	else if (noOfZombiesDie == 100)
		zombie.getZombieSpawntime() -= 70;

	zombie.getZombieSpawntime() = max(300, zombie.getZombieSpawntime());
}
