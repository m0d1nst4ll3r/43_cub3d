#include "cub3d.h"

static void	cleanup_parse(t_parse *parse)
{
	if (parse->file)
		free_file(parse->file);
	if (parse->split_line)
		free_strs(parse->split_line);
	if (parse->tex_no)
		free(parse->tex_no);
	if (parse->tex_so)
		free(parse->tex_so);
	if (parse->tex_we)
		free(parse->tex_we);
	if (parse->tex_ea)
		free(parse->tex_ea);
}

static void	cleanup_map(void *mlx, t_cub *cub)
{
	if (cub->map)
		free(cub->map);
	if (cub->grid)
		free(cub->grid);
	if (cub->tex_no.ptr)
		mlx_destroy_image(mlx, cub->tex_no.ptr);
	if (cub->tex_so.ptr)
		mlx_destroy_image(mlx, cub->tex_so.ptr);
	if (cub->tex_we.ptr)
		mlx_destroy_image(mlx, cub->tex_we.ptr);
	if (cub->tex_ea.ptr)
		mlx_destroy_image(mlx, cub->tex_ea.ptr);
}

static void	cleanup_mlx(t_mlx *mlx)
{
	if (mlx->img.ptr)
		mlx_destroy_image(mlx->ptr, mlx->img.ptr);
	if (mlx->win)
		mlx_destroy_window(mlx->ptr, mlx->win);
	if (mlx->ptr)
	{
		mlx_destroy_display(mlx->ptr);
		free(mlx->ptr);
	}
}

void	cleanup_prog(t_cub *cub)
{
	cleanup_parse(&cub->parse);
	cleanup_map(cub->mlx.ptr, cub);
	cleanup_mlx(&cub->mlx);
}
