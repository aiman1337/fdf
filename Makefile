# Compiler and flags
CC             = cc
CFLAGS         = -Wall -Wextra -Werror -DGL_SILENCE_DEPRECATION

# Directories and libraries
GNL_DIR        = get_next_line
MLX_DIR        = minilibx_macos
MLX            = $(MLX_DIR)/libmlx.a

# Sources and objects
SRCS           = fdf.c ft_atoi_hex.c ft_keypress.c ft_drawing.c ft_fill_map.c ft_atoi.c ft_isdigit.c ft_memset.c ft_split.c\
                 get_next_line.c \
                 get_next_line_utils.c
OBJS           = $(SRCS:.c=.o)

# Libraries
LIBS           = $(MLX) -framework OpenGL -framework AppKit

# Name of the executable
NAME           = fdf

# Rules
all: $(NAME)

$(NAME): $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

clean:
	$(MAKE) -C $(MLX_DIR) clean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
