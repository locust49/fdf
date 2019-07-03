/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 15:31:54 by slyazid           #+#    #+#             */
/*   Updated: 2019/07/03 03:26:16 by slyazid          ###   ########.fr       */
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
			// line ? free(line) : 0;
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
		if (ft_isdigit(row[index.x][0]) == false
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
	else
	{
		index.x = -1;
		index.y = 0;
		while ((*check = get_next_line(fd, &line)) > 0)
		{
			if (!(ft_strwcount(line, ' ') == (unsigned int)size.x))
			{
				line ? free(line) : 0;
				return (false);
			}
			splitted_row = ft_strsplit(line, ' ');
			line ? free(line) : 0;
			if (!write_map(map, size, index, splitted_row))
			{
				freedom(splitted_row);
				return (false);
			}
			index.y += 1;
			freedom(splitted_row);
		}
		line ? free(line) : 0;
		close(fd);
	}
	return (true);
}

int		parse_input(int argc, char **argv)
{
	t_coord	size;
	t_map	**map;
	int		check;
	int		return_value;

	return_value = 0;
	if (argc == 2)
	{
		read_file(argv[1], &size);
		allocate_map(&map, size);
		if (set_height_map(argv[1], &map, size, &check) && check >= 0)
			return_value = 1;
		else
		{	
			ft_putendl("byebye");
			exit(0);
		}
		freedomap(map, size);
	}
	return (return_value);
}