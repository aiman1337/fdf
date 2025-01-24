/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keypress.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouass <ahouass@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:11:09 by ahouass           #+#    #+#             */
/*   Updated: 2025/01/24 16:22:39 by ahouass          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    handle_projection(int keycode, t_map *map)
{
    // Change the projection
    if (keycode == 35)
        map->flag = 0;
    if (keycode == 34)
        map->flag = 1;
}

void    handle_rotation(int keycode, t_map *map)
{
    // Rotation keys
    if (keycode == 13) // 'w' key
        map->rotation_x -= 3;
    if (keycode == 1) // 's' key
        map->rotation_x += 3;
    if (keycode == 0) // 'a' key
        map->rotation_y -= 3;
    if (keycode == 2) // 'd' key
        map->rotation_y += 3;
    if (keycode == 12) // 'q' key
        map->rotation_z -= 3;
    if (keycode == 14) // 'e' key
        map->rotation_z += 3;
}

void    handle_zoom(int keycode, t_map *map)
{
    if (keycode == 69) // '+' key (Zoom in)
        map->zoom += 1;
    if (keycode == 78) // '-' key (Zoom out)
        map->zoom -= 1;
    if (map->zoom < 1) // Prevent zoom from becoming negative
        map->zoom = 1;
}

void    handle_moves(int keycode, t_map *map)
{
    if (keycode == 123) // Left arrow key
        map->x_offset -= 10;
    if (keycode == 124) // Right arrow key
        map->x_offset += 10;
    if (keycode == 125) // Down arrow key
        map->y_offset += 10;
    if (keycode == 126) // Up arrow key
        map->y_offset -= 10;
}

int handle_keypress(int keycode, t_map *map)
{
    if (keycode == 53)
    {
        system("leaks fdf");
        exit(0);
    }
    handle_projection(keycode, map);
    handle_rotation(keycode, map);
    handle_zoom(keycode, map);
    handle_moves(keycode, map);
    draw_map(map);
    return (0);
}