/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 20:59:46 by slyazid           #+#    #+#             */
/*   Updated: 2019/06/30 00:24:25 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "fdf.h"
#include <stdio.h>
#include <math.h>

typedef struct s_line
{
    int x0;
    int y0;
    int x1;
    int y1;
} t_line;

typedef struct s_plot
{
    int dx;
    int sx;
    int dy;
    int sy;
    int err;
    int e2;
} t_plot;

void    plot_line(t_line line, void *mlx_ptr, void *win_ptr)
{
    t_plot    plot;

    plot.dx = abs(line.x1 - line.x0);
    plot.sx = line.x0 < line.x1 ? 1 : -1;
    plot.dy = -abs(line.y1 - line.y0);
    plot.sy = line.y0 < line.y1 ? 1 : -1;
    plot.err = plot.dx + plot.dy;
    while (1)
    {
        mlx_pixel_put(mlx_ptr, win_ptr, line.x0, line.y0, 0xFFFFFF);
        if (line.x0 == line.x1 && line.y0 == line.y1)
            break ;
        plot.e2 = 2 * plot.err;
        if (plot.e2 >= plot.dy)
        {
            plot.err += plot.dy;
            line.x0 += plot.sx;
        }
        if (plot.e2 <= plot.dx)
        {
            plot.err += plot.dx;
            line.y0 += plot.sy;
        }
    }
}

int *isometric(int x, int y, int z) //care leaks\\ .. 
{
  int *points;

  points = malloc(sizeof(int) * 2);
  points[0] = x * cos(-M_PI / 6) - y * sin(-M_PI / 3);
  points[1] = - y * cos(-M_PI / 3) - x * sin(-M_PI / 6) - z;
  return (points);
}

// void plot_line(t_line ln, void *mlx_ptr, void *win_ptr)
// {
//   int dx;
//   int sx;
//   int dy;
//   int sy;
//   int err;
//   int e2;

//   dx = abs(ln.x1 - ln.x0);
//   sx = ln.x0 < ln.x1 ? 1 : -1;
//   dy = -abs(ln.y1 - ln.y0);
//   sy = ln.y0 < ln.y1 ? 1 : -1;
//   err = dx + dy;

//   while (1)
//   {
//     mlx_pixel_put(mlx_ptr, win_ptr, ln.x0, ln.y0, 0xFFFFFF);
//     if (ln.x0 == ln.x1 && ln.y0 == ln.y1)
//       break;
//     e2 = 2 * err;
//     if (e2 >= dy)
//     {
//       err += dy;
//       ln.x0 += sx;
//     }
//     if (e2 <= dx)
//     {
//       err += dx;
//       ln.y0 += sy;
//     }
//   }
// }

void	print_map(t_map **map, int rows, int cols)
{
	int r;
	int	c;

	r = 0;
	while (r < rows)
	{
		c = 0;
		while (c < cols)
		{
			printf("%2d ", (map[r][c]).color);
		//	printf("%2x ", (map[r][c]).height);
			c += 1;
		}
		printf("\n");
		r += 1;
	}
}

void	print_error(void)
{
	char *error;

	error = ft_strdup("Error");
	ft_putendl(error);
	free(error);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_map	**map;
	t_coord	init;
	int		fd;
	char	*line;
	int		error;
	void	*mlx_ptr;
	void	*win_ptr;
	t_coord	rc;


	init.row = 0;
	error = 0;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		(fd < 0) ? print_error() : 0;	
		while (get_next_line(fd, &line))
		{
			init.row += 1;
			free(line);
		}
		close(fd);
		map = (t_map **)malloc(init.row * sizeof(t_map*));
		if (get_map(&error, argv[1], map, &init) == false
			|| error == -1 || !init.row)
			print_error();
		else
		{
			rc.row = 0;
			mlx_ptr = mlx_init();
			win_ptr = mlx_new_window(mlx_ptr, 1920, 1080, "Bazaglo");
			while (rc.row < init.row - 1)
			{
				rc.col = 0;
				while (rc.col < init.col - 1)
				{
					// t_line start;
					// t_line end;
					t_line ln;

					ln.x0 = 400 + isometric(rc.row * 50, rc.col * 50, map[rc.row][rc.col].height * 15)[0];
					ln.y0 = 400 + isometric(rc.row * 50, rc.col * 50, map[rc.row][rc.col].height * 15)[1];
					ln.x1 = 400 + isometric((rc.row + 1) * 50, rc.col * 50, map[rc.row + 1][rc.col].height * 15)[0];
					ln.y1 = 400 + isometric((rc.row + 1) * 50, rc.col * 50, map[rc.row + 1][rc.col].height * 15)[1];
					plot_line(ln, mlx_ptr, win_ptr);

					ln.x1 = 400 + isometric(rc.row * 50, (rc.col + 1) * 50, map[rc.row][rc.col + 1].height * 15)[0];
					ln.y1 = 400 + isometric(rc.row * 50, (rc.col + 1) * 50, map[rc.row][rc.col + 1].height * 15)[1];
					plot_line(ln, mlx_ptr, win_ptr);
					if (rc.row + 2 == init.row)
					{
						ln.x0 = 400 + isometric((rc.row + 1) * 50, (rc.col + 1) * 50, map[rc.row + 1][rc.col].height * 15)[0];
						ln.y0 = 400 + isometric((rc.row + 1) * 50, (rc.col + 1) * 50, map[rc.row + 1][rc.col].height * 15)[1];
						ln.x1 = 400 + isometric((rc.row + 1) * 50, (rc.col + 1) * 50, map[rc.row][rc.col + 1].height * 15)[0];
						ln.y1 = 400 + isometric((rc.row + 1) * 50, (rc.col + 1) * 50, map[rc.row][rc.col + 1].height * 15)[1];
						plot_line(ln, mlx_ptr, win_ptr);
					}

					/*start.x = isometric(rc.row * 50, rc.col * 100, map[rc.row][rc.col].height)[0];
					start.y = isometric(rc.row * 50, rc.col * 100, map[rc.row][rc.col].height)[1];
					end.x = isometric((rc.row + 1) * 50, rc.col * 100, map[rc.row][rc.col].height)[0];
					end.y = isometric((rc.row + 1) * 50, rc.col * 100, map[rc.row][rc.col].height)[1];
					plot_line(mlx_ptr, win_ptr, start.x, start.y, end.x, end.y);
					end.x = isometric(rc.row * 50, (rc.col + 1) * 100, map[rc.row][rc.col].height)[0];
					end.y = isometric(rc.row * 50, (rc.col + 1) * 100, map[rc.row][rc.col].height)[1];
					plot_line(mlx_ptr, win_ptr, start.x, start.y, end.x, end.y);*/
					// if (rc.row == 3 && rc.col == 3)
					// 	plot_line(mlx_ptr, win_ptr, 200 + (rc.row - rc.col * 2) * 20, 100 + (rc.row + rc.col - 5) * 20, 200 + (rc.row + 1 - rc.col * 2) * 20, 100 + (rc.row + rc.col + 1) * 20);
					// else if (rc.row + 1 == 3 && rc.col == 3)
					// 	plot_line(mlx_ptr, win_ptr, 200 + (rc.row - rc.col * 2) * 20, 100 + (rc.row + rc.col) * 20, 200 + (rc.row + 1 - rc.col * 2) * 20, 100 + (rc.row + 1 + rc.col - 5) * 20);
					// else
					// plot_line(mlx_ptr, win_ptr, 500 + (rc.row - rc.col * 2) * 20, 100 + (rc.row + rc.col) * 20, 500 + (rc.row + 1 - rc.col * 2) * 20, 100 + (rc.row + rc.col + 1) * 20);
					// plot_line(mlx_ptr, win_ptr, 500 + (rc.row - rc.col * 2) * 20, 100 + (rc.row + rc.col) * 20, 500 + (rc.row + 2 - rc.col * 2) * 20, 100 + (rc.row + rc.col - 1) * 20);
					// printf("x: %d -- y: %d -- z: %d -- color: %d\n", rc.row, rc.col, map[rc.row][rc.col].height, map[rc.row][rc.col].color);
					rc.col += 1;
				}
				rc.row += 1;
			}
			mlx_loop(mlx_ptr);
		}
	}
	return (0);
}
