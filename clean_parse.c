/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouyizme <mouyizme@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 15:31:54 by slyazid           #+#    #+#             */
/*   Updated: 2019/07/05 16:58:19 by mouyizme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	read_file(char *map_name, t_coord *map)
{
	int		fd;
	char	*line;

	map->x = 0;
	map->y = 0;
	if ((fd = open(map_name, O_RDONLY)) >= 0)
	{
		while (get_next_line(fd, &line) > 0)
		{
			!map->x ? map->x = ft_strwcount(line, ' ') : 0;
			map->y += 1;
			line ? free(line) : 0;
		}
		line ? free(line) : 0;
		close(fd);
	}
}

void	allocate_map(t_map ***map, t_coord size)
{
	int	index;

	index = -1;
	(*map) = (t_map**)malloc(sizeof(t_map*) * size.y);
	while (++index < size.y)
		(*map)[index] = (t_map*)malloc(sizeof(t_map) * size.x);
}

t_bool	write_map(t_map ***map, t_coord size, t_coord current, char **row)
{
	t_coord	index;
	char	*pre_hex;

	index.x = -1;
	while (++index.x < size.x)
	{
		if ((ft_isdigit(row[index.x][0]) == false && row[index.x][0] != '-')
		|| (row[index.x][0] == '-' && !ft_isdigit(row[index.x][1])))
			break ;
		(*map)[current.y][index.x].height = ft_atoi(row[index.x]);
		if ((pre_hex = ft_strstr(row[index.x], ",0X"))
		|| (pre_hex = ft_strstr(row[index.x], ",0X")))
			(*map)[current.y][index.x].color = ft_atoi_base(pre_hex, 16);
		else
			(*map)[current.y][index.x].color = 0xffffff;
	}
	return (index.x == size.x ? true : false);
}

t_bool	set_height_map(char *map_name, t_map ***map, t_coord size, int *check)
{
	int		fd;
	t_coord	index;
	char	*line;
	char	**splitted_row;

	if ((fd = open(map_name, O_RDONLY)) < 0)
		return (false);
	index.x = -1;
	index.y = 0;
	while ((*check = get_next_line(fd, &line)) > 0)
	{
		if (!check_rows(line, size))
			return (false);
		splitted_row = ft_strsplit(line, ' ');
		line ? free(line) : 0;
		if (!check_to_write(map, size, index, splitted_row))
			return (false);
		index.y += 1;
		freedom(splitted_row);
	}
	line ? free(line) : 0;
	close(fd);
	return (true);
}

t_input	*parse_input(int argc, char **argv)
{
	t_input	*input;
	int		check;
	int		return_value;

	input = (t_input*)malloc(sizeof(t_input));
	input->map = NULL;
	input->size.x = -1;
	input->size.y = -1;
	return_value = 0;
	if (argc == 2)
	{
		read_file(argv[1], &(input->size));
		allocate_map(&(input->map), input->size);
		if (set_height_map(argv[1], &(input->map), input->size, &check)
			&& check >= 0)
			return (input);
		else
		{
			ft_putendl("Invalid map.");
			input->map ? freedomap(input->map, input->size) : 0;
			input ? free(input) : 0;
			exit(0);
		}
	}
	return (NULL);
}
