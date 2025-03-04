#ifndef HANDLE_EVENT_H
# define HANDLE_EVENT_H

# include <scene.h>
# include <vec3.h>
# include <matrix.h>
# include <mlx.h>
# include <camera.h>

# define STEP -1
# define ANGLE 1

# define KEY_ESC 65307
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65363
# define KEY_RIGHT 65361

# define KEY_SCROLL_UP 4
# define KEY_SCROLL_DOWN 5

enum
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

int	on_key_event(int keycode, t_mlx *mlx);
int	on_mouse_event(int keycode, int x, int y, t_mlx *mlx);
int	close_win(t_mlx *mlx);

#endif