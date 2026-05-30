#include "cub3d.h"

void	free_file_contents(t_file_contents *file)
{
	t_file_contents	*last;

	while (file)
	{
		last = file;
		file = file->next;
		free(last->line);
		free(last);
	}
}

void	free_strs(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}
