/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 22:52:32 by slyazid           #+#    #+#             */
/*   Updated: 2019/06/28 03:04:48 by slyazid          ###   ########.fr       */
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
			printf("%2d ", (map[r][c]).colour);
		//	printf("%2x ", (map[r][c]).height);
			c += 1;
		}
		printf("\n");
		r += 1;
	}
}


int	main(int argc, char **argv)
{
	t_map	**map;
	int		n_rows;
	int		fd;
	char	*line;

	n_rows = 0;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			exit(0);
		while (get_next_line(fd, &line))
		{
			n_rows += 1;
			free(line);		
		}
		close(fd);
		map = (t_map **)malloc(n_rows * sizeof(t_map*));
		if (get_map(argv[1], map, n_rows) == false)
			printf("Error\n");
		else
			printf("Good\n");
	}
	else
		printf("Error\n");
	return (1);
}