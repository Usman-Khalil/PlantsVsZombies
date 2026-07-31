# Plants_vs_Zombies

A student / hobby implementation of a Plants vs. Zombies–style tower-defense game implemented in C++ using SFML and built with Visual Studio.

## Project summary

This repository contains a small, self-contained Windows game inspired by Plants vs. Zombies. The player places plants on a lawn to stop waves of zombies from reaching the house. The game includes plant selection and placement, automatic plant attacks, projectiles, collectible suns/flowers, zombie waves with HP and simple AI, and a HUD for resources and controls.

The codebase is written in modern C++ (Visual Studio solution and project files are provided) and uses the SFML library for graphics, audio, windowing, and input. Runtime SFML DLLs and basic assets (Images/, Fonts/, Music/) are included so the project can be built and executed quickly on a compatible Windows machine.

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
- SFML runtime libraries (SFML DLLs are included in the repository). If you prefer to use an installed SFML SDK, make sure the project links against the SDK and that the matching DLLs are available alongside the built executable.

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

## Project structure (important files & folders)

- main.cpp - program entry.
- main_menu.* - initializes the window and main menu.
- game.cpp / game.h - main game loop and orchestration.
- Plant.h / Plant.cpp - plant sprites, costs, HUD elements, and spawn/selection logic.
- zombies.h / zombies.cpp - zombie sprites, spawning, movement, and HP management.
- projectiles.h / projectiles.cpp - projectile sprites and behaviors.
- Lawn.h / Lawn.cpp - background and lawn rendering.
- Images/ - art assets (sprites and textures).
- Fonts/ - font files used by HUD and menus.
- Music/ - audio assets (background music and effects).
- Plants_vs_Zombies.vcxproj / Plants_vs_Zombies.slnx - Visual Studio project and solution.
- architecture.txt - high-level architecture and game loop notes.

## Architecture overview

- Program initializes: loads textures & fonts, creates the window, and initializes managers (Lawn, Plant menu, Zombies, HUD).
- Game loop: process events → update game state (spawn suns, spawn zombies, move bullets, resolve collisions, update resources) → render everything → display frame.
- Managers: PlantManager, ZombieManager, BulletManager, SunManager, and a simple CollisionManager coordinate responsibilities.

Refer to `architecture.txt` for an ASCII flow diagram and more details.

## Troubleshooting

- Black screen or missing assets: ensure `Images/` and `Fonts/` are in the working directory with the executable and that file names match (case-sensitive on some systems).
- Build/link errors: configure Visual Studio include and linker settings for SFML if you installed SFML separately.
- Platform mismatch: ensure you use the platform configuration (x86 vs x64) that matches your SFML binaries.

## Contributing

Contributions are welcome. If you want to contribute:

1. Fork the repo.
2. Create a feature branch for your changes.
3. Open a pull request describing your changes.

## Contact

Author: Usman-Khalil
GitHub: https://github.com/Usman-Khalil

