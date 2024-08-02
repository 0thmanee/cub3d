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
	int		i;
	char	**splited;

	i = 0;
	if (data->cub3d_map.infos_presence[direction])
		ft_error(REPETED_ERR, collector);
	while (line[i] == ' ')
		i++;
	if (line[i])
	{
		splited = ft_split(line + i, ',', collector);
		if (!splited || words_counts(line + i, ',') != 3)
			ft_error(COLOR_ERR, collector);
		set_grb(data, direction, splited, collector);
	}
}

int invalid_order(int infos_presence[])
{
	return (!infos_presence[NO] || !infos_presence[SO] || !infos_presence[WE] ||
		!infos_presence[EA] || !infos_presence[FL] || !infos_presence[CE]);
}

int full_wall(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	set_player_position(t_data *data, char direc)
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

void	parse_map_line(char *line, int i, t_data *data, t_free **collector)
{
	int	j;

	data->cub3d_map.infos_presence[BOTTOM_CLOSED] = full_wall(line);
	j = 0;
	while (line[j])
	{
		if (line[j] == 'N' || line[j] == 'S' || line[j] == 'W' || line[j] == 'E')
		{
			if (data->cub3d_map.infos_presence[PLAYER])
				ft_error(REP_PLAYER_ERR, collector);
			set_player_position(data, line[j]);
			if (not_closed(data, i, j))
			{
				printf("%c\n", line[j]);
				ft_error(MAP_ERR, collector);
			}
		}
		else if (line[j] == '0' && not_closed(data, i, j))
				ft_error(MAP_ERR, collector);
		else if (line[j] != '0' && line[j] != '1' && line[j] != ' ')
			ft_error(INVALID_ERR, collector);
		j++;
	}
}

void	parse_map(t_data *data, t_free **collector)
{
	int	i;

	if (!full_wall(data->cub3d_map.map[0]))
		ft_error(UNCLOSED_ERR, collector);
	data->cub3d_map.infos_presence[TOP_CLOSED] = 1;
	i = 1;
	while (data->cub3d_map.map[i])
	{
		parse_map_line(data->cub3d_map.map[i], i, data, collector);
		i++;
	}
}

char	**ft_realloc(t_data *data, char *line, t_free **collector)
{
	size_t	old_size;
	char	**new_ptr;
	int		len;
	
	data->cub3d_map.map_height++;
	if (!data->cub3d_map.map)
	{
		new_ptr = ft_malloc(collector, 2 * sizeof(char *));
		new_ptr[0] = ft_strdup(line, collector);
		new_ptr[1] = NULL;
		return (new_ptr);
	}
	old_size = 0;
	while (data->cub3d_map.map[old_size])
		old_size++;
	new_ptr = ft_malloc(collector, (old_size + 2) * sizeof(char *));
	ft_memcpy(new_ptr, data->cub3d_map.map, old_size * sizeof(char *));
	new_ptr[old_size] = ft_strdup(line, collector);
	new_ptr[old_size + 1] = NULL;
	len = ft_strlen(line);
	if (len > data->cub3d_map.map_width)
		data->cub3d_map.map_width = len;
	return (new_ptr);
}

void	add_map_line(t_data *data, char *line, t_free **collector)
{
	char	**old_map;

	old_map = data->cub3d_map.map;
	data->cub3d_map.map = ft_realloc(data, line, collector);
	ft_free_ptr(collector, old_map);
}

void read_data(int map_fd, t_data *data, t_free **collector)
{
	char *line;
	int i;

	data->cub3d_map.map = NULL;
	data->cub3d_map.map_height = 0;
	data->cub3d_map.map_width = 0;
	line = get_next_line(map_fd);
	while (line)
	{
		i = 0;
		ft_strtrim(&line, collector);
		if (line)
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
				add_map_line(data, line, collector);
			}
			else
				ft_error(INVALID_ERR, collector);
		}
		ft_free_ptr(collector, line);
		line = get_next_line(map_fd);
	}
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

void	parse_data(int ac, char *file, t_data *data, t_free **collector)
{
	int	map_fd;
	int	i;

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
	i = 0;
	check_infos_avalable(data->cub3d_map.infos_presence, 1, collector);
	parse_map(data, collector);
	check_infos_avalable(data->cub3d_map.infos_presence, 0, collector);
	display_infos(data->cub3d_map);
}
