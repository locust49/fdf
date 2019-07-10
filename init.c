/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 03:18:15 by slyazid           #+#    #+#             */
/*   Updated: 2019/07/10 00:05:44 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	write_in_window(void *connect, void *window)
{
	mlx_string_put(connect, window, 0, 0, 0xffffff, "Hello World\n");
	mlx_pixel_put(connect, window, 130, 0, 0x00009036);
}

void	prepare_image(void *connect, t_coord size)
{
	t_image	*img;

	img = (t_image*)malloc(sizeof(t_image));
	img->image = mlx_new_image(connect, size.x, size.y);
	img->data = (int *)malloc(sizeof(int) * size.x);
	img->data = (int *)mlx_get_data_addr(img->image, &(img->depth),
				&(img->sizeline), &(img->endian));
}

void	open_window(t_connection *workspace, char *name)
{
	workspace->connect = mlx_init();
	workspace->window = mlx_new_window(workspace->connect,
						workspace->size_win.x, workspace->size_win.y, name);
}

int		key_press(int keycode, t_settings *sets)
{
	printf("[%d]\n", keycode);
	if (keycode == 53)
	{
		sets->in->map ? freedomap(sets->in->map, sets->in->size) : 0;
		exit (0);
	}
	if (keycode == 35)
	{
		if (sets->project == 1)
			sets->project = 2;
		else //sets->project == 2 ? 
			sets->project = 1;
		mlx_clear_window(sets->workspace.connect, sets->workspace.window);
		draw_map(sets->workspace, *(sets->in), sets->data, sets->project);
	}
	return (1);
}

int		main(int argc, char **argv)
{
	// t_params		data;
	// t_connection	workspace;
	// t_input			*in;
	t_settings		sets;

	if ((sets.in = parse_input(argc, argv)))
	{
		sets.data.gutter = 50;
		sets.data.offset.y = 1080 / 2;
		sets.workspace.size_win.x = 1920;
		sets.workspace.size_win.y = 1080;
		sets.project = 2;
		printf("%d\n", sets.in->size.y);
		if (sets.in->size.x >= 50)
		{
			sets.data.gutter /= (sets.in->size.x/ sets.data.gutter);
			sets.workspace.size_win.x *= 2;
			sets.workspace.size_win.y *= 2;
			sets.data.offset.y *= 2;
		}
		// {
		// 	if (data.gutter / 2 > 1)
		// 		data.gutter /= 2;
		// 	// if (data.offset.y / 2 > 0)
		// 	// 	data.offset.y /= 2;
		// }
		printf("win.y = %d * %d = win.x\n", sets.workspace.size_win.y, sets.workspace.size_win.x);
		printf("off.y = %d * %d = off.x\n", sets.data.offset.y, sets.data.offset.x);
		sets.data.offset.x = sets.workspace.size_win.x / 3 / sets.in->size.x;
		open_window(&sets.workspace, argv[1]);
		mlx_key_hook(sets.workspace.window, &key_press, &sets);
		draw_map(sets.workspace, *sets.in, sets.data, sets.project);
		mlx_loop(sets.workspace.connect);
		freedomap(sets.in->map, sets.in->size);
	}
	return (0);
}
