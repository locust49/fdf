/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 17:06:33 by slyazid           #+#    #+#             */
/*   Updated: 2019/07/12 17:06:42 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_coord	project_one(t_settings *sets, t_coord i, t_projection *project)
{
	t_coord p;

	p.x = sets->data.offset.x +
			project(i.y * sets->data.gutter, i.x * sets->data.gutter,
			sets->list->inputs->map[i.y][i.x].height * sets->data.zscale).x;
	p.y = sets->data.offset.y +
			project(i.y * sets->data.gutter, i.x * sets->data.gutter,
			sets->list->inputs->map[i.y][i.x].height * sets->data.zscale).y;
	return (p);
}

t_coord	project_two(t_settings *sets, t_coord i, t_projection *project)
{
	t_coord p;

	p.x = sets->data.offset.x +
			project((i.y + 1) * sets->data.gutter, i.x * sets->data.gutter,
			sets->list->inputs->map[i.y + 1][i.x].height * sets->data.zscale).x;
	p.y = sets->data.offset.y +
			project((i.y + 1) * sets->data.gutter, i.x * sets->data.gutter,
			sets->list->inputs->map[i.y + 1][i.x].height * sets->data.zscale).y;
	return (p);
}

t_coord	project_th(t_settings *sets, t_coord i, t_projection *project)
{
	t_coord p;

	p.x = sets->data.offset.x +
			project(i.y * sets->data.gutter, (i.x + 1) * sets->data.gutter,
			sets->list->inputs->map[i.y][i.x + 1].height * sets->data.zscale).x;
	p.y = sets->data.offset.y +
			project(i.y * sets->data.gutter, (i.x + 1) * sets->data.gutter,
			sets->list->inputs->map[i.y][i.x + 1].height * sets->data.zscale).y;
	return (p);
}

t_coord	project_four(t_settings *sets, t_coord i, t_projection *project)
{
	t_coord p;

	p.x = sets->data.offset.x +
		project((i.y + 1) * sets->data.gutter, (i.x + 1) * sets->data.gutter,
		sets->list->inputs->map[i.y + 1][i.x + 1].height * sets->data.zscale).x;
	p.y = sets->data.offset.y +
		project((i.y + 1) * sets->data.gutter, (i.x + 1) * sets->data.gutter,
		sets->list->inputs->map[i.y + 1][i.x + 1].height * sets->data.zscale).y;
	return (p);
}
