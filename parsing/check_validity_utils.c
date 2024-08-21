/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validity_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:12:49 by yboutsli          #+#    #+#             */
/*   Updated: 2024/08/21 11:40:21 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	invalid_order(int infos_presence[])
{
	return (!infos_presence[NO] || !infos_presence[SO] || !infos_presence[WE]
		|| !infos_presence[EA] || !infos_presence[FL] || !infos_presence[CE]);
}

int	full_wall(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	not_closed(t_data *data, int i, int j)
{
	return (i == 0 || j == 0 || i == data->cub3d_map.map_height - 1
		|| j == ft_strlen(data->cub3d_map.map[i]) - 1
		|| data->cub3d_map.map[i - 1][j] == ' '
		|| data->cub3d_map.map[i + 1][j] == ' '
		|| data->cub3d_map.map[i][j - 1] == ' '
		|| data->cub3d_map.map[i][j + 1] == ' ');
}
