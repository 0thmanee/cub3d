/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:44:09 by obouchta          #+#    #+#             */
/*   Updated: 2024/05/09 22:29:47 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_view_lines(t_player *player, t_fov_rad *fov_rad)
{
	fov_rad->direction = player->direction * M_PI / 180.0;
	fov_rad->fov = player->fov * M_PI / 180.0;
	fov_rad->left_angle = fov_rad->direction - fov_rad->fov / 2.0;
	fov_rad->right_angle = fov_rad->direction + fov_rad->fov / 2.0;
	fov_rad->left_x = player->x + player->distance * cos(fov_rad->left_angle);
	fov_rad->left_y = player->y + player->distance * sin(fov_rad->left_angle);
	fov_rad->right_x = player->x + player->distance * cos(fov_rad->right_angle);
	fov_rad->right_y = player->y + player->distance * sin(fov_rad->right_angle);
}

void	draw_player(t_data *data)
{
	int		i;
	int		j;
	int		color;

	color = get_rgb(255, 151, 51);
	i = data->cub3d_map->player.y;
	while (i < data->cub3d_map->player.y + data->cub3d_map->tile_val / 4)
	{
		j = data->cub3d_map->player.x;
		while (j < data->cub3d_map->player.x + data->cub3d_map->tile_val / 4)
		{
			if (i >= 0 && i < data->mlx_data->win_height
				&& j >= 0 && j < data->mlx_data->win_width)
				mlx_put_pixel(data->mlx_data->img, j, i, color);
			j++;
		}
		i++;
	}
}

void move_player(t_data *data, int key)
{
	int new_x;
	int new_y;
	int	size_x;
	int	size_y;

	(1) && (new_x = data->cub3d_map->player.x, new_y = data->cub3d_map->player.y);
	(1) && (size_x = 0, size_y = 0);
	if (key == MLX_KEY_UP)
		new_y--;
	else if (key == MLX_KEY_DOWN)
		(1) && (new_y++, size_y = data->cub3d_map->player.player_size);
	else if (key == MLX_KEY_LEFT)
		new_x--;
	else if (key == MLX_KEY_RIGHT)
		(1) && (new_x++, size_x = data->cub3d_map->player.player_size);
	if (new_x + size_x >= 0 && new_x + size_x < data->mlx_data->win_width &&
		new_y + size_y >= 0 && new_y + size_y < data->mlx_data->win_height &&
		data->cub3d_map->map[(new_y + size_y) / data->cub3d_map->tile_val]
		[(new_x + size_x) / data->cub3d_map->tile_val] != '1')
		(1) && (data->cub3d_map->player.x = new_x, data->cub3d_map->player.y = new_y);
}

void	draw_square(t_data *data, int x, int y, int color)
{
	int		i;
	int		j;
	int		i_side;
	int		j_side;

	(1) && (i_side = x * data->cub3d_map->tile_val,
		j_side = y * data->cub3d_map->tile_val,	i = i_side - 1);
	while (++i < i_side + data->cub3d_map->tile_val)
	{
		j = j_side;
		while (j < j_side + data->cub3d_map->tile_val)
			if (i >= 0 && i < data->mlx_data->win_height
				&& j >= 0 && j < data->mlx_data->win_width)
				mlx_put_pixel(data->mlx_data->img, j++, i, color);
	}
}

void	draw_2d_map(t_data *data)
{
	int		i;
	int		j;
	i = 0;
	while (i < data->cub3d_map->map_height)
	{
		j = 0;
		while (j < data->cub3d_map->map_width)
		{
			if (data->cub3d_map->map[i][j] == '1')
				draw_square(data, i, j, get_rgb(0, 0, 0));
			else
				draw_square(data, i, j, get_rgb(255, 255, 255));
			j++;
		}
		i++;
	}
}