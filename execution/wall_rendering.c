/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_rendering.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:27:46 by yboutsli          #+#    #+#             */
/*   Updated: 2024/07/31 21:13:19 by yboutsli         ###   ########.fr       */
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
	int			i;
	int			j;
	float		distanceProjPlane;
	float		wallStripHeiht;
	float		corrected_wall_distance;
	uint32_t	*wall_textures;
	int			x_offset;
	int			y_offset;
	uint32_t	color;
	int 		top;
	int			bottom;

	distanceProjPlane = (WINDOW_WIDTH / 2) / tan(data->fov.fov_angle);
	bottom = (WINDOW_HEIGHT / 2 + wallStripHeiht / 2);
	wall_textures = textures(data);
	j = 0;
	while (j < data->fov.nbr_rays)
	{
		if (data->rays[j].hit_vertical)
			x_offset = (int)((data->rays[j].wall_hit_y)) % data->cub3d_map.tile_size;
		else
			x_offset = (int)((data->rays[j].wall_hit_x)) % data->cub3d_map.tile_size;
		corrected_wall_distance = data->rays[j].distance * cos(data->rays[j].ray_angle - data->player.rotation_angle);
		wallStripHeiht = (data->cub3d_map.tile_size / corrected_wall_distance) * distanceProjPlane;
		top = (WINDOW_HEIGHT / 2 - wallStripHeiht / 2);
		bottom = (WINDOW_HEIGHT / 2 + wallStripHeiht / 2);
		i = 0;
		while (i < WINDOW_HEIGHT)
		{
			if (i > top && i < bottom)
			{
				y_offset = floor((i - top) * (TEX_HEIGHT / wallStripHeiht));
				color = wall_textures[(TEX_WIDTH * y_offset) + x_offset];
				mlx_put_pixel(data->mlx_data.img, j, i, color);
			}
			else
				mlx_put_pixel(data->mlx_data.img, j, i, get_rgb(0, 0, 0));
			i++;
		}
		j++;
	}
}

// void walls_rendering(t_data *data)
// {
// 	int i;
// 	int j;
// 	float	distanceProjPlane;
// 	float	wallStripHeiht;
// 	float	corrected_wall_distance;
// 	size_t 		top;
// 	size_t			bottom;

// 	j = 0;
// 	top = (WINDOW_HEIGHT / 2 - wallStripHeiht / 2);
// 	bottom = (WINDOW_HEIGHT / 2 + wallStripHeiht / 2);
// 	distanceProjPlane = (WINDOW_WIDTH / 2) / tan(data->fov.fov_angle);
// 	while (j < data->fov.nbr_rays)
// 	{
// 		corrected_wall_distance = data->rays[j].distance * cos(data->rays[j].ray_angle - data->player.rotation_angle);
// 		wallStripHeiht = (data->cub3d_map.tile_size / corrected_wall_distance) * distanceProjPlane;
// 		i = 0;
// 		while (i < WINDOW_HEIGHT)
// 		{
// 			if (i > (WINDOW_HEIGHT / 2 - wallStripHeiht / 2) && i < (WINDOW_HEIGHT / 2 + wallStripHeiht / 2))
// 				mlx_put_pixel(data->mlx_data.img, j, i, get_rgb(255, 0, 0));
// 			else
// 				mlx_put_pixel(data->mlx_data.img, j, i, get_rgb(0, 0, 0));
// 			i++;
// 		}
// 		j++;
// 	}
// }