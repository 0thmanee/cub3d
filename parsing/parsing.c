/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:51:20 by obouchta          #+#    #+#             */
/*   Updated: 2024/05/10 05:16:28 by obouchta         ###   ########.fr       */
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
	char *tmp_line;

	i = 0;
	while (line[i] == ' ')
		i++;
	tmp_line = line;
	line = ft_strtrim(line, collector);
	free(tmp_line);
	if (data->cub3d_map.infos_presence[direction])
		ft_error(REPETED_ERR, collector);
	if (line[i])
	{
		tmp_line = line;
		char *texture_path = ft_strdup(line + i, collector);
		free(tmp_line);
		if (ft_strlen(texture_path) < 4 || ft_strcmp(ft_substr(texture_path,
			ft_strlen(texture_path) - 4, 4, collector), ".xpm"))
				ft_error(TEXTURE_ERR, collector);
		if (access(texture_path, F_OK) == -1)
			ft_error(TEXTURE_ERR, collector);
		set_texture_path(data, direction, texture_path);
		data->cub3d_map.infos_presence[direction] = 1;
	}
}
static	int		check_rgb_range(int n)
{
	return (n >= 0 && n <= 255);
}

void	set_grb(t_data *data, int direction, char **splited, t_free **collector)
{
	if (check_rgb_range(ft_atoi(splited[0])) &&
		check_rgb_range((ft_atoi(splited[1]))) &&
		check_rgb_range(ft_atoi(splited[2])))
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
	int i;
	char	**splited;

	i = 0;
	if (data->cub3d_map.infos_presence[direction])
		ft_error(REPETED_ERR, collector);
	line = ft_strtrim(line, collector);
	while (line[i] == ' ')
		i++;
	if (line[i])
	{
		splited = ft_split(line, ',', collector);
		if (!splited || sizeof(splited) / 8 != 3)
			ft_error(COLOR_ERR, collector);
		set_grb(data, direction, splited, collector);
	}
}

void read_data(int map_fd, t_data *data, t_free **collector)
{
	char *line;
	int i;

	line = get_next_line(map_fd);
	while (line)
	{
		i = 0;
		while (line[i] == ' ')
			i++;
		if (line[i])
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
			else
				ft_error("INVALID_ERR", collector);
		}
		free(line);
		line = get_next_line(map_fd);
	}
}

void	parse_map(int ac, char *file, t_free **collector, t_data *data)
{
	(void)data;
	int	map_fd;

	ft_memset(data->cub3d_map.infos_presence, 0, sizeof(data->cub3d_map.infos_presence));
	if (ac != 2)
		ft_error(ARGS_ERR, collector);
	if (ft_strlen(file) < 4 || \
		ft_strcmp(ft_substr(file, ft_strlen(file) - 4, 4, collector), ".cub"))
		ft_error(EXTN_ERR, collector);
	map_fd = open(file, O_RDONLY);
	if (map_fd == -1)
		ft_error(FILE_ERR, collector);
	read_data(map_fd, data, collector);
}
