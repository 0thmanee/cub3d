/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 10:02:24 by yboutsli          #+#    #+#             */
/*   Updated: 2024/08/15 10:10:40 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	wall_hitted(t_data *data, int x, int y)
{
	if (data->cub3d_map.map[(y / TILE_SIZE)][x / TILE_SIZE] == '1')
		return (1);
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

void	detect_h_wall(t_data *data, t_ray *ray)
{
	float	next_h_hit_x;
	float	next_h_hit_y;

	ray->h_found = 0;
	next_h_hit_x = ray->h_x_interc;
	next_h_hit_y = ray->h_y_interc;
	ray->h_wall_hit_x = 0;
	ray->h_wall_hit_y = 0;
	if (ray->up)
		next_h_hit_y--;
	while (next_h_hit_x >= 0 && next_h_hit_x < data->mlx_data.win_width
		&& next_h_hit_y >= 0 && next_h_hit_y < data->mlx_data.win_height)
	{
		if (wall_hitted(data, next_h_hit_x, next_h_hit_y))
		{
			ray->h_wall_hit_x = next_h_hit_x;
			ray->h_wall_hit_y = next_h_hit_y;
			ray->h_found = 1;
			break ;
		}
		next_h_hit_x += ray->h_x_step;
		next_h_hit_y += ray->h_y_step;
	}
}

void	detect_v_wall(t_data *data, t_ray *ray)
{
	float	next_v_hit_x;
	float	next_v_hit_y;

	ray->v_found = 0;
	next_v_hit_x = ray->v_x_interc;
	next_v_hit_y = ray->v_y_interc;
	ray->v_wall_hit_x = 0;
	ray->v_wall_hit_y = 0;
	if (ray->left)
		next_v_hit_x--;
	while (next_v_hit_x >= 0 && next_v_hit_x < data->mlx_data.win_width
		&& next_v_hit_y >= 0 && next_v_hit_y < data->mlx_data.win_height)
	{
		if (wall_hitted(data, next_v_hit_x, next_v_hit_y))
		{
			ray->v_wall_hit_x = next_v_hit_x;
			ray->v_wall_hit_y = next_v_hit_y;
			ray->v_found = 1;
			break ;
		}
		next_v_hit_x += ray->v_x_step;
		next_v_hit_y += ray->v_y_step;
	}
}
