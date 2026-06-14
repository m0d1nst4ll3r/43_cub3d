#include "cub3d.h"

void	init_hooks(t_cub *cub)
{
	(void)cub; // WIP
}

void	init_data(t_cub *cub)
{
	ft_memset(cub, 0, sizeof(*cub));
	cub->parse.i = 1;
	cub->color_f = -1;
	cub->color_c = -1;
}

// Commented for rewrite
// Belongs to init_data
//
//	a->time.img_need_redraw = true;
//	gettimeofday(&a->time.last_refresh, NULL);
//	a->time.last_fps = a->time.last_refresh;
