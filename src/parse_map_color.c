#include "cub3d.h"

static int	get_color(char *s, int *to_fill)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	int				ret;
	int				i;

	i = ft_atox(s, NULL, &r, sizeof(r) | ATOX_U | ATOX_TR);
	if (i < 0 || s[i++] != ',')
		return (1);
	ret = ft_atox(s + i, NULL, &g, sizeof(g) | ATOX_U | ATOX_TR);
	i += ret;
	if (ret < 0 || s[i++] != ',')
		return (1);
	ret = ft_atox(s + i, NULL, &b, sizeof(b) | ATOX_U | ATOX_TR);
	i += ret;
	if (ret < 0 || s[i])
		return (1);
	*to_fill = b + (g << 8) + (r << 16);
	return (0);
}

void	read_color(t_all *a, t_map_elem elem_type)
{
	if ((elem_type == COLOR_F && a->game.map.color_f != -1)
		|| (elem_type == COLOR_C && a->game.map.color_c != -1))
		error_parse_duplicate(a, a->file.split_line[0]);
	if ((elem_type == COLOR_F
			&& get_color(a->file.split_line[1], &a->game.map.color_f))
		|| (elem_type == COLOR_C
			&& get_color(a->file.split_line[1], &a->game.map.color_c)))
		error_parse(a, ERR_BADCOLOR, NULL);
}
