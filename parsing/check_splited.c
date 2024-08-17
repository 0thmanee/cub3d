/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_splited.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:50:36 by yboutsli          #+#    #+#             */
/*   Updated: 2024/08/16 18:54:24 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_splited_map(t_data *data, t_free **collector)
{
	int	i;

	i = 0;
    data->cub3d_map.map_height = 0;
	while (data->cub3d_map.map[i])
	{
		if (empty_line(data->cub3d_map.map[i]))
		{
			data->cub3d_map.map[i++] = NULL;
			while (data->cub3d_map.map[i])
			{
				if (!empty_line(data->cub3d_map.map[i]))
					ft_error(MAP_ERR, collector);
				i++;
			}
			break ;
		}
		data->cub3d_map.map_height++;
		i++;
	}
}
