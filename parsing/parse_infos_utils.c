/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_infos_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:05:29 by yboutsli          #+#    #+#             */
/*   Updated: 2024/08/17 18:54:00 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	check_rgb_range(char *nbr)
{
	int		i;
	long	color;

	i = 0;
	while (nbr[i])
	{
		if (!ft_isdigit(nbr[i]) && nbr[i] != ' ')
			return (0);
		i++;
	}
	color = ft_atoi(nbr);
	if (color < -2147483648 || color > 2147483647 || color < 0 || color > 255)
		return (0);
	return (1);
}

void	set_grb(t_data *data, int direction, char **splited, t_free **collector)
{
	if (check_rgb_range(splited[0])
		&& check_rgb_range(splited[1])
		&& check_rgb_range(splited[2]))
	{
		if (direction == FL)
		{
			data->cub3d_map.floor_color[0] = ft_atoi(splited[0]);
			data->cub3d_map.floor_color[1] = ft_atoi(splited[1]);
			data->cub3d_map.floor_color[2] = ft_atoi(splited[2]);
			data->cub3d_map.infos_presence[FL] = 1;
		}
		else if (direction == CE)
		{
			data->cub3d_map.ceiling_color[0] = ft_atoi(splited[0]);
			data->cub3d_map.ceiling_color[1] = ft_atoi(splited[1]);
			data->cub3d_map.ceiling_color[2] = ft_atoi(splited[2]);
			data->cub3d_map.infos_presence[CE] = 1;
		}
	}
	else
		ft_error(COLOR_ERR, collector);
}

void	set_texture_path(t_data *data, int direction, char *texture_path)
{
	if (direction == NO)
		data->cub3d_map.no_texture = texture_path;
	else if (direction == SO)
		data->cub3d_map.so_texture = texture_path;
	else if (direction == WE)
		data->cub3d_map.we_texture = texture_path;
	else if (direction == EA)
		data->cub3d_map.ea_texture = texture_path;
}
