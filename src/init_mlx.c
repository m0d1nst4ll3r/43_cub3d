#include "cub3d.h"

static int	open_single_texture(void *mlx, t_img *img, char *filename)
{
	img->ptr = mlx_xpm_file_to_image(mlx, filename, &img->width, &img->height);
	if (!img->ptr)
		return (1);
	img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->llen,
			&img->endian);
	return (0);
}

static void	open_all_textures(t_cub *cub)
{
	if (open_single_texture(cub->mlx.ptr, &cub->tex_no, cub->parse.tex_no))
		error_out(cub, ERR_BADTEX, cub->parse.tex_no);
	if (open_single_texture(cub->mlx.ptr, &cub->tex_so, cub->parse.tex_so))
		error_out(cub, ERR_BADTEX, cub->parse.tex_so);
	if (open_single_texture(cub->mlx.ptr, &cub->tex_we, cub->parse.tex_we))
		error_out(cub, ERR_BADTEX, cub->parse.tex_we);
	if (open_single_texture(cub->mlx.ptr, &cub->tex_ea, cub->parse.tex_ea))
		error_out(cub, ERR_BADTEX, cub->parse.tex_ea);
}

static void	free_xpm_filenames(t_cub *cub)
{
	free(cub->parse.tex_no);
	free(cub->parse.tex_so);
	free(cub->parse.tex_we);
	free(cub->parse.tex_ea);
	cub->parse.tex_no = NULL;
	cub->parse.tex_so = NULL;
	cub->parse.tex_we = NULL;
	cub->parse.tex_ea = NULL;
}

// 1. Init mlx
// 2. Open xpm
// 3. Init win
// 4. Init img
void	init_mlx(t_cub *cub)
{
	cub->mlx.ptr = mlx_init();
	if (!cub->mlx.ptr)
		error_out(cub, ERR_MLX, NULL);
	open_all_textures(cub);
	free_xpm_filenames(cub);
	cub->mlx.win = mlx_new_window(cub->mlx.ptr, WIN_X, WIN_Y, WIN_NAME);
	if (!cub->mlx.win)
		error_out(cub, ERR_MLX, NULL);
	cub->mlx.img.ptr = mlx_new_image(cub->mlx.ptr, WIN_X, WIN_Y);
	if (!cub->mlx.img.ptr)
		error_out(cub, ERR_MLX, NULL);
	cub->mlx.img.addr = mlx_get_data_addr(cub->mlx.img.ptr,
			&cub->mlx.img.bpp, &cub->mlx.img.llen, &cub->mlx.img.endian);
	cub->mlx.img.width = WIN_X;
	cub->mlx.img.height = WIN_Y;
}
