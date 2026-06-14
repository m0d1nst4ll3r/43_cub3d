#include "cub3d.h"

void	error_parse_duplicate(t_cub *cub, char *s)
{
	ft_fprintf(2, RED "Error" RES ": " YEL "line %d" RES ": Duplicate element \
'%s' found\n", cub->parse.i, s);
	exit_prog(cub, 1);
}

// Also displays line
void	error_parse(t_cub *cub, char *s1, char *s2)
{
	ft_fprintf(2, RED "Error" RES ": " YEL "line %d" RES ": %s", cub->parse.i, s1);
	if (s2)
		ft_fprintf(2, ": %s", s2);
	if (errno)
		ft_fprintf(2, ": %s", strerror(errno));
	ft_fprintf(2, "\n");
	exit_prog(cub, 1);
}

void	error_out(t_cub *cub, char *s1, char *s2)
{
	ft_fprintf(2, RED "Error" RES ": %s", s1);
	if (s2)
		ft_fprintf(2, ": %s", s2);
	if (errno)
		ft_fprintf(2, ": %s", strerror(errno));
	ft_fprintf(2, "\n");
	exit_prog(cub, 1);
}
