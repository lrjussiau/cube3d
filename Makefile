NAME = cube3D
FILES = cube3d \
			utils \
			parsing_map \
			parsing_map__utils

CFILES = $(FILES:%=%.c)
OFILES = $(FILES:%=%.o)

LIBFT_DIR = libft
LIBFT_MAKEFILE = $(LIBFT_DIR)/Makefile
LIBFT = $(LIBFT_DIR)/$(NAME)

#-Wall -Wextra -Werror

CC = gcc
CFLAGS = -Imlx -I$(LIBFT_DIR) -g
LDFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit -L$(LIBFT_DIR) -lft

all: $(NAME)

$(NAME): $(OFILES) $(LIBFT)
	$(CC) $(OFILES) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OFILES)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re $(LIBFT)
