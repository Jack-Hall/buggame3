# Bug Game 3 - 2D Top-Down Game

A 2D top-down game inspired by Realm of the Mad God, built with SFML and C++. This is a single-player game focusing on enemy AI and environmental interactions.

## Features

- **Multiple Enemy Types:**
  - **Wanderers** (Green): Move randomly around the world
  - **Chasers** (Red): Will chase targets when implemented
  - **Guards** (Blue): Patrol around their spawn point

- **Dynamic World:**
  - Bounded game world with collision detection
  - Enemy-to-enemy collision handling
  - Smooth camera movement

- **Controls:**
  - Arrow Keys: Move camera around the world
  - Escape: Exit game

## Prerequisites

- SFML 2.5 or later
- CMake 3.16 or later
- C++17 compatible compiler
- Visual Studio 2019 or later (Windows)

## Building

### Windows
1. Install SFML and ensure it's in your system PATH or CMAKE_PREFIX_PATH
2. Run `build.bat` to build the project
3. The executable will be created in `build/Release/BugGame3.exe`

### Manual Build
```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

## Architecture

The game is structured with the following core classes:

- **Game**: Main game loop and window management
- **World**: Manages the game environment and entities
- **Entity**: Base class for all game objects
- **Enemy**: AI-controlled entities with different behaviors
- **Vector2**: 2D vector math utilities

## Current State

The game currently features:
- A world populated with 15 enemies of different types
- Basic AI behaviors for each enemy type
- Collision detection and response
- Camera system for exploring the world
- Bounded world with visual borders

## Future Enhancements

- Player character implementation
- Combat system
- More complex AI behaviors
- Terrain and obstacles
- Particle effects
- Audio system
