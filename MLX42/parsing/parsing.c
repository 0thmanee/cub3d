/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:51:20 by obouchta          #+#    #+#             */
/*   Updated: 2024/04/22 11:59:36 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	parsing(t_free **ptrs)
{
	t_map	cub3d_map;
	int		i;

	char	*map_data[] = {
		"1111111111111111111111111",
		"1000000000110000000000001",
		"1011000001110000000000001",
		"1001000000000000000000001",
		"111111111011000001110000000000001",
		"100000000011000001110111111111111",
		"11110111111111011100000010001",
		"11110111111111011101010010001",
		"11000000110101011100000010001",
		"10000000000000001100000010001",
		"10000000000000001101010010001",
		"11000001110101011111011110N0111",
		"11110111 1110101 101111010001",
		"11111111 1111111 111111111111"
	};
	i = 0;
	cub3d_map.map_height = sizeof(map_data) / sizeof(map_data[0]);
	cub3d_map.map = ft_malloc(ptrs, cub3d_map.map_height * sizeof(char *));
	while (i < cub3d_map.map_height)
	{
		cub3d_map.map[i] = ft_strdup(map_data[i], ptrs);
		i++;
	}
	return (cub3d_map);
}