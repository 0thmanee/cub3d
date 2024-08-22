/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:34:29 by yboutsli          #+#    #+#             */
/*   Updated: 2024/08/22 11:18:57 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_player(t_data *data, t_mini_map mini)
{
	int		i;
	int		j;
	int		color;

	color = data->player.body_color;
	i = mini.center_x - PLAYER_SIZE / 2;
	while (i < mini.center_x + PLAYER_SIZE / 2)
	{
		j = mini.center_y - PLAYER_SIZE / 2;
		while (j < mini.center_y + PLAYER_SIZE / 2)
		{
			if (i >= 0 && i < data->mlx_data.win_height
				&& j >= 0 && j < data->mlx_data.win_width)
				mlx_put_pixel(data->mlx_data.img, j, i, color);
			j++;
		}
		i++;
	}
}

void	draw_map_init(t_mini_map *mini, t_data *data)
{
	int	i;
	int	j;

	mini->y = 0;
	mini->center_x = M_MAP_WIDTH / 2;
	mini->center_y = M_MAP_HEIGHT / 2;
	mini->diffx = mini->center_x - (int)floor(data->player.x);
	mini->diffy = mini->center_y - (int)floor(data->player.y);
	i = -1;
	while (++i < M_MAP_WIDTH)
	{
		j = -1;
		while (++j < M_MAP_HEIGHT)
			mlx_put_pixel(data->mlx_data.img, i, j, 0x00FF);
	}
}

void	draw_mini_map(t_data *data)
{
	t_mini_map	mini;

	draw_map_init(&mini, data);
	while (mini.y < M_MAP_HEIGHT)
	{
		mini.x = 0;
		while (mini.x < M_MAP_WIDTH)
		{
			mini.map_x = (int)((mini.x - mini.diffx) / TILE_SIZE);
			mini.map_y = (int)((mini.y - mini.diffy) / TILE_SIZE);
			if (mini.map_y >= 0 && mini.map_x >= 0 && mini.map_y < M_MAP_HEIGHT
				&& mini.map_x < M_MAP_WIDTH
				&& mini.map_y < data->cub3d_map.map_height
				&& mini.map_x < data->cub3d_map.map_width)
			{
				if (data->cub3d_map.map[mini.map_y][mini.map_x] != '1')
					mlx_put_pixel(data->mlx_data.img, mini.x, mini.y, 0xFFFF);
			}
			mini.x++;
		}
		mini.y++;
	}
	draw_player(data, mini);
}
