/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:44:09 by obouchta          #+#    #+#             */
/*   Updated: 2024/05/13 21:02:18 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	wall_hitted(t_data *data, int x, int y)
{
	if (data->cub3d_map.map[y / data->cub3d_map.tile_size]
			[x / data->cub3d_map.tile_size] == '1')
		return (1);
	return (0);
}

t_line	create_line(int x1, int y1, int x2, int y2)
{
	t_line line;
	
	line.x1 = x1;
	line.y1 = y1;
	line.x2 = x2;
	line.y2 = y2;
	return (line);
}

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

	line.x1 = data->player.x + data->player.player_head;
	line.y1 = data->player.y;
	line.x2 = line.x1 + cos(data->player.rotation_angle) * data->player.line_len;
	line.y2 = line.y1 + sin(data->player.rotation_angle) * data->player.line_len;
	draw_line(data, line, data->player.body_color);
}

void	init_fov(t_data *data)
{
	data->fov.fov_angle = 60 * (M_PI / 180);
	data->fov.wall_width = 1;
	data->fov.nbr_rays = data->mlx_data.win_width / data->fov.wall_width;
}

// determine the f_h_y of the first horizontal line
// f_h_y = p_y /32

// determine the f_h_x of this point:
// tan(r_a) = = (p_y - f_h_y) / (f_h_x - p_x)
// f_h_x = p_x + (p_y - f_h_y) / tan(r_a) 
void	init_faces_dirs(t_data *data, double ray_angle)
{
	data->fov.faces[0] = ray_angle > 0 && ray_angle < M_PI;
	data->fov.faces[1] = !data->fov.faces[0];
	data->fov.faces[2] = ray_angle < 0.5 * M_PI || ray_angle > 1.5 * M_PI;
	data->fov.faces[3] = !data->fov.faces[2];
}

void	init_h_ray(t_data *data, double ray_angle)
{
	data->fov.h_y_step = data->cub3d_map.tile_size;
	if (data->fov.faces[1])
		data->fov.h_y_step *= -1;
	data->fov.h_x_step = data->fov.h_y_step / tan(ray_angle);
	if (data->fov.h_x_step > 0 && data->fov.faces[3])
		data->fov.h_x_step *= -1;
	if (data->fov.h_x_step < 0 && data->fov.faces[2])
		data->fov.h_x_step *= -1;
}

void	init_ray(t_data *data, double ray_angle)
{
	printf("angle_before: %f, ", ray_angle / (M_PI / 180));
	if (ray_angle)
		ray_angle = fmod(ray_angle, 2 * M_PI);
	if (ray_angle < 0)
		ray_angle = 2 * M_PI + ray_angle;
	init_faces_dirs(data, ray_angle);
	printf("Angle: %f, UP: %d, Down %d, Left: %d, Right: %d\n", ray_angle / (M_PI / 180),  data->fov.faces[1], data->fov.faces[0], data->fov.faces[3], data->fov.faces[2]);
	data->fov.y_interc = data->player.y / data->cub3d_map.tile_size
		+ data->fov.faces[0] * data->cub3d_map.tile_size;
	data->fov.x_interc = data->player.x
		+ (data->fov.y_interc - data->player.y) / tan(ray_angle);
	init_h_ray(data, ray_angle);
	// init_v_ray(data, ray_angle);
}

void	detect_h_wall(t_data *data)
{
	int	next_h_touch_x;
	int	next_h_touch_y;
	int	wall_hit_x;
	int	wall_hit_y;
	int	h_wall_found;

	(1) && (next_h_touch_x = data->fov.x_interc, next_h_touch_y = data->fov.y_interc);
	(1) && (h_wall_found = 0, wall_hit_x = 0, wall_hit_y = 0);
	if (data->fov.faces[1])
		next_h_touch_y--;
	while (next_h_touch_x >= 0 && next_h_touch_x < data->mlx_data.win_width
		&& next_h_touch_y >= 0 && next_h_touch_y < data->mlx_data.win_height)
	{
		if (wall_hitted(data, next_h_touch_x, next_h_touch_y))
		{
			(1) && (wall_hit_x = next_h_touch_x, wall_hit_y = next_h_touch_y);
			h_wall_found = 1;
			draw_line(data,create_line(data->player.x, data->player.y,
				data->player.x + wall_hit_x, data->player.y + wall_hit_y), data->player.body_color);
			t_line	line;
			line.x1 = data->player.x + data->player.player_head;
			line.y1 = data->player.y;
			line.x2 = line.x1 + wall_hit_x;
			line.y2 = line.y1 + wall_hit_y;
			// draw_line(data, line, data->player.line_color);
			break ;
		}
		else
		{
			next_h_touch_x += data->fov.h_x_step;
			next_h_touch_y += data->fov.h_y_step;
		}
	}
}

void	cast_ray(t_data *data, double ray_angle, int col)
{
	(void)col;
	init_ray(data, ray_angle);
	detect_h_wall(data);
}

void	cast_rays(t_data *data)
{
	double	ray_angle;
	int		i;

	init_fov(data);
	ray_angle = data->player.rotation_angle - (data->fov.fov_angle / 2);
	i = 0;
	while (i < 1)
	{
		cast_ray(data, ray_angle, i);
		ray_angle += data->fov.fov_angle / data->fov.nbr_rays;
		// t_line	line;
		// line.x1 = data->player.x + data->player.player_head;
		// line.y1 = data->player.y;
		// line.x2 = line.x1 + cos(ray_angle) * data->player.line_len;
		// line.y2 = line.y1 + sin(ray_angle) * data->player.line_len;
		// draw_line(data, line, data->player.line_color);
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