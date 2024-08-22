/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_rendering.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:27:46 by yboutsli          #+#    #+#             */
/*   Updated: 2024/08/22 17:58:35 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

uint32_t	get_color(t_wall *wall, int texture_width)
{
	uint32_t	color;
	uint8_t		red;
	uint8_t		green;
	uint8_t		blue;
	uint8_t		alpha;

	if ((int)(wall->texture->width * wall->texture->height)
		<= (((int)(wall->y_offset) * texture_width)
		+ (int)(wall->x_offset)))
		return (0);
	color = wall->buffer[((int)(wall->y_offset) * texture_width)
		+ (int)(wall->x_offset)];
	alpha = (color >> 24) & 0xFF;
	blue = (color >> 16) & 0xFF;
	green = (color >> 8) & 0xFF;
	red = color & 0xFF;
	color = (red << 24) | (green << 16) | (blue << 8) | alpha;
	return (color);
}

void	walls_init(t_data *data, t_wall *wall, int x)
{
	wall->texture = get_texture(wall, &data->rays[x]);
	wall->buffer = (uint32_t *)wall->texture->pixels;
	wall->x_factor = wall->texture->width / TILE_SIZE;
	wall->d_p_plane = (WINDOW_WIDTH / 2) / tan(data->fov.fov_angle / 2);
	wall->c_w_distance = data->rays[x].distance
		* cos(data->rays[x].ray_angle - data->player.rotation_angle);
	wall->wallstripheiht = (TILE_SIZE / wall->c_w_distance) * wall->d_p_plane;
	wall->bottom_wall_pixel = ((WINDOW_HEIGHT / 2)
			+ (wall->wallstripheiht / 2));
	wall->top_wall_pixel = ((WINDOW_HEIGHT / 2) - (wall->wallstripheiht / 2));
}

void	walls_rendering(t_data *data, t_wall *wall)
{
	int			y;
	int			x;
	uint32_t	color;

	x = -1;
	while (++x < WINDOW_WIDTH)
	{
		walls_init(data, wall, x);
		y = -1;
		set_x_coordinates(data, wall, x);
		while (++y < WINDOW_HEIGHT)
		{
			if (y < wall->top_wall_pixel)
				fc_coloring(data, x, y, data->cub3d_map.ceiling_color);
			else if (y > wall->top_wall_pixel && y < wall->bottom_wall_pixel)
			{
				set_y_coordinates(wall, y, wall->texture->height);
				color = get_color(wall, wall->texture->width);
				mlx_put_pixel(data->mlx_data.img, x, y, color);
			}
			else
				fc_coloring(data, x, y, data->cub3d_map.floor_color);
		}
	}
}
