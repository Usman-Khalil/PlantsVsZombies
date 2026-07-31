# Plants_vs_Zombies

A small Plants vs. Zombies–style tower-defense game implemented in C++ using SFML and built with Visual Studio.

## Purpose
This project is a student / hobby implementation of a Plants vs. Zombies inspired game. Players place plant defenders on a lawn to stop waves of zombies before they reach the house. The code includes game logic for plants, zombies, projectiles, menus, and simple asset loading (images, fonts, music).

## Features
- Core gameplay: plant placement, automatic plant attacks, zombie waves, projectiles, and sun/flower collection.
- Built for Windows using Visual Studio project files (.slnx, .vcxproj).
- Uses SFML for graphics, audio, and window/input handling.
- Assets organized under Images/, Fonts/, and Music/.

## Requirements
- Windows (project files target Visual Studio).
- Visual Studio (2019/2022 recommended) or another C++ toolchain compatible with the included .vcxproj.
- SFML runtime libraries (SFML DLLs are included in the repository). If you prefer an SDK install, make sure the project links against SFML and that the correct DLLs are available in the executable folder.

## Build & Run
1. Clone or download this repository.
2. Open `Plants_vs_Zombies.slnx` in Visual Studio.
3. Select the desired configuration (Debug or Release) and the appropriate platform (x86/x64) matching the included SFML DLLs.
4. Build the solution (Build -> Build Solution).
5. Ensure the following directories are present alongside the executable (these are required at runtime): `Images/`, `Fonts/`, `Music/`, and the SFML DLLs (already committed in the repo). If you installed SFML system-wide, ensure the correct SFML DLLs are reachable by the executable.
6. Run the built executable (from Visual Studio or by launching the .exe in the output folder).

Notes:
- If you run into missing DLL errors, either copy the SFML runtime DLLs to the folder containing the built .exe or install the correct SFML redistributables.
- The project includes SFML DLLs in the repository; confirm you use the matching platform (32-bit vs 64-bit) configuration.

## How to play
- Start the game by launching the executable and clicking the "Start" button on the main menu.
- Controls:
  - Mouse left-click to interact with menu buttons, collect suns/flowers, select a plant, and place a plant on the lawn.
  - Press Esc at any time to close the main menu or exit.
- Objective: Prevent zombies from reaching the house by strategically placing plants. Plants automatically attack when placed.
- Resource: Flowers / suns appear during gameplay — click them to collect and use them to place more plants.
- Plant types (examples in-game):
  - Shooter plants (fire green/blue projectiles)
  - Sunflower (generates suns/collectibles)
  - Other plant variants depending on the code under `Plant.cpp` / `Plant.h`

## Project structure (important files)
- `main.cpp` - program entry.
- `main_menu.*` - initializes the window and main menu.
- `game.cpp`, `game.h` - main game loop and logic.
- `Plant.*`, `zombies.*`, `Lawn.*`, `projectiles.*` - gameplay components.
- `Images/`, `Fonts/`, `Music/` - runtime assets.
- `Plants_vs_Zombies.vcxproj` / `Plants_vs_Zombies.slnx` - Visual Studio project files.
- `architecture.txt` - notes and design details.

## Troubleshooting
- Black screen or missing assets: ensure `Images/` and `Fonts/` are in the same working directory as the executable and that the file names match (case-sensitive on some systems).
- Build/link errors: configure your Visual Studio project's include and linker settings for SFML if you installed SFML separately.

## License
Add a license file or choose a license for this project.

---

If you want, I can:
- Open and paste the full README into this chat for review.
- Customize the README with screenshots, controls mapping per-plant, or exact SFML version details if you tell me which SFML version / platform you used.
