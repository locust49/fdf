/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 03:18:15 by slyazid           #+#    #+#             */
/*   Updated: 2019/07/12 20:06:22 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		main(int argc, char **argv)
{
	t_settings		sets;
	int				ac;
	t_mmap			*allmap;

	ac = 0;
	allmap = parse_input(argc, argv);
	if (allmap)
	{
		while (++ac < argc)
		{
			sets.list = allmap;
			initialize_settings(&sets);
			open_window(&sets.workspace, argv[0]);
			mlx_hook(sets.workspace.window, 2, 0, &key_press, &sets);
			draw_map(&sets);
			allmap = allmap->next;
			mlx_loop(sets.workspace.connect);
		}
	}
	return (0);
}
