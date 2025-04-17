NAME = miniRT

CC = cc

INCLUDE = ./includes/

CFLAGS = -Wall -Wextra -Werror -Ilibmath -Ilibft -I$(INCLUDE) -O3 #-fsanitize=thread

HEADER_FILES = minirt.h    \
			   parser.h    \
			   scene.h	   \
			   camera.h    \
			   on_event.h  \
			   keybind.h   \
			   object.h	   \
			   ray.h       \
			   mlx_image.h

PARSER = parser.c            \
		 parser_utils.c      \
		 parser_predicates.c \
		 parser_error.c      \
		 parse_float.c       \
		 parse_line_object.c \
		 parse_line_meta.c   \
		 post_parse.c

OBJECT = plane.c             \
		 sphere.c            \
		 cylinder.c          \
		 cone.c              \
		 find_intersection.c \
		 object.c 

TEXTURE = texture.c              \
		  texture_bumpmap.c      \
		  texture_checkerboard.c \
		  texture_colored.c      \
		  texture_solid.c

KEYBIND = keybind.c        \
		  keybind_update.c \
		  keybind_utils.c

MLX = mlx_image.c \
	  mlx_init.c

MAIN = minirt.c         \
	   lighting.c       \
	   render.c         \
	   ray.c            \
	   on_event.c       \
	   on_event_utils.c \
	   camera.c

HEADERS = $(addprefix $(INCLUDE), $(HEADER_FILES))

SRCS = $(addprefix parser/, $(PARSER))   \
	   $(addprefix object/, $(OBJECT))   \
	   $(addprefix texture/, $(TEXTURE)) \
	   $(addprefix keybind/, $(KEYBIND)) \
	   $(addprefix mlx/, $(MLX))         \
	   $(MAIN)

OBJS_DIR = .objects/
OBJS = $(SRCS:%.c=$(OBJS_DIR)%.o)

LIBRARIES = libft/libft.a libmath/libmath.a

all: $(NAME)

$(NAME): $(LIBRARIES) $(OBJS)
	$(CC)  $(CFLAGS) $(LIBRARIES) $(OBJS) -o $(NAME) -Llibmath -Llibft -lmath -lft -lm -lmlx -L/usr/lib -lmlx -lXext -lX11 -lz

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC)  $(CFLAGS) -c $< -o $@ 

libmath/libmath.a: FORCE
	@make -C libmath --no-print-directory

libft/libft.a: FORCE
	@make -C libft --no-print-directory

FORCE:

clean:
	rm -rf $(OBJS_DIR)
	@make -C libft clean --no-print-directory
	@make -C libmath clean --no-print-directory

fclean: clean
	rm -rf $(NAME)
	@make -C libft fclean --no-print-directory
	@make -C libmath fclean --no-print-directory

re: fclean all

bonus: all

.PHONY: all clean fclean re FORCE bonus
