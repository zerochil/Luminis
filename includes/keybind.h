/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybind.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:53:13 by rrochd            #+#    #+#             */
/*   Updated: 2025/04/15 17:31:04 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYBIND_H
# define KEYBIND_H

# include <camera.h>
# include <libft.h>
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

typedef struct s_keybind	t_keybind;

struct	s_keybind
{
	int		property;
	int		pos_key;
	int		neg_key;
	int		dir_flag;
	void	(*update)(t_keybind *, t_entity *);
};

void		keybind_set_dir_flag(t_keybind *keybind, int keycode);
void		keybind_reset_dir_flag(t_keybind *keybind, int keycode);
t_array		*keybinds_init(void);
t_vec3		get_rot_axis(int axis, t_vec3 a1, t_vec3 a2, t_vec3 a3);
void		update_fov(t_keybind *keybind, t_entity *selected);
void		update_radius(t_keybind *keybind, t_entity *selected);
void		update_height(t_keybind *keybind, t_entity *selected);
void		update_angle(t_keybind *keybind, t_entity *selected);
void		update_pos(t_keybind *keybind, t_entity *selected);
void		update_rot(t_keybind *keybind, t_entity *selected);

#endif
