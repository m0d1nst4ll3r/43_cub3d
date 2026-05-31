#include "cub3d.h"

// 1. Checks name (.cub)
// 2. Tries to open
// 3. Parse pre-grid elements (textures and colors)
// 4. Parse map grid
//
// Note that before 4, the rest of the file (normally, grid) is buffered.
// This is done so that we can know dimensions, malloc, and check-as-we-fill.
void	parse_data_from_file(t_all *a, char *filename)
{
	int	i;

	i = 0;
	while (filename[i])
		i++;
	if (i < 5 || filename[i - 1] != 'b' || filename[i - 2] != 'u'
		|| filename[i - 3] != 'c' || filename[i - 4] != '.')
		error_out(a, ERR_BADNAME, NULL);
	a->file.fd = open(filename, O_RDONLY);
	if (a->file.fd == -1)
		error_out(a, ERR_OPEN, filename);
	parse_map_elems(a); // NO SO WE EA F C, exits by itself
	buffer_map_grid(a); // Buffer map grid in advance, exits in case of newline
	close(a->file.fd);
	a->file.fd = -1;
	parse_map_grid(a); // Map grid, exits by itself
	free_file_contents(a->file.contents); // Could rename "file_contents" to "file_buffer"
	a->file.contents = NULL;
}
