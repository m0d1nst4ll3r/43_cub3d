#ifndef CUB3D_H
# define CUB3D_H

// ================================= INCLUDES ==================================

# include "mlx.h"
# include "libft.h"
# include <stdbool.h>		// bool type
# include <errno.h>		// errno
# include <string.h>	// strerror
# include <unistd.h>	// write, read, exit
# include <stdio.h>		// printf
# include <fcntl.h>		// open, close
# include <stdlib.h>	// malloc, free
# include <math.h>		// M_PI
# include <X11/X.h>		// macros for hooks
# include <sys/time.h>	// gettimeofday

// ================================== MACROS ===================================

// MLX
# define WIN_X				800
# define WIN_Y				600
# define WIN_NAME			"cub3d"
# define REFRESH_RATE_USEC	16666

// Game - Minimap
# define COLOR_VOID		0x0
# define COLOR_WALL		0x555555
# define COLOR_OPEN		0xaaaaaa
# define COLOR_PLAYER	0xff0000
# define RADIUS_PLAYER	2

// Game - Player
# define PLAYER_SPEED	0.1 // Will also depend on key repeat speed

// Colors
# define RED			"\e[0;31m"
# define GRN			"\e[0;32m"
# define YEL			"\e[0;33m"
# define RES			"\e[0m"

// Identifiers
# define TEX_NO_STR		"NO"
# define TEX_SO_STR		"SO"
# define TEX_WE_STR		"WE"
# define TEX_EA_STR		"EA"
# define COLOR_F_STR	"F"
# define COLOR_C_STR	"C"

// Keys
# define KEY_Q				'q'
# define KEY_E				'e'
# define KEY_W				'w'
# define KEY_A				'a'
# define KEY_S				's'
# define KEY_D				'd'
# define KEY_R				'r'
# define KEY_F				'f'
# define KEY_ESC			65307
# define KEY_UP				65362
# define KEY_DOWN			65364
# define KEY_LEFT			65361
# define KEY_RIGHT			65363
# define KEY_LCTRL			65507
# define KEY_LSHIFT			65505

// Mouse buttons
# define BTN_LMB			1
# define BTN_MMB			2
# define BTN_RMB			3
# define BTN_MWU			4
# define BTN_MWD			5

// Errors - Custom
# define ERR_NOARGS		"Not enough arguments\n\e[0;32mUsage\e[0m:\
 ./cub3d your_map.cub"
# define ERR_MANYARGS	"Too many arguments\n\e[0;32mUsage\e[0m:\
 ./cub3d your_map.cub"
# define ERR_BADNAME	"Map filename must end in .cub and name cannot be empty"
# define ERR_MLX		"Failed initializing minilibx"
# define ERR_MAPELEMS	"Map does not contain all required textures and/or\
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
	char					*line;
	struct s_file_contents	*next;
}	t_file_contents;

typedef enum e_map_elem
{
	TEX_NO,
	TEX_SO,
	TEX_WE,
	TEX_EA,
	COLOR_F,
	COLOR_C,
}	t_map_elem;

typedef struct s_file
{
	t_file_contents	*contents; // Only used during map grid parsing (after elems) - can rename this "file buffer" or "grid buffer"
	char			**split_line; // Contains line elems (normally only 2)
	int				i; // Parse line index
	int				fd;
}	t_file;

// Contains image either for texture or for main window
typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp; //bits per pixel
	int		llen; //line length
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef enum e_map_tile_char
{
	MAP_SPACE = ' ',
	MAP_WALL = '1',
	MAP_EMPTY = '0',
	MAP_N = 'N',
	MAP_S = 'S',
	MAP_E = 'E',
	MAP_W = 'W',
}	t_map_tile_char;

typedef enum e_map_tile
{
	TILE_VOID,	// ' '
	TILE_WALL,	// '1'
	TILE_OPEN,	// '0' or 'N' 'W' 'E' 'S'
}	t_map_tile;	// Can add more, e.g MAP_HDOOR and MAP_VDOOR

typedef struct s_map
{
	t_map_tile	*data;
	t_map_tile	**grid;
	int			width;
	int			height;
	t_img		tex_no;
	t_img		tex_so;
	t_img		tex_we;
	t_img		tex_ea;
	int			color_c; // May swap to t_color if rgb values needed
	int			color_f;
}	t_map;

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;
}	t_player;

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

typedef struct s_time
{
	struct timeval	current;
	struct timeval	last_refresh;
	struct timeval	last_fps;
	unsigned int	frame_count;
	unsigned int	loop_count;
	bool			img_need_redraw;
}	t_time;

typedef struct s_all
{
	t_game	game;
	t_mlx	mlx;
	t_file	file;
	t_time	time;
}	t_all;

// ================================ PROTOTYPES =================================

// ======= Parsing =======
void	parse_data_from_file(t_all *a, char *filename);
// Helpers called in main func
void	parse_map_elems(t_all *a);
void	parse_map_grid(t_all *a);
void	buffer_map_grid(t_all *a);
// Sub helpers called in parse_map_elems
void	read_texture(t_all *a, t_map_elem elem_type);
void	read_color(t_all *a, t_map_elem elem_type);
// Sub helper called in parse_map_grid
void	fill_grid(t_all *a, t_file_contents *list);

// ======= Hooks =======
void	set_hooks(t_all *a);

// ======= Rendering =======
void	redraw_img(t_all *a);

// ======= Init =======
void	init_prog(t_all *a);
void	init_mlx_win(t_all *a);

// ======= Cleanup =======
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
