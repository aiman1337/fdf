# Compiler and flags
CC             = cc
CFLAGS         = -Wall -Wextra -Werror -DGL_SILENCE_DEPRECATION

# Directories and libraries
LIBFT_DIR      = libft
LIBFT          = $(LIBFT_DIR)/libft.a
GNL_DIR        = get_next_line
MLX_DIR        = minilibx_macos
MLX            = $(MLX_DIR)/libmlx.a

# Sources and objects
SRCS           = fdf.c ft_atoi_hex.c ft_keypress.c ft_drawing.c ft_fill_map.c\
                 $(GNL_DIR)/get_next_line.c \
                 $(GNL_DIR)/get_next_line_utils.c
OBJS           = $(SRCS:.c=.o)

# Libraries
LIBS           = $(LIBFT) $(MLX) -framework OpenGL -framework AppKit

# Name of the executable
NAME           = fdf

# Rules
all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
