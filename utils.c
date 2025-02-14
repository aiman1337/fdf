/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouass <ahouass@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:00:27 by ahouass           #+#    #+#             */
/*   Updated: 2025/02/06 13:30:07 by ahouass          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel(t_map *map, int x, int y, unsigned int color)
{
	int	offset;

	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		offset = (y * map->size_line) + (x * (map->bpp / 8));
		*(int *)(map->data + offset) = color;
	}
}

int	close_window(t_map *fdf)
{
	mlx_destroy_image(fdf->mlx, fdf->mlx_img);
	mlx_destroy_window(fdf->mlx, fdf->mlx_win);
	ft_free_map(fdf->point, fdf->height);
	exit(0);
}

void	ft_free_map(t_point **point, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(point[i]);
		i++;
	}
	free(point);
}
