#include "cub3d.h"

static int	got_all_elems(t_cub *cub)
{
	return (cub->color_f != -1 && cub->color_c != -1
			&& cub->parse.tex_no && cub->parse.tex_so
			&& cub->parse.tex_we && cub->parse.tex_ea);
}

static t_map_elem	check_line_elem_id(t_cub *cub)
{
	if (!ft_strcmp(cub->parse.split_line[0], TEX_NO_STR))
		return (TEX_NO);
	else if (!ft_strcmp(cub->parse.split_line[0], TEX_SO_STR))
		return (TEX_SO);
	else if (!ft_strcmp(cub->parse.split_line[0], TEX_WE_STR))
		return (TEX_WE);
	else if (!ft_strcmp(cub->parse.split_line[0], TEX_EA_STR))
		return (TEX_EA);
	else if (!ft_strcmp(cub->parse.split_line[0], COLOR_F_STR))
		return (COLOR_F);
	else if (!ft_strcmp(cub->parse.split_line[0], COLOR_C_STR))
		return (COLOR_C);
	else
	{
		ft_fprintf(2, RED "Error" RES ": " YEL "line %d" RES ": \
Unrecognized element identifier '%s'\n", cub->parse.i, cub->parse.split_line[0]);
		exit_prog(cub, 1);
	}
	return (0);
}

static void	check_line_elem_count(t_cub *cub)
{
	int	i;

	i = 0;
	while (cub->parse.split_line[i])
		i++;
	if (i < 2)
		error_parse(cub, ERR_FEWELEM, NULL);
	else if (i > 2)
		error_parse(cub, ERR_MANYELEM, NULL);
}

static void	read_single_elem(t_cub *cub)
{
	t_map_elem	elem_type;

	elem_type = check_line_elem_id(cub);
	check_line_elem_count(cub);
	if (elem_type < 4)
		parse_texture(cub, elem_type);
	else
		parse_color(cub, elem_type);
}

void	parse_elems(t_cub *cub)
{
	cub->parse.head = cub->parse.file;
	while (!got_all_elems(cub))
	{
		if (!ft_str_is_empty(cub->parse.head->line))
		{
			cub->parse.split_line = ft_ssplit(cub->parse.head->line, " \n");
			if (!cub->parse.split_line)
				error_out(cub, ERR_MALLOC, NULL);
			read_single_elem(cub);
			free_strs(cub->parse.split_line);
			cub->parse.split_line = NULL;
		}
		cub->parse.head = cub->parse.head->next;
		cub->parse.i++;
	}
}
