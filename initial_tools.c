/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 00:05:21 by slyazid           #+#    #+#             */
/*   Updated: 2019/07/12 17:18:28 by slyazid          ###   ########.fr       */
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

void	allocate_simple_input(t_input **input)
{
	(*input) = (t_input*)malloc(sizeof(t_input));
	(*input)->map = NULL;
	(*input)->size.x = -1;
	(*input)->size.y = -1;
}

void	allocate_map(t_map ***map, t_coord size)
{
	int	index;

	index = -1;
	(*map) = (t_map**)malloc(sizeof(t_map*) * size.y);
	while (++index < size.y)
		(*map)[index] = (t_map*)malloc(sizeof(t_map) * size.x);
}

void	force_quite(int number, char **argv, t_input *input, t_mmap *maps)
{
	ft_putstr(argv[number]);
	ft_putendl(" : Invalid map.");
	input->map ? freedomap(input->map, input->size) : 0;
	input ? ft_memdel((void*)&input) : 0;
	maps ? free_list(maps) : 0;
	exit(-1);
}
