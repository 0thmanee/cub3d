/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:44:09 by obouchta          #+#    #+#             */
/*   Updated: 2024/05/11 23:41:38 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_data *data)
{
	int		i;
	int		j;
	int		color;

	color = data->player.body_color;
	i = data->player.y;
	while (i < data->player.y + data->player.player_size)
	{
		j = data->player.x;
		while (j < data->player.x + data->player.player_size)
		{
			if (i >= 0 && i < data->mlx_data.win_height
				&& j >= 0 && j < data->mlx_data.win_width)
				mlx_put_pixel(data->mlx_data.img, j, i, color);
			j++;
		}
		i++;
	}
}

void draw_line(t_data *data, t_line line, int color)
{
	double dx = abs(line.x2 - line.x1);
	double dy = abs(line.y2 - line.y1);
	double sx = (line.x1 < line.x2) ? 1 : -1;
	double sy = (line.y1 < line.y2) ? 1 : -1;
	double err = dx - dy;

	while (line.x1 != line.x2 || line.y1 != line.y2)
	{
		if (line.y1 >= 0 && line.y1 < data->mlx_data.win_height
			&& line.x1 >= 0 && line.x1 < data->mlx_data.win_width)
			mlx_put_pixel(data->mlx_data.img, line.x1, line.y1, color);
		double err2 = 2 * err;
		if (err2 > -dy)
		{
			err -= dy;
			line.x1 += sx;
		}
		if (err2 < dx)
		{
			err += dx;
			line.y1 += sy;
		}
	}
}

void	draw_angle(t_data *data)
{
	t_line	line;

	line.x1 = data->player.x + data->player.player_size / 2;
	line.y1 = data->player.y;
	line.x2 = line.x1 + cos(data->player.rotation_angle) * data->player.line_len;
	line.y2 = line.y1 + sin(data->player.rotation_angle) * data->player.line_len;
	draw_line(data, line, data->player.line_color);
}

void	init_fov(t_data *data)
{
	data->fov.fov_angle = 60 * (M_PI / 180);
	data->fov.wall_width = 1;
	data->fov.nbr_rays = data->mlx_data.win_width / data->fov.wall_width;
}

void	draw_rays(t_data *data)
{
	init_fov(data);
	double	ray_angle;
	t_line	line;
	int		i;

	ray_angle = data->player.rotation_angle - (data->fov.fov_angle / 2);
	i = 0;
	while (i < data->fov.nbr_rays)
	{
		line.x1 = data->player.x;
		line.y1 = data->player.y;
		line.x2 = line.x1 + cos(ray_angle) * data->player.line_len;
		line.y2 = line.y1 + sin(ray_angle) * data->player.line_len;
		draw_line(data, line, data->player.line_color);
		ray_angle += data->fov.fov_angle / data->fov.nbr_rays;
		i++;
	}
}

void	draw_square(t_data *data, int x, int y, int color)
{
	int		i;
	int		j;
	int		i_side;
	int		j_side;

	(1) && (i_side = x * data->cub3d_map.tile_size,
		j_side = y * data->cub3d_map.tile_size,	i = i_side - 1);
	while (++i < i_side + data->cub3d_map.tile_size)
	{
		j = j_side;
		while (j < j_side + data->cub3d_map.tile_size)
			if (i >= 0 && i < data->mlx_data.win_height
				&& j >= 0 && j < data->mlx_data.win_width)
				mlx_put_pixel(data->mlx_data.img, j++, i, color);
	}
}

void	draw_2d_map(t_data *data)
{
	int		i;
	int		j;
	i = 0;
	while (i < data->cub3d_map.map_height)
	{
		j = 0;
		while (j < data->cub3d_map.map_width)
		{
			if (data->cub3d_map.map[i][j] == '1')
				draw_square(data, i, j, get_rgb(0, 0, 0));
			else
				draw_square(data, i, j, get_rgb(255, 255, 255));
			j++;
		}
		i++;
	}
}