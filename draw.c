/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 15:44:02 by slyazid           #+#    #+#             */
/*   Updated: 2019/07/10 00:06:14 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_coord		projected_one(t_params data, t_coord count, t_input inp,
			t_projection *projection)
{
	t_coord point;

	point.x = data.offset.x + projection(count.y * data.gutter,
			count.x * data.gutter, inp.map[count.y][count.x].height * 15).x;
	point.y = data.offset.y + projection(count.y * data.gutter,
			count.x * data.gutter, inp.map[count.y][count.x].height * 15).y;
	return (point);
}

t_coord		projected_two(t_params data, t_coord count, t_input inp,
			t_projection *projection)
{
	t_coord point;

	point.x = data.offset.x + projection((count.y + 1) * data.gutter,
		count.x * data.gutter, inp.map[count.y + 1][count.x].height * 15).x;
	point.y = data.offset.y + projection((count.y + 1) * data.gutter,
		count.x * data.gutter, inp.map[count.y + 1][count.x].height * 15).y;
	return (point);
}

t_coord		projected_th(t_params data, t_coord count, t_input inp,
			t_projection *projection)
{
	t_coord point;

	point.x = data.offset.x + projection(count.y * data.gutter, (count.x + 1) *
			data.gutter, inp.map[count.y][count.x + 1].height * 15).x;
	point.y = data.offset.y + projection(count.y * data.gutter, (count.x + 1) *
			data.gutter, inp.map[count.y][count.x + 1].height * 15).y;
	return (point);
}

t_coord		projected_four(t_params data, t_coord count, t_input inp,
			t_projection *projection)
{
	t_coord p;

	p.x = data.offset.x + projection((count.y + 1) * data.gutter, (count.x + 1)
		* data.gutter, inp.map[count.y + 1][count.x + 1].height * 15).x;
	p.y = data.offset.y + projection((count.y + 1) * data.gutter, (count.x + 1)
		* data.gutter, inp.map[count.y + 1][count.x + 1].height * 15).y;
	return (p);
}

void		draw_map(t_connection wrksp, t_input inp, t_params data, int project)
{
	t_coord			 count;
	t_coord 		start;
	t_coord 		end;
	t_projection	*func;

	func = project == 1 ? isometric_projection : oblique_projection;
	count.y = -1;
	while (++count.y < inp.size.y - 1)
	{
		count.x = -1;
		while (++count.x < inp.size.x - 1)
		{
			start = projected_one(data, count, inp, func);
			end = projected_two(data, count, inp, func);
			draw_line(wrksp, start, end);
			end = projected_th(data, count, inp, func);
			draw_line(wrksp, start, end);
			if (count.y + 2 == inp.size.y)
				draw_line(wrksp, projected_two(data, count,
				inp, func), projected_four(data, count,
				inp, func));
			if (count.x + 2 == inp.size.x)
				draw_line(wrksp, projected_th(data, count,
				inp, func), projected_four(data, count,
				inp, func));
		}
	}
}
