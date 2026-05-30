#include "cub3d.h"

static int	line_is_empty(t_all *a, char *line)
{
	if (ft_str_is_empty(line))
	{	
		if (!a->file.contents)
			error_parse(a, ERR_MAPNEWLINE, NULL); // This fires also for trailing newlines
		return (1);
	}
	return (0);
}

static t_file_contents	*new_line(char *line)
{
	t_file_contents	*new;

	new = malloc(sizeof(*new));
	if (!new)
	{
		free(line);
		return (NULL);
	}
	new->line = line;
	new->next = NULL;
	return (new);
}

static void	add_line_to_list(t_all *a, char *line, t_file_contents **last_node)
{
	t_file_contents	*line_node;

	line_node = new_line(line);
	if (!line_node)
		error_out(a, ERR_MALLOC, NULL);
	if (!a->file.contents)
		a->file.contents = line_node;
	else
		(*last_node)->next = line_node;
	*last_node = line_node;
}

// Detects empty lines in the middle of the map
// Also detects trailing empty lines
void	buffer_map_grid(t_all *a)
{
	t_file_contents	*last_node;
	char			*line;

	while (1)
	{
		line = get_next_line(a->file.fd);
		if (errno)
			error_out(a, ERR_READ, NULL);
		if (!line)
			return ;
		if (!line_is_empty(a, line))
			add_line_to_list(a, line, &last_node);
		else
		{
			free(line);
			a->file.i++;
		}
	}
}
