/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 22:52:32 by slyazid           #+#    #+#             */
/*   Updated: 2019/06/30 07:40:23 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fdf.h"

void	print_map(t_map **map, int rows, int cols)
{
	int r;
	int	c;

	r = 0;
	while (r < rows)
	{
		c = 0;
		while (c < cols)
		{
			//printf("%2d ", (map[r][c]).color);
			printf("%2x ", (map[r][c]).height);
			c += 1;
		}
		printf("\n");
		r += 1;
	}
}

void	print_error(void)
{
	char *error;

	error = ft_strdup("Error");
	ft_putendl(error);
	free(error);
	exit(0);
}

void	free_double(t_map ***map, t_coord range, char ***map_row)
{
	int to_max;
	int	index;

	to_max = 0;
	index = 0;
	if (!map && map_row)
	{
		while ((*map_row)[index])
		{
			free((*map_row)[index]);
			index += 1;
		}
		// free(*map_row);
	}
	if (map)
	{
		while (to_max++ < range.row)
			free(map[to_max]);
		map && *map ? ft_memdel((void**)map) : 0;
	}
}

int	main(int argc, char **argv)
{
	t_map	**map;
	t_coord	init;
	int		fd;
	char	*line;
	int		error;
	int		to_max = 0;
	int i = 0;

	init.row = 0;
	init.col = 0;
	error = 0;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		(fd < 0) ? print_error() : 0;
		while (get_next_line(fd, &line)) //leaks
		{
			init.row += 1;
			init.col == 0 ? init.col = ft_strwcount(line, ' ') : 0;
			free(line);
		}
		close(fd);
		map = (t_map **)malloc(init.row * sizeof(t_map*));
		while (i < init.col)
			map[i++] = (t_map*)malloc(init.col * sizeof(t_map));
		if (get_map(&error, argv[1], &map, &init) == false
			|| error == -1 || !init.row)
			{
				print_error();
			}
		else
		{
			while (to_max++ < init.row)
				free(map[to_max]);
			map ? free(map) : 0;
			printf("All good\n");
		}
		free(map);
	}
	else
		print_error();
	return (1);
}