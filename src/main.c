#include "cub3d.h"

static void	init_prog(t_all *a)
{
	ft_memset(a, 0, sizeof(*a));
	a->file.fd = -1;
	a->game.map.color_f = -1;
	a->game.map.color_c = -1;
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
