/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:50:37 by obouchta          #+#    #+#             */
/*   Updated: 2024/05/08 05:27:41 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void move_player(t_data *data, int key)
{
	int new_x;
	int new_y;

	new_x = data->cub3d_map->player.x;
	new_y = data->cub3d_map->player.y;
	if (key == MLX_KEY_UP)
		new_y--;
	else if (key == MLX_KEY_DOWN)
		new_y++;
	else if (key == MLX_KEY_LEFT)
		new_x--;
	else if (key == MLX_KEY_RIGHT)
		new_x++;
	if (new_x >= 0 && new_x < data->mlx_data->win_width &&
		new_y >= 0 && new_y < data->mlx_data->win_height &&
		data->cub3d_map->map[new_y / data->cub3d_map->tile_val]
		[new_x / data->cub3d_map->tile_val] != '1')
	{
		data->cub3d_map->player.x = new_x;
		data->cub3d_map->player.y = new_y;
	}
}

void handle_key_hooks(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data*) param;
	if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_DOWN
		|| keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_RIGHT)
		move_player(data, keydata.key);
}

void	loop_hook_func(void *param)
{
	t_data	*data;
	
	data = (t_data*)param;
	draw_2d_map(data);
	draw_player(data);
}