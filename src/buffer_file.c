#include "cub3d.h"

void	buffer_file(t_cub *cub, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_out(cub, ERR_OPEN, file);
	cub->parse.file = get_file(fd);
	close(fd);
	if (errno)
		error_out(cub, ERR_READ, file);
	if (!cub->parse.file)
		error_out(cub, file, ERR_EMPFILE);
}
