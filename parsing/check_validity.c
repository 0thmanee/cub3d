/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 21:19:18 by obouchta          #+#    #+#             */
/*   Updated: 2024/08/04 19:17:56 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int invalid_order(int infos_presence[])
{
	return (!infos_presence[NO] || !infos_presence[SO] || !infos_presence[WE] ||
		!infos_presence[EA] || !infos_presence[FL] || !infos_presence[CE]);
}

int full_wall(char *line)
{
	int i;

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

int	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	all_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	check_info(char *line, int i, t_data *data, t_free **collector)
{
	if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		parse_texture(line + i + 2, data, NO, collector);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		parse_texture(line + i + 2, data, SO, collector);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		parse_texture(line + i + 2, data, WE, collector);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		parse_texture(line + i + 2, data, EA, collector);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		parse_color(line + i + 1, data, FL, collector);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		parse_color(line + i + 1, data, CE, collector);
	else if (line[i] == '1' || line[i] == '0')
	{
		if (invalid_order(data->cub3d_map.infos_presence))
			ft_error(ORDER_ERR, collector);
		data->cub3d_map.infos_presence[MAP_FOUND] = 1;
		return (1);
	}
	else
		ft_error(INVALID_ERR, collector);
	return (0);
}