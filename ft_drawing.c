/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouass <ahouass@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:39:50 by ahouass           #+#    #+#             */
/*   Updated: 2025/02/14 15:44:40 by ahouass          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Calculate appropriate scaling factors based on map dimensions
void calculate_scale(t_map *map)
{
    // Get the maximum possible width and height after rotation
    double max_projected_width = (map->width + map->height) * cos(30 * M_PI / 180.0);
    double max_projected_height = (map->width + map->height) * sin(30 * M_PI / 180.0);
    
    // Calculate scaling factors for both dimensions
    double scale_x = (WINDOW_WIDTH * 0.75) / max_projected_width;
    double scale_y = (WINDOW_HEIGHT * 0.75) / max_projected_height;
    
    // Use the smaller scaling factor to maintain aspect ratio
    map->scale.scale_factor = fmin(scale_x, scale_y);
    // Adjust z-scale based on map size
    map->scale.z_scale = map->scale.scale_factor * 0.5;
    
    // Ensure minimum and maximum scale bounds
    if (map->scale.scale_factor < 2)
        map->scale.scale_factor = 2;
    if (map->scale.scale_factor > 30)
        map->scale.scale_factor = 30;
}

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
	t_p	p;

	p.x = (x - y) * cos(30 * M_PI / 180.0) * map->scale.scale_factor;
	p.y = (x + y) * sin(30 * M_PI / 180.0) * map->scale.scale_factor - 
		z * map->scale.z_scale;
	return (p);
}

t_p	project(int x, int y, int z, t_map *map)
{
	t_p	p;

	p = iso_projection(map, x, y, z);
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
