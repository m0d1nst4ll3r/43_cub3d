#include "cub3d.h"

// Advanced key handling:
// Key down sets key state to "ON"
// Key up sets key state to "OFF"
// When key is ON, a timer starts - when the timer expires, the key will now auto-repeat at a set rate
//
// This overwrites the system's own key handling which would not allow holding W and A at the same time, for example
/*void	set_hooks(t_all *a)
{
	mlx_hook(a->mlx.win, KEYPRESS, KEYPRESSMASK, key_down_hook, a);
	mlx_hook(a->mlx.win, KEYRELEASE, KEYRELEASEMASK, key_up_hook, &a->key);
	mlx_hook(a->mlx.win, BUTTONPRESS, BUTTONPRESSMASK, mouse_down_hook, a);
	mlx_hook(a->mlx.win, BUTTONRELEASE, BUTTONRELEASEMASK,
		mouse_up_hook, &a->mouse);
	mlx_hook(a->mlx.win, MOTIONNOTIFY, POINTERMOTIONMASK,
		pointer_motion_hook, a);
	mlx_hook(a->mlx.win, CLIENTMESSAGE, 1, clientmsg_hook, a);
	mlx_loop_hook(a->mlx.ptr, engine_loop, a);
}*/

// Attempts to move player for x and y
// Values are clamped to [0.01,0.99] in case of a wall
// These values might be a problem for raycasting, will see later
// 1. Where is player?
// 2. Are x and y positive or negative?
// 3. Check relevant tile. Is it wall?
// 4. Will movement go beyond wall? -> Clamp.
// We are forbidding > 1 movements (too high speed, algorithm will break)
void	player_move(t_all *a, float x, float y)
{
	if (x > 1)
		x = 1;
	if (y > 1)
		y = 1;
	a->game.player.y += y;
	a->game.player.x += x;
	if (y > 0 && a->game.map.grid[(int)a->game.player.y][(int)a->game.player.x]
		== TILE_WALL)
		a->game.player.y = (float)(int)a->game.player.y - 0.01;
	else if (y < 0 && a->game.map.grid[(int)a->game.player.y][(int)a->game.player.x]
		== TILE_WALL)
		a->game.player.y = (float)(int)(a->game.player.y + 1) + 0.01;
	if (x > 0 && a->game.map.grid[(int)a->game.player.y][(int)a->game.player.x]
		== TILE_WALL)
		a->game.player.x = (float)(int)a->game.player.x - 0.01;
	if (x < 0 && a->game.map.grid[(int)a->game.player.y][(int)a->game.player.x]
		== TILE_WALL)
		a->game.player.x = (float)(int)(a->game.player.x + 1) + 0.01;
}

// This moves only NESW for now. We need a formula for the angle
// Imagine a circle of radius 1. We want player to move 1 unit in any direction, depending on angle. Visualize his angle and draw a point on the circle. That point has a x and y coordinate. This is the x and y by how much the player will move if he moves forward. Moving backwards, just invert x and y. Left, take the angle and add half a Pi to the radian. Right, remove half a Pi.
void	player_move_forward(t_all *a)
{
	player_move(a, 0, -PLAYER_SPEED);
	a->time.img_need_redraw = true;
}

void	player_move_backward(t_all *a)
{
	player_move(a, 0, PLAYER_SPEED);
	a->time.img_need_redraw = true;
}

void	player_move_left(t_all *a)
{
	player_move(a, -PLAYER_SPEED, 0);
	a->time.img_need_redraw = true;
}

void	player_move_right(t_all *a)
{
	player_move(a, PLAYER_SPEED, 0);
	a->time.img_need_redraw = true;
}

int	key_down_hook(int keycode, t_all *a)
{
	if (keycode == KEY_ESC)
		exit_prog(a, 0);
	else if (keycode == KEY_W)
		player_move_forward(a);
	else if (keycode == KEY_A)
		player_move_left(a);
	else if (keycode == KEY_S)
		player_move_backward(a);
	else if (keycode == KEY_D)
		player_move_right(a);
	return (0);
}

void	show_fps(t_time *time)
{
	printf("[Engine speed: %d] [Fps: %d]\n", time->loop_count, time->frame_count);
	time->loop_count = 0;
	time->frame_count = 0;
	time->last_fps = time->current;
}

int	engine_loop(t_all *a)
{
	gettimeofday(&a->time.current, NULL);
	if (a->time.img_need_redraw && ft_time_sub(a->time.current,
			a->time.last_refresh) > REFRESH_RATE_USEC)
		redraw_img(a);
	if (ft_time_sub(a->time.current, a->time.last_fps) > 1000000)
		show_fps(&a->time);
	a->time.loop_count++;
	return (0);
}

void	set_hooks(t_all *a)
{
	mlx_hook(a->mlx.win, KeyPress, KeyPressMask, key_down_hook, a);
	mlx_loop_hook(a->mlx.ptr, engine_loop, a);
}
