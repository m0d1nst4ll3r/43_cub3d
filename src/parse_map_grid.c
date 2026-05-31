#include "cub3d.h"

// Truncate trailing spaces in line, to avoid allocating unnecessary space
static void	get_map_dimensions(t_file_contents *list, int *width, int *height)
{
	int	i;

	while (list)
	{
		(*height)++;
		i = 0;
		while (list->line[i + 1] && list->line[i + 1] != '\n')
			i++;
		while (list->line[i] == ' ')
			i--;
		if (*width < i + 1)
			*width = i + 1;
		list = list->next;
	}
}

static void	alloc_grid(t_all *a)
{
	int	i;

	a->game.map.grid = malloc(sizeof(*a->game.map.grid) * a->game.map.height);
	if (!a->game.map.grid)
		error_out(a, ERR_MALLOC, NULL);
	i = 0;
	while (i < a->game.map.height)
	{
		a->game.map.grid[i] = a->game.map.data + i * a->game.map.width;
		i++;
	}
}

// 1. Alloc data (1D array)
// 2. Alloc grid (2D virtual array)
// 3. Fill grid (check while filling)
void	parse_map_grid(t_all *a)
{
	get_map_dimensions(a->file.contents, &a->game.map.width,
		&a->game.map.height);
	a->game.map.data = malloc(sizeof(*a->game.map.data) * a->game.map.width
			* a->game.map.height);
	if (!a->game.map.data)
		error_out(a, ERR_MALLOC, NULL);
	alloc_grid(a);
	fill_grid(a, a->file.contents);
}
