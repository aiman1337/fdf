/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouass <ahouass@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:50:03 by ahouass           #+#    #+#             */
/*   Updated: 2025/02/26 16:14:32 by ahouass          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# define ANGLE 0.523599
# define WINDOW_WIDTH 1700
# define WINDOW_HEIGHT 1000
# define KEY_P 35
# define KEY_I 34
# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2
# define KEY_Q 12
# define KEY_E 14
# define PLUS_KEY 		69
# define MINUS_KEY 		78
# define LEFT_ARROW 	123
# define RIGHT_ARROW 	124
# define UP_ARROW 		125
# define DOWN_ARROW 	126
# define ESC_KEY 		53
# define R_KEY			15

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_rotation
{
	double	x;
	double	y;
	double	z;
}	t_rotation;

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
	int		zoom;
	int		x_offset;
	int		y_offset;
	int		rotation_x;
	int		rotation_y;
	int		rotation_z;
	int		flag;
	int		auto_rotate;
}	t_map;

// Function prototypes
int				get_map_height(char *filename);
int				get_map_width(char *filename);
void			put_pixel(t_map *map, int x, int y, unsigned int color);
void			draw_line_to_image(t_map *mp, t_p f, t_p s, unsigned int color);
t_p				project(int x, int y, int z, t_map *map);
int				close_window(t_map *map);
unsigned int	ft_atoi_hex(const char *str);
void			handle_projection(int keycode, t_map *map);
void			handle_rotation(int keycode, t_map *map);
void			handle_zoom(int keycode, t_map *map);
void			handle_moves(int keycode, t_map *map);
int				handle_keypress(int keycode, t_map *map);
void			draw_map(t_map *map);
void			ft_fill_matrix(t_map *fdf, char *filename);
int				ft_atoi(const char *str);
int				ft_isdigit(int x);
void			*ft_memset(void *s, int c, size_t n);
char			**ft_split(char const *s, char c);
int				ft_count_words(char const *str, char c);
int				ft_strcmp(char *s1, char *s2);
t_bresenham		init_bresenham(t_p f, t_p s);
int				bresenham_step(t_p *f, t_bresenham *b);
double			degrees_to_radians(double degrees);
void			rotate_x(double y, double z, double rad_x, t_rotation *result);
void			rotate_y(double x, double z, double rad_y, t_rotation *result);
void			rotate_z(double x, double y, double rad_z, t_rotation *result);
int				ft_auto_rotate(t_map *map);
void			ft_free_map(t_point **point, int height);
void			ft_swap(t_bresenham *b);
char			*get_next_line(int fd);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strdup(const char *s);
size_t			ft_strlen(const char *str);
char			*ft_strchr(const char *s, int c);
char			*ft_substr(char const *s, unsigned int start, size_t len);

#endif