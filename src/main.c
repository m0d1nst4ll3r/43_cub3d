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

// Dead files for rewrite WIP:
// - mlx_hooks.c (contains all hooks/game logic WIP)
// - render.c (contains all render logic WIP)
int	main(int argc, char **argv)
{
	t_cub	cub;

	/* 1 */ init_data(&cub); // Inits all data points so we can exit cleanly, cannot fail
	/* 2 */ check_args(&cub, argc, argv); // Checks right amount of args and right format, can error
	/* 3 */ buffer_file(&cub, argv[1]); // Attempts to open file, buffer it into a chained list, and close it, can error
	/* 4 */ parse_file(&cub); // Reads file data, can error
	/* 5 */ init_mlx(&cub); // Init MLX and opens texture files, can still error - only creates display after opening XPMs
	/* 6 */ init_hooks(&cub); // Sets all keyboard, mouse, clientmessage, loop hooks
//	/* 7 */ mlx_loop(cub.mlx.ptr); // Engages mlx loop, game starts
	exit_prog(&cub, 0);
}
