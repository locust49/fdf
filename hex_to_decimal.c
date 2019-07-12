/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_to_decimal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 02:46:30 by mouyizme          #+#    #+#             */
/*   Updated: 2019/07/12 17:13:23 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		hex_to_decimal(const char *str)
{
	int				i;
	unsigned int	nb;
	unsigned int	len;

	i = 0;
	nb = 16777215;
	len = ft_strlen(str) - 1;
	if ((str[i] >= '0' && str[i] <= '9') ||
		(str[i] >= 'A' && str[i] <= 'F') || (str[i] >= 'a' && str[i] <= 'f'))
	{
		nb = 0;
		while (len)
		{
			if (str[i] >= '0' && str[i] <= '9')
				nb += (str[i] - '0') * pow(16, len);
			if (str[i] >= 'a' && str[i] <= 'z')
				nb += ((str[i] - 'a' + 10) * pow(16, len));
			if (str[i] >= 'A' && str[i] <= 'Z')
				nb += (str[i] - 'A' + 10) * pow(16, len);
			i++;
			len--;
		}
	}
	return (nb);
}
