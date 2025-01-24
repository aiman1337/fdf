/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouass <ahouass@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:52:40 by ahouass           #+#    #+#             */
/*   Updated: 2025/01/24 20:06:15 by ahouass          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void allocate_points(t_map *fdf)
{
	int i;

	fdf->point = malloc(sizeof(t_point *) * fdf->height);
	if (!fdf->point)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < fdf->height)
	{
		fdf->point[i] = malloc(sizeof(t_point) * fdf->width);
		i++;
	}
}

static void parse_value(t_point *point, char *value)
{
	char	*coordinate;
	char	*color;

	if (ft_strchr(value, ','))
    {
        coordinate = ft_substr(value, 0, ft_strlen(value) - ft_strlen(ft_strchr(value, ',')));
        color = ft_substr(value, ft_strlen(coordinate) + 1, ft_strlen(value) - ft_strlen(coordinate) - 1);
        point->height = ft_atoi(coordinate);
        point->color = ft_atoi_hex(color + 2);
        free(coordinate);
        free(color);
    }
    else
    {
        point->height = ft_atoi(value);
        point->color = ft_atoi_hex("FFFFFF");
    }
}

static void parse_line(t_map *fdf, char *line, int row)
{
    char **values;
    int col;

    values = ft_split(line, ' ');
    col = 0;
    while (values[col])
    {
        parse_value(&fdf->point[row][col], values[col]);
        free(values[col]);
        col++;
    }
    free(values);
}

void    ft_fill_matrix(t_map *fdf, char *filename)
{
    char *line;
    int fd;
    int row;

    allocate_points(fdf);
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return;
    row = 0;
    line = get_next_line(fd);
    while (line)
    {
        parse_line(fdf, line, row);
        free(line);
        row++;
        line = get_next_line(fd);
    }
    close(fd);
}
