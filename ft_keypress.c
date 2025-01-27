/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keypress.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouass <ahouass@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:11:09 by ahouass           #+#    #+#             */
/*   Updated: 2025/01/27 17:10:57 by ahouass          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	handle_projection(int keycode, t_map *map)
{
	if (keycode == 35)
		map->flag = 0;
	if (keycode == 34)
		map->flag = 1;
}

void	handle_rotation(int keycode, t_map *map)
{
	if (keycode == 13)
		map->rotation_x -= 3;
	if (keycode == 1)
		map->rotation_x += 3;
	if (keycode == 0)
		map->rotation_y -= 3;
	if (keycode == 2)
		map->rotation_y += 3;
	if (keycode == 12)
		map->rotation_z -= 3;
	if (keycode == 14)
		map->rotation_z += 3;
}

void	handle_zoom(int keycode, t_map *map)
{
	if (keycode == 69)
		map->zoom += 1;
	if (keycode == 78)
		map->zoom -= 1;
	if (map->zoom < 1)
		map->zoom = 1;
}

void	handle_moves(int keycode, t_map *map)
{
	if (keycode == 123)
		map->x_offset -= 10;
	if (keycode == 124)
		map->x_offset += 10;
	if (keycode == 125)
		map->y_offset += 10;
	if (keycode == 126)
		map->y_offset -= 10;
}

int	handle_keypress(int keycode, t_map *map)
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
