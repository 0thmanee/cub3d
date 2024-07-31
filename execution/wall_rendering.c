/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_rendering.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:27:46 by yboutsli          #+#    #+#             */
/*   Updated: 2024/07/30 18:27:03 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	opacity_calc(int distance)
{
	int	opacity_factor;
	float	opacity;

	opacity_factor = 3;
	if (distance == 0)
		distance = 1;
	opacity = ((255 * opacity_factor) / distance) % 256;
	return (floor(opacity));
}
void walls_rendering(t_data *data)
{
	int i;
	int j;
	float	distanceProjPlane;
	float	wallStripHeiht;
	float	corrected_wall_distance;

	i = 0;
	distanceProjPlane = (WINDOW_WIDTH / 2) / tan(data->fov.fov_angle);
	while (j < data->fov.nbr_rays)
	{
		corrected_wall_distance = data->rays[j].distance * cos(data->rays[j].ray_angle - data->player.rotation_angle);
		wallStripHeiht = (data->cub3d_map.tile_size / corrected_wall_distance) * distanceProjPlane;
		i = 0;
		while (i < WINDOW_HEIGHT)
		{
			if (i > (WINDOW_HEIGHT / 2 - wallStripHeiht / 2) && i < (WINDOW_HEIGHT / 2 + wallStripHeiht / 2))
				mlx_put_pixel(data->mlx_data.img, j, i, get_rgb_opacity(220, 220, 220, opacity_calc(corrected_wall_distance)));
			else
				mlx_put_pixel(data->mlx_data.img, j, i, get_rgb(0, 0, 0));
			i++;
		}
		j++;
	}
}