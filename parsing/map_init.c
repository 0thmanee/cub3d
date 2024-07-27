/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 05:16:31 by obouchta          #+#    #+#             */
/*   Updated: 2024/05/14 05:39:31 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	calc_width(char **map_data, int height)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (i < height)
	{
		if ((int)ft_strlen(map_data[i]) > len)
			len = ft_strlen(map_data[i]);
		i++;
	}
	return (len);
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

void	init_player(t_data *data, int i, int j)
{
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

t_data	map_init(t_free **collector)
{
	t_data		data;
	int		i;
	int		j;
	char	*map_data[] = {
		"1111111111111111111111111",
		"1000000000110000000000001",
		"1011000001110000000000001",
		"1001000000000000000000001",
		"111111111011000001110000011111111",
		"100000000011000001110111111111111",
		"11110111111111011100000010001",
		"11110111111111011101010010001",
		"11000000110000011100000010001",
		"10000000000000000000000010001",
		"10000000000000000000000000001",
		"10000000000000N00000000000001",
		"10000000000000000000000000001",
		"11111111111111111111111111111"
	};
	
	i = 0;
	data.cub3d_map.tile_size = 32;
	data.cub3d_map.map_height = sizeof(map_data) / sizeof(map_data[0]);
	data.cub3d_map.map_width = calc_width(map_data, data.cub3d_map.map_height);
	data.cub3d_map.map = ft_malloc(collector, data.cub3d_map.map_height * sizeof(char *));
	while (i < data.cub3d_map.map_height)
	{
		j = 0;
		data.cub3d_map.map[i] = ft_malloc(collector, data.cub3d_map.map_width + 1);
		while (j < ft_strlen(map_data[i]))
		{
			data.cub3d_map.map[i][j] = map_data[i][j];
			if (is_player(data.cub3d_map.map[i][j]))
				init_player(&data, i, j);
			else if (map_data[i][j] != '0')
				data.cub3d_map.map[i][j] = '1';
			else
				data.cub3d_map.map[i][j] = map_data[i][j];
			j++;
		}
		while (j < data.cub3d_map.map_width)
		{
			data.cub3d_map.map[i][j] = '0';
			j++;
		}
		data.cub3d_map.map[i][j] = 0;
		i++;
	}
	return (data);
}