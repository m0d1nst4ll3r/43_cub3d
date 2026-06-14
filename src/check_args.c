#include "cub3d.h"

static void	check_file(t_cub *cub, char *file)
{
	int	len;
	int	i;

	len = ft_strlen(file);
	if (len < 5 || ft_strncmp(&file[len - 4], ".cub", 4))
		error_out(cub, ERR_INVNAME, file);
	i = 0;
	while (len && file[len - 1] != '/')
	{
		len--;
		i++;
	}
	if (i == 4)
		error_out(cub, ERR_INVNAME, file);
	if (file[len] == '.')
		error_out(cub, ERR_VISNAME, file);
}

void	check_args(t_cub *cub, int argc, char **argv)
{
	if (argc < 2)
		error_out(cub, ERR_NOARGS, NULL);
	if (argc > 2)
		error_out(cub, ERR_MANYARGS, NULL);
	check_file(cub, argv[1]);
}
