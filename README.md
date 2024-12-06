# mlx_lib (aka so_long)

### Description
`mlx_lib` or `so_long`  is a graphical project from 42 school. It uses the minilibx that contains the API from X11

### Features
- Easy-to-use API for graphics manipulation.
- Supports event handling for interactive applications.
- Includes utility functions for common tasks.

### Requirements
- A C compiler (e.g., CC)
- Make
- minilibx - [minilibx-linux](https://github.com/42Paris/minilibx-linux)

### Usage
To compile the project:
```sh
make
```

To run the program:
```sh
./so_long maps/test.ber
```
The name of the runnable `so_long`, and it takes a map file as an argument, e.g.,`maps/test.ber`.

### Attention 
You can make your own custom map!
- The map needs to be surrounded by walls
- It must be winnable (You need to collect all the Collectables and can reach the exit)
- The map needs to be a `.ber` file

### How to create a map
- Collectables are `C`
- Player is `P`
- Enemies are `X`
- Exit is `E`
