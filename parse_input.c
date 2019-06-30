/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 00:24:59 by slyazid           #+#    #+#             */
/*   Updated: 2019/06/30 04:59:04 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>


// like them fdf
// t_bool	valid_row(char **map_row, t_coord range)
// {
// 	int			init;
// 	int			c;
// 	static int	n_cols;

// 	init = 0;
// 	c = 0;
// 	if (n_cols == 0)
// 		n_cols = range.col;
// 	else if (n_cols > 0 && range.col != n_cols)
// 		return (false);
// 	printf("%d | %s \n", ft_isdigit(*map_row[init] + c), map_row[init]);
// 	while (map_row[init])
// 	{
// 		if (ft_isdigit(*(map_row[init] + c)) || ((*map_row[init] + c == '-'
// 		    && *(map_row[init] + c + 1) && ft_isdigit(*(map_row[init] + c + 1)))))
// 		{
//         	while ((map_row[init] && ft_isdigit(*(map_row[init] + c))) || !(*(*map_row + c)))
// 			{
// 				if (!ft_isdigit(*map_row[init] + c) && *map_row[init] + c != ',')
// 				{
// 					printf("> %d | %d | %s \n", ft_isdigit(*map_row[init] + c), *(map_row[init] + c) ,map_row[init]);
// 					return (false);
// 				}
// 				if (!(*(*map_row + c)) || *(map_row[init] + c) == ',')
// 					break ;
// 				c += 1;
// 				map_row += 1;
// 			}
//         }
// 		else
// 		{
// 			printf("< %d | %c | %s \n", ft_isdigit(*map_row[init] + c), *(map_row[init] + c) ,map_row[init]);
// 			return (false);
// 		}
// 		init += 1;
// 	}
// 	return (true);
// }

/*
**
**	wrong file = letter inside map, letter after number (15ajshdasd), cols not == 
**
*/

t_bool	valid_row(char **map, t_coord range)
{
	int			index;
	int			c;
	static int	n_cols;

	index = 0;
	if (n_cols == 0)
		n_cols = range.col;
	else if (n_cols > 0 && range.col != n_cols)
		return (false);
	while (map[index])
	{
		c = 0;
		if (ft_isdigit(map[index][c]) || map[index][c] == '-') // if "{0..9}xxxxx" || "-xxxxx"
        {
            if (map[index][c] == '-' && !((map[index][c + 1] && ft_isdigit(map[index][c + 1])) || !map[index][c + 1])) // if "-" || "-xxx" where x != {0..9}
                return (false);
            c += 1; // second char
			if (map[index][c]) // if 2nd char exists
			{
				while (ft_isdigit(map[index][c]) || map[index][c] == ',') //breaks if !map[index][c] => true =>index+=1 | //breaks if (not digit => false || if != , then false )
				{
					if (map[index][c] == ',') // breaks if true and found , then index += 1;
					{
						c = -1;
						index += 1;
						break ;
					}
					c += 1;
				}																						
				if (c > 0 && map[index][c] && (!ft_isdigit(map[index][c]) || map[index][c] != ','))
					return (false);
				else if (!(map[index][c]) || c == -1)
				{
					c = 0;
					index += 1;
				}
			}
			else //one number move to next;
				index += 1;
		}
		else
			return (false);
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
			((*map)[range.row][col]).color = ft_atoi_base(comma + 3, 16);
		else
			((*map)[range.row][col]).color = 0Xffffff;
		map_row + 1 ? map_row += 1 : 0;
	}
}


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

int		get_map(int *get, char *map_name, t_map **map, t_coord *init)
{
	int		fd;
	t_coord	range;
	char	*line;
	char	**map_row;

	range.row = 0;
	range.col = -1;
	fd = open(map_name, O_RDONLY);
	while ((*get = get_next_line(fd, &line)) == 1)
	{
		map_row = ft_strsplit(line, ' '); //leaks
		//print_map_row(map_row);
		//goto AA;
		if (valid_row(map_row, range) == false)
		{
			// ft_memdel((void**)map_row); || /!\ *** BE CAREFUL *** /!\ */
			// free_double(map, range, map_row);
			free(line);
			//map && *map ? ft_memdel((void**)map) : 0;
			return (false);
		}
		range.col == -1 ? range.col = range_row(map_row) : 0;
		map[range.row] = (t_map*)malloc(sizeof(t_map) * range.col);
		init->col = range.col;
		store_map(&map, range, map_row, init->row);
		// ft_memdel((void**)map_row); || /!\ *** BE CAREFUL *** /!\ */
		free(line);
		range.row += 1;
	}
	//print_map(map, init->row, init->col);
	close(fd);
	return (true);
}
