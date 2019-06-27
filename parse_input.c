/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 00:24:59 by slyazid           #+#    #+#             */
/*   Updated: 2019/06/27 02:48:02 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//	int		init;

//			init = 0;
//			if (ft_isdigit(map_row[init][0]) || (map_row[init][0]) == '-'
//				&& map_row[init][1] && ft_isidigit(map_row[init][1]))
//			{
//			}

/*
** find a way to store		||  create struct for RGB	||	split hexa to 3
** colours from HEX			||	containing 3 int.		||	2 first		= R
** to RGB ? passing by		||	same type ?= int[3]		||	2 second	= G
** int form (or char*)		||	(0 = R, 1 = G, 2 = B)	||	2 last		= B


** ********************** BIRI SAID NO **********************
** int		*hextorgb(int hex)
** {
**	int		*rgb;
**
**	rgb = (int*)malloc(sizeof(int) * 3);
**	rgb[0] = 255;
**	rgb[1] = 255;
**	rgb[2] = 255;
**	return (rgb);
** }
** ********************** BIRI SAID NO **********************
*/

int	range_row(char **map_row)
{
	int	cols;

	cols = 0;
	while (map_row[cols])
		cols += 1;
	return (cols);
}

void	store_map(t_map **map, t_coord range, char **map_row, int n_rows)
{
	t_coord	i;
	char	*comma;

	i.row = -1;
	while (++i.row < n_rows)
	{
		i.col = -1;
		map[range.row] = ft_memalloc(sizeof(t_map) * range.col);
		while (++i.col < range.col)
		{
			(map[range.row][range.col]).height = ft_atoi(map_row[i.row]);
			if ((comma = ft_strchr(map_row[*************], ',')))
				(map[range.row][range.col]).colour = ft_atoi_base(comma + 1, 16);
			else
				(map[range.row][range.col]).colour = 0Xffffff; 	
		}
	}
}

int     get_map(char *map_name, t_map **map, int n_rows)
{
	int		fd;
	t_coord	range;
	char	*line;
	char	**map_row;

	range.row = -1;
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		return (false);
	while (get_next_line(fd, &line) == 1 && ++range.row)
	{
		map_row = ft_strsplit(line, ' ');
		if (valid_row(map_row, range) == false)
		{
			//ft_memdel((void**)map_row); || /!\ *** BE CAREFUL *** /!\ 
			free(line);
			map && *map ? ft_memdel((void**)map) : 0;
			return (false);
		}
		else
		{
			range.col == -1 ? range.col = range_row(map_row) : 0; //if same cols, 1 time sf
			store_map(map, range, map_row, n_rows);
			//ft_memdel((void**)map_row); || /!\ *** BE CAREFUL *** /!\ 
			free(line);
		}
	}
	close(fd);
	return (true);
}