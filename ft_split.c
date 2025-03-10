/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouass <ahouass@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:51:48 by ahouass           #+#    #+#             */
/*   Updated: 2025/01/27 16:57:28 by ahouass          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_freeup(char **strs, int i)
{
	while (i >= 0)
	{
		free(strs[i]);
		i--;
	}
	free(strs);
}

int	ft_count_words(char const *str, char c)
{
	int	i;
	int	flag;
	int	counter;

	i = 0;
	flag = 1;
	counter = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
		{
			flag = 1;
		}
		if (str[i] != c && flag == 1)
		{
			flag = 0;
			counter++;
		}
		i++;
	}
	return (counter);
}

static char	**ft_fill(char **arr, char const *s, char c)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (i < ft_count_words(s, c))
	{
		while (s[j] == c && s[j])
			j++;
		k = j;
		while (s[j] != c && s[j])
			j++;
		arr[i] = ft_substr(s, k, j - k);
		if (!arr[i])
		{
			ft_freeup(arr, i - 1);
			return (NULL);
		}
		i++;
	}
	arr[i] = 0;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;

	if (!s)
		return (NULL);
	arr = (char **)malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	arr = ft_fill(arr, s, c);
	if (!arr)
		return (NULL);
	return (arr);
}
