/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_maps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 17:44:10 by slyazid           #+#    #+#             */
/*   Updated: 2019/07/12 15:58:29 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mmap	*create_list(t_mmap **list, t_input *inp)
{
	t_mmap	*tmp;

	if (!(*list))
	{
		(*list) = (t_mmap*)malloc(sizeof(t_mmap));
		(*list)->inputs = inp;
		(*list)->next = NULL;
	}
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (t_mmap*)malloc(sizeof(t_mmap));
		tmp->next->inputs = inp;
		tmp->next->next = NULL;
	}
	return (*list);
}
