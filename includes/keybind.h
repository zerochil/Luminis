#ifndef KEYBINDS_H
# define KEYBINDS_H

# include <libft.h>
# include <entity.h>
# include <vec3.h>

# define RADIUS_STEP 0.1
# define HEIGHT_STEP 1.0
# define ANGLE_STEP 1.0
# define POS_STEP 2.0
# define FOV_STEP 1.0

# define KEY_ESC 65307
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65363
# define KEY_RIGHT 65361

# define KEY_LEFT_CLICK 1
# define KEY_RIGHT_CLICK 2
# define KEY_SCROLL_UP 4
# define KEY_SCROLL_DOWN 5

enum
{
	FOV,
	RADIUS,
	OBJ_HEIGHT,
	ANGLE,
	X_POS,
	Y_POS,
	Z_POS,
	X_ROT,
	Y_ROT,
	Z_ROT,
};

enum
{
	NONE,
	LIGHT,
	CAMERA,
	OBJECT,
};

typedef struct s_entity
{
	int		type;
	union
	{
		t_light *light;
		t_camera *camera;
		t_object *object;
	};
}	t_entity;

typedef struct s_keybind t_keybind;

struct s_keybind
{
    int	property;
	int pos_key;
	int neg_key;
	int dir_flag;
    void (*update)(t_keybind *, t_entity *);
};

void    keybind_set_dir_flag(t_keybind *keybind, int keycode);
void    keybind_reset_dir_flag(t_keybind *keybind, int keycode);
t_array *keybinds_init(void);

#endif
