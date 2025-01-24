/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouass <ahouass@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:50:24 by ahouass           #+#    #+#             */
/*   Updated: 2025/01/24 13:53:49 by ahouass          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		get_map_height(char *filename)
{
	int		height;
	char	*line;
	int		fd;

	height = 0;
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	while(line)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (height);
}

int		get_map_width(char *filename)
{
	int		width;
	char	*line;
	int		fd;

	width = 0;
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	width = ft_count_words(line, ' ');
	free(line);
	close(fd);
	return (width);
}

int	close_window(void *param)
{
    (void)param;
    exit(0);
}

void	put_pixel_to_image(char *data, int x, int y, int color, int size_line, int bpp)
{
    if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT) {
        int offset = (y * size_line) + (x * (bpp / 8));
        *(int *)(data + offset) = color;
    }
}

int main(int argc, char **argv)
{
    
    t_map *fdf_map;

    fdf_map = malloc(sizeof(t_map));
    if (!fdf_map)
        return 0;
    if (argc != 2 || strlen(argv[1]) <= 4 || strcmp(argv[1] + strlen(argv[1]) - 4, ".fdf") != 0)
        return 0;
    fdf_map->height = get_map_height(argv[1]);
    fdf_map->width = get_map_width(argv[1]);
    fdf_map->zoom = 10;
    fdf_map->x_offset = 0;
    fdf_map->y_offset = 0;
    fdf_map->rotation_x = 1;
    fdf_map->rotation_y = 1;
    fdf_map->rotation_z = 1;
    fdf_map->flag = 1;
    ft_fill_matrix(fdf_map, argv[1]);

    fdf_map->mlx = mlx_init();
    fdf_map->mlx_win = mlx_new_window(fdf_map->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FDF");
    fdf_map->mlx_img = mlx_new_image(fdf_map->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    fdf_map->data = mlx_get_data_addr(fdf_map->mlx_img, &fdf_map->bpp, &fdf_map->size_line, &fdf_map->endian);

    draw_map(fdf_map);

    mlx_put_image_to_window(fdf_map->mlx, fdf_map->mlx_win, fdf_map->mlx_img, 0, 0);
    
    mlx_hook(fdf_map->mlx_win, 17, 0, close_window, NULL);
    mlx_key_hook(fdf_map->mlx_win, handle_keypress, fdf_map);
    mlx_loop(fdf_map->mlx);
    
    return 0;

}
