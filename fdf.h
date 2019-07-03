/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 15:32:13 by slyazid           #+#    #+#             */
/*   Updated: 2019/07/03 10:27:13 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "fcntl.h"
# include "libft/libft.h"
# include "minilibx_macos/mlx.h"

typedef	enum	e_bool
{
	false,
	true
}				t_bool;

typedef struct	s_coord
{
	int		y;
	int		x;
}				t_coord;

typedef struct	s_map
{
	int		height;
	int		color;
}				t_map;


typedef struct	s_image
{
	void	*image;
	int		*data;
	int		depth;
	int		sizeline;
	t_bool	endian;
}				t_image;

typedef struct	s_connection
{
	void	*connect;
	void	*window;
	// t_image	*image;
}				t_connection;

/*
**	clean_parse.c:
*/
int		parse_input(int argc, char **argv);

/*
**	tools.c:
*/
t_bool	check_rows(char *line, t_coord size);
t_bool	write_map(t_map ***map, t_coord size, t_coord current, char **row);
t_bool	check_to_write(t_map ***map, t_coord size,
		t_coord index, char **splitted_row);
void	freedom(char **to_free);
void	freedomap(t_map **map, t_coord size);


# endif