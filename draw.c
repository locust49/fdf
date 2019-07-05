/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouyizme <mouyizme@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 15:44:02 by slyazid           #+#    #+#             */
/*   Updated: 2019/07/05 16:58:19 by mouyizme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    draw_map(t_connection wrksp, t_input inp)
{
    // t_coord start;
    t_coord projected;
    int gutter;
    int offset;
    t_coord count;
    t_coord start;
    t_coord end;

    // draw_line(wrksp, start, gutter);
    count.y = -1;
    gutter = 100;
    offset = wrksp.size_win.y / 2;
    while (++count.y < inp.size.y - 1)
    {
        count.x = -1;
        while (++count.x < inp.size.x - 1)
        {
            projected = oblique_projection(count.y, count.x,
                        inp.map[count.y][count.x].height);

			start.x = offset + oblique_projection(count.y * gutter, count.x * gutter, inp.map[count.y][count.x].height * 15).x;
			start.y = offset + oblique_projection(count.y * gutter, count.x * gutter, inp.map[count.y][count.x].height * 15).y;
			end.x = offset + oblique_projection((count.y + 1) * gutter, count.x * gutter, inp.map[count.y + 1][count.x].height * 15).x;
			end.y = offset + oblique_projection((count.y + 1) * gutter, count.x * gutter, inp.map[count.y + 1][count.x].height * 15).y;
		    draw_line(wrksp, start, end);

			end.x = offset +  oblique_projection(count.y * gutter, (count.x + 1) * gutter, inp.map[count.y][count.x + 1].height * 15).x;
			end.y = offset + oblique_projection(count.y * gutter, (count.x + 1) * gutter, inp.map[count.y][count.x + 1].height * 15).y;
			draw_line(wrksp, start, end);
			if (count.x + 2 == inp.size.x)
			{
				start.x = offset + oblique_projection(count.y * gutter, (count.x + 1) * gutter, inp.map[count.y][count.x + 1].height * 15).x;
				start.y = offset + oblique_projection(count.y * gutter, (count.x + 1) * gutter, inp.map[count.y][count.x + 1].height * 15).y;
				end.x = offset + oblique_projection((count.y + 1) * gutter, (count.x + 1) * gutter, inp.map[count.y + 1][count.x + 1].height * 15).x;
				end.y = offset + oblique_projection((count.y + 1) * gutter, (count.x + 1) * gutter, inp.map[count.y + 1][count.x + 1].height * 15).y;
				draw_line(wrksp, start, end);
			}
			if (count.y + 2 == inp.size.y)
			{
				start.x = offset + oblique_projection((count.y + 1) * gutter, count.x * gutter, inp.map[count.y + 1][count.x].height * 15).x;
				start.y = offset + oblique_projection((count.y + 1) * gutter, count.x * gutter, inp.map[count.y + 1][count.x].height * 15).y;
				end.x = offset + oblique_projection((count.y + 1) * gutter, (count.x + 1) * gutter, inp.map[count.y + 1][count.x + 1].height * 15).x;
				end.y = offset + oblique_projection((count.y + 1) * gutter, (count.x + 1) * gutter, inp.map[count.y + 1][count.x + 1].height * 15).y;
				draw_line(wrksp, start, end);
			}
            // if (count.y + 2 == inp.size.y)
            // {
            //     start.x = 400 + oblique_projection((count.y + 1) * 50, (count.x + 1) * 50, inp.map[count.y + 1][count.x].height * 15).x;
            //     start.y = 400 + oblique_projection((count.y + 1) * 50, (count.x + 1) * 50, inp.map[count.y + 1][count.x].height * 15).y;
            //     end.x = 400 + oblique_projection((count.y + 1) * 50, (count.x + 1) * 50, inp.map[count.y][count.x + 1].height * 15).x;
            //     end.y = 400 + oblique_projection((count.y + 1) * 50, (count.x + 1) * 50, inp.map[count.y][count.x + 1].height * 15).y;
            //     draw_line(wrksp, start, end);
            // }
        }
    }
}