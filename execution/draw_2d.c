/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:44:09 by obouchta          #+#    #+#             */
/*   Updated: 2024/08/18 16:18:17 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_player(t_data *data)
{
	int		i;
	int		j;
	int		x;
	int		y;
	int		color;

	color = data->player.body_color;
	i = data->player.y - data->player.player_size / 2;
	y = 0;
	while (y < data->player.player_size)
	{
		j = data->player.x - data->player.player_size / 2;
		x = 0;
		while (x < data->player.player_size)
		{
				mlx_put_pixel(data->mlx_data.img,
					MINI_MAP_SCALE * (j + x), MINI_MAP_SCALE * (i + y), color);
			x++;
		}
		y++;
	}
}

void	draw_square(t_data *data, int x, int y, int color)
{
	int		i;
	int		j;
	int		i_side;
	int		j_side;

	i_side = x * TILE_SIZE;
	j_side = y * TILE_SIZE;
	i = i_side - 1;
	while (++i < i_side + TILE_SIZE)
	{
		j = j_side;
		while (j < j_side + TILE_SIZE)
		{
			if (i >= 0 && i < data->mlx_data.win_height
				&& j >= 0 && j < data->mlx_data.win_width)
				mlx_put_pixel(data->mlx_data.img,
					MINI_MAP_SCALE * j, MINI_MAP_SCALE * i, color);
			j++;
		}
	}
}

void	draw_2d_map(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	while (i < data->cub3d_map.map_height)
	{
		j = 0;
		while (j < data->cub3d_map.map_width)
		{
			if (data->cub3d_map.map[i][j] == '1')
				draw_square(data, i, j, get_rgb(0, 0, 0));
			else if (data->cub3d_map.map[i][j] == '0'
				|| data->cub3d_map.map[i][j] == 'P')
				draw_square(data, i, j, get_rgb(255, 255, 255));
			j++;
		}
		i++;
	}
}
