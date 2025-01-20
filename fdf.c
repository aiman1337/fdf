/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouass <ahouass@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:50:24 by ahouass           #+#    #+#             */
/*   Updated: 2025/01/20 22:15:30 by ahouass          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#define SCALE 7
#define ISO_ANGLE 30 // Isometric angle
#define Z_SCALE 0.9 // Adjust this value to control the height effect
#define WINDOW_WIDTH 2000
#define WINDOW_HEIGHT 1600

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

void		ft_fill_matrix(t_map *fdf, char *filename)
{
	int		i;
	int		j;
	int		fd;
	char	*line;
	char	**values;

	char	*coordinate;
	char	*color;

	fdf->point = malloc(sizeof(t_point *) * fdf->height);
	if(!fdf->point)
		return ;
	i = 0;
	while(i < fdf->height)
	{
		fdf->point[i] = malloc(sizeof(t_point) * fdf->width);
		i++;
	}
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	i = 0;
	// printf("height-%d- : width-%d-\n", fdf->height, fdf->width);
	while(line)
	{
		j = 0;
		values = ft_split(line, ' ');
		while(values[j])
		{
			// printf("-%s-\n", values[j]);
			if(ft_strchr(values[j], ','))
			{
				coordinate = ft_substr(values[j], 0, ft_strlen(values[j]) - ft_strlen(ft_strchr(values[j], ',')));
				color = ft_substr(values[j], ft_strlen(coordinate) + 1, ft_strlen(values[j]) - ft_strlen(coordinate) - 1);
				fdf->point[i][j].height = ft_atoi(coordinate);
				fdf->point[i][j].color = ft_atoi_hex(color+2);
				// printf("-%s-\n", color+2);
			}
			else
			{
				fdf->point[i][j].height = ft_atoi(values[j]);
				fdf->point[i][j].color = ft_atoi_hex("FFFFFF");
			}
			j++;
		}
		i++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}



// Isometric projection
void apply_isometric_projection(int x, int y, int z, int *iso_x, int *iso_y)
{
    *iso_x = (x - y) * cos(ISO_ANGLE * M_PI / 180.0);
    *iso_y = (x + y) * sin(ISO_ANGLE * M_PI / 180.0) - z;
}

int close_window(void *param)
{
    (void)param; // Unused parameter
    exit(0);     // Exit the program
}

// void draw_line(void *mlx, void *mlx_win, int x0, int y0, int x1, int y1, int color)
// {
//     int dx = abs(x1 - x0);
//     int dy = abs(y1 - y0);
//     int sx = (x0 < x1) ? 1 : -1;
//     int sy = (y0 < y1) ? 1 : -1;
//     int err = dx - dy;

//     while (1)
//     {
//         mlx_pixel_put(mlx, mlx_win, x0, y0, color);
//         if (x0 == x1 && y0 == y1)
//             break;
//         int e2 = 2 * err;
//         if (e2 > -dy)
//         {
//             err -= dy;
//             x0 += sx;
//         }
//         if (e2 < dx)
//         {
//             err += dx;
//             y0 += sy;
//         }
//     }
// }

typedef struct s_p {
    int x;
    int y;
} t_p;

void put_pixel(void *mlx, void *win, int x, int y, int color)
{
    if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
    {
        mlx_pixel_put(mlx, win, x, y, color);
    }
}

void draw_line(void *mlx, void *win, t_p f, t_p s, int color)
{
    int dx = abs(s.x - f.x);
    int dy = abs(s.y - f.y);
    int sx = f.x < s.x ? 1 : -1;
    int sy = f.y < s.y ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        put_pixel(mlx, win, f.x, f.y, color);
        if (f.x == s.x && f.y == s.y)
            break;
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            f.x += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            f.y += sy;
        }
    }
}

t_p project(int x, int y, int z, int scale)
{
    t_p	p;

    // Apply isometric projection
    p.x = (x - y) * cos(0.523599) * scale; // 0.523599 radians = 30 degrees
    p.y = (x + y) * sin(0.523599) * scale - z * scale;

    // Center the map in the window
    p.x += WINDOW_WIDTH / 2;
    p.y += WINDOW_HEIGHT / 2 - 500;

    return p;
}

int main(int argc, char **argv)
{
    // int		fd;
    void	*mlx;
    void	*mlx_win;
	t_map	*fdf_map;
	// int iso_x, iso_y;
	
	fdf_map = malloc(sizeof(t_map));
	if (!fdf_map)
	{
    	perror("Failed to allocate memory");
    	return 1;
	}
    if (argc != 2 || strlen(argv[1]) <= 4 || strcmp(argv[1] + strlen(argv[1]) - 4, ".fdf") != 0)
        return 0;
	fdf_map->height = get_map_height(argv[1]);
	fdf_map->width = get_map_width(argv[1]);
	ft_fill_matrix(fdf_map, argv[1]);

	mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FDF");

	// int color;
	// Function to draw pixels 2D
	// int x, y;
	// for (y = 0; y < fdf_map->height; y++) {
    // for (x = 0; x < fdf_map->width; x++) {
    //     // Scale the coordinates without centering
    //     int pixel_x = x * 20; // Scale x by 20
    //     int pixel_y = y * 20; // Scale y by 20

    //     // Plot the pixel
    //     int color = fdf_map->point[y][x].color;
    //     mlx_pixel_put(mlx, mlx_win, pixel_x + 300, pixel_y + 300, color);
    // 	}
	// }
	
	// int color;
	// int x, y , z, iso_x, iso_y;
	// for (y = 0; y < fdf_map->height; y++) {
    //     for (x = 0; x < fdf_map->width; x++)
	// 	{
	// 		z = fdf_map->point[y][x].height;
    //         apply_isometric_projection(x, y, z, &iso_x, &iso_y);

    //         // Scale and shift to fit within the window
    //         iso_x = iso_x * SCALE + 300; // Center the map horizontally
    //         iso_y = iso_y * SCALE + 300; // Center the map vertically

    //         // Plot the pixel
	// 		color = fdf_map->point[y][x].color;
    //         mlx_pixel_put(mlx, mlx_win, iso_x, iso_y, color);
	// 	}
    // }

    // Draw the map
	// int color;
    // for (int y = 0; y < fdf_map->height; y++) {
    //     for (int x = 0; x < fdf_map->width; x++) {
    //         int iso_x1, iso_y1, iso_x2, iso_y2;

    //         // Current point
    //         apply_isometric_projection(x, y, fdf_map->point[y][x].height, &iso_x1, &iso_y1);
    //         iso_x1 = iso_x1 * SCALE + 300;
    //         iso_y1 = iso_y1 * SCALE + 300;

    //         // Right neighbor
    //         if (x + 1 < fdf_map->width) {
    //             apply_isometric_projection(x + 1, y, fdf_map->point[y][x + 1].height, &iso_x2, &iso_y2);
    //             iso_x2 = iso_x2 * SCALE + 300;
    //             iso_y2 = iso_y2 * SCALE + 300;
    //             draw_line(mlx, mlx_win, iso_x1, iso_y1, iso_x2, iso_y2, fdf_map->point[y][x].color);
    //         }

    //         // Bottom neighbor
    //         if (y + 1 < fdf_map->height) {
    //             apply_isometric_projection(x, y + 1, fdf_map->point[y + 1][x].height, &iso_x2, &iso_y2);
    //             iso_x2 = iso_x2 * SCALE + 300;
    //             iso_y2 = iso_y2 * SCALE + 300;
    //             draw_line(mlx, mlx_win, iso_x1, iso_y1, iso_x2, iso_y2, fdf_map->point[y][x].color);
    //         }
    //     }
    // }

	int x, y;
	// Draw the map
    for (y = 0; y < fdf_map->height; y++) {
        for (x = 0; x < fdf_map->width; x++) {
            // Project the current point
            t_p p1 = project(x, y, fdf_map->point[y][x].height, SCALE);

            // Draw line to the right neighbor
            if (x + 1 < fdf_map->width) {
                t_p p2 = project(x + 1, y, fdf_map->point[y][x + 1].height, SCALE);
                draw_line(mlx, mlx_win, p1, p2, fdf_map->point[y][x].color);
            }

            // Draw line to the bottom neighbor
            if (y + 1 < fdf_map->height) {
                t_p p2 = project(x, y + 1, fdf_map->point[y + 1][x].height, SCALE);
                draw_line(mlx, mlx_win, p1, p2, fdf_map->point[y][x].color);
            }
        }
    }
	
    // Handle window close event
    mlx_hook(mlx_win, 17, 0, close_window, NULL);

    mlx_loop(mlx);
    return 0;
}
