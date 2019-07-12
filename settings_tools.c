/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 17:04:18 by slyazid           #+#    #+#             */
/*   Updated: 2019/07/12 17:16:34 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	initialize_settings(t_settings *sets)
{
	sets->project = 1;
	sets->workspace.size_win.x = WINDOW_WIDTH;
	sets->workspace.size_win.y = WINDOW_HEIGHT;
	isometric_sets(sets);
	sets->data.zscale = sets->data.gutter / 2;
}

void	finalize_settings(t_settings *sets)
{
	sets->project = 0;
	sets->workspace.size_win.y = WINDOW_HEIGHT;
	sets->workspace.size_win.x = WINDOW_WIDTH;
}

void	final_sets(t_settings *sets)
{
	t_mmap	*to_free;

	if (sets->list->next)
	{
		to_free = sets->list;
		sets->list = sets->list->next;
		initialize_settings(sets);
		freedomap(to_free->inputs->map, to_free->inputs->size);
		free(to_free);
		to_free = NULL;
	}
	else
		finalize_settings(sets);
}

void	isometric_sets(t_settings *sets)
{
	sets->project = 1;
	sets->data.gutter = sets->list->inputs->size.x > sets->list->inputs->size.y
		? sets->workspace.size_win.x / sets->list->inputs->size.x / 2
		: sets->workspace.size_win.y / sets->list->inputs->size.y / 2;
	sets->data.offset.x = (sets->workspace.size_win.x -
		isometric_projection((sets->list->inputs->size.x - 1) *
		sets->data.gutter, (sets->list->inputs->size.y - 1) *
		sets->data.gutter, 0).x) / 2;
	sets->data.offset.y = (sets->workspace.size_win.y -
		isometric_projection((sets->list->inputs->size.y - 1) *
		sets->data.gutter, (sets->list->inputs->size.x - 1) *
		sets->data.gutter, 0).y) / 2;
}

void	oblique_sets(t_settings *sets)
{
	sets->project = 2;
	if (sets->list->inputs->size.x > sets->list->inputs->size.y)
	{
		sets->data.gutter = (sets->workspace.size_win.x - 400) /
			(sets->list->inputs->size.x - 1);
		sets->data.offset.x = 200;
		sets->data.offset.y = (sets->workspace.size_win.y -
			(sets->data.gutter * (sets->list->inputs->size.y - 1))) / 2;
	}
	else
	{
		sets->data.gutter = (sets->workspace.size_win.y - 400) /
			(sets->list->inputs->size.y - 1);
		sets->data.offset.y = 200;
		sets->data.offset.x = (sets->workspace.size_win.x -
			(sets->data.gutter * sets->list->inputs->size.x)) / 2;
	}
}
