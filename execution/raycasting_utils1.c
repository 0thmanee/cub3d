/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 10:02:24 by yboutsli          #+#    #+#             */
/*   Updated: 2024/08/21 09:36:57 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	wall_hitted1(t_data *data, int x, int y)
{
	if (data->cub3d_map.map[(y / TILE_SIZE)][x / TILE_SIZE] == '1')
		return (1);
	return (0);
}

int	wall_hitted2(t_data *data, int x, int y)
{
	int	i;
	int	j;

	i = y - data->player.player_size / 2;
	while (i < y + data->player.player_size / 2)
	{
		j = x - data->player.player_size / 2;
		while (j < x + data->player.player_size / 2)
		{
			if (i >= 0 && i < data->mlx_data.win_height
				&& j >= 0 && j < data->mlx_data.win_width)
			{
				if (data->cub3d_map.map[(i / TILE_SIZE)][j / TILE_SIZE] == '1')
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	init_h_ray(t_data *data, t_ray *ray)
{
	ray->h_y_interc = floor(data->player.y / TILE_SIZE)
		* TILE_SIZE;
	if (ray->down)
		ray->h_y_interc += TILE_SIZE;
	ray->h_x_interc = data->player.x
		+ (ray->h_y_interc - data->player.y) / tan(ray->ray_angle);
	ray->h_y_step = TILE_SIZE;
	if (ray->up)
		ray->h_y_step *= -1;
	ray->h_x_step = TILE_SIZE / tan(ray->ray_angle);
	if (ray->h_x_step > 0 && ray->left)
		ray->h_x_step *= -1;
	if (ray->h_x_step < 0 && ray->right)
		ray->h_x_step *= -1;
}

void	init_v_ray(t_data *data, t_ray *ray)
{
	ray->v_x_interc = floor(data->player.x / TILE_SIZE)
		* TILE_SIZE;
	if (ray->right)
		ray->v_x_interc += TILE_SIZE;
	ray->v_y_interc = data->player.y
		+ (ray->v_x_interc - data->player.x) * tan(ray->ray_angle);
	ray->v_x_step = TILE_SIZE;
	if (ray->left)
		ray->v_x_step *= -1;
	ray->v_y_step = TILE_SIZE * tan(ray->ray_angle);
	if (ray->v_y_step > 0 && ray->up)
		ray->v_y_step *= -1;
	if (ray->v_y_step < 0 && ray->down)
		ray->v_y_step *= -1;
}
