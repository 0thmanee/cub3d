/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:44:09 by obouchta          #+#    #+#             */
/*   Updated: 2024/08/02 19:49:32 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	wall_hitted(t_data *data, int x, int y)
{
	if (data->cub3d_map.map[(y / data->cub3d_map.tile_size)]
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
				mlx_put_pixel(data->mlx_data.img, MINI_MAP_SCALE * j, MINI_MAP_SCALE * i, color);
			j++;
		}
		i++;
	}
}

void draw_line(t_data *data, t_line line, int color)
{
	float dx = abs(line.x2 - line.x1);
	float dy = abs(line.y2 - line.y1);
	float sx = (line.x1 < line.x2) ? 1 : -1;
	float sy = (line.y1 < line.y2) ? 1 : -1;
	float err = dx - dy;

	while (line.x1 != line.x2 || line.y1 != line.y2)
	{
		if (line.y1 >= 0 && line.y1 < data->mlx_data.win_height
			&& line.x1 >= 0 && line.x1 < data->mlx_data.win_width)
			mlx_put_pixel(data->mlx_data.img, MINI_MAP_SCALE * line.x1, MINI_MAP_SCALE * line.y1, color);
		float err2 = 2 * err;
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
	draw_line(data, line, get_rgb(0, 0, 0));
}

void	init_faces_dirs(t_ray *ray)
{
	ray->faces[0] = ray->ray_angle > 0
		&& ray->ray_angle < M_PI;
	ray->faces[1] = !ray->faces[0];
	ray->faces[2] = ray->ray_angle < 0.5 * M_PI
		|| ray->ray_angle > 1.5 * M_PI;
	ray->faces[3] = !ray->faces[2];
}

void	init_h_ray(t_data *data, t_ray *ray)
{
	ray->h_y_interc = floor(data->player.y / data->cub3d_map.tile_size)
		* data->cub3d_map.tile_size;
	if (ray->faces[0])
		ray->h_y_interc += data->cub3d_map.tile_size;
	ray->h_x_interc = data->player.x
		+ (ray->h_y_interc - data->player.y) / tan(ray->ray_angle);
	ray->h_y_step = data->cub3d_map.tile_size;
	if (ray->faces[1])
		ray->h_y_step *= -1;
	ray->h_x_step = data->cub3d_map.tile_size / tan(ray->ray_angle);
	if (ray->h_x_step > 0 && ray->faces[3])
		ray->h_x_step *= -1;
	if (ray->h_x_step < 0 && ray->faces[2])
		ray->h_x_step *= -1;
}

void	init_v_ray(t_data *data, t_ray *ray)
{
	ray->v_x_interc = floor(data->player.x / data->cub3d_map.tile_size)
		* data->cub3d_map.tile_size;
	if (ray->faces[2])
		ray->v_x_interc += data->cub3d_map.tile_size;
	ray->v_y_interc = data->player.y
		+ (ray->v_x_interc - data->player.x) * tan(ray->ray_angle);
	ray->v_x_step = data->cub3d_map.tile_size;
	if (ray->faces[3])
		ray->v_x_step *= -1;
	ray->v_y_step = data->cub3d_map.tile_size * tan(ray->ray_angle);
	if (ray->v_y_step > 0 && ray->faces[1])
		ray->v_y_step *= -1;
	if (ray->v_y_step < 0 && ray->faces[0])
		ray->v_y_step *= -1;
}

void	detect_h_wall(t_data *data, t_ray *ray)
{
	float	next_h_hit_x;
	float	next_h_hit_y;

	next_h_hit_x = ray->h_x_interc;
	next_h_hit_y = ray->h_y_interc;
	ray->h_wall_hit_x = 0;
	ray->h_wall_hit_y = 0;
	if (ray->faces[1])
		next_h_hit_y--;
	while (next_h_hit_x >= 0 && next_h_hit_x < data->mlx_data.win_width
		&& next_h_hit_y >= 0 && next_h_hit_y < data->mlx_data.win_height)
	{
		if (wall_hitted(data, next_h_hit_x, next_h_hit_y))
		{
			ray->h_wall_hit_x = next_h_hit_x;
			 ray->h_wall_hit_y = next_h_hit_y;
			break ;
		}
		next_h_hit_x += ray->h_x_step;
		next_h_hit_y += ray->h_y_step;
	}
}

void	detect_v_wall(t_data *data, t_ray *ray)
{
	float	next_v_hit_x;
	float	next_v_hit_y;

	next_v_hit_x = ray->v_x_interc;
	next_v_hit_y = ray->v_y_interc;
	ray->v_wall_hit_x = 0;
	ray->v_wall_hit_y = 0;
	if (ray->faces[3])
		next_v_hit_x--;
	while (next_v_hit_x >= 0 && next_v_hit_x < data->mlx_data.win_width
		&& next_v_hit_y >= 0 && next_v_hit_y < data->mlx_data.win_height)
	{
		if (wall_hitted(data, next_v_hit_x, next_v_hit_y))
		{
			(1) && (ray->v_wall_hit_x = next_v_hit_x, ray->v_wall_hit_y = next_v_hit_y);
			break ;
		}
		next_v_hit_x += ray->v_x_step;
		next_v_hit_y += ray->v_y_step;
	}
}

void	cast_ray(t_data *data, t_ray *ray)
{
	if (ray->ray_angle)
		ray->ray_angle = fmod(ray->ray_angle, 2 * M_PI);
	if (ray->ray_angle < 0)
		ray->ray_angle = 2 * M_PI + ray->ray_angle;
	init_faces_dirs(ray);
	init_h_ray(data, ray);
	detect_h_wall(data, ray);
	init_v_ray(data, ray);
	detect_v_wall(data, ray);
	ray->h_distance = sqrt(pow(ray->h_wall_hit_x - data->player.x, 2)
		+ pow(ray->h_wall_hit_y - data->player.y, 2));
	ray->v_distance = sqrt(pow(ray->v_wall_hit_x - data->player.x, 2)
		+ pow(ray->v_wall_hit_y - data->player.y, 2));
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
	draw_line(data, create_line(data->player.x + data->player.player_head, data->player.y,
			ray->wall_hit_x, ray->wall_hit_y), data->player.body_color);
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

void	draw_square(t_data *data, int x, int y, int color)
{
	int		i;
	int		j;
	int		i_side;
	int		j_side;

	i_side = x * data->cub3d_map.tile_size;
	j_side = y * data->cub3d_map.tile_size;
	i = i_side - 1;
	while (++i < i_side + data->cub3d_map.tile_size)
	{
		j = j_side;
		while (j < j_side + data->cub3d_map.tile_size)
		{
			if (i >= 0 && i < data->mlx_data.win_height && j >= 0 && j < data->mlx_data.win_width)
				mlx_put_pixel(data->mlx_data.img, MINI_MAP_SCALE * j, MINI_MAP_SCALE * i, color);
			j++;
		}
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
