/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bresenham.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouass <ahouass@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:06:08 by ahouass           #+#    #+#             */
/*   Updated: 2025/02/17 16:12:47 by ahouass          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_swap(t_bresenham *b)
{
	int	tmp;

	tmp = b->dx;
	b->dx = b->dy;
	b->dy = tmp;
}

t_bresenham	init_bresenham(t_p f, t_p s)
{
	t_bresenham	b;

	b.dx = abs(s.x - f.x);
	b.dy = abs(s.y - f.y);
	b.swap_axes = 0;
	if (f.x < s.x)
		b.sx = 1;
	else
		b.sx = -1;
	if (f.y < s.y)
		b.sy = 1;
	else
		b.sy = -1;
	return (b);
}

int	bresenham_step(t_p *f, t_bresenham *b)
{
	if (b->err >= 0)
	{
		if (b->swap_axes)
			f->x += b->sx;
		else
			f->y += b->sy;
		b->err -= 2 * b->dx;
	}
	if (b->swap_axes)
		f->y += b->sy;
	else
		f->x += b->sx;
	b->err += 2 * b->dy;
	return (1);
}
