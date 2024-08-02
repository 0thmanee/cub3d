/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_rendering.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:27:46 by yboutsli          #+#    #+#             */
/*   Updated: 2024/08/02 10:30:32 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void wall_init(t_data *data, t_wall *wall)
{
	uint32_t i;
	wall->textures = textures(data);
	wall->distanceProjPlane = (WINDOW_WIDTH / 2) / tan(data->fov.fov_angle);
	wall->buffer = (uint32_t *)wall->textures->pixels;
	wall->x_factor = wall->textures->width / data->cub3d_map.tile_size;
}

void set_x_coordinates(t_data *data, t_wall *wall, int x)
{
	float x_offset;
	if (data->rays[x].hit_vertical)
		x_offset = fmodf(data->rays[x].wall_hit_y, data->cub3d_map.tile_size);
	else
		x_offset = fmodf(data->rays[x].wall_hit_x, data->cub3d_map.tile_size);
	wall->x_offset = x_offset * wall->x_factor;
}

void set_y_coordinates(t_data *data, t_wall *wall, int y)
{
	float	y_offset;
	float	offset;

	wall->y_factor = wall->textures->height / wall->wallStripHeiht;
	wall->y_offset = (y - wall->TOP_wall_pixel) * wall->y_factor;
}

uint32_t get_color(t_data *data, uint32_t *pixels, t_wall *wall)
{
	uint32_t color;
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha;

	// printf("x = %d | y = %d\n", (int)wall->x_offset, (int)wall->y_offset);
	// printf("y_offset = %d | wall_width = %d\n", (int)(wall->y_offset) , wall->textures->width);
	// printf("mul = %f\n", wall->y_offset * wall->textures->width);
	// printf("buffer = %d\n", ((int)(wall->y_offset) * wall->textures->width) + (int)(wall->x_offset));
	color = pixels[((int)(wall->y_offset) * wall->textures->width) + (int)(wall->x_offset)]; // ABGR
	alpha = (color >> 24) & 0xFF;
	blue = (color >> 16) & 0xFF;
	green = (color >> 8) & 0xFF;
	red = color & 0xFF;
	color = (red << 24) | (green << 16) | (blue << 8) | alpha; // RGBA
	return (color);
}

void walls_rendering(t_data *data, t_wall *wall)
{
	int y;
	int x;
	int x_offset;
	int y_offset;
	uint32_t color;

	wall_init(data, wall);
	x = -1;
	while (++x < data->fov.nbr_rays)
	{
		set_x_coordinates(data, wall, x);
		wall->corrected_wall_distance = data->rays[x].distance * cos(data->rays[x].ray_angle - data->player.rotation_angle);
		wall->wallStripHeiht = (data->cub3d_map.tile_size / wall->corrected_wall_distance) * wall->distanceProjPlane;
		wall->BOTTOM_wall_pixel = (WINDOW_HEIGHT / 2 + wall->wallStripHeiht / 2);
		wall->TOP_wall_pixel = (WINDOW_HEIGHT / 2 - wall->wallStripHeiht / 2);
		y = 0;
		while (y < WINDOW_HEIGHT)
		{
			// printf ("x_offset = %d | y_offset = %f\n", (int)wall->x_offset, (int)wall->y_offset);
			if (y > wall->TOP_wall_pixel && y < wall->BOTTOM_wall_pixel)
			{
				set_y_coordinates(data, wall, y);
				color = get_color(data, wall->buffer, wall);
				mlx_put_pixel(data->mlx_data.img, x, y, color);
			}
			else
				mlx_put_pixel(data->mlx_data.img, x, y, get_rgb(0, 0, 0));
			y++;
		}
	}
}

// void walls_rendering(t_data *data, t_wall *wall)
// {
// 	int y;
// 	int x;
// 	int x_offset;
// 	int y_offset;
// 	uint32_t color;

// 	wall_init(data, wall);
// 	x = -1;
// 	while (++x < data->fov.nbr_rays)
// 	{
// 		wall->x_offset = get_x_coordinates(data, wall, x);
// 		wall->corrected_wall_distance = data->rays[x].distance * cos(data->rays[x].ray_angle - data->player.rotation_angle);
// 		wall->wallStripHeiht = (data->cub3d_map.tile_size / wall->corrected_wall_distance) * wall->distanceProjPlane;
// 		wall->BOTTOM_wall_pixel = (WINDOW_HEIGHT / 2 + wall->wallStripHeiht / 2);
// 		wall->TOP_wall_pixel = (WINDOW_HEIGHT / 2 - wall->wallStripHeiht / 2);
// 		y = 0;
// 		while (y < WINDOW_HEIGHT)
// 		{
// 			wall->y_offset = get_y_coordinates(data, wall, y);
// 			if (y > wall->TOP_wall_pixel && y < wall->BOTTOM_wall_pixel)
// 			{
// 				color = get_color(data, wall->buffer, wall);
// 				mlx_put_pixel(data->mlx_data.img, x, y, color);
// 				// wall->y_offset += (wall->textures->height / wall->wallStripHeiht);
// 			}
// 			else
// 				mlx_put_pixel(data->mlx_data.img, x, y, get_rgb(0, 0, 0));
// 			y++;
// 		}
// 	}
// }

// float get_y_coordinates(t_data *data, t_wall *wall, int y)
// {
// 	float	y_offset;
// 	float	offset;

// 	wall->y_factor = wall->textures->height / wall->wallStripHeiht;
// 	y_offset = (wall->TOP_wall_pixel - (WINDOW_HEIGHT / 2) + (wall->wallStripHeiht / 2)) * wall->y_factor;
// 	return (y_offset);
// }