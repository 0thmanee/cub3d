/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_rendering_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 09:00:03 by yboutsli          #+#    #+#             */
/*   Updated: 2024/08/15 09:21:32 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

mlx_texture_t	*get_texture(t_wall *wall, t_ray *ray)
{
	if (ray->hit_vertical)
	{
		if (ray->ray_angle < 0.5 * M_PI || ray->ray_angle > 1.5 * M_PI)
			return (wall->E_texture);
		else
			return (wall->W_texture);
	}
	else
	{
		if (ray->ray_angle > 0 && ray->ray_angle < M_PI)
			return (wall->S_texture);
		else
			return (wall->N_texture);
	}
}

void	set_x_coordinates(t_data *data, t_wall *wall, int x)
{
	float	offset;

	if (data->rays[x].hit_vertical)
		offset = fmodf(data->rays[x].wall_hit_y, TILE_SIZE);
	else
		offset = fmodf(data->rays[x].wall_hit_x, TILE_SIZE);
	wall->x_offset = offset * wall->x_factor;
}

void	set_y_coordinates(t_wall *wall, int y, int texture_height)
{
	wall->y_factor = (float)texture_height / wall->wallStripHeiht;
	wall->y_offset = (y - (float)wall->TOP_wall_pixel) * wall->y_factor;
}

void	fc_coloring(t_data *data, int x, int y, int rgb[3])
{
	uint32_t	color;

	color = get_rgb(rgb[0], rgb[1], rgb[3]);
	mlx_put_pixel(data->mlx_data.img, x, y, color);
}
