/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouass <ahouass@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:50:03 by ahouass           #+#    #+#             */
/*   Updated: 2025/01/24 17:31:59 by ahouass          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_macos/mlx.h"
#include "get_next_line.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#define SCALE 20
#define ISO_ANGLE 30 // Isometric angle
#define Z_SCALE 2 // Adjust this value to control the height effect
#define WINDOW_WIDTH 1700
#define WINDOW_HEIGHT 1000

typedef struct s_point
{
	int	height;
	int	color;
}	t_point;

typedef struct s_p
{
    int x;
    int y;
} t_p;

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
}	t_map;

// Function prototypes
int		get_map_height(char *filename);
int		get_map_width(char *filename);
void	ft_fill_matrix(t_map *fdf, char *filename);
void	put_pixel_to_image(char *data, int x, int y, int color, int size_line, int bpp);
void	draw_line_to_image(char *data, t_p f, t_p s, int color, int size_line, int bpp);
t_p		project(int x, int y, int z, t_map *map);
void	draw_map(t_map *map);
int		handle_keypress(int keycode, t_map *map);
int		close_window(void);
int		ft_atoi_hex(const char *str);

void    handle_projection(int keycode, t_map *map);
void    handle_rotation(int keycode, t_map *map);
void    handle_zoom(int keycode, t_map *map);
void    handle_moves(int keycode, t_map *map);
int 	handle_keypress(int keycode, t_map *map);

void    draw_map(t_map *map);

void    ft_fill_matrix(t_map *fdf, char *filename);

int	ft_atoi(const char *str);
int	ft_isdigit(int x);
void	*ft_memset(void *s, int c, size_t n);
char	**ft_split(char const *s, char c);
int	ft_count_words(char const *str, char c);