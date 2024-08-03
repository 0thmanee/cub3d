/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_rendering.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasser03 <yasser03@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:27:46 by yboutsli          #+#    #+#             */
/*   Updated: 2024/08/03 11:12:46 by yasser03         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void wall_init(t_data *data, t_wall *wall)
{
	// wall->textures = textures(data);
	// wall->buffer = (uint32_t *)wall->textures->pixels;
	// wall->x_factor = wall->textures->width / data->cub3d_map.tile_size;
}

// float	set_x_coordinates(t_data *data, t_wall *wall, int x)
// {
// 	if (data->rays[x].hit_vertical)
// 		return (fmodf(data->rays[x].wall_hit_y * wall->x_factor, data->wall->textures->width));
// 	return (fmodf(data->rays[x].wall_hit_x * wall->x_factor, data->wall->textures->width));
	
// }

// void set_y_coordinates(t_wall *wall)
// {
// 	wall->y_factor = (float)wall->textures->height / wall->wallStripHeiht;
// 	wall->y_offset = ((float)wall->TOP_wall_pixel - ((float)WINDOW_HEIGHT / 2.0) + (wall->wallStripHeiht / 2.0)) * wall->y_factor;
// 	if (wall->y_offset < 0)
// 		wall->y_offset = 0;
// }

mlx_texture_t	*get_texture(t_data *data, t_wall *wall, t_ray *ray)
{
	t_directs	player;
	player = NORTH;
	
	if (player == NORTH)
	{
		if (!ray->hit_vertical && ray->ray_angle > 180 && ray->ray_angle <= 360)
			return (wall->N_texture);
		else if (!ray->hit_vertical && ray->ray_angle < 180)
			return (wall->S_texture);
	}
	return (wall->W_texture);
}
void	set_x_coordinates(t_data *data, t_wall *wall, int x)
{
	float	offset;

	if (data->rays[x].hit_vertical)
		offset = fmodf(data->rays[x].wall_hit_y, data->cub3d_map.tile_size);
	else
		offset = fmodf(data->rays[x].wall_hit_x, data->cub3d_map.tile_size);
	wall->x_offset = offset * wall->x_factor;
}

void set_y_coordinates(t_wall *wall, int y, int texture_height)
{
	wall->y_factor = (float)texture_height / wall->wallStripHeiht;
	wall->y_offset = (y - (float)wall->TOP_wall_pixel) * wall->y_factor;
}

uint32_t get_color(t_data *data, t_wall *wall, int texture_width)
{
	uint32_t color;
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha;
	uint32_t		*buffer;

	color = wall->buffer[((int)(wall->y_offset) * texture_width) + (int)(wall->x_offset)]; // ABGR
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
	uint32_t color;
	mlx_texture_t	*texture;

	// wall_init(data, wall);
	x = -1;
	while (++x < WINDOW_WIDTH)
	{
		texture = get_texture(data, wall, &data->rays[x]);
		wall->buffer = (uint32_t *)texture->pixels;
		wall->x_factor = texture->width / data->cub3d_map.tile_size;
		wall->distanceProjPlane = (WINDOW_WIDTH / 2) / tan(data->fov.fov_angle / 2);
		wall->corrected_wall_distance = data->rays[x].distance * cos(data->rays[x].ray_angle - data->player.rotation_angle);
		wall->wallStripHeiht = (data->cub3d_map.tile_size / wall->corrected_wall_distance) * wall->distanceProjPlane;
		wall->BOTTOM_wall_pixel = ((WINDOW_HEIGHT / 2) + (wall->wallStripHeiht / 2));
		wall->TOP_wall_pixel = ((WINDOW_HEIGHT / 2) - (wall->wallStripHeiht / 2));
		y = -1;
		set_x_coordinates(data, wall, x);
		while (++y < WINDOW_HEIGHT)
		{
			if (y > wall->TOP_wall_pixel && y < wall->BOTTOM_wall_pixel)
			{
				set_y_coordinates(wall, y, texture->height);
				color = get_color(data, wall, texture->width);
				mlx_put_pixel(data->mlx_data.img, x, y, color);
			}
			else
				mlx_put_pixel(data->mlx_data.img, x, y, get_rgb(0, 0, 0));
		}
	}
}
