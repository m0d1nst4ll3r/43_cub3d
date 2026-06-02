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
