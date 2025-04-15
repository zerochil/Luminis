/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybind.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inajah <inajah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 09:39:38 by inajah            #+#    #+#             */
/*   Updated: 2025/04/15 15:37:03 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <keybind.h>

static t_keybind	*keybind_create(int property, int pos_key, int neg_key,
		void (*update)(t_keybind *, t_entity *))
{
	t_keybind	*keybind;

	keybind = track_malloc(sizeof(t_keybind));
	keybind->property = property;
	keybind->pos_key = pos_key;
	keybind->neg_key = neg_key;
	keybind->dir_flag = 0;
	keybind->update = update;
	return (keybind);
}

void	keybind_set_dir_flag(t_keybind *keybind, int keycode)
{
	if (keycode != keybind->pos_key && keycode != keybind->neg_key)
		return ;
	keybind->dir_flag = 1 - 2 * (keycode == keybind->neg_key);
}

void	keybind_reset_dir_flag(t_keybind *keybind, int keycode)
{
	if (keycode != keybind->pos_key && keycode != keybind->neg_key)
		return ;
	keybind->dir_flag = 0;
}

t_array	*keybinds_init(void)
{
	t_array	*keybinds;

	keybinds = array_create();
	array_push(keybinds, keybind_create(FOV, KEY_SCROLL_DOWN, KEY_SCROLL_UP,
			update_fov));
	array_push(keybinds, keybind_create(RADIUS, 'r', 't', update_radius));
	array_push(keybinds, keybind_create(OBJ_HEIGHT, 'h', 'j', update_height));
	array_push(keybinds, keybind_create(ANGLE, 'x', 'z', update_angle));
	array_push(keybinds, keybind_create(X_POS, 'd', 'a', update_pos));
	array_push(keybinds, keybind_create(Y_POS, 'e', 'q', update_pos));
	array_push(keybinds, keybind_create(Z_POS, 'w', 's', update_pos));
	array_push(keybinds, keybind_create(X_ROT, KEY_UP, KEY_DOWN, update_rot));
	array_push(keybinds, keybind_create(Y_ROT, KEY_RIGHT, KEY_LEFT,
			update_rot));
	array_push(keybinds, keybind_create(Z_ROT, '[', ']', update_rot));
	return (keybinds);
}
