[Subject](https://cdn.intra.42.fr/pdf/pdf/199846/en.subject.pdf)

### Constraints & Rules

- One argument to program: name of the .cub file
- .cub file must contain 3 elements:
    1. Map contents
    2. Wall textures (NO SO WE EA)
    3. Floor/ceiling colors (F C)
    The map contents are always last. Other elements can be in any order and separated by however many empty lines.
- Map contents:
    1. 1 is a wall
    2. 0 is an open square
    3. N/S/E/W is the player spawn (only 1), determines starting orientation
    4. A space, meaning "nothing" (to create non-rectangular maps)
    Map does not need to be rectangular, it can be any shape. It only needs to be surrounded by walls.
- Textures:
    1. NO, SO, WE, EA, followed by path to the texture
    2. Any amount of spaces between both strings
- Colors:
    1. F, C followed by R,G,B in decimal (range [0,255])
    2. Any amount of spaces between both strings

### Possible errors

Argument error:
1. No argument/too many arguments
2. Invalid argument name (not .cub, or only ".cub")

File error:
1. Cannot open file
2. Did not find all elements that HAVE to come before map (6 elements)
3. Found duplicate elements
4. Found invalid elements (not one of NO, SO, WE, EA, F, C)
5. Element not followed by only ONE string
6. Color string invalid (not R,G,B between 0 and 255)

Texture error:
1. Cannot find texture file
2. Cannot open texture file
3. Texture file not correct format (to be researched)

Map error:
1. Found invalid character (not one of 1, 0, N, S, W, E, ' ')
2. Not surrounded by walls
3. Disjointed map (separate areas not linked together)

### Possible bonuses (beyond bonuses proposed by subject)

1. Other "entities" inside labyrinth e.g enemies, pickups, decor...
2. A "win" (or end) condition
3. Pickup-able items, inventory, ammo
4. Weapons and enemies
5. Some kind of other mechanic beyond shooting stuff
