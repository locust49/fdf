/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 15:44:02 by slyazid           #+#    #+#             */
/*   Updated: 2019/07/12 20:23:23 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	make_line(t_connection connect, t_coord xy0, t_coord xy1, long color)
{
	t_line d;
	t_line s;

	d.x = abs(xy1.x - xy0.x);
	s.x = xy0.x < xy1.x ? 1 : -1;
	d.y = -abs(xy1.y - xy0.y);
	s.y = xy0.y < xy1.y ? 1 : -1;
	d.err = d.x + d.y;
	while (1)
	{
		mlx_pixel_put(connect.connect, connect.window, xy0.x, xy0.y, color);
		if (xy0.x == xy1.x && xy0.y == xy1.y)
			break ;
		s.err = 2 * d.err;
		if (s.err >= d.y)
		{
			d.err += d.y;
			xy0.x += s.x;
		}
		if (s.err <= d.x)
		{
			d.err += d.x;
			xy0.y += s.y;
		}
	}
}

void	draw_line(t_connection connect, t_coord xy0, t_coord xy1, long color)
{
	if ((xy0.x < 0 && xy1.x < 0) ||
	(xy0.x > WINDOW_WIDTH && xy1.x > WINDOW_WIDTH) ||
	(xy0.y < 0 && xy1.y < 0) ||
	(xy0.y > WINDOW_HEIGHT && xy1.y > WINDOW_HEIGHT))
		return ;
	make_line(connect, xy0, xy1, color);
}

void	draw_map_edges(t_coord i, t_settings *sets,
		t_projection func, long color)
{
	if (i.y + 2 == sets->list->inputs->size.y)
		draw_line(sets->workspace, project_two(sets, i, func),
		project_four(sets, i, func), color);
	if (i.x + 2 == sets->list->inputs->size.x)
		draw_line(sets->workspace, project_th(sets, i, func),
		project_four(sets, i, func), color);
}

void	draw_map(t_settings *sets)
{
	t_coord			i;
	t_coord			start;
	t_coord			end;
	t_projection	*func;
	long			color;

	func = sets->project == 1 ? isometric_projection : oblique_projection;
	i.y = -1;
	while (++i.y < sets->list->inputs->size.y - 1)
	{
		i.x = -1;
		while (++i.x < sets->list->inputs->size.x - 1)
		{
			color = sets->list->inputs->map[i.y][i.x].color;
			start = project_one(sets, i, func);
			end = project_two(sets, i, func);
			draw_line(sets->workspace, start, end, color);
			end = project_th(sets, i, func);
			draw_line(sets->workspace, start, end, color);
			draw_map_edges(i, sets, func, color);
		}
	}
	write_key_map(sets->workspace.connect, sets->workspace.window);
}
