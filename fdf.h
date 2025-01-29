/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouass <ahouass@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:50:03 by ahouass           #+#    #+#             */
/*   Updated: 2025/01/29 17:51:48 by ahouass          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include "../minilibx_macos/mlx.h"
#include "get_next_line.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#define SCALE 20
#define ANGLE 0.523599
#define Z_SCALE 2 // Adjust this value to control the height effect
#define WINDOW_WIDTH 1700
#define WINDOW_HEIGHT 1000

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
void			ft_fill_matrix(t_map *fdf, char *filename);
void			put_pixel(t_map *map, int x, int y, unsigned int color);
void			draw_line_to_image(t_map *mp, t_p f, t_p s, unsigned int color);
t_p				project(int x, int y, int z, t_map *map);
void			draw_map(t_map *map);
int				handle_keypress(int keycode, t_map *map);
int				close_window(void);
unsigned int	ft_atoi_hex(const char *str);
void			handle_projection(int keycode, t_map *map);
void			handle_rotation(int keycode, t_map *map);
void			handle_zoom(int keycode, t_map *map);
void			handle_moves(int keycode, t_map *map);
int				handle_keypress(int keycode, t_map *map);
void			draw_map(t_map *map);
void			ft_fill_matrix(t_map *fdf, char *filename);
unsigned int	ft_atoi(const char *str);
int				ft_isdigit(int x);
void			*ft_memset(void *s, int c, size_t n);
char			**ft_split(char const *s, char c);
int				ft_count_words(char const *str, char c);
int				ft_strcmp(char *s1, char *s2);
t_bresenham		init_bresenham(t_p f, t_p s);
int				bresenham_step(t_p *f, t_p s, t_bresenham *b);
double			degrees_to_radians(double degrees);
void			rotate_x(double y, double z, double rad_x, t_rotation *result);
void			rotate_y(double x, double z, double rad_y, t_rotation *result);
void			rotate_z(double x, double y, double rad_z, t_rotation *result);
int				ft_auto_rotate(t_map *map);

#endif