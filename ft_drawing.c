/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouass <ahouass@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:39:50 by ahouass           #+#    #+#             */
/*   Updated: 2025/01/24 13:40:26 by ahouass          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    draw_line_to_image(char *data, t_p f, t_p s, int color, int size_line, int bpp)
{
    int dx = abs(s.x - f.x);
    int dy = abs(s.y - f.y);
    int sx = f.x < s.x ? 1 : -1;
    int sy = f.y < s.y ? 1 : -1;
    int err = dx - dy;

    while (1) {
        put_pixel_to_image(data, f.x, f.y, color, size_line, bpp);
        if (f.x == s.x && f.y == s.y)
            break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            f.x += sx;
        }
        if (e2 < dx) {
            err += dx;
            f.y += sy;
        }
    }
}

t_p	iso_projection(t_map *map, int x, int y, int z)
{
	t_p	p;
	// Isometric projection
    double rad_x = map->rotation_x * M_PI / 180.0;
    double rad_y = map->rotation_y * M_PI / 180.0;
    double rad_z = map->rotation_z * M_PI / 180.0;

    // Apply rotation around X-axis
    double y1 = y * cos(rad_x) - z * sin(rad_x);
    double z1 = y * sin(rad_x) + z * cos(rad_x);

    // Apply rotation around Y-axis
    double x2 = x * cos(rad_y) + z1 * sin(rad_y);
    double z2 = -x * sin(rad_y) + z1 * cos(rad_y);

    // Apply rotation around Z-axis
    double x3 = x2 * cos(rad_z) - y1 * sin(rad_z);
    double y3 = x2 * sin(rad_z) + y1 * cos(rad_z);

    // Isometric projection
    p.x = (x3 - y3) * cos(30 * M_PI / 180.0) * map->zoom + map->x_offset;
    p.y = (x3 + y3) * sin(30 * M_PI / 180.0) * map->zoom - z2 * 2 + map->y_offset;

	return p;
}

t_p project(int x, int y, int z, t_map *map)
{
    t_p p;

    if (map->flag == 1)
        p = iso_projection(map, x, y, z);
    else 
    {
        p.x = x * map->zoom + map->x_offset;
        p.y = y * map->zoom + map->y_offset;
    }
    p.x += WINDOW_WIDTH / 2;
    p.y += WINDOW_HEIGHT / 2;

    return p;
}

void    draw_adjacent_lines(t_map *map, t_p p1, int x, int y)
{
    t_p p2;

    if (x + 1 < map->width)
    {
        p2 = project(x + 1, y, map->point[y][x + 1].height, map);
        draw_line_to_image(map->data, p1, p2, map->point[y][x].color, map->size_line, map->bpp);
    }
    if (y + 1 < map->height)
    {
        p2 = project(x, y + 1, map->point[y + 1][x].height, map);
        draw_line_to_image(map->data, p1, p2, map->point[y][x].color, map->size_line, map->bpp);
    }
}

void    draw_map(t_map *map)
{
    t_p p1;
    int x;
    int y;
    
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
