/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:50:37 by obouchta          #+#    #+#             */
/*   Updated: 2024/05/10 05:01:37 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void move_player(t_data *data, int key)
{
	int	new_x;
	int	new_y;
	int	size_x;
	int	size_y;

	(void)key;
	(1) && (new_x = data->player.x, new_y = data->player.y, size_x = 0, size_y = 0);
	data->player.rotation_angle += (data->player.turn_direction
		* data->player.rotation_speed);
	new_x += (data->player.walk_direction * data->player.move_speed
		* cos(data->player.rotation_angle) * data->player.move_speed);
	new_y += (data->player.walk_direction * data->player.move_speed
		* sin(data->player.rotation_angle) * data->player.move_speed);
	if (new_x + size_x >= 0 && new_x + size_x < data->mlx_data.win_width &&
		new_y + size_y >= 0 && new_y + size_y < data->mlx_data.win_height &&
		data->cub3d_map.map[(new_y + size_y) / data->cub3d_map.tile_val]
		[(new_x + size_x) / data->cub3d_map.tile_val] != '1')
		(1) && (data->player.x = new_x, data->player.y = new_y);
}

void	press_and_release(mlx_key_data_t keydata, int *data, int value)
{
	if (keydata.action == MLX_PRESS)
		*data = value;
	else if (keydata.action == MLX_RELEASE)
		*data = 0;
}

void handle_key_hooks(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data*) param;
	if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W)
		press_and_release(keydata, &data->player.walk_direction, 1);
	else if (keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S)
		press_and_release(keydata, &data->player.walk_direction, -1);
	else if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_A)
		press_and_release(keydata, &data->player.turn_direction, -1);
	else if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_D)
		press_and_release(keydata, &data->player.turn_direction, 1);
	else if (keydata.key == MLX_KEY_ESCAPE)
	{
		ft_free_all(data->ptrs);
		mlx_terminate(data->mlx_data.mlx);
		exit(0);
	}
	else
		return ;
	move_player(data, keydata.key);
}

void	loop_hook_func(void *param)
{
	t_data	*data;
	
	data = (t_data*)param;
	draw_2d_map(data);
	draw_player(data);
	draw_fov(data);
}