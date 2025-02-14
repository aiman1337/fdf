/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouass <ahouass@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:39:50 by ahouass           #+#    #+#             */
/*   Updated: 2025/02/12 13:25:00 by ahouass          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line_to_image(t_map *map, t_p f, t_p s, unsigned int color)
{
	t_bresenham	b;

	b = init_bresenham(f, s);
	while (1)
	{
		put_pixel(map, f.x, f.y, color);
		if (!bresenham_step(&f, s, &b))
			break ;
	}
}

t_p	iso_projection(t_map *map, int x, int y, int z)
{
	t_p			p;
	double		rad_x;
	double		rad_y;
	double		rad_z;
	t_rotation	rot;

	rad_x = degrees_to_radians(map->rotation_x);
	rad_y = degrees_to_radians(map->rotation_y);
	rad_z = degrees_to_radians(map->rotation_z);
	rotate_x((double)y, (double)z, rad_x, &rot);
	rotate_y((double)x, rot.z, rad_y, &rot);
	rotate_z(rot.x, rot.y, rad_z, &rot);
	p.x = (rot.x - rot.y) * cos(ANGLE) * map->zoom + map->x_offset;
	p.y = ((rot.x + rot.y) * sin(ANGLE) - rot.z) * map->zoom + map->y_offset;
	return (p);
}

t_p	project(int x, int y, int z, t_map *map)
{
	t_p	p;

	if (map->flag == 1)
		p = iso_projection(map, x, y, z);
	else 
	{
		p.x = x * map->zoom + map->x_offset;
		p.y = y * map->zoom + map->y_offset;
	}
	p.x += WINDOW_WIDTH / 2;
	p.y += WINDOW_HEIGHT / 3;
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
