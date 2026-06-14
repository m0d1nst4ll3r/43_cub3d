#include "cub3d.h"

// In radians:
// E   -> N   -> W   -> S
// 0   -> 1/2 -> 1   -> 3/2
// (multiples of pi)
static float	get_start_angle(char c)
{
	if (c == 'E')
		return (0);
	else if (c == 'N')
		return (M_PI / 2);
	else if (c == 'W')
		return (M_PI);
	else
		return (M_PI * 3 / 2);
}

// Check:
// - Not first line/column
// - Not last line/column
// - Check all previously parsed adjacent tiles
//		???
//		?0
static int	add_open_tile(t_cub *cub, int x, int y)
{
	cub->grid[y][x] = TILE_OPEN;
	return (!x || !y
		|| x == cub->width - 1 || y == cub->height - 1
		|| cub->grid[y][x - 1] == TILE_VOID
		|| cub->grid[y - 1][x - 1] == TILE_VOID
		|| cub->grid[y - 1][x] == TILE_VOID
		|| cub->grid[y - 1][x + 1] == TILE_VOID);
}

// Check:
// - All previously parsed adjacent tiles
//		???
//		?v
// (less tiles to check if first/last line/column)
static int	add_void_tile(t_cub *cub, int x, int y)
{
	cub->grid[y][x] = TILE_VOID;
	return ((y && cub->grid[y - 1][x] == TILE_OPEN)
			|| (x && cub->grid[y][x - 1] == TILE_OPEN)
			|| (x && y && cub->grid[y - 1][x - 1] == TILE_OPEN)
			|| (x != cub->width - 1 && y
				&& cub->grid[y - 1][x + 1] == TILE_OPEN));
}

static void	check_and_fill_tile(t_cub *cub, int x, int y, char c)
{
	if (c == ' ' && add_void_tile(cub, x, y))
		error_parse(cub, ERR_NOWALL, NULL);
	else if (c == '1')
		cub->grid[y][x] = TILE_WALL;
	else if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		{
			if (cub->plx)
				error_parse(cub, ERR_MANYSPAWN, NULL);
			cub->plr = get_start_angle(c);
			cub->plx = x + 0.5;
			cub->ply = y + 0.5;
		}
		if (add_open_tile(cub, x, y))
			error_parse(cub, ERR_NOWALL, NULL);
	}
	else if (c != ' ')
	{
		ft_fprintf(2, RED "Error" RES ": " YEL "line %d" RES ": \
Invalid map tile identifier '%c'\n", cub->parse.i, c);
		exit_prog(cub, 1);
	}
}

// Rules:
//
// Only " 01NSWE" are valid identifiers
// Anything NOT '1' or ' ' is an empty room
// An empty room cannot be on row == 0 or row == height - 1
// An empty room cannot be on column == 0 or column == width - 1
// An empty room cannot have a ' ' on y - 1 and x - 1, x or x + 1
// An empty room cannot have a ' ' on y and x - 1
// A ' ' cannot have an empty room on y - 1 and x -1, x, or x + 1
// A ' ' cannot have an empty room on y and x - 1
//
// There has to be exactly one starting position for the player
void	parse_map_fill(t_cub *cub, t_file *file)
{
	int	x;
	int	y;
	int	i;

	y = 0;
	while (y < cub->height)
	{
		x = 0;
		i = 0;
		while (x < cub->width)
		{
			if (file->line[i] && file->line[i] != '\n')
				check_and_fill_tile(cub, x, y, file->line[i++]);
			else if (add_void_tile(cub, x, y))
				error_parse(cub, ERR_NOWALL, NULL);
			x++;
		}
		file = file->next;
		cub->parse.i++;
		y++;
	}
	if (!cub->plx)
		error_out(cub, ERR_NOSPAWN, NULL);
}
