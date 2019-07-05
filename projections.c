/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouyizme <mouyizme@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 14:43:43 by slyazid           #+#    #+#             */
/*   Updated: 2019/07/05 16:58:19 by mouyizme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_coord	isometric_projection(int x, int y, int z)
{
	t_coord points;

	points.x = x * cos(-M_PI_2 / 3) - y * sin(-M_PI / 3);
	points.y = -y * cos(-M_PI / 3) - x * sin(-M_PI_2 / 3) - z;
	return (points);
}

t_coord	oblique_projection(int x, int y, int z)
{
	t_coord points;

	points.x = x + 0.5 * z * cos(45);
	points.y = y + 0.5 * z * sin(45);
	return (points);
}
