#include "cub3d.h"

// Writes directly into mlx image
// Display does not update until next put_image_to_window
// Only returns true if pixel was actually changed
static void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*addr;

	if (x < 0 || y < 0 || x >= WIN_X || y >= WIN_Y)
		return ;
	addr = img->addr + y * img->llen + x * img->bpp / 8;
	*(int *)addr = color;
}

// Draws a full circle for one octant
// Test func for now, will update
static void	octant_circle_draw_full(t_img *img, int x, int y, int cx, int cy, int color)
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

// Draws full circle, test func
// Centered on x,y of radius n
// Radius of 0 is just a point
// Radius of 1 is 3 pixels wide, 2 is 5, etc..
static void	draw_circle(t_img *img, int x, int y, int radius, int color)
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

static void	draw_square(t_img *img, int ppt, int x, int y, int color)
{
	int	yy;
	int	xx;

	yy = 0;
	while (yy < ppt)
	{
		xx = 0;
		while (xx < ppt)
		{
			pixel_put(img, xx + x, yy + y, color);
			xx++;
		}
		yy++;
	}
}

// This is a test func. Might or might not keep (do we want a full-screen map?). Might adapt to minimap (smaller, only display radius around player).
// Steps:
// 1. How many pixels per tile? (ppt)
// 2. Take smallest ppt, because we want tiles to be squares (map will fit, not stretch)
// 3. Calculate offset to center image
// 4. For each square of the map, draw the corresponding square in pixels
// This function does not deal with floats so image may not be exactly centered or exactly fit
static void	render_big_map(t_all *a)
{
	int	ppt_x = WIN_X / a->game.map.width;
	int	ppt_y = WIN_Y / a->game.map.height;
	int	ppt = ft_min(ppt_x, ppt_y);
	int	offset_x = (WIN_X - ppt * a->game.map.width) / 2;
	int	offset_y = (WIN_Y - ppt * a->game.map.height) / 2;
	int	x;
	int	y;

	y = 0;
	while (y < a->game.map.height)
	{
		x = 0;
		while (x < a->game.map.width)
		{
			if (a->game.map.grid[y][x] == TILE_VOID)
				draw_square(&a->mlx.img, ppt, x * ppt, y * ppt, COLOR_VOID);
			else if (a->game.map.grid[y][x] == TILE_WALL)
				draw_square(&a->mlx.img, ppt, x * ppt, y * ppt, COLOR_WALL);
			else
				draw_square(&a->mlx.img, ppt, x * ppt, y * ppt, COLOR_OPEN);
			x++;
		}
		y++;
	}
	draw_circle(&a->mlx.img, (int)(a->game.player.x * ppt + offset_x), (int)(a->game.player.y * ppt + offset_y), RADIUS_PLAYER, COLOR_PLAYER);
	mlx_put_image_to_window(a->mlx.ptr, a->mlx.win, a->mlx.img.ptr, 0, 0);
}

static void	reset_img(t_img *img)
{
	int	y;
	int	x;

	y = 0;
	while (y < img->width)
	{
		x = 0;
		while (x < img->height)
		{
			pixel_put(img, x, y, 0);
			x++;
		}
		y++;
	}
}

void	redraw_img(t_all *a)
{
	reset_img(&a->mlx.img);
	render_big_map(a); // test for now
	a->time.img_need_redraw = false;
	a->time.last_refresh = a->time.current;
	a->time.frame_count++;
}
