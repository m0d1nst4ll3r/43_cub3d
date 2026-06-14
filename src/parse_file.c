#include "cub3d.h"

static void	skip_newlines(t_cub *cub)
{
	while (cub->parse.head && ft_str_is_empty(cub->parse.head->line))
	{
		cub->parse.head = cub->parse.head->next;
		cub->parse.i++;
	}
}

// 1. Parse 6 elems (NO, SO, WE, EA, F, C - any order, skip empty lines)
// 2. Skip empty lines for map
// 3. Parse map
// 4. Free file (not needed anymore)
void	parse_file(t_cub *cub)
{
	parse_elems(cub);
	skip_newlines(cub);
	parse_map(cub);
	free_file(cub->parse.file);
	cub->parse.file = NULL;
}
