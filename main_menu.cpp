#include <iostream>
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"  
#include "SFML\Audio.hpp"
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

	exitButtonText = nullptr;
	startButtonText = nullptr;
	main = nullptr;
}

void MainMenu::initializeMainMenuTexture() {

	if (!mainTex.loadFromFile("Images/main_menu.jfif"))
		throw "could not load main_menu.jfif from the file";

	main = make_unique<Sprite>(mainTex);
	main->setScale({ 1.78 , 1.7 });

	startButton.setSize({ 100 , 50 });
	startButton.setPosition({ 710 , 600 });
	startButton.setFillColor(Color(0, 200, 0));

	exitButton.setSize({ 100 , 50 });
	exitButton.setPosition({ 490 , 600 });
	exitButton.setFillColor(Color(0, 200, 0));

	if (!font.openFromFile("Fonts/RUSTED PERSONAL USE.ttf"))
		throw "could load font front the file";

	startButtonText = make_unique<Text>(font, "Start", 40);
	startButtonText->setPosition({ startButton.getPosition().x + 8 , startButton.getPosition().y});
	startButtonText->setFillColor(Color(184,45,40));

	exitButtonText = make_unique<Text>(font, "Exit", 40);
	exitButtonText->setPosition({ exitButton.getPosition().x + 10 , exitButton.getPosition().y });
	exitButtonText->setFillColor(Color(184, 45, 40));

	if (!mainMenu.openFromFile("Music/main.ogg"))
		throw "could not open main.ogg from the file";
	mainMenu.setLooping(1000);
}

void MainMenu::initialize() {

	RenderWindow window(VideoMode({ 1300 , 700 }) , "Plant_VS_Zombies");
	window.setFramerateLimit(60);

	initializeMainMenuTexture();

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
					if (startButton.getGlobalBounds().contains(pos)) {
						stopMusic();
						game.initializeGame(window);
					}
					else if (exitButton.getGlobalBounds().contains(pos))
						window.close();
				}
			}
		}

		// Updates Everything here

		window.clear();

		//Draw Objects
		window.draw(*main);
		window.draw(startButton);
		window.draw(exitButton);
		window.draw(*startButtonText);
		window.draw(*exitButtonText);
		window.display();

	}
}

void MainMenu::closeMainMenu(RenderWindow& window) {
	window.close();
}

void MainMenu::stopMusic() {
	mainMenu.stop();
}