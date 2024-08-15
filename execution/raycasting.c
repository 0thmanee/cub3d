/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:49:57 by obouchta          #+#    #+#             */
/*   Updated: 2024/08/15 10:14:20 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_line	create_line(int x1, int y1, int x2, int y2)
{
	t_line	line;

	line.x1 = x1;
	line.y1 = y1;
	line.x2 = x2;
	line.y2 = y2;
	return (line);
}

static void	init_faces_dirs(t_ray *ray)
{
	ray->down = ray->ray_angle > 0
		&& ray->ray_angle < M_PI;
	ray->up = !ray->down;
	ray->right = ray->ray_angle < 0.5 * M_PI
		|| ray->ray_angle > 1.5 * M_PI;
	ray->left = !ray->right;
}

static void	set_distances(t_data *data, t_ray *ray)
{
	if (ray->h_found)
		ray->h_distance = sqrt(pow(ray->h_wall_hit_x - data->player.x, 2)
				+ pow(ray->h_wall_hit_y - data->player.y, 2));
	else
		ray->h_distance = __DBL_MAX__;
	if (ray->v_found)
		ray->v_distance = sqrt(pow(ray->v_wall_hit_x - data->player.x, 2)
				+ pow(ray->v_wall_hit_y - data->player.y, 2));
	else
		ray->v_distance = __DBL_MAX__;
}

static void	set_wall_hitted(t_ray *ray)
{
	if (ray->h_distance < ray->v_distance)
	{
		ray->wall_hit_x = ray->h_wall_hit_x;
		ray->wall_hit_y = ray->h_wall_hit_y;
		ray->distance = ray->h_distance;
		ray->hit_vertical = 0;
	}
	else
	{
		ray->wall_hit_x = ray->v_wall_hit_x;
		ray->wall_hit_y = ray->v_wall_hit_y;
		ray->distance = ray->v_distance;
		ray->hit_vertical = 1;
	}
}

static void	cast_ray(t_data *data, t_ray *ray)
{
	ray->ray_angle = fmod(ray->ray_angle, 2.0 * M_PI);
	if (ray->ray_angle < 0)
		ray->ray_angle += 2.0 * M_PI;
	init_faces_dirs(ray);
	init_h_ray(data, ray);
	detect_h_wall(data, ray);
	init_v_ray(data, ray);
	detect_v_wall(data, ray);
	set_distances(data, ray);
	set_wall_hitted(ray);
	draw_line(data, create_line(data->player.x + data->player.player_head, data->player.y + data->player.player_head,
			ray->wall_hit_x, ray->wall_hit_y), data->player.line_color); // to be removed
}

void	cast_rays(t_data *data)
{
	float	ray_angle;
	int		i;

	data->fov.fov_angle = 60 * (M_PI / 180);
	data->fov.nbr_rays = WINDOW_WIDTH;
	ray_angle = data->player.rotation_angle - (data->fov.fov_angle / 2);
	i = 0;
	while (i < data->fov.nbr_rays)
	{
		data->rays[i].ray_angle = ray_angle;
		cast_ray(data, &data->rays[i]);
		ray_angle += (data->fov.fov_angle / data->fov.nbr_rays);
		i++;
	}
}
