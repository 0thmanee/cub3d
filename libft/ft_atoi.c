/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:39:17 by obouchta          #+#    #+#             */
/*   Updated: 2024/04/22 11:39:18 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

long	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	res;
	long	tmp;

	i = 0;
	sign = 1;
	res = 0;
	tmp = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if ((sign == 1 && res > INT_MAX) || (sign == -1 && (-res) < INT_MIN))
			break ;
		res = (res * 10) + (str[i] - 48);
		i++;
	}
	return (sign * res);
}
