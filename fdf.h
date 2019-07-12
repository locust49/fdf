/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 15:32:13 by slyazid           #+#    #+#             */
/*   Updated: 2019/07/12 20:07:37 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <math.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <mlx.h>
# define WINDOW_HEIGHT 1400
# define WINDOW_WIDTH 1400

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

typedef struct	s_parameters
{
	t_coord	offset;
	int		gutter;
	int		zscale;
}				t_params;

typedef struct	s_connection
{
	void	*connect;
	void	*window;
	t_coord	size_win;
}				t_connection;

typedef struct	s_mult_maps
{
	t_input				*inputs;
	struct s_mult_maps	*next;
}				t_mmap;

typedef struct	s_settings
{
	t_params		data;
	t_connection	workspace;
	int				project;
	int				*num_maps;
	t_mmap			*list;
}				t_settings;

typedef	t_coord	t_projection(int y, int x, int z);

/*
**	parsing.c:
*/
t_mmap			*parse_input(int argc, char **argv);

/*
** list_maps.c :
*/
t_mmap			*create_list(t_mmap **list, t_input *inp);

/*
**	int hex_to_decimal.c:
*/
int				hex_to_decimal(const char *str);

/*
** plot_line.c:
*/
void			draw_line(t_connection connect, t_coord xy0,
				t_coord xy1, long color);

/*
** draw.c && draw_tools.c :
*/
void			draw_map(t_settings *sets);
t_coord			project_one(t_settings *sets, t_coord i,
				t_projection *project);
t_coord			project_two(t_settings *sets, t_coord i,
				t_projection *project);
t_coord			project_th(t_settings *sets, t_coord i,
				t_projection *project);
t_coord			project_four(t_settings *sets, t_coord i,
				t_projection *project);

/*
** projections.c:
*/
t_coord			isometric_projection(int x, int y, int z);
t_coord			oblique_projection(int x, int y, int z);

/*
**	settings_tools.c:
*/
void			initialize_settings(t_settings *sets);
void			isometric_sets(t_settings *sets);
void			oblique_sets(t_settings *sets);
void			finalize_settings(t_settings *sets);
void			final_sets(t_settings *sets);

/*
**	initial_tools.c:
*/
t_bool			check_rows(char *line, t_coord size);
void			allocate_simple_input(t_input **input);
void			allocate_map(t_map ***map, t_coord size);
void			force_quite(int number, char **argv, t_input *input,
				t_mmap *maps);
t_bool			write_map(t_map ***map, t_coord size, t_coord current,
				char **row);
t_bool			check_to_write(t_map ***map, t_coord size,
				t_coord index, char **splitted_row);

/*
**	window_fdf.c:
*/
void			open_window(t_connection *workspace, char *name);
void			write_in_window(void *connect, void *window);
int				key_press(int keycode, t_settings *sets);
void			write_key_map(void *connect, void *window);

/*
**	free_tools.c:
*/
void			freedom(char **to_free);
void			freedomap(t_map **map, t_coord size);
void			free_list(t_mmap *list);

#endif
