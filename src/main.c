#include "cub3d.h"

static void	init_mlx(t_all *a)
{
	a->mlx.ptr = mlx_init();
	if (!a->mlx.ptr)
		error_out(a, ERR_MLX, NULL);
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
}

static void	init_prog(t_all *a)
{
	ft_memset(a, 0, sizeof(*a));
	a->file.fd = -1;
	a->file.i = 1;
	a->game.map.color_f = -1;
	a->game.map.color_c = -1;
	init_mlx(a);
	errno = 0;
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
	exit_prog(&a, 0);
}
