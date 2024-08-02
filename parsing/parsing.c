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

int	not_closed(t_data *data, int i, int j)
{
	return (i == 0 || j == 0 || i == data->cub3d_map.map_height - 1
		|| j == ft_strlen(data->cub3d_map.map[i]) - 1
		|| data->cub3d_map.map[i - 1][j] == ' '
		|| data->cub3d_map.map[i + 1][j] == ' '
		|| data->cub3d_map.map[i][j - 1] == ' '
		|| data->cub3d_map.map[i][j + 1] == ' ');
}

char	*ft_realloc_line(char *line, int len, t_free **collector)
{
	char	*new_line;
	int		i;

	new_line = ft_malloc(collector, len + 1);
	ft_memcpy(new_line, line, ft_strlen(line));
	new_line[len] = '\0';
	i = ft_strlen(line);
	while (i < len)
	{
		new_line[i] = ' ';
		i++;
	}
	return (new_line);
}

void	fill_lines_end(t_data *data, t_free **collector)
{
	int		i;

	i = 0;
	while (data->cub3d_map.map[i])
	{
		if (ft_strlen(data->cub3d_map.map[i]) < data->cub3d_map.map_width)
			data->cub3d_map.map[i] = ft_realloc_line(data->cub3d_map.map[i],
			data->cub3d_map.map_width, collector);
		i++;
	}
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
			set_player(data, line[j], i, j);
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

void	parse_map(t_data *data, t_free **collector)
{
	int	i;

	if (!full_wall(data->cub3d_map.map[0]))
		ft_error(UNCLOSED_ERR, collector);
	data->cub3d_map.infos_presence[TOP_CLOSED] = 1;
	i = 1;
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
		parse_map_line(data->cub3d_map.map[i], i, data, collector);
		i++;
	}
}

char	**ft_realloc_map(t_data *data, char *line, t_free **collector)
{
	size_t	old_size;
	char	**new_map;
	int		len;
	
	data->cub3d_map.map_height++;
	if (!data->cub3d_map.map)
	{
		new_map = ft_malloc(collector, 2 * sizeof(char *));
		new_map[0] = line;
		new_map[1] = NULL;
		return (new_map);
	}
	old_size = 0;
	while (data->cub3d_map.map[old_size])
		old_size++;
	new_map = ft_malloc(collector, (old_size + 2) * sizeof(char *));
	ft_memcpy(new_map, data->cub3d_map.map, old_size * sizeof(char *));
	new_map[old_size] = line;
	new_map[old_size + 1] = NULL;
	len = ft_strlen(line);
	if (len > data->cub3d_map.map_width)
		data->cub3d_map.map_width = len;
	return (new_map);
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

void read_data(int map_fd, t_data *data, t_free **collector)
{
	char	*line;
	char	*n_line;
	int		i;

	data->cub3d_map.map = NULL;
	data->cub3d_map.map_height = 0;
	data->cub3d_map.map_width = 0;
	line = get_next_line(map_fd);
	while (line)
	{
		i = 0;
		n_line = ft_strtrim(line, collector);
		if (n_line)
		{
			if (n_line[i] == 'N' && n_line[i + 1] == 'O' && n_line[i + 2] == ' ')
				parse_texture(n_line + i + 2, data, NO, collector);
			else if (n_line[i] == 'S' && n_line[i + 1] == 'O' && n_line[i + 2] == ' ')
				parse_texture(n_line + i + 2, data, SO, collector);
			else if (n_line[i] == 'W' && n_line[i + 1] == 'E' && n_line[i + 2] == ' ')
				parse_texture(n_line + i + 2, data, WE, collector);
			else if (n_line[i] == 'E' && n_line[i + 1] == 'A' && n_line[i + 2] == ' ')
				parse_texture(n_line + i + 2, data, EA, collector);
			else if (n_line[i] == 'F' && n_line[i + 1] == ' ')
				parse_color(n_line + i + 1, data, FL, collector);
			else if (n_line[i] == 'C' && n_line[i + 1] == ' ')
				parse_color(n_line + i + 1, data, CE, collector);
			else if (n_line[i] == '1' || n_line[i] == '0')
			{
				if (invalid_order(data->cub3d_map.infos_presence))
					ft_error(ORDER_ERR, collector);
				data->cub3d_map.infos_presence[MAP_FOUND] = 1;
				break ;
			}
			else
				ft_error(INVALID_ERR, collector);
		}
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
	fill_lines_end(data, collector);
	// display_infos(data->cub3d_map);
	parse_map(data, collector);
	check_infos_avalable(data->cub3d_map.infos_presence, 0, collector);
	data->cub3d_map.tile_size = 32;
}
