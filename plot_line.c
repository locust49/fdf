/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 14:28:49 by slyazid           #+#    #+#             */
/*   Updated: 2019/07/05 16:29:58 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_connection connect, t_coord xy0, t_coord xy1)
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
		mlx_pixel_put(connect.connect, connect.window, xy0.x, xy0.y, 0xFFFFFF);
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
