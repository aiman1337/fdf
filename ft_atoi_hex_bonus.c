/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_hex_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouass <ahouass@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:47:54 by ahouass           #+#    #+#             */
/*   Updated: 2025/02/17 16:31:45 by ahouass          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

unsigned int	ft_atoi_hex(const char *str)
{
	unsigned int	res;

	res = 0;
	while (*str)
	{
		if (ft_isdigit(*str))
			res = res * 16 + (*str - '0');
		else if (*str >= 'a' && *str <= 'f')
			res = res * 16 + (*str - 'a' + 10);
		else if (*str >= 'A' && *str <= 'F')
			res = res * 16 + (*str - 'A' + 10);
		else
			break ;
		str++;
	}
	return (res);
}
