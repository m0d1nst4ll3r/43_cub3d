#include "cub3d.h"

static void	cleanup_file(t_file *file)
{
	if (file->fd != -1)
		close(file->fd);
	if (file->contents)
		free_file_contents(file->contents);
	if (file->split_line)
		free_strs(file->split_line);
}

static void	cleanup_map(void *mlx, t_map *map)
{
	if (map->data)
		free(map->data);
	if (map->grid)
		free(map->grid);
	if (map->tex_no.ptr)
		mlx_destroy_image(mlx, map->tex_no.ptr);
	if (map->tex_so.ptr)
		mlx_destroy_image(mlx, map->tex_so.ptr);
	if (map->tex_we.ptr)
		mlx_destroy_image(mlx, map->tex_we.ptr);
	if (map->tex_ea.ptr)
		mlx_destroy_image(mlx, map->tex_ea.ptr);
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

void	cleanup_prog(t_all *a)
{
	cleanup_file(&a->file);
	cleanup_map(a->mlx.ptr, &a->map);
	cleanup_mlx(&a->mlx);
}
