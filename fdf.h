/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouyizme <mouyizme@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 15:32:13 by slyazid           #+#    #+#             */
/*   Updated: 2019/07/05 16:58:19 by mouyizme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <math.h>
# include <fcntl.h>
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

typedef struct	s_line
{
	int			x;
	int			y;
	int			err;
}				t_line;

typedef struct	s_map
{
	int		height;
	int		color;
}				t_map;

typedef struct	s_input
{
	t_map	**map;
	t_coord	size;
}				t_input;

typedef struct	s_image
{
	void	*image;
	int		*data;
	int		depth;
	int		sizeline;
	int		endian;
}				t_image;

typedef struct	s_connection
{
	void	*connect;
	void	*window;
	t_coord	size_win;
	// t_image	*image;
}				t_connection;

/*
**	clean_parse.c:
*/
t_input		*parse_input(int argc, char **argv);

/*
** plot_line.c:
*/
void	draw_line(t_connection connect, t_coord xy0, t_coord xy1);
void    draw_map(t_connection wrksp, t_input inp);

/*
** projections.c:
*/
t_coord	isometric_projection(int x, int y, int z);
t_coord	oblique_projection(int x, int y, int z);

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