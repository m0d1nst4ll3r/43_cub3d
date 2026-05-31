#include "cub3d.h"

static int	got_all_elems(t_map *map)
{
	return (map->color_f != -1 && map->color_c != -1 && map->tex_no.ptr
		&& map->tex_so.ptr && map->tex_we.ptr && map->tex_ea.ptr);
}

static t_map_elem	check_line_elem_id(t_all *a)
{
	if (!ft_strcmp(a->file.split_line[0], TEX_NO_STR))
		return (TEX_NO);
	else if (!ft_strcmp(a->file.split_line[0], TEX_SO_STR))
		return (TEX_SO);
	else if (!ft_strcmp(a->file.split_line[0], TEX_WE_STR))
		return (TEX_WE);
	else if (!ft_strcmp(a->file.split_line[0], TEX_EA_STR))
		return (TEX_EA);
	else if (!ft_strcmp(a->file.split_line[0], COLOR_F_STR))
		return (COLOR_F);
	else if (!ft_strcmp(a->file.split_line[0], COLOR_C_STR))
		return (COLOR_C);
	else
	{
		ft_fprintf(2, RED "Error" RES ": " YEL "line %d" RES ": \
Unrecognized element identifier '%s'\n", a->file.i, a->file.split_line[0]);
		exit_prog(a, 1);
	}
	return (0);
}

static void	check_line_elem_count(t_all *a)
{
	int	i;

	i = 0;
	while (a->file.split_line[i])
		i++;
	if (i < 2)
		error_parse(a, ERR_FEWELEM, NULL);
	else if (i > 2)
		error_parse(a, ERR_MANYELEM, NULL);
}

static void	read_single_elem(t_all *a)
{
	t_map_elem	elem_type;

	elem_type = check_line_elem_id(a);
	check_line_elem_count(a);
	if (elem_type < 4) // TEX
		read_texture(a, elem_type);
	else // COLOR
		read_color(a, elem_type);
}

void	parse_map_elems(t_all *a)
{
	char	*line;

	line = NULL;
	while (!got_all_elems(&a->game.map))
	{
		line = get_next_line(a->file.fd);
		if (errno)
			error_out(a, ERR_READ, NULL);
		if (!line)
			error_out(a, ERR_MAPELEMS, NULL);
		if (!ft_str_is_empty(line))
		{
			a->file.split_line = ft_ssplit(line, " \n");
			free(line);
			if (!a->file.split_line)
				error_out(a, ERR_MALLOC, NULL);
			read_single_elem(a); // Exits by itself depending on error
			free_strs(a->file.split_line);
			a->file.split_line = NULL;
		}
		else
			free(line);
		a->file.i++;
	}
}
