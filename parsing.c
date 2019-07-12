/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 15:31:54 by slyazid           #+#    #+#             */
/*   Updated: 2019/07/12 17:07:47 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	read_file(char *map_name, t_coord *map)
{
	int		fd;
	char	*line;
	int		v;

	map->x = 0;
	map->y = 0;
	line = NULL;
	if ((fd = open(map_name, O_RDONLY)) >= 0)
	{
		if ((v = read(fd, line, 0) == -1))
		{
			ft_putstr(map_name);
			ft_putendl(" : Invalid map.");
			exit(-1);
		}
		while ((v = get_next_line(fd, &line)))
		{
			!map->x ? map->x = ft_strwcount(line, ' ') : 0;
			map->y += 1;
			line ? free(line) : 0;
		}
		line ? free(line) : 0;
		fd >= 0 ? close(fd) : 0;
	}
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
		|| (pre_hex = ft_strstr(row[index.x], ",0x")))
			(*map)[current.y][index.x].color = hex_to_decimal(pre_hex + 3);
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
	fd >= 0 ? close(fd) : 0;
	return (true);
}

t_mmap	*parse_input(int argc, char **argv)
{
	t_mmap	*maps;
	t_input	*input;
	int		check;
	int		number;

	number = 0;
	maps = NULL;
	while (++number < argc)
	{
		allocate_simple_input(&input);
		read_file(argv[number], &(input->size));
		allocate_map(&(input->map), input->size);
		if (set_height_map(argv[number], &(input->map), input->size, &check)
			&& check >= 0)
		{
			maps = create_list(&maps, input);
			if (number == argc - 1)
				return (maps);
		}
		else
			force_quite(number, argv, input, maps);
	}
	return (NULL);
}
