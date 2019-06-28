/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouyizme <mouyizme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 00:24:59 by slyazid           #+#    #+#             */
/*   Updated: 2019/06/28 03:16:15 by mouyizme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

t_bool	valid_row(char **map_row, t_coord range)
{
	int			init;
	int			c;
	static int	n_cols;

	init = 0;
	c = 0;
	if (n_cols == 0)
		n_cols = range.col;
	else if (n_cols > 0 && range.col != n_cols)
		return (false);
	while (map_row[init])
	{
		if (ft_isdigit(**map_row) || ((**map_row == '-'
		&& *(*map_row + 1) && ft_isdigit(*(*map_row + 1)))))
			while (ft_isdigit(*(*(map_row + 1)) || !(*(*map_row + 1))))
			{
				if (!(*(*map_row + 1)))
					break ;
				map_row += 1;
			}
		else
			return (false);
		init += 1;
	}
	return (true);
}

int		range_row(char **map_row)
{
	int	cols;

	cols = 0;
	while (map_row[cols])
		cols += 1;
	return (cols);
}

void	store_map(t_map ***map, t_coord range, char **map_row, int n_rows)
{
	int		col;
	char	*comma;

	n_rows = 0;
	col = -1;
	while (++col < range.col)
	{
		((*map)[range.row][col]).height = ft_atoi(*map_row);
	 	if ((comma = ft_strchr(*map_row, ',')))
			((*map)[range.row][col]).colour = ft_atoi_base(comma + 3, 16);
		else
			((*map)[range.row][col]).colour = 0Xffffff;
		map_row + 1 ? map_row += 1 : 0;
	}
}

int		get_map(char *map_name, t_map **map, int n_rows)
{
	int		fd;
	t_coord	range;
	char	*line;
	char	**map_row;

	range.row = 0;
	range.col = -1;
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		return (false);
	while (get_next_line(fd, &line) == 1)
	{
		//printf("line = %s\n", line);
		map_row = ft_strsplit(line, ' ');
		if (valid_row(map_row, range) == false)
		{
			/*ft_memdel((void**)map_row); || /!\ *** BE CAREFUL *** /!\ */
			free(line);
			map && *map ? ft_memdel((void**)map) : 0;
			return (false);
		}
		else
		{
			range.col == -1 ? range.col = range_row(map_row) : 0;
			map[range.row] = (t_map*)malloc(sizeof(t_map) * range.col);
			store_map(&map, range, map_row, n_rows);
			/* ft_memdel((void**)map_row); || /!\ *** BE CAREFUL *** /!\ */
			free(line);
		}
		range.row += 1;
	}
	close(fd);
	print_map(map, n_rows, range.col);
	return (true);
}
