#ifndef CUB3D_H
# define CUB3D_H

// ================================= INCLUDES ==================================

# include "mlx.h"
# include "libft.h"
# include <stdbool.h>	// bool type
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
# define ERR_INVNAME	"Invalid map name. A valid '*.cub' file is required"
# define ERR_VISNAME	"Invalid map name. A visible '*.cub' file is required"
# define ERR_EMPFILE	"File is empty"
# define ERR_MLX		"Failed initializing minilibx"
# define ERR_MAPELEMS	"Map does not contain all required textures and/or\
 colors (NO, SO, WE, EA, F, C)"
# define ERR_FEWELEM	"Line is missing corresponding value (texture file or\
 color)"
# define ERR_MANYELEM	"Too many values in this line"
# define ERR_BADTEX		"Could not open texture file"
# define ERR_BADCOLOR	"Bad color format, expected R,G,B each between 0 and\
 255"
# define ERR_NOMAP		"Missing map"
# define ERR_MAPNEWLINE	"Found empty line in map"
# define ERR_NOSPAWN	"Missing player spawn point"
# define ERR_MANYSPAWN	"Found multiple player spawn points"
# define ERR_NOWALL		"An open tile is not completely surrounded by walls"

// Errors - Syscall
# define ERR_OPEN		"Could not open file"
# define ERR_READ		"Read/malloc error while reading map file"
# define ERR_MALLOC		"Malloc failed"

// ================================== STRUCTS ==================================

typedef enum e_map_elem
{
	TEX_NO,
	TEX_SO,
	TEX_WE,
	TEX_EA,
	COLOR_F,
	COLOR_C,
}	t_map_elem;

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

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
	t_img	img;
}	t_mlx;

typedef struct s_parse
{
	t_file	*file;
	t_file	*head; // File reading head
	char	**split_line;
	int		i;
	char	*tex_no;
	char	*tex_so;
	char	*tex_we;
	char	*tex_ea;
}	t_parse;

typedef struct s_cub
{
	t_mlx		mlx;
	t_parse		parse;
	t_map_tile	*map; // 1D map
	t_map_tile	**grid; // 2D map (virtual)
	int			width;
	int			height;
	t_img		tex_no;
	t_img		tex_so;
	t_img		tex_we;
	t_img		tex_ea;
	int			color_c;
	int			color_f;
	float		plx;
	float		ply;
	float		plr;
}	t_cub;

typedef struct s_time
{
	struct timeval	current;
	struct timeval	last_refresh;
	struct timeval	last_fps;
	unsigned int	frame_count;
	unsigned int	loop_count;
	bool			img_need_redraw;
}	t_time;

// ================================ PROTOTYPES =================================

// ==========================
// ========== Init ==========
// ==========================
void	check_args(t_cub *cub, int argc, char **argv);
void	init_data(t_cub *cub);
void	init_mlx(t_cub *cub);

// ==========================
// ========== Parse =========
// ==========================
void	buffer_file(t_cub *cub, char *file);
void	parse_file(t_cub *cub);
void	parse_elems(t_cub *cub);
void	parse_map(t_cub *cub);
// Parse elems helpers
void	parse_color(t_cub *cub, t_map_elem elem_type);
void	parse_texture(t_cub *cub, t_map_elem elem_type);
// Parse map helper
void	parse_map_fill(t_cub *cub, t_file *file);

// ==========================
// ======= Game Logic =======
// ==========================
void	init_hooks(t_cub *cub);

// ==========================
// ========= Render =========
// ==========================
void	redraw_img(t_cub *cub);

// ==========================
// ========= Cleanup ========
// ==========================
void	cleanup_prog(t_cub *cub);
// Exit
void	exit_prog(t_cub *cub, unsigned char exitval);
// Error
void	error_parse_duplicate(t_cub *cub, char *s);
void	error_parse(t_cub *cub, char *s1, char *s2);
void	error_out(t_cub *cub, char *s1, char *s2);
// Free
void	free_strs(char **s);

#endif /* CUB3D_H */
