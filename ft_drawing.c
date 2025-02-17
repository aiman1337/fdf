/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouass <ahouass@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:39:50 by ahouass           #+#    #+#             */
/*   Updated: 2025/02/17 18:09:36 by ahouass          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line_to_image(t_map *map, t_p f, t_p s, unsigned int color)
{
	t_bresenham	b;

	b = init_bresenham(f, s);
	if (b.dy > b.dx)
	{
		ft_swap(&b);
		b.swap_axes = 1;
	}
	b.err = 2 * b.dy - b.dx;
	while (1)
	{
		put_pixel(map, f.x, f.y, color);
		if (f.x == s.x && f.y == s.y)
			break ;
		bresenham_step(&f, &b);
	}
}

t_p	iso_projection(t_map *map, int x, int y, int z)
{
	t_p	p;
	int	scale;

	if (map->height > 250)
		scale = 1;
	else if (map->height > 40)
		scale = 3;
	else
		scale = 20;
	p.x = (x - y) * cos(30 * M_PI / 180.0) * scale;
	p.y = (x + y) * sin(30 * M_PI / 180.0) * scale - z * scale;
	return (p);
}

t_p	project(int x, int y, int z, t_map *map)
{
	t_p	p;

	p = iso_projection(map, x, y, z);
	p.x += WINDOW_WIDTH / 2;
	p.y += WINDOW_HEIGHT / 2;
	return (p);
}

void	draw_adjacent_lines(t_map *map, t_p p1, int x, int y)
{
	t_p	p2;

	if (x + 1 < map->width)
	{
		p2 = project(x + 1, y, map->point[y][x + 1].height, map);
		draw_line_to_image(map, p1, p2, map->point[y][x].color);
	}
	if (y + 1 < map->height)
	{
		p2 = project(x, y + 1, map->point[y + 1][x].height, map);
		draw_line_to_image(map, p1, p2, map->point[y][x].color);
	}
}

void	draw_map(t_map *map)
{
	t_p	p1;
	int	x;
	int	y;

	y = 0;
	ft_memset(map->data, 0, WINDOW_WIDTH * WINDOW_HEIGHT * (map->bpp / 8));
	while (y < map->height)
	{
		x = 0;
		while (x < map->width) 
		{
			p1 = project(x, y, map->point[y][x].height, map);
			draw_adjacent_lines(map, p1, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(map->mlx, map->mlx_win, map->mlx_img, 0, 0);
}
