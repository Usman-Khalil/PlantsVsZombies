# Plants_vs_Zombies

A student / hobby implementation of a Plants vs. Zombies–style tower-defense game implemented in C++ using SFML and built with Visual Studio.

## 💻 Tech Stack:
<div align="center">
  
  ![C++](https://img.shields.io/badge/c++-%23E34F26.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white) 
  ![SFML](https://img.shields.io/badge/SFML-%23F05033.svg?style=for-the-badge) 
  ![OOP](https://img.shields.io/badge/OOP-%23007ACC.svg?style=for-the-badge)  
  ![Visual Studio](https://img.shields.io/badge/Visual%20Studio-%230A0FFF.svg?style=for-the-badge&logo=visual-studio&logoColor=white) 
  ![STL](https://img.shields.io/badge/STL-%23000000.svg?style=for-the-badge)
  
</div>

## Project summary

This repository contains a small, self-contained Windows game inspired by Plants vs. Zombies. The player places plants on a lawn to stop waves of zombies from reaching the house. The game includes simple AI for zombies, projectile attacks, and resource collection.

The codebase is written in modern C++ (Visual Studio solution and project files are provided) and uses the SFML library for graphics, audio, windowing, and input. Runtime SFML DLLs and basic asset placeholders are included for convenience.

This project is intended as an educational/hobby implementation and demonstrates basic game loop design, simple managers (plants, zombies, bullets, suns), collision handling, and asset loading.

## Features

- Core gameplay: plant placement, automatic plant attacks, zombie waves, projectile movement, and simple collisions.
- Resource generation and collection (suns/flowers) used to buy/place plants.
- Multiple plant types (shooter, sunflower, etc.) with distinct costs and behaviors.
- Zombie spawning on multiple rows with HP bars and simple movement toward the house.
- Visuals and audio via SFML; basic sound effect for spawning zombies.
- Visual Studio solution (.slnx) and project files (.vcxproj) provided for Windows builds.

## Requirements

- Windows (Visual Studio-targeted project files).
- Visual Studio 2019 or 2022 (recommended) or any MSVC toolchain compatible with the included .vcxproj.
- SFML runtime libraries (SFML DLLs are included in the repository). If you prefer to use an installed SFML SDK, make sure the project links against the SDK and that the matching DLLs are available.

Note: The included SFML DLLs are present for convenience. Make sure you match the project platform (x86 vs x64) and Debug vs Release configuration to the DLLs you use.

## Build & Run

1. Clone or download this repository:

   git clone https://github.com/Usman-Khalil/PlantsVsZombies.git

2. Open `Plants_vs_Zombies.slnx` in Visual Studio.
3. Select the desired configuration (Debug or Release) and the appropriate platform (x86/x64) matching the included SFML DLLs.
4. Build the solution (Build -> Build Solution).
5. Ensure the following directories and files are present alongside the executable at runtime: `Images/`, `Fonts/`, `Music/`, and the SFML DLLs (already committed in the repo).
6. Run the built executable from Visual Studio or by launching the .exe from the output folder.

If you encounter missing DLL errors, either copy the SFML runtime DLLs to the executable folder or install the correct SFML redistributables and/or link against the installed SDK.

## How to play

- Start the game by launching the executable and clicking the "Start" button on the main menu.
- Controls:
  - Mouse left-click: interact with menu buttons, collect suns/flowers, select a plant, and place a plant on the lawn.
  - Press Esc to close the main menu or exit the game.
- Objective: Prevent zombies from reaching the house by placing plants strategically and collecting resources.
- Resource: Flowers / suns appear during gameplay — click them to collect and use them to place more plants.
  

## Architecture overview

- Program initializes: loads textures & fonts, creates the window, and initializes managers (Lawn, Plant menu, Zombies, HUD).
- Game loop: process events → update game state (spawn suns, spawn zombies, move bullets, resolve collisions, update resources) → render everything → display frame.
- Managers: PlantManager, ZombieManager, BulletManager, SunManager, and a simple CollisionManager coordinate responsibilities.

Refer to `architecture.txt` for an ASCII flow diagram and more details.

## Screenshots 
### main_menu.png

![Main Menu](ScreenShots/main_menu.png)

Main menu screen showing the game background and Start button.


### gameOver.png

![Game Over](ScreenShots/gameOver.png)

Game over screen with a large message indicating the player failed to stop the zombie wave.


### fight.png

![In-Game Fight](ScreenShots/fight.png)

In-game action showing plants and zombies during gameplay.


### interface.png

![Interface / HUD](ScreenShots/interface.png)

Close-up of the HUD and lawn grid with the sun counter and plant cost slots.


### playerDead.png

![Player Dead / Menu](ScreenShots/playerDead.png)

Screenshot showing the player-death / pause menu screen.


