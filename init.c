/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouyizme <mouyizme@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 03:18:15 by slyazid           #+#    #+#             */
/*   Updated: 2019/07/05 16:58:19 by mouyizme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	write_in_window(void *connect, void *window)
{
	mlx_string_put(connect, window, 0, 0, 0xffffff, "Hello World\n");
	mlx_pixel_put(connect, window, 130, 0, 0x00009036);
}

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
			// printf("%2d ", (map[r][c]).color);
			printf("%3d ", (map[r][c]).height);
			c += 1;
		}
		printf("\n");
		r += 1;
	}
}

// void	write_image(void *connect, void *window)
// {
// 	void			*image;
// 	int			*img_data;
// 	int				depth;
// 	int				szl;
// 	int				endi;
// 	int 			pixel;
// 	unsigned int	rgba;

// 	pixel = -1;
// 	image = mlx_new_image(connect, 1949, 2000);
// 	img_data = (int *)mlx_get_data_addr(image, &depth, &szl, &endi);
// 	mlx_string_put(connect, window, 1001, 250, 0xffffff, "NO HOMO\n");
// 	while (++pixel < szl * 240)
// 	{
// 		if (pixel <= szl * 40)
// 			img_data[pixel] = 0xE70000;
// 		else if (pixel <= szl * 80)
// 			img_data[pixel] = 0xFF8C00;
// 		else if (pixel <= szl * 120)
// 			img_data[pixel] = 0xFFEF00;
// 		else if (pixel <= szl * 160)
// 			img_data[pixel] = 0x00811F;
// 		else if (pixel <= szl * 200)
// 			img_data[pixel] = 0x0044FF;
// 		else if (pixel <= szl * 240)
// 			img_data[pixel] = 0x760089;
// 	}
// 	printf("bpp = %d, szl = %d, endi = %d\n", depth, szl, endi);
// 	rgba = mlx_get_color_value(connect, 0x009036);
// 	// mlx_pixel_put(connect, window, 0, 5, rgba);
// 	mlx_put_image_to_window(connect, window, image, 0, 500);
// }

void	prepare_image(void *connect, int width, int height)
{
	t_image	*img;

	img = (t_image*)malloc(sizeof(t_image));
	img->image = mlx_new_image(connect, width, height);
	img->data = (int *)malloc(sizeof(int) * width);
	img->data = (int *)mlx_get_data_addr(img->image, &(img->depth),
				&(img->sizeline), &(img->endian));
}

void	open_window(t_connection *workspace)
{
	workspace->connect = mlx_init();
	workspace->window = mlx_new_window(workspace->connect, 1949, 2003, "Bazaglo");
}

int		main(int argc, char **argv)
{
	t_connection	workspace;
	t_input			*in;
	// t_coord			mapsize;

	// if (parse_input(&map, &mapsize, argc, argv))
	if ((in = parse_input(argc, argv)))
	{
		// printf("%p\n", map);
		open_window(&workspace);
		workspace.size_win.x = 500;
		workspace.size_win.y = 500;
		prepare_image(workspace.connect, workspace.size_win.x, workspace.size_win.y);
		draw_map(workspace, *in);
		// print_map(in->map, 8, 9);
		freedomap(in->map, in->size);
		mlx_loop(workspace.connect);
	}
	return (1);
}
