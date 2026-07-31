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

Game game;

MainMenu::MainMenu() {

	startButtonText = nullptr;
	main = nullptr;
	loadingTime = 0;
}

void MainMenu::initializeMainMenuTexture(RenderWindow& window) {

	if (!mainTex.loadFromFile("Images/main.png"))
		throw "could not load main.png from the file";

	main = make_unique<Sprite>(mainTex);
	main->setOrigin({ main->getLocalBounds().size.x / 2 , main->getLocalBounds().size.y / 2 });
	main->setPosition({ static_cast<float>(window.getSize().x / 2) , static_cast<float>(window.getSize().y / 2) });

	if (!loadingTex.loadFromFile("Images/loading.png"))
		throw "could not load loading.png from the file";

	loading = make_unique<Sprite>(loadingTex);
	loading->setScale({ 0.865 , 1 });

	if (!font.openFromFile("Fonts/Coraline's Cat.otf"))
		throw "could load font front the file";

	startButtonText = make_unique<Text>(font, "Start", 30);
	startButtonText->setOrigin({ startButtonText->getLocalBounds().size.x / 2 , startButtonText->getLocalBounds().size.y / 2 });
	startButtonText->setPosition({ static_cast<float>(window.getSize().x / 2)  , 510});
	startButtonText->setFillColor(Color(184,45,40));

	if (!mainMenu.openFromFile("Music/main.ogg"))
		throw "could not open main.ogg from the file";

	if (!bgTex.loadFromFile("Images/main_menu.png"))
		throw "could not load main_menu.png from the file";

	bg = make_unique<Sprite>(bgTex);
	bg->setOrigin({ bg->getLocalBounds().size.x / 2 , bg->getLocalBounds().size.y / 2 });
	bg->setPosition({ static_cast<float>(window.getSize().x / 2) , static_cast<float>(window.getSize().y / 2) });
	bg->setScale({ 0.86 , 0.97 });

	mainMenu.setLooping(1000);
}

void MainMenu::initialize() {

	RenderWindow window(VideoMode({ 1300 , 700 }) , "Plant_VS_Zombies");
	window.setFramerateLimit(60);

	initializeMainMenuTexture(window);

	mainMenu.play();

	while (window.isOpen()) {

		while (const optional event = window.pollEvent()) {
			if (event->is<Event::Closed>())
				window.close();
			if (const auto* keyPressed = event->getIf<Event::KeyPressed>()) {
				if (keyPressed->scancode == Keyboard::Scancode::Escape)
					window.close();
			}
			if (const auto mouseButtonPresed = event->getIf<Event::MouseButtonPressed>()) {
				if (mouseButtonPresed->button == Mouse::Button::Left) {
					Vector2f pos;
					pos.x = Mouse::getPosition().x;
					pos.y = Mouse::getPosition().y - 40;
					if (startButtonText->getGlobalBounds().contains(pos)) {
						stopMusic();
						game.initializeGame(window);
					}
				}
			}
		}

		// Updates Everything here

		window.clear();

		//Draw Objects
		if (loadingTime <= 360) {
			window.draw(*loading);
			loadingTime++;
		}
		else {

			window.draw(*bg);
			window.draw(*main);
			window.draw(*startButtonText);
		}
		window.display();
	}
}

void MainMenu::closeMainMenu(RenderWindow& window) {
	window.close();
}

void MainMenu::stopMusic() {
	mainMenu.stop();
}