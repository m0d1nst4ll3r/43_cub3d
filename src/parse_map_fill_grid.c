#include "cub3d.h"

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

static int	add_open_tile(t_all *a, int x, int y)
{
	a->game.map.grid[y][x] = TILE_OPEN;
	return (!x || !y
		|| x == a->game.map.width - 1 || y == a->game.map.height - 1
		|| a->game.map.grid[y][x - 1] == TILE_VOID
		|| a->game.map.grid[y - 1][x - 1] == TILE_VOID
		|| a->game.map.grid[y - 1][x] == TILE_VOID
		|| a->game.map.grid[y - 1][x + 1] == TILE_VOID);
}

static int	add_void_tile(t_all *a, int x, int y)
{
	a->game.map.grid[y][x] = TILE_VOID;
	return ((y && a->game.map.grid[y - 1][x] == TILE_OPEN)
			|| (x && a->game.map.grid[y][x - 1] == TILE_OPEN)
			|| (x && y && a->game.map.grid[y - 1][x - 1] == TILE_OPEN)
			|| (x != a->game.map.width - 1
				&& y && a->game.map.grid[y - 1][x + 1] == TILE_OPEN));
}

static void	check_and_fill_tile(t_all *a, int x, int y, char c)
{
	if (c == ' ' && add_void_tile(a, x, y))
		error_parse(a, ERR_NOWALL, NULL);
	else if (c == '1')
		a->game.map.grid[y][x] = TILE_WALL;
	else if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		{
			if (a->game.player.x)
				error_parse(a, ERR_MANYSPAWN, NULL);
			a->game.player.angle = get_start_angle(c);
			a->game.player.x = x + 0.5;
			a->game.player.y = y + 0.5;
		}
		if (add_open_tile(a, x, y))
			error_parse(a, ERR_NOWALL, NULL);
	}
	else if (c != ' ')
	{
		ft_fprintf(2, RED "Error" RES ": " YEL "line %d" RES ": \
Invalid map tile identifier '%c'\n", a->file.i, c);
		exit_prog(a, 1);
	}
}

// Rules:
//
// Something NOT a '1' or a ' ' is an empty room
// An empty room cannot be on row == 0 or row == height - 1
// An empty room cannot be on column == 0 or column == width - 1
// An empty room cannot have a ' ' on y - 1 and x - 1, x or x + 1
// An empty room cannot have a ' ' on y and x - 1
//
// There has to be exactly one starting position for the player
void	fill_grid(t_all *a, t_file_contents *list)
{
	int	x;
	int	y;
	int	i;

	y = 0;
	while (y < a->game.map.height)
	{
		x = 0;
		i = 0;
		while (x < a->game.map.width)
		{
			if (list->line[i] && list->line[i] != '\n')
				check_and_fill_tile(a, x, y, list->line[i++]);
			else if (add_void_tile(a, x, y))
				error_parse(a, ERR_NOWALL, NULL);
			x++;
		}
		list = list->next;
		a->file.i++;
		y++;
	}
	if (!a->game.player.x)
		error_out(a, ERR_NOSPAWN, NULL);
}
