/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:50:37 by obouchta          #+#    #+#             */
/*   Updated: 2024/05/09 22:17:52 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void update_player_direction(t_data *data, int key)
{
	if (key == MLX_KEY_LEFT)
	{
		data->cub3d_map->player.direction -= data->cub3d_map->player.turn_speed;
		if (data->cub3d_map->player.direction < 0)
			data->cub3d_map->player.direction += 360;
	}
	else if (key == MLX_KEY_RIGHT)
	{
		data->cub3d_map->player.direction += data->cub3d_map->player.turn_speed;
		if (data->cub3d_map->player.direction >= 360)
			data->cub3d_map->player.direction -= 360;
	}
}

void handle_key_hooks(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data*) param;
	if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_DOWN
		|| keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_RIGHT)
		{
			move_player(data, keydata.key);
			update_player_direction(data, keydata.key);	
		}
}


void	loop_hook_func(void *param)
{
	t_data	*data;
	
	data = (t_data*)param;
	draw_2d_map(data);
	draw_player(data);
}