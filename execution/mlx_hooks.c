/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:50:37 by obouchta          #+#    #+#             */
/*   Updated: 2024/08/17 18:54:00 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	press_and_release(mlx_key_data_t keydata, int *data, int value)
{
	if (keydata.action == MLX_PRESS)
		*data = value;
	else if (keydata.action == MLX_RELEASE)
		*data = 0;
}

void	handle_key_hooks(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W)
		press_and_release(keydata, &data->player.walk_direction, 1);
	else if (keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S)
		press_and_release(keydata, &data->player.walk_direction, -1);
	else if (keydata.key == MLX_KEY_LEFT)
		press_and_release(keydata, &data->player.turn_direction, -1);
	else if (keydata.key == MLX_KEY_RIGHT)
		press_and_release(keydata, &data->player.turn_direction, 1);
	else if (keydata.key == MLX_KEY_D)
		press_and_release(keydata, &data->player.s_direction, 1);
	else if (keydata.key == MLX_KEY_A)
		press_and_release(keydata, &data->player.s_direction, -1);
	else if (keydata.key == MLX_KEY_ESCAPE)
	{
		ft_free_all(data->collector);
		free_textures(&data->wall);
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

	data = (t_data *)param;
	cast_rays(data);
	walls_rendering(data, &data->wall);
	draw_2d_map(data);
	draw_player(data);
	draw_angle(data);
}
