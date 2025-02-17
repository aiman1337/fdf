NAME		= fdf

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

MLX_DIR		= ../minilibx_macos
MLX			= $(MLX_DIR)/libmlx.a

SRCS		= fdf.c ft_atoi_hex.c ft_keypress.c ft_drawing.c ft_fill_map.c ft_atoi.c ft_isdigit.c ft_memset.c ft_split.c ft_strcmp.c utils.c ft_bresenham.c get_next_line.c get_next_line_utils.c
OBJS		= $(SRCS:.c=.o)

SRCS_BNS	= fdf_bonus.c ft_atoi_hex_bonus.c ft_keypress_bonus.c ft_drawing_bonus.c ft_fill_map_bonus.c ft_atoi_bonus.c ft_isdigit_bonus.c ft_memset_bonus.c ft_split_bonus.c ft_strcmp_bonus.c utils_bonus.c \
				ft_bresenham_bonus.c ft_rotate_bonus.c get_next_line_bonus.c get_next_line_utils_bonus.c
OBJS_BNS	= $(SRCS_BNS:.c=.o)

LIBS		= $(MLX) -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

bonus: $(OBJS_BNS)
	$(CC) $(CFLAGS) $(OBJS_BNS) $(LIBS) -o $(NAME)
	@touch bonus

%_bonus.o: %_bonus.c fdf_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c fdf.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OBJS_BNS) bonus

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
