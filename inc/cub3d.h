#ifndef CUB3D_H
# define CUB3D_H

// ================================= INCLUDES ==================================

#include "mlx.h"
#include "libft.h"
#include <unistd.h> // write, read, open
#include <stdio.h> // printf
#include <fcntl.h> // open

// ================================== MACROS ===================================

// Colors
# define RED			"\e[0;31m"
# define YEL			"\e[0;33m"
# define RES			"\e[0m"

// Identifiers
# define TEX_NO_STR		"NO"
# define TEX_SO_STR		"SO"
# define TEX_WE_STR		"WE"
# define TEX_EA_STR		"EA"
# define COLOR_F_STR	"F"
# define COLOR_C_STR	"C"

// Errors - Custom
# define ERR_NOARGS		"Not enough arguments\nUsage: ./cub3d your_map.cub"
# define ERR_MANYARGS	"Too many arguments\nUsage: ./cub3d your_map.cub"
# define ERR_BADNAME	"Map filename must end in .cub and name cannot be empty"
# define ERR_MAPELEMS	"Map does not contain all required textures and/or \
colors (NO, SO, WE, EA, F, C)"
# define ERR_FEWELEM	"Line is missing corresponding value (texture file or\
color)"
# define ERR_MANYELEM	"Too many values in this line"
# define ERR_BADTEX		"Could not open texture file"
# define ERR_BADCOLOR	"Bad color format, expected R,G,B each between 0 and\
255"
# define ERR_MAPNEWLINE	"Empty lines inside of the level map are not accepted"
# define ERR_NOSPAWN	"Missing player spawn point"
# define ERR_MANYSPAWN	"Found multiple player spawn points"
# define ERR_NOWALL		"An open tile is not completely surrounded by walls"
// Errors - Syscall
# define ERR_OPEN		"Could not open file"
# define ERR_READ		"Read/malloc error while reading map file"
# define ERR_MALLOC		"Malloc failed"

// ================================== STRUCTS ==================================

typedef struct s_file_contents
{
	char			*line;
	struct s_file	*next;
}	t_file_contents;

typedef enum e_map_elem
{
	TEX_NO,
	TEX_SO,
	TEX_WE,
	TEX_EA,
	COLOR_F,
	COLOR_C
}	t_map_elem;

typedef struct s_file
{
	t_file_contents	*contents; // Only used during map grid parsing (after elems) - can rename this "file buffer" or "grid buffer"
	char			**split_line; // Contains line elems (normally only 2)
	int				i; // Parse line index
	int				fd;
}	t_file;

// Contains image either for texture or for main window
typedef struct  s_img
{
    void    *ptr;
    char    *addr;
    int     bpp; //bits per pixel
    int     llen; //line length
    int     endian;
    int     width;
    int     height;
}   t_img;

// May not be needed, TODO remove if not needed
typedef struct s_color
{
    int             val;
    unsigned char   r;
    unsigned char   g;
    unsigned char   b;
}   t_color;

typedef enum e_map_tile_char
{
	MAP_SPACE = ' ',
	MAP_WALL = '1',
	MAP_EMPTY = '0',
	MAP_N = 'N',
	MAP_S = 'S',
	MAP_E = 'E',
	MAP_W = 'W'
}	t_map_tile_char;

typedef enum e_map_tile
{
    TILE_VOID, // ' '
    TILE_WALL, // '1'
    TILE_OPEN // '0' or 'N' 'W' 'E' 'S'
	// Can add more, e.g MAP_HDOOR and MAP_VDOOR
}   t_map_tile;

typedef struct s_map
{
    t_map_tile  *data;
	t_map_tile	**grid;
    int         width;
    int         height;
	t_img		tex_no;
	t_img		tex_so;
	t_img		tex_we;
	t_img		tex_ea;
	int			color_c; // May swap to t_color if rgb values needed
	int			color_f;
}   t_map;

typedef struct s_player
{
    float   x;
    float   y;
    float   angle;
}   t_player;

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
	t_img	img;
}	t_mlx;

typedef struct s_game
{
	t_player	player;
	t_map		map;
}	t_game;

typedef struct s_all
{
	t_game	game;
	t_mlx	mlx;
	t_file	file;
}	t_all;

// ================================ PROTOTYPES =================================

// Parsing - main func
void	parse_data_from_file(t_all *a, char *filename);
// Parsing - helpers called in main func
void	parse_map_elems(t_all *a);
void	parse_map_grid(t_all *a);
void	buffer_map_grid(t_all *a);
// Parsing - sub helpers called in parse_map_elems
int		read_texture(t_all *a, e_map_elem elem_type);
int		read_color(t_all *a, e_map_elem elem_type);
// Parsing - sub helper called in parse_map_grid
void	fill_grid(t_all *a, t_file_contents *list);

// Cleanup
void	cleanup_prog(t_all *a);
// Exit
void	exit_prog(t_all *a, unsigned char exitval);
// Error
void	error_parse_duplicate(t_all *a, char *s);
void	error_parse(t_all *a, char *s1, char *s2);
void	error_out(t_all *a, char *s1, char *s2);
// Free
void	free_file_contents(t_file_contents *file);
void	free_strs(char **s);

#endif /* CUB3D_H */
