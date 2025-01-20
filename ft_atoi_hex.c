/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouass <ahouass@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:47:54 by ahouass           #+#    #+#             */
/*   Updated: 2025/01/20 12:16:00 by ahouass          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_find(char c, char *base)
{
	int	i;

	i = 0;
	while(base[i])
	{
		if(base[i] == c)
			return 1;
		i++;
	}
	return 0;
}

int	ft_atoi_hex(const char *str)
{
	int		sign;
	long	res;

	res = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str)
    {
        if (ft_isdigit(*str))
            res = res * 16 + (*str - '0');
        else if (*str >= 'a' && *str <= 'f')
            res = res * 16 + (*str - 'a' + 10);
        else if (*str >= 'A' && *str <= 'F')
            res = res * 16 + (*str - 'A' + 10);
        else
            break;
        str++;
    }
	return (res * sign);
}