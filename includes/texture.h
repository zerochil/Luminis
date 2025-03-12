#ifndef TEXTURE_H
# define TEXTURE_H

# include <mlx.h>
# include <mlx_image.h>
# include <object.h>
# include <libft.h>

#define IS_BUMP_TEXTURE true
#define IS_COLOR_TEXTURE false

enum e_texturetype{
    TEXTURE_SOLID,
    TEXTURE_CHECKER,
    TEXTURE_BUMP_MAP
};

struct s_solidtexture{
    t_vec3 color;
};

struct s_checkertexture{
    t_vec3 color1;
	t_vec3 color2;
    double scale;
};

struct s_bumpmaptexture{
    unsigned char *ptr;
    int width;
	int height;
	int channels;
};

typedef struct s_texture t_texture;
typedef t_vec3 (*uv_map)(struct s_texture *self, t_hit *hit);

struct s_texture {
	char *name;
	char *filename;
    enum e_texturetype type;
    union {
        struct s_solidtexture solid;
        struct s_checkertexture checker;
        struct s_bumpmaptexture bump_map;
    };
    uv_map evaluate;
};



/*typedef struct s_texture*/
/*{*/
/*	double	*ptr;*/
/*	int 	width;*/
/*	int 	height;*/
/*}	t_texture;*/

bool load_texture(void *mlx, char *filename, t_texture *texture, bool is_bump_texture);
double get_texture_uv(t_texture *texture, double u, double v);

#endif
