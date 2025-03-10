/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouass <ahouass@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:50:24 by ahouass           #+#    #+#             */
/*   Updated: 2025/03/03 14:09:23 by ahouass          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_map_height(char *filename)
{
	int		height;
	char	*line;
	int		fd;

	height = 0;
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (height);
}

int	get_map_width(char *filename)
{
	int		width;
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	width = ft_count_words(line, ' ');
	while (line)
	{
		if (width != ft_count_words(line, ' '))
		{
			write(2, "width is not handled properly\n", 30);
			free(line);
			exit(1);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (width);
}

void	map_init(t_map *fdf_map, char *argv)
{
	fdf_map->height = get_map_height(argv);
	fdf_map->width = get_map_width(argv);
}

void	ft_mlx_init(t_map *fdf)
{
	fdf->mlx = mlx_init();
	fdf->mlx_win = mlx_new_window(fdf->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FDF");
	fdf->mlx_img = mlx_new_image(fdf->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	fdf->data = mlx_get_data_addr(fdf->mlx_img, &fdf->bpp, &fdf->size_line, 
			&fdf->endian);
}

int	main(int argc, char **argv)
{
	t_map	fdf;
	int		fd;

	if (argc != 2 || ft_strlen(argv[1]) <= 4 || 
		ft_strcmp(argv[1] + ft_strlen(argv[1]) - 4, ".fdf") != 0)
	{
		write(2, "Not valid arguments\n", 21);
		exit(1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	close(fd);
	map_init(&fdf, argv[1]);
	ft_mlx_init(&fdf);
	ft_fill_matrix(&fdf, argv[1]);
	draw_map(&fdf);
	mlx_put_image_to_window((&fdf)->mlx, (&fdf)->mlx_win, 
		(&fdf)->mlx_img, 0, 0);
	mlx_hook((&fdf)->mlx_win, 17, 0, close_window, &fdf);
	mlx_key_hook((&fdf)->mlx_win, handle_keypress, &fdf);
	mlx_loop((&fdf)->mlx);
	return (0);
}
