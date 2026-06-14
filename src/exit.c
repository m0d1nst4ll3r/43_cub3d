
#include "cub3d.h"

void	exit_prog(t_cub *cub, unsigned char exitval)
{
	cleanup_prog(cub);
	exit(exitval);
}
