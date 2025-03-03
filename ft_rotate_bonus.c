/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouass <ahouass@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:34:09 by ahouass           #+#    #+#             */
/*   Updated: 2025/02/17 16:53:38 by ahouass          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

double	degrees_to_radians(double degrees)
{
	return (degrees * M_PI / 180.0);
}

void	rotate_x(double y, double z, double rad_x, t_rotation *rot)
{
	rot->y = y * cos(rad_x) - z * sin(rad_x);
	rot->z = y * sin(rad_x) + z * cos(rad_x);
}

void	rotate_y(double x, double z, double rad_y, t_rotation *rot)
{
	rot->z = z * cos(rad_y) - x * sin(rad_y);
	rot->x = z * sin(rad_y) + x * cos(rad_y);
}

void	rotate_z(double x, double y, double rad_z, t_rotation *rot)
{
	rot->x = x * cos(rad_z) - y * sin(rad_z);
	rot->y = x * sin(rad_z) + y * cos(rad_z);
}

int	ft_auto_rotate(t_map *map)
{
	if (map->auto_rotate)
	{
		map->rotation_x += 1;
		map->rotation_y += 1;
		map->rotation_z += 1;
		draw_map(map);
	}
	return (0);
}
