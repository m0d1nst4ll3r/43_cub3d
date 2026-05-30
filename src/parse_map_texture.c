#include "cub3d.h"

static int	get_texture(t_mlx *mlx, t_img *img, char *filename)
{
	img->ptr = mlx_xpm_file_to_image(mlx, filename, &img->width, &img->height);
	if (!img->ptr)
		return (1);
	img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->llen, &img->endian);
	if (!img->addr)
		return (1);
	return (0);
}

int	read_texture(t_all *a, t_map_elem elem_type)
{
	if ((elem_type == TEX_NO && a->game.map.tex_no.ptr)
		|| (elem_type == TEX_SO && a->game.map.tex_so.ptr)
		|| (elem_type == TEX_WE && a->game.map.tex_we.ptr)
		|| (elem_type == TEX_EA && a->game.map.tex_ea.ptr))
		error_parse_duplicate(a, a->file.split_line[0]);
	if ((elem_type == TEX_NO && get_texture(a->mlx.ptr, &a->game.map.tex_no,
					a->file.split_line[1]))
		|| (elem_type == TEX_SO && get_texture(a->mlx.ptr, &a->game.map.tex_so,
				a->file.split_line[1]))
		|| (elem_type == TEX_WE && get_texture(a->mlx.ptr, &a->game.map.tex_we,
				a->file.split_line[1]))
		|| (elem_type == TEX_EA && get_texture(a->mlx.ptr, &a->game.map.tex_ea,
				a->file.split_line[1])))
		error_parse(a, ERR_BADTEX, a->file.split_line[1]);
}
