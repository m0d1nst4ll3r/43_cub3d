### Parsing

4 Textures: SO NO EA WE

Textures are actually mlx images:

```
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
```

2 Colors: F C

Those are simple ints, but a rgb struct can be useful too:

```
typedef struct s_color
{
	int				val;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;
```

Map

This is an enum array, always rectangular:

```
typedef enum e_map_tile
{
	MAP_NONE,
	MAP_WALL,
	MAP_EMPTY // Can add more, e.g MAP_HDOOR and MAP_VDOOR
}	t_map_tile;

typedef struct s_map
{
	t_map_tile	*contents;
	int			width;
	int			height;
}	t_map;
```

Player pos and angle

For now, pos is a float value and angle also a float value (radian)

```
typedef struct s_player
{
	float	x;
	float	y;
	float	angle;
}	t_player;
```
