/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouass <ahouass@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:50:03 by ahouass           #+#    #+#             */
/*   Updated: 2025/02/17 17:59:27 by ahouass          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../minilibx_macos/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# define WINDOW_WIDTH 2100
# define WINDOW_HEIGHT 1300
# define ESC_KEY 		53

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_bresenham
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	swap_axes;
}	t_bresenham;

typedef struct s_point
{
	int				height;
	unsigned int	color;
}	t_point;

typedef struct s_p
{
	int	x;
	int	y;
}	t_p;

typedef struct s_map
{
	t_point	**point;
	void	*mlx;
	void	*mlx_win;
	void	*mlx_img;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
	int		height;
	int		width;
}	t_map;

// Function prototypes
int				get_map_height(char *filename);
int				get_map_width(char *filename);
void			put_pixel(t_map *map, int x, int y, unsigned int color);
void			draw_line_to_image(t_map *mp, t_p f, t_p s, unsigned int color);
t_p				project(int x, int y, int z, t_map *map);
void			draw_map(t_map *map);
int				close_window(t_map *map);
unsigned int	ft_atoi_hex(const char *str);
int				handle_keypress(int keycode, t_map *map);
void			ft_fill_matrix(t_map *fdf, char *filename);
int				ft_atoi(const char *str);
int				ft_isdigit(int x);
void			*ft_memset(void *s, int c, size_t n);
char			**ft_split(char const *s, char c);
int				ft_count_words(char const *str, char c);
int				ft_strcmp(char *s1, char *s2);
t_bresenham		init_bresenham(t_p f, t_p s);
int				bresenham_step(t_p *f, t_bresenham *b);
void			ft_free_map(t_point **point, int height);
void			ft_swap(t_bresenham *b);
char			*get_next_line(int fd);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strdup(const char *s);
size_t			ft_strlen(const char *str);
char			*ft_strchr(const char *s, int c);
char			*ft_substr(char const *s, unsigned int start, size_t len);

#endif