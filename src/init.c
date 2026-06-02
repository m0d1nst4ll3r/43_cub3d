#include "cub3d.h"

void	init_mlx_win(t_all *a)
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

void	init_prog(t_all *a)
{
	ft_memset(a, 0, sizeof(*a));
	a->file.fd = -1;
	a->file.i = 1;
	a->game.map.color_f = -1;
	a->game.map.color_c = -1;
	a->time.img_need_redraw = true;
	gettimeofday(&a->time.last_refresh, NULL);
	a->time.last_fps = a->time.last_refresh;
	init_mlx(a);
}
