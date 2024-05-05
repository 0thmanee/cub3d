/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:51:20 by obouchta          #+#    #+#             */
/*   Updated: 2024/05/05 15:42:57 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

t_map	parsing(t_free **ptrs)
{
	t_map	cub3d_map;
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
		"11000000110101011100000010001",
		"10000000000000001100000010001",
		"10000000000000000000000000001",
		"100000E0000000000000000000001",
		"10000000000000000000000000001",
		"11111111111111111111111111111"
	};
	i = 0;
	cub3d_map.tile_val = 32;
	cub3d_map.map_height = sizeof(map_data) / sizeof(map_data[0]);
	cub3d_map.map_width = calc_width(map_data, cub3d_map.map_height);
	printf("width: %d, height: %d\n",cub3d_map.map_width, cub3d_map.map_height);
	cub3d_map.map = ft_malloc(ptrs, cub3d_map.map_height * sizeof(char *));
	while (i < cub3d_map.map_height)
	{
		j = 0;
		cub3d_map.map[i] = ft_malloc(ptrs, cub3d_map.map_width + 1);
		while (j < ft_strlen(map_data[i]))
		{
			cub3d_map.map[i][j] = map_data[i][j];
			if (is_player(cub3d_map.map[i][j]))
			{
				cub3d_map.player.x = j;
				cub3d_map.player.y = i;
				cub3d_map.player.direction = get_player_pos(cub3d_map.map[i][j]);
				cub3d_map.map[i][j] = 'P';
			}
			else
				cub3d_map.map[i][j] = map_data[i][j];
			j++;
		}
		while (j < cub3d_map.map_width)
		{
			cub3d_map.map[i][j] = '0';
			j++;
		}
		cub3d_map.map[i][j] = 0;
		i++;
	}
	return (cub3d_map);
}