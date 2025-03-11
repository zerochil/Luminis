#include <keybind.h>
#include <camera.h>
static t_keybind *keybind_create(int property, int pos_key, int neg_key, void (*update)(t_keybind*, t_entity *))
{
    t_keybind   *keybind;

    keybind = track_malloc(sizeof(t_keybind));
    keybind->property = property;
    keybind->pos_key = pos_key;
    keybind->neg_key = neg_key;
    keybind->dir_flag = 0;
    keybind->update = update;
    return (keybind);
}

void    keybind_set_dir_flag(t_keybind *keybind, int keycode)
{
    if (keycode != keybind->pos_key && keycode != keybind->neg_key)
        return ;
    keybind->dir_flag = 1 - 2 * (keycode == keybind->neg_key);
}

void    keybind_reset_dir_flag(t_keybind *keybind, int keycode)
{
    if (keycode != keybind->pos_key && keycode != keybind->neg_key)
        return ;
    keybind->dir_flag = 0;
}

void    keybind_print(void *ptr)
{
    t_keybind *keybind;

    keybind = ptr;
    printf("keybind {%d, dir= %d}\n", keybind->property, keybind->dir_flag);
}

void update_radius(t_keybind *keybind, t_entity *selected)
{
    t_object *object;

    if (keybind == NULL || selected == NULL)
        return ;
    if (selected->type != OBJECT)
        return ;
    object = selected->object;
    if (object->type == SPHERE)
        object->radius += keybind->dir_flag * RADIUS_STEP;
    else if (object->type == CYLINDER)
        object->radius += keybind->dir_flag * RADIUS_STEP;
}

void update_height(t_keybind *keybind, t_entity *selected)
{
    t_object *object;

    if (keybind == NULL || selected == NULL)
        return ;
    if (selected->type != OBJECT || selected->object->type != CYLINDER)
        return ;
    object = selected->object;
    object->height += keybind->dir_flag * HEIGHT_STEP;
}

void update_angle(t_keybind *keybind, t_entity *selected)
{
    t_object *object;
    if (keybind == NULL || selected == NULL)
        return ;
    if (selected->type != OBJECT || selected->object->type != CONE)
        return ;
    object = selected->object;
    object->angle += keybind->dir_flag * ANGLE_STEP;
}

void update_pos(t_keybind *keybind, t_entity *selected)
{
    t_vec3 *pos;

    if (selected->type == CAMERA)
    {
        camera_translate(selected->camera, keybind->property, keybind->dir_flag * POS_STEP);
        return ;
    }
    if (selected->type == LIGHT)
        pos = &selected->light->origin;
    if (selected->type == OBJECT)
        pos = &selected->object->origin;
    pos->x += keybind->dir_flag * (keybind->property == X_POS) * POS_STEP;
    pos->y += keybind->dir_flag * (keybind->property == Y_POS) * POS_STEP;
    pos->z += keybind->dir_flag * (keybind->property == Z_POS) * -POS_STEP;
}

void    object_rotate(t_object *object, t_vec3 axis, double angle)
{
    if (object->type == CYLINDER)
        rotate_dev(&object->orientation, axis, angle);
    else if (object->type == PLANE)
        rotate_dev(&object->orientation, axis, angle);
    else if (object->type == CONE)
        rotate_dev(&object->orientation, axis, angle);
}

void update_rot(t_keybind *keybind, t_entity *selected)
{
    t_camera *camera;
    t_object *object;
    t_vec3  axis;
    double angle;

    angle = keybind->dir_flag * ANGLE_STEP;
    if (selected->type == LIGHT)
        return ;
    if (selected->type == CAMERA)
    {
        camera = selected->camera;
        if (keybind->property == X_ROT)
            axis = camera->right;
        else if (keybind->property == Y_ROT)
            axis = camera->up;
        else
            axis = camera->forward;
        camera_rotate(selected->camera, axis, angle);
    }
    if (keybind->property == X_ROT)
        axis = (t_vec3){1,0,0};
    else if (keybind->property == Y_ROT)
        axis = (t_vec3){0,1,0};
    else
        axis = (t_vec3){0,0,1};
    //TODO: flatten object definition so that we apply rotation directly on the normal.
    object = selected->object;
    object_rotate(object, axis, keybind->dir_flag * ANGLE_STEP);
}

t_array *keybinds_init(void)
{
    t_array *keybinds;

    keybinds = array_create();
    array_push(keybinds, keybind_create(RADIUS, 'r', 't', update_radius));
    array_push(keybinds, keybind_create(OBJ_HEIGHT, 'h', 'j', update_height));
    array_push(keybinds, keybind_create(ANGLE, 'x', 'z', update_angle));
    array_push(keybinds, keybind_create(X_POS, 'd', 'a', update_pos));
    array_push(keybinds, keybind_create(Y_POS, 'e', 'q', update_pos));
    array_push(keybinds, keybind_create(Z_POS, 'w', 's', update_pos));
    array_push(keybinds, keybind_create(X_ROT, KEY_UP, KEY_DOWN, update_rot));
    array_push(keybinds, keybind_create(Y_ROT, KEY_RIGHT, KEY_LEFT, update_rot));
    array_push(keybinds, keybind_create(Z_ROT, '[', ']', update_rot));
    return (keybinds);
}

