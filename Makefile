NAME = minirt
CC = cc
INCLUDE = ./includes
CFLAGS = -Werror -Wextra -Wall -Llibmath -Ilibmath -Ilibft -Llibft -I$(INCLUDE) #-fsanitize=address

SRCS = minirt.c \
       parser/parser.c\
	   parser/parser_utils.c\
	   parser/parser_predicates.c\
	   parser/parser_error.c\
	   debug.c\
	   object.c\
	   render.c\
	   handle_event.c\
	   camera.c\
	   color.c\
	   mlx_image.c\
	   texture.c

OBJS_DIR = .objects/
OBJS = $(SRCS:%.c=$(OBJS_DIR)%.o)
HEADER_FILES = minirt.h         \
			   parser.h			\
			   scene.h			\
			   debug.h			\
			   camera.h         \
			   handle_event.h   \
			   object.h			\
			   mlx_image.h		\
			   texture.h		\
			   material.h		

HEADERS = $(HEADER_FILES:%=$(INCLUDE)/%)
LIBRARIES = libft/libft.a libmath/libmath.a

all: $(NAME)

$(NAME): $(LIBRARIES) $(OBJS)
	$(CC)  $(CFLAGS) $(LIBRARIES) $(OBJS) -o $(NAME) -lmath -lft -lm -lmlx -L/usr/lib -lmlx -lXext -lX11 -lz

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

fclean: clean
	rm -rf $(NAME)
	@make -C libft fclean --no-print-directory

re: fclean all

bonus: all

.PHONY: all clean fclean re FORCE bonus
