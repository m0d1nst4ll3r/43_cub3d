#include "cub3d.h"

static int	check_empty_lines(t_cub *cub)
{
	t_file	*head;
	int		i;

	i = cub->parse.i;
	head = cub->parse.head;
	if (!head)
		error_parse(cub, ERR_NOMAP, NULL);
	while (head && !ft_str_is_empty(head->line))
	{
		head = head->next;
		cub->parse.i++;
	}
	while (head && ft_str_is_empty(head->line))
		head = head->next;
	if (head)
		error_parse(cub, ERR_MAPNEWLINE, NULL);
	cub->parse.i = i;
	return (0);
}

// Truncate trailing spaces in line, to avoid allocating unnecessary space
static void	get_map_dimensions(t_file *file, int *width, int *height)
{
	int	i;

	while (file)
	{
		(*height)++;
		i = 0;
		while (file->line[i + 1] && file->line[i + 1] != '\n')
			i++;
		while (file->line[i] == ' ')
			i--;
		if (*width < i + 1)
			*width = i + 1;
		file = file->next;
	}
}

static void	alloc_grid(t_cub *cub)
{
	int	i;

	cub->grid = malloc(sizeof(*cub->grid) * cub->height);
	if (!cub->grid)
		error_out(cub, ERR_MALLOC, NULL);
	i = 0;
	while (i < cub->height)
	{
		cub->grid[i] = cub->map + i * cub->width;
		i++;
	}
}

static void	alloc_map(t_cub *cub)
{
	cub->map = malloc(sizeof(*cub->map) * cub->width * cub->height);
	if (!cub->map)
		error_out(cub, ERR_MALLOC, NULL);
}

// 1. Check for empty lines in map
// 2. Get map dimensions
// 3. Alloc map (1D array)
// 4. Alloc grid (2D virtual array)
// 5. Fill grid (check while filling)
// 6. Clean
void	parse_map(t_cub *cub)
{
	check_empty_lines(cub);
	get_map_dimensions(cub->parse.head, &cub->width, &cub->height);
	alloc_map(cub);
	alloc_grid(cub);
	parse_map_fill(cub, cub->parse.head);
	free_file(cub->parse.file);
	cub->parse.file = NULL;
}
