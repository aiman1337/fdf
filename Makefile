NAME           = fdf

CC             = cc
CFLAGS         = -Wall -Wextra -Werror

MLX_DIR        = ../minilibx_macos
MLX            = $(MLX_DIR)/libmlx.a

SRCS           = fdf.c ft_atoi_hex.c ft_keypress.c ft_drawing.c ft_fill_map.c ft_atoi.c ft_isdigit.c ft_memset.c ft_split.c ft_strcmp.c utils.c ft_bresenham.c ft_rotate_bonus.c get_next_line.c get_next_line_utils.c
OBJS           = $(SRCS:.c=.o)

LIBS           = $(MLX) -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

bonus: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@touch bonus

%.o: %.c fdf.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) bonus

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
