## Code overview

There are 3 main modules to the program. Parsing, rendering, and game logic. The program always starts by initializing data and always ends by cleaning it up (freeing mallocs, fd).

Errors always cause a swift exit. There is no attempt for recovery.

Main program steps:
1. Declare, initialize program data
2. Parse
3. Setup mlx and hooks
4. Fire the mlx loop, which fires the engine loop, which automatically renders frames - the game starts
5. Destroy programa data cleanly

### Parsing

Consists in handling args, map file, and building data. This is only done once on program start. Most program errors happen here.

Steps:
1. Check args
2. Open file and place it in RAM
3. Parse file in 2 steps: first the 6 texture + color lines, then the map

Errors include:
1. Not enough args
2. Too many args
3. Invalid filename
4. Cannot open file (absent, no perms, etc...)
5. Cannot read file, or malloc error
7. Missing texture/color line
8. Extra unrecognized tokens
9. Invalid map

### Rendering

/!\ WIP /!\

Since we want to render a minimap on top of the regular image, we have to decide between several methods:
1. 2 images, or 1: with 2 images, the minimap image starts at 0,0 and then needs to placed at the right coordinates. This simplifies the code a tiny bit. In both cases, pixels should not be calculated just to be overwritten (wasted resources).
2. Minimap size, changeable vs unchangeable: if we implement hotkeys to change its size and we use the 2 images method, we need to destroy and recreate the image whenever we want to resize.
3. Whole map vs area around the player: if we want to display the entire map, it might end up being really small/borderline unreadable if the map is really big.
4. Cone of vision vs none: we can display the player's cone of vision on the minimap, this adds some work.
5. Map that rotates with the player or not: some people could find it easier to read this way, but this adds extra work.
6. Map that can change corner: a hotkey could be implemented to cycle minimpap position between each of the 4 corners of the window.
Even in its simplest form, we still need to decide whether to use 1 or 2 images. We also need to decide how the map reacts to window size changes. Is the map size always a fraction of the window size? Does it have a minimum?

For the main image rendering, more research needs to be done.

### Game logic

Consists in setting up hooks and defining behaviors on key press.

There are 2 main parts for this:
1. Engine loop: this is the main loop which runs constantly in the background. It renders frames and handles key press/repeat logic.
2. Key/mouse hooks: handle all user interaction. There is geometric math involved in movement as movement happens on a rotating axis (according to the player's angle).

### Tracking current progress

We currently have many sub-structs, but typing `a->game.map.grid[a->game.map.height - y][a->game.map.width - x]` is really annoying. It might be better to group everything into one structure. It's messy both ways: either you have long messy names, or you have one big messy struct.

Parsing is done, but a bit messy and could be remade in a cleaner way. Currently, the file is not fully placed in RAM, only the map part is. Also, mlx is initialized before parsing, while it would make more sense to init after. Some inconsistencies, like refusing a map with trailing empty lines at the end of file.

Rendering is TBD. Needs research. For now, we have a map view for testing game logic.

Game logic is 3/4th done. What remains is interaction logic, namely geometric math for angle and movement.
