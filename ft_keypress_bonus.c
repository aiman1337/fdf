/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keypress_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouass <ahouass@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:11:09 by ahouass           #+#    #+#             */
/*   Updated: 2025/02/17 16:31:59 by ahouass          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	handle_projection(int keycode, t_map *map)
{
	if (keycode == KEY_P)
		map->flag = 0;
	if (keycode == KEY_I)
		map->flag = 1;
}

void	handle_rotation(int keycode, t_map *map)
{
	if (keycode == KEY_W)
		map->rotation_x -= 3;
	if (keycode == KEY_S)
		map->rotation_x += 3;
	if (keycode == KEY_A)
		map->rotation_y -= 3;
	if (keycode == KEY_D)
		map->rotation_y += 3;
	if (keycode == KEY_Q)
		map->rotation_z -= 3;
	if (keycode == KEY_E)
		map->rotation_z += 3;
}

void	handle_zoom(int keycode, t_map *map)
{
	if (keycode == PLUS_KEY)
		map->zoom += 1;
	if (keycode == MINUS_KEY)
		map->zoom -= 1;
	if (map->zoom < 1)
		map->zoom = 1;
}

void	handle_moves(int keycode, t_map *map)
{
	if (keycode == LEFT_ARROW)
		map->x_offset -= 10;
	if (keycode == RIGHT_ARROW)
		map->x_offset += 10;
	if (keycode == UP_ARROW)
		map->y_offset += 10;
	if (keycode == DOWN_ARROW)
		map->y_offset -= 10;
}

int	handle_keypress(int keycode, t_map *map)
{
	if (keycode == ESC_KEY)
		close_window(map);
	if (keycode == R_KEY)
		map->auto_rotate = !map->auto_rotate;
	handle_projection(keycode, map);
	handle_rotation(keycode, map);
	handle_zoom(keycode, map);
	handle_moves(keycode, map);
	draw_map(map);
	return (0);
}
