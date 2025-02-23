# cub3d

cub3d is a project that implements a simple 3D game engine using the ray-casting technique, inspired by the classic game Wolfenstein 3D. This project is developed in C and utilizes the MLX42 library for graphics rendering.

## Features

- **Ray-Casting Engine**: Renders a 3D perspective view from a 2D map layout.
- **Texture Mapping**: Applies textures to walls for a more immersive experience.
- **Player Movement**: Allows the player to navigate through the map with real-time rendering.
- **Bonus Features**: Additional functionalities and enhancements are available in the `bonus` directory.

## Requirements

- **Operating System**: Unix-like system (Linux, macOS).
- **Compiler**: `gcc` or any C99-compliant compiler.
- **Libraries**:
  - [MLX42](https://github.com/codam-coding-college/MLX42): A modern graphics library for 42 school projects.
  - Standard C libraries.

## Installation

1. **Clone the Repository**:
   ```sh
   git clone https://github.com/0thmanee/cub3d.git
   cd cub3d
   ```

2. **Install MLX42**:
   ```sh
   git clone https://github.com/codam-coding-college/MLX42.git
   cd MLX42
   cmake -B build
   cmake --build build -j4
   sudo cp build/libmlx42.a /usr/local/lib/
   sudo cp include/MLX42/MLX42.h /usr/local/include/
   cd ..
   ```

3. **Compile the Project**:
   ```sh
   make
   ```

## Usage

To run the game, execute:
```sh
./cub3d path/to/map.cub
```
Replace `path/to/map.cub` with the path to a valid map file. Sample maps are available in the `maps` directory.

## Controls

- **W**: Move forward
- **S**: Move backward
- **A**: Move left
- **D**: Move right
- **Left Arrow**: Rotate view left
- **Right Arrow**: Rotate view right
- **ESC**: Exit the game

## Map Configuration

Map files define the layout and textures of the game environment. A map file (`.cub` extension) includes:

- **Textures**: Paths to texture images for walls and sprites.
- **Colors**: RGB values for floor and ceiling colors.
- **Map Layout**: A grid representation using characters to denote walls, spaces, and the player's starting position.

Example map file:
```
NO ./textures/wall_north.xpm
SO ./textures/wall_south.xpm
WE ./textures/wall_west.xpm
EA ./textures/wall_east.xpm
F 220,100,0
C 225,30,0

111111
100001
100P01
100001
111111
```
In the map layout:
- `1` represents walls.
- `0` represents empty space.
- `P` represents the player's starting position.

## Bonus Features

The `bonus` directory contains additional features and enhancements, such as:
- **Sprite Rendering**: Displaying objects like enemies or items.
- **Improved Textures**: Higher resolution textures and floor/ceiling textures.
- **Mini-map**: A small map overlay to aid navigation.

To compile and run the bonus version:
```sh
make bonus
./cub3d_bonus path/to/map.cub
```

## License

This project does not have a license.

## Acknowledgments

- Inspired by [Wolfenstein 3D](https://en.wikipedia.org/wiki/Wolfenstein_3D).
- Utilizes the [MLX42](https://github.com/codam-coding-college/MLX42) library for graphics rendering.

For any questions or contributions, please contact the project maintainer through the GitHub repository.
