NAME = minirt
CC = cc
LIBFT_INCLUDE = ./libft
INCLUDE = ./includes
CFLAGS = -Werror -Wextra -Wall -I$(LIBFT_INCLUDE) -Ilibmath -I$(INCLUDE) -fsanitize=address


SRCS = minirt.c parser.c

OBJS_DIR = .objects/
OBJS = $(SRCS:%.c=$(OBJS_DIR)%.o)
HEADER_FILES = minirt.h            \
			   parser.h

HEADERS = $(HEADER_FILES:%=$(INCLUDE)/%)
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS_DIR) $(OBJS)
	$(CC)  $(CFLAGS) $(LIBFT) $(OBJS) -o $(NAME) -Ilibft -Llibft -lft -lmath -lm

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC)  $(CFLAGS) -c $< -o $@ 

$(LIBFT): FORCE
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
