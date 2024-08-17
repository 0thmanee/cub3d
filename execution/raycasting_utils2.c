/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:30:57 by yboutsli          #+#    #+#             */
/*   Updated: 2024/08/17 18:32:27 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	detect_h_wall_init(t_ray *ray, t_ray_utils *rayu)
{
	ray->h_found = 0;
	ray->h_wall_hit_x = 0;
	ray->h_wall_hit_y = 0;
	rayu->next_h_hit_x = ray->h_x_interc;
	rayu->next_h_hit_y = ray->h_y_interc;
	rayu->x_c = rayu->next_h_hit_x;
	rayu->y_c = rayu->next_h_hit_y;
}

void	detect_h_wall(t_data *data, t_ray *ray)
{
	t_ray_utils	rayu;

	detect_h_wall_init(ray, &rayu);
	while (rayu.next_h_hit_x >= 0
		&& rayu.next_h_hit_x < data->mlx_data.win_width
		&& rayu.next_h_hit_y >= 0
		&& rayu.next_h_hit_y < data->mlx_data.win_height)
	{
		rayu.x_c = rayu.next_h_hit_x;
		rayu.y_c = rayu.next_h_hit_y;
		if (ray->up)
			rayu.y_c--;
		if (wall_hitted1(data, rayu.x_c, rayu.y_c))
		{
			ray->h_wall_hit_x = rayu.next_h_hit_x;
			ray->h_wall_hit_y = rayu.next_h_hit_y;
			ray->h_found = 1;
			break ;
		}
		rayu.next_h_hit_x += ray->h_x_step;
		rayu.next_h_hit_y += ray->h_y_step;
	}
}

static void	detect_v_wall_init(t_ray *ray, t_ray_utils *rayu)
{
	ray->v_found = 0;
	rayu->next_v_hit_x = ray->v_x_interc;
	rayu->next_v_hit_y = ray->v_y_interc;
	ray->v_wall_hit_x = 0;
	ray->v_wall_hit_y = 0;
	rayu->x_c = rayu->next_v_hit_x;
	rayu->y_c = rayu->next_v_hit_y;
}

void	detect_v_wall(t_data *data, t_ray *ray)
{
	t_ray_utils	rayu;

	detect_v_wall_init(ray, &rayu);
	while (rayu.next_v_hit_x >= 0
		&& rayu.next_v_hit_x < data->mlx_data.win_width
		&& rayu.next_v_hit_y >= 0
		&& rayu.next_v_hit_y < data->mlx_data.win_height)
	{
		rayu.x_c = rayu.next_v_hit_x;
		rayu.y_c = rayu.next_v_hit_y;
		if (ray->left)
			rayu.x_c--;
		if (wall_hitted1(data, rayu.x_c, rayu.y_c))
		{
			ray->v_wall_hit_x = rayu.next_v_hit_x;
			ray->v_wall_hit_y = rayu.next_v_hit_y;
			ray->v_found = 1;
			break ;
		}
		rayu.next_v_hit_x += ray->v_x_step;
		rayu.next_v_hit_y += ray->v_y_step;
	}
}
