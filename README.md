# Cub3d

🎮 Welcome to Cub3d! 🎮

Cub3d is a project inspired by the classic game [Wolfenstein 3D](http://users.atw.hu/wolf3d/), where you navigate through a maze-like environment from a first-person perspective. It's part of the 42 curriculum and aims to introduce students to the fundamentals of raycasting, graphics rendering, and game development.

## Constraints 🎯

- The project must be written in C.
- Usage of external libraries such as OpenGL is prohibited.
- The graphics rendering must be implemented using the MiniLibX, a simple graphic library provided by 42.
- It should display different wall textures that vary depending on which side the wall is facing (North, South, East, West), as well as set the floor and ceiling colors to two different ones;
- Allowed functions: open, close, read, write, printf, malloc, free, perror, strerror, exit, all functions of the math and MinilibX libraries;

## Implementation Details and Approach 🛠️

Cub3d employs [raycasting](https://permadi.com/1996/05/ray-casting-tutorial-2/#WHAT%20IS%20RAY-CASTING) to render the 3D environment. The map is represented as a grid of cells, containing information about the walls and player position. Raycasting involves casting rays from the player's perspective to simulate the 3D effect, calculating intersections with walls, and rendering the scene accordingly.

Key components of Cub3d include:

- Parsing map files to extract relevant information.
- Implementing raycasting algorithms to render the scene.
- Handling player movement and collisions.
- Rendering textures and sprites.

## Usage 🚀

- First download [Minilibx](https://github.com/42Paris/minilibx-linux), rename its directory to 'mlx' and add it to the root directory of the cub3d project;
- To compile Cub3d, run ```make``` or ```make bonus``` (if you want to try the bonus version);
- Then run it as such ```./cub3d <maps/map.cub>``` or ```./cub3d_bonus <maps/map.cub>```. Replace `maps/map.cub` with the path to your custom map file. You can find sample map files in the `maps` directory;

### Controls 🕹️

- The left ⬅️ and right ➡️ arrow keys of the keyboard allow you to look left and right in the maze;
- The **W** and **S** keys allow you to move forward or backward in a straight line;
- The **A** and **D** keys allow you to move left or right in a straight line;
- The **Esc** key allows you to exit the game cleanly (so does clicking on the red cross on the window’s frame);

## Mapfile example 📜
```
NO textures/tech_1.xpm
SO textures/tech_2.xpm
WE textures/tech_3.xpm
EA textures/tech_4.xpm

F 95,95,95
C 113,211,244

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111100111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

## Demo 💿
[Screencast from 04-04-2024 02:35:06 PM.webm](https://github.com/damachad/42_cub3d/assets/128734978/c91cfff9-46d6-47e9-9778-e741205c6f31)

## Useful links 🔗
- [Raycasting and DDA](https://lodev.org/cgtutor/raycasting.html);
- [Raycasting tutorial](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/);
- [Creating a raycaster](https://www.youtube.com/watch?v=gYRrGTC7GtA);

- Personal page for [notes](https://spicy-dirigible-2b6.notion.site/Cub3D-cc92684cfbf64eb8ae13841b32ea4603?pvs=4);
