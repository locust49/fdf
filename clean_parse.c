/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.42.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 15:31:54 by slyazid           #+#    #+#             */
/*   Updated: 2019/07/01 20:48:21 by mouyizme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void    print_map_row(char **map)
{
    int i;

    i  = 0;
    while (map[i])
    {
        printf("[%d]: [%s]\n", i, map[i]);
        i++;
    }
}

void	read_file(char *map_name, t_coord *map)
{
	int		fd;
	char	*line;

	map->x = 0;
	map->y = 0;
	fd = open(map_name, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		!map->x ? map->x = ft_strwcount(line, ' ') : 0;
		map->y += 1;
		free(line);
	}
	line ? free(line) : 0;
	close(fd);
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
		{
			// printf("[%s][%c]\n", row[index.x], row[index.x][0]);
			print_map_row(row);
			break ;
		}	
		(*map)[current.y][index.x].height = ft_atoi(row[index.x]);
		if ((pre_hex = ft_strstr(row[index.x], ",0X"))
		|| (pre_hex = ft_strstr(row[index.x], ",0X")))
			(*map)[current.y][index.x].color = ft_atoi_base(pre_hex, 16);
		else
			(*map)[current.y][index.x].color = 0xffffff;
	}
	return (index.x == size.x ? true : false);
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

t_bool	set_height_map(char *map_name, t_map ***map, t_coord size)
{
	int		fd;
	int		check;
	t_coord	index;
	char	*line;
	char	**splitted_row;

	index.x = -1;
	index.y = 0;
	fd = open(map_name, O_RDONLY);
	while ((check = get_next_line(fd, &line)) > 0)
	{
		if (!(ft_strwcount(line, ' ') == (unsigned int)size.x))
		{
			line ? free(line) : 0;
			printf("1\n");
			return (false);
		}
		splitted_row = ft_strsplit(line, ' ');
		free(line);
		if (!write_map(map, size, index, splitted_row))
		{	
			freedom(splitted_row);
			printf("2\n");
			return (false);
		}
		index.y += 1;
		freedom(splitted_row);
	}
	line ? free(line) : 0;
	close(fd);
	printf("%c d\n\n", check);
	return (check == -1 ? false : true);
}


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
			// printf("%2d ", (map[r][c]).color);
			printf("%3d ", (map[r][c]).height);
			c += 1;
		}
		printf("\n");
		r += 1;
	}
}

int main(int argc, char **argv)
{
	t_coord	size;
	t_map	**map;

	if (argc == 2)
	{
		read_file(argv[1], &size);
		allocate_map(&map, size);
		if (set_height_map(argv[1], &map, size))
			ft_putendl("hi");
			//print_map(map, size.y, size.x);
		else
			ft_putendl("byebye");
		freedomap(map, size);
	}
	return (1);
}





