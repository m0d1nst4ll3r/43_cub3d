#include "cub3d.h"

static void	init_mlx_win(t_all *a)
{
	a->mlx.win = mlx_new_window(a->mlx.ptr, WIN_X, WIN_Y, WIN_NAME);
	if (!a->mlx.win)
		error_out(a, ERR_MLX, NULL);
	a->mlx.img.ptr = mlx_new_image(a->mlx.ptr, WIN_X, WIN_Y);
	if (!a->mlx.img.ptr)
		error_out(a, ERR_MLX, NULL);
	a->mlx.img.addr = mlx_get_data_addr(a->mlx.img.ptr,
			&a->mlx.img.bpp, &a->mlx.img.llen, &a->mlx.img.endian);
	a->mlx.img.width = WIN_X;
	a->mlx.img.height = WIN_Y;
	errno = 0;
}

static void	init_mlx(t_all *a)
{
	a->mlx.ptr = mlx_init();
	if (!a->mlx.ptr)
		error_out(a, ERR_MLX, NULL);
	errno = 0;
}

static void	init_prog(t_all *a)
{
	ft_memset(a, 0, sizeof(*a));
	a->file.fd = -1;
	a->file.i = 1;
	a->game.map.color_f = -1;
	a->game.map.color_c = -1;
	init_mlx(a);
}

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

// Writes directly into mlx image
// Display does not update until next put_image_to_window
// Only returns true if pixel was actually changed
void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*addr;

	if (x < 0 || y < 0 || x >= WIN_X || y >= WIN_Y)
		return ;
	addr = img->addr + y * img->llen + x * img->bpp / 8;
	*(int *)addr = color;
}

void	octant_circle_draw_full(t_img *img, int x, int y, int cx, int cy, int color)
{
	int	lx;

	lx = x - cx;
	while (lx <= x + cx)
	{
		pixel_put(img, lx, y + cy, color);
		pixel_put(img, lx, y - cy, color);
		lx++;
	}
	lx = x - cy;
	while (lx <= x + cy)
	{
		pixel_put(img, lx, y + cx, color);
		pixel_put(img, lx, y - cx, color);
		lx++;
	}
}

// centered on x,y of radius n
// radius of 0 is just a point
// radius of 1 is 3 pixels wide, 2 is 5, etc..
void	draw_circle(t_img *img, int x, int y, int radius, int color)
{
	int	t1;
	int	t2;
	int	cx;
	int	cy;

	t1 = radius / 16;
	cx = radius;
	cy = 0;
	while (cx >= cy)
	{
		octant_circle_draw_full(img, x, y, cx, cy, color);
		cy++;
		t1 = t1 + cy;
		t2 = t1 - cx;
		if (t2 >= 0)
		{
			t1 = t2;
			cx--;
		}
	}
}

// Steps:
// 1. How many pixels per tile? (ppt)
// 2. Take smallest ppt, because we want tiles to be squares (map will fit, not stretch)
// 3. Calculate offset to center image
// 4. For each square of the map, draw the corresponding square in pixels
// This function does not deal with floats so image may not be exactly centered or exactly fit
void	render_big_map(t_all *a)
{
	int	ppt_x = WIN_X / a->game.map.width;
	int	ppt_y = WIN_Y / a->game.map.height;
	int	ppt_final = ft_min(ppt_x, ppt_y);
	int	offset_x = (WIN_X - ppt_final * a->game.map.width) / 2;
	int	offset_y = (WIN_Y - ppt_final * a->game.map.height) / 2;
	int	x;
	int	y;
	int	px;
	int	py;

	y = 0;
	while (y < a->game.map.height)
	{
		x = 0;
		while (x < a->game.map.width)
		{
			py = 0;
			while (py < ppt_final)
			{
				px = 0;
				while (px < ppt_final)
				{
					if (a->game.map.grid[y][x] == TILE_VOID)
						pixel_put(&a->mlx.img, px + offset_x + x * ppt_final, py + offset_y + y * ppt_final, COLOR_VOID);
					else if (a->game.map.grid[y][x] == TILE_WALL)
						pixel_put(&a->mlx.img, px + offset_x + x * ppt_final, py + offset_y + y * ppt_final, COLOR_WALL);
					else
						pixel_put(&a->mlx.img, px + offset_x + x * ppt_final, py + offset_y + y * ppt_final, COLOR_OPEN);
					px++;
				}
				py++;
			}
			x++;
		}
		y++;
	}
	draw_circle(&a->mlx.img, (int)(a->game.player.x * ppt_final + offset_x), (int)(a->game.player.y * ppt_final + offset_y), RADIUS_PLAYER, COLOR_PLAYER);

	mlx_put_image_to_window(a->mlx.ptr, a->mlx.win, a->mlx.img.ptr, 0, 0);
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
	render_big_map(&a);
	//set_hooks(&a);
	mlx_loop(a.mlx.ptr);
	exit_prog(&a, 0);
}
