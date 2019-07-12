/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 17:05:17 by slyazid           #+#    #+#             */
/*   Updated: 2019/07/12 17:07:03 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	freedom(char **to_free)
{
	int	index;

	index = -1;
	while (to_free[++index])
		free(to_free[index]);
	free((void*)to_free);
}

void	freedomap(t_map **map, t_coord size)
{
	int	index;

	index = -1;
	while (++index < size.y)
		free(map[index]);
	free((void*)map);
}

void	free_list(t_mmap *list)
{
	t_mmap *tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		freedomap(tmp->inputs->map, tmp->inputs->size);
		free(tmp);
		tmp = NULL;
	}
}
