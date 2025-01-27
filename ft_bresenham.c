/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bresenham.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouass <ahouass@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:06:08 by ahouass           #+#    #+#             */
/*   Updated: 2025/01/27 20:12:45 by ahouass          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_bresenham	init_bresenham(t_p f, t_p s)
{
	t_bresenham	b;

	b.dx = abs(s.x - f.x);
	b.dy = abs(s.y - f.y);
	if (f.x < s.x)
		b.sx = 1;
	else
		b.sx = -1;
	if (f.y < s.y)
		b.sy = 1;
	else
		b.sy = -1;
	b.err = b.dx - b.dy;
	return (b);
}

int	bresenham_step(t_p *f, t_p s, t_bresenham *b)
{
	int	e2;

	if (f->x == s.x && f->y == s.y)
		return (0);
	e2 = 2 * b->err;
	if (e2 > -b->dy)
	{
		b->err -= b->dy;
		f->x += b->sx;
	}
	if (e2 < b->dx)
	{
		b->err += b->dx;
		f->y += b->sy;
	}
	return (1);
}
