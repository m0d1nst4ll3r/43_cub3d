#include "cub3d.h"

// Tmp test func to visualize map
void	display_grid(t_map_tile	**grid, int width, int height)
{
	int	x;
	int	y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (grid[y][x] == TILE_VOID)
				printf(" ");
			else if (grid[y][x] == TILE_WALL)
				printf("1");
			else
				printf("0");
			x++;
		}
		printf("\n");
		y++;
	}
}

int	main(int argc, char **argv)
{
	t_all	a;

	init_prog(&a);
	if (argc < 2)
		error_out(&a, ERR_NOARGS, NULL);
	if (argc > 2)
		error_out(&a, ERR_MANYARGS, NULL);
	parse_data_from_file(&a, argv[1]); // Exits by itself in case of error
	display_grid(a.game.map.grid, a.game.map.width, a.game.map.height);
	init_mlx_win(&a);
	set_hooks(&a);
	mlx_loop(a.mlx.ptr);
	exit_prog(&a, 0);
}
