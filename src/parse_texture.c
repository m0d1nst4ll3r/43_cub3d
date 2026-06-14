#include "cub3d.h"

void	parse_texture(t_cub *cub, t_map_elem elem_type)
{
	char	*tex_file;

	tex_file = ft_strdup(cub->parse.split_line[1]);
	if (!tex_file)
		error_out(cub, ERR_MALLOC, NULL);
	if (elem_type == TEX_NO && !cub->parse.tex_no)
		cub->parse.tex_no = tex_file;
	else if (elem_type == TEX_SO && !cub->parse.tex_so)
		cub->parse.tex_so = tex_file;
	else if (elem_type == TEX_WE && !cub->parse.tex_we)
		cub->parse.tex_we = tex_file;
	else if (elem_type == TEX_EA && !cub->parse.tex_ea)
		cub->parse.tex_ea = tex_file;
	else
	{
		free(tex_file);
		error_parse_duplicate(cub, cub->parse.split_line[0]);
	}
}
