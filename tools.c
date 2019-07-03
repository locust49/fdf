/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 00:05:21 by slyazid           #+#    #+#             */
/*   Updated: 2019/07/03 00:29:51 by slyazid          ###   ########.fr       */
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
