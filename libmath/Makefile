CC = cc

CFLAGS = -Wall -Wextra -Werror


OBJECTS_DIR = .objects/

SRCS = libmath.c vec3.c matrix.c

OBJS = $(addprefix $(OBJECTS_DIR), $(SRCS:.c=.o))

HEADERS = libmath.h vec3.h matrix.h

NAME = libmath.a

all: $(NAME)

$(NAME): $(OBJS)
	ar crs $(NAME) $(OBJS)

$(OBJECTS_DIR)%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
