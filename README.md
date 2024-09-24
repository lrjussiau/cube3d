
# Cub3D - 3D Game Project

## Description

*Cub3D* is a project from 42 school aimed at creating a simple 3D game using raycasting, a technique used to simulate 3D perspectives in a 2D environment. The project is inspired by classic games like *Wolfenstein 3D* and focuses on understanding 3D rendering, managing graphical output, and handling user input.

## Project Objectives

- Implement a basic 3D graphics engine using raycasting.
- Understand how to render a 3D view from a 2D map.
- Manage player movement, collision detection, and rendering.
- Gain experience using the *minilibx* library for graphics output.

## Features

1. **Raycasting**
   - Use raycasting to create a 3D projection of a 2D map.
   - Simulate depth and perspective based on player position and orientation.
   - Handle walls, textures, and lighting effects.

2. **Player Movement**
   - Implement basic controls for moving forward, backward, and rotating left or right.
   - Collision detection to prevent the player from passing through walls.

3. **Textures**
   - Support for textured walls and different materials.
   - Load and apply textures for walls, floors, and ceilings.

4. **2D Map**
   - The game is based on a 2D map file representing walls and empty spaces.
   - The player navigates this map in first-person, with the map used to render the 3D world.

## System Calls and Functions

Key functions and system calls used in the project include:

- `mlx_init()`: Initialize the connection between the program and the windowing system.
- `mlx_new_window()`: Create a new window.
- `mlx_loop()`: Manage the event loop for rendering and interaction.
- `mlx_pixel_put()`: Place individual pixels on the window.
- `key_hook()`: Handle keyboard input for movement.

## Installation

To compile and run the *Cub3D* project, follow these steps:

```bash
git clone https://github.com/your-repo/cub3d.git
cd cub3d
make
```

Run the program with a map file:

```bash
./cub3D maps/map.cub
```

## Usage

- The player can move using the keyboard:
  - `W`: Move forward.
  - `S`: Move backward.
  - `A`: Strafe left.
  - `D`: Strafe right.
  - `←` and `→`: Rotate view.
- The game renders a 3D environment based on the map file and player position.

## Map File Format

The map is stored in a `.cub` file and represents the layout of walls and empty spaces. Example of a map:

```
1111111111
1000000001
1000000001
100P000001
1000000001
1111111111
```

- `1`: Wall.
- `0`: Empty space.
- `P`: Player starting position.

## Error Handling

The program should handle:

- Invalid map files or incorrectly formatted maps.
- Rendering and window errors.
- Collision detection issues (preventing the player from passing through walls).

## Testing

Test the program with different maps and ensure that the rendering behaves correctly. The player should not pass through walls, and the 3D environment should respond smoothly to input.

```bash
./cub3D maps/map2.cub
```

## Author

- **Louis** - 42 Lausanne Student
