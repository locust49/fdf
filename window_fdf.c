/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_fdf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 19:06:24 by slyazid           #+#    #+#             */
/*   Updated: 2019/07/12 20:03:49 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	open_window(t_connection *workspace, char *name)
{
	workspace->connect = mlx_init();
	workspace->window = mlx_new_window(workspace->connect,
						workspace->size_win.x, workspace->size_win.y, name);
}

void	write_key_map(void *connect, void *win)
{
	mlx_string_put(connect, win, 20, 30, 0xffff0f,
		" ____________ KEY MAP ____________");
	mlx_string_put(connect, win, 20, 55, 0xffff0f,
		"| [TAB]      : switch map        |");
	mlx_string_put(connect, win, 20, 75, 0xffff0f,
		"| [ESC]      : exit program      |");
	mlx_string_put(connect, win, 20, 95, 0xffff0f,
		"| [ARROWS]   : move map          |");
	mlx_string_put(connect, win, 20, 115, 0xffff0f,
		"| [Z]        : up scale height   |");
	mlx_string_put(connect, win, 20, 135, 0xffff0f,
		"| [X]        : down scale height |");
	mlx_string_put(connect, win, 20, 155, 0xffff0f,
		"| [P]        : change projection |");
	mlx_string_put(connect, win, 20, 175, 0xffff0f,
		"| [+]        : zoom in           |");
	mlx_string_put(connect, win, 20, 195, 0xffff0f,
		"| [-]        : zoom out          |");
	mlx_string_put(connect, win, 20, 220, 0xffff0f,
		" _______________________________");
}

void	write_in_window(void *connect, void *window)
{
	char	*msg0;
	char	*msg1;

	msg0 = ft_strdup("The END");
	msg1 = ft_strdup("Tap ESC to exit fdf");
	mlx_string_put(connect, window, (WINDOW_WIDTH / 2) -
		(ft_strlen(msg0) * 10 / 2), 700, 0x0000ff, msg0);
	mlx_string_put(connect, window, (WINDOW_WIDTH / 2) -
		(ft_strlen(msg1) * 10 / 2), 725, 0xff0000, msg1);
	free(msg0);
	free(msg1);
}

int		key_press(int keycode, t_settings *sets)
{
	if (keycode == 53)
	{
		sets->list->inputs->map ?
			freedomap(sets->list->inputs->map, sets->list->inputs->size) : 0;
		exit(0);
	}
	if (keycode == 35 && sets->project)
		(sets->project == 1) ? oblique_sets(sets) : isometric_sets(sets);
	else if (keycode == 124 || keycode == 123)
		sets->data.offset.x += keycode == 124 ? 25 : -25;
	else if (keycode == 125 || keycode == 126)
		sets->data.offset.y += keycode == 125 ? 25 : -25;
	else if (keycode == 24 || keycode == 27)
		sets->data.gutter += keycode == 24 ? 2 : -2;
	else if (keycode == 6 || keycode == 7)
		sets->data.zscale += keycode == 6 ? 1 : -1;
	if (keycode == 48)
		final_sets(sets);
	mlx_clear_window(sets->workspace.connect, sets->workspace.window);
	if (sets->project)
		draw_map(sets);
	else
		write_in_window(sets->workspace.connect, sets->workspace.window);
	return (1);
}
