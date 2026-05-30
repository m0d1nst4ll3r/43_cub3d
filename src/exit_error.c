#include "cub3d.h"

void	exit_prog(t_all *a, unsigned char exitval)
{
	cleanup_prog(a);
	exit(exitval);
}

void	error_parse_duplicate(t_all *a, char *s)
{
	ft_fprintf(2, RED "Error" RES ": " YEL "line %d" RES ": Duplicate element \
'%s' found\n", a->file.i, s);
	exit_prog(a, 1);
}

// Also displays line
void	error_parse(t_all *a, char *s1, char *s2)
{
	ft_fprintf(2, RED "Error" RES ": " YEL "line %d" RES ": %s", a->file.i, s1);
	if (s2)
		ft_fprintf(2, ": %s", s2);
	if (errno)
		ft_fprintf(2, ": %s", strerror(errno));
	ft_fprintf(2, "\n");
	exit_prog(a, 1);
}

void	error_out(t_all *a, char *s1, char *s2)
{
	ft_fprintf(2, RED "Error" RES ": %s", s1);
	if (s2)
		ft_fprintf(2, ": %s", s2);
	if (errno)
		ft_fprintf(2, ": %s", strerror(errno));
	ft_fprintf(2, "\n");
	exit_prog(a, 1);
}
