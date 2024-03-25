# cub3d_sandbox
Building repo for cub3d

## Parser plan

1. Check arg count and file extension before starting the game.
2. Open file, trim whitepace if the line contains textures and colors, store texture and color info
3. In the same loop, count lines and rows to determine max map size (get max numbers, map will be square)
4. Texture validation: check file extension and for duplicates
5. Color validation: check duplicates, check incorrect color number (≠3) check for non-numeric characters, negative numbers and >255
6. Transform the 3 color numbers into one
7. Open the file again to parse the map
8. Skip the lines that contain textures and colors
9. Copy map lines into map matrix (if the rows are not max length, fill the rest with spaces), set the player position and direction angle
10. Map validation: check for empty rows, check if only valid characters present, check for player duplicates, 
11. Map validation (part 2): check if the border contains only ‘ ’ and ‘1’, if the coordinate is ‘ ‘, check if the grid around it contains only ‘ ‘ or ‘1’ → ensures that all parts of the map is closed.
    
## TODOs:

Graphics:
- Fisheye correction not working perfectly;

## To Solve:
- If there is only one color value, program does not return error ("F 123");
- Repeated color input does not cause error (last one overwrites previous) if between F and C color input lines;
- Missing information on map does not trigger the right error message;
- If there is a space after the color value and before the ',' the program gives an error ("F 101  ,183,65");
- Extra ',' after color values does not cause an error;
- **Leaks** (still reachables) when:
    - invalid texture;
    - invalid character in map, or extra player;
    - invalid element identifier;
    - space between color value and ',' "C 123,211   ,";
    - invalid color value;
    - extra ',' or '.';
    - extra content;
- Fix empty line exit in the map.
## Done
- More than a '.' in texture file extension leads to **SEGFAULT**. Ex: "EA textures/directions/E1..xpm"; - DONE
- More characters on Identifier leads to **SEGFAULT**. Ex: "EAA textures/directions/E1.xpm"; - DONE
- A '/' before texture file path leads to **SEGFAULT**. Ex: "SO /textures/directions/S1.xpm"; - DONE
- If a file does not exist (wrong path or filename), leads to **SEGFAULT**; - DONE
- Adding a pdf as a .xpm texture file leads to **SEGFAULT**; - DONE
- More than a '/' in texture file path does not cause an error; - and it shouldn't :) check bash
- More than a ',' between color values does not cause an error; - DONE?
- Extra spaces after map (to the right or below) get parsed into map matrix, causing problems to minimap;
- Same thing for spaces before map (to the left);
- Fix empty line exit in the map.

## Links:
- [Raycasting and DDA](https://lodev.org/cgtutor/raycasting.html) (contains 2 files with implementations in c++)
- [Raycasting tutorial](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/) (easier to understand) (Currently basing on this one)
- [Creating a raycaster](https://www.youtube.com/watch?v=gYRrGTC7GtA) (series of 3 videos)

- Personal page for [notes](https://spicy-dirigible-2b6.notion.site/Cub3D-cc92684cfbf64eb8ae13841b32ea4603?pvs=4)

Using this as reference for orientation in map:   
![image](https://github.com/damachad/cub3d_sandbox/assets/128734978/dfe879ec-18be-4987-a7c4-a59e359449b4)

Top left corner (even if it has to be imagined, when map shape does not allow it) coincides with grid coordinate (0,0). E is 0° (0), N is 90° (π/2), W is 180° (π) and S is 270° (3π/2).
