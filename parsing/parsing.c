/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:51:20 by obouchta          #+#    #+#             */
/*   Updated: 2024/08/03 02:17:13 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	display_infos(t_map cub3d_map)
{
	printf("NO = {%s}\n", cub3d_map.no_texture);
	printf("SO = {%s}\n", cub3d_map.so_texture);
	printf("WE = {%s}\n", cub3d_map.we_texture);
	printf("EA = {%s}\n", cub3d_map.ea_texture);
	printf("F = {%d, %d, %d}\n", cub3d_map.floor_color[0], cub3d_map.floor_color[1], cub3d_map.floor_color[2]);
	printf("C = {%d, %d, %d}\n", cub3d_map.ceiling_color[0], cub3d_map.ceiling_color[1], cub3d_map.ceiling_color[2]);
	printf("Map:\n");
	int i = 0;
	if (cub3d_map.map)
	{
		while (cub3d_map.map[i])
		{
			printf("%s\n", cub3d_map.map[i]);
			i++;
		}
	}
}

t_directs	get_player_pos(char c)
{
	if (c == 'N')
		return (NORTH);
	if (c == 'S')
		return (SOUTH);
	if (c == 'W')
		return (WEST);
	if (c == 'E')
		return (EAST);
	return (NORTH);
}

void	set_player(t_data *data, char direc, int i, int j)
{
	data->cub3d_map.infos_presence[PLAYER] = 1;
	if (direc == 'N')
		data->player.player_direction = NO;
	else if (direc == 'S')
		data->player.player_direction = SO;
	else if (direc == 'W')
		data->player.player_direction = WE;
	else if (direc == 'E')
		data->player.player_direction = EA;
	data->player.y = i * data->cub3d_map.tile_size;
	data->player.x = j * data->cub3d_map.tile_size;
	data->player.rotation_angle =
		get_player_pos(data->cub3d_map.map[i][j]) * (M_PI / 180);
	data->cub3d_map.map[i][j] = 'P';
	data->player.turn_direction = 0;
	data->player.walk_direction = 0;
	data->player.move_speed = 3;
	data->player.rotation_speed = 5 * (M_PI / 180);
	data->player.line_len = 100;
	data->player.body_color = get_rgb(255, 0, 0);
	data->player.line_color = get_rgb(255, 0, 0);
	data->player.player_size = data->cub3d_map.tile_size / 4;
	data->player.player_head = data->player.player_size / 2;
}

void	add_map_line(t_data *data, char *line, t_free **collector)
{
	char	**old_map;
	char	*new_line;
	char	*tmp_line;

	old_map = data->cub3d_map.map;
	if (line[ft_strlen(line) - 1] == '\n')
		new_line = ft_substr(line, 0, ft_strlen(line) - 1, collector);
	else
		new_line = ft_strdup(line, collector);
	if (!new_line || all_spaces(new_line))
	{
		tmp_line = new_line;
		new_line = ft_strdup(" ", collector);
		ft_free_ptr(collector, tmp_line);
	}
	data->cub3d_map.map = ft_realloc_map(data, new_line, collector);
	ft_free_ptr(collector, old_map);
}

void	check_infos_avalable(int *infos_presence, int bef, t_free **collector)
{
	if (bef)
	{
		if (!infos_presence[NO])
			ft_error(MISSING_NO_TEXT_ERR, collector);
		if (!infos_presence[SO])
			ft_error(MISSING_SO_TEXT_ERR, collector);
		if (!infos_presence[WE])
			ft_error(MISSING_WE_TEXT_ERR, collector);
		if (!infos_presence[EA])
			ft_error(MISSING_EA_TEXT_ERR, collector);
		if (!infos_presence[FL])
			ft_error(MISSING_F_COLOR_ERR, collector);
		if (!infos_presence[CE])
			ft_error(MISSING_C_COLOR_ERR, collector);
		if (!infos_presence[MAP_FOUND])
			ft_error(MISSING_MAP_ERR, collector);
		return ;
	}
	if (!infos_presence[PLAYER])
		ft_error(PLAYER_ERR, collector);
	if (!infos_presence[BOTTOM_CLOSED])
		ft_error(UNCLOSED_ERR, collector);
}

void read_data(int map_fd, t_data *data, t_free **collector)
{
	char	*line;
	char	*n_line;
	int		i;

	data->cub3d_map.map = NULL;
	(data->cub3d_map.map_height = 0, data->cub3d_map.map_width = 0);
	line = get_next_line(map_fd);
	while (line)
	{
		i = 0;
		n_line = ft_strtrim(line, collector);
		if (n_line && check_info(n_line, i, data, collector))
			break ;
		(free(line), ft_free_ptr(collector, n_line));
		line = get_next_line(map_fd);
	}
	while (line)
	{
		add_map_line(data, line, collector);
		free(line);
		line = get_next_line(map_fd);
	}
}
