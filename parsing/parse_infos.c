/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_infos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 21:18:23 by obouchta          #+#    #+#             */
/*   Updated: 2024/08/03 23:04:32 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void parse_texture(char *line, t_data *data, int direction, t_free **collector)
{
	int i;
	int	fd;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (data->cub3d_map.infos_presence[direction])
		ft_error(REPETED_ERR, collector);
	if (line[i])
	{
		char *texture_path = ft_strdup(line + i, collector);
		fd = open(texture_path, O_RDONLY);
		if (fd == -1)
			ft_error(TEXTURE_ERR, collector);
		close(fd);
		set_texture_path(data, direction, texture_path);
		data->cub3d_map.infos_presence[direction] = 1;
	}
}

static int		check_rgb_range(char *nbr)
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
	if (check_rgb_range(splited[0]) &&
		check_rgb_range(splited[1]) &&
		check_rgb_range(splited[2]))
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

void parse_color(char *line, t_data *data, int direction, t_free **collector)
{
	int		i;
	int		count;
	char	**splited;
	char	last_char;

	if (data->cub3d_map.infos_presence[direction])
		ft_error(REPETED_ERR, collector);
	(i = -1, count = 0);
	while (line[++i])
	{
		while (line[i] && line[i] == ' ')
			i++;
		if (!ft_isdigit(line[i]) && line[i] != ',')
			ft_error(COLOR_ERR, collector);
		if (line[i] == ',')
		{
			if (last_char == ',')
				ft_error(COLOR_ERR, collector);
			count++;
		}
		last_char = line[i];
	}
	if (count != 2)
		ft_error(COLOR_ERR, collector);
	splited = ft_split(line, ',', collector);
	if (!splited || words_counts(line, ',') != 3)
		ft_error(COLOR_ERR, collector);
	set_grb(data, direction, splited, collector);
}
