/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 00:05:21 by slyazid           #+#    #+#             */
/*   Updated: 2019/07/03 10:27:12 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_bool	check_rows(char *line, t_coord size)
{
	if (!(ft_strwcount(line, ' ') == (unsigned int)size.x))
	{
		line ? free(line) : 0;
		return (false);
	}
	return (true);
}

t_bool	check_to_write(t_map ***map, t_coord size,
		t_coord index, char **splitted_row)
{
	if (!write_map(map, size, index, splitted_row))
	{
		freedom(splitted_row);
		return (false);
	}
	return (true);
}

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
