/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 19:27:05 by obouchta          #+#    #+#             */
/*   Updated: 2024/05/08 01:11:05 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_up(t_data *data)
{
	if (data->cub3d_map->player.x - 1 < 0
		|| data->cub3d_map->map[data->cub3d_map->player.x - 1][data->cub3d_map->player.y] == '1')
		return ;
	data->cub3d_map->map[data->cub3d_map->player.x][data->cub3d_map->player.y] = '0';
	data->cub3d_map->player.x--;
	data->cub3d_map->map[data->cub3d_map->player.x][data->cub3d_map->player.y] = 'P';
	// draw_2d_map(data);
}

void	move_down(t_data *data)
{
	if (data->cub3d_map->player.x + 1 >= data->cub3d_map->map_height
		|| data->cub3d_map->map[data->cub3d_map->player.x + 1][data->cub3d_map->player.y] == '1')
		return ;
	data->cub3d_map->map[data->cub3d_map->player.x][data->cub3d_map->player.y] = '0';
	data->cub3d_map->player.x++;
	data->cub3d_map->map[data->cub3d_map->player.x][data->cub3d_map->player.y] = 'P';
	// draw_2d_map(data);
}

void	move_left(t_data *data)
{
	if (data->cub3d_map->player.y - 1 < 0
		|| data->cub3d_map->map[data->cub3d_map->player.x][data->cub3d_map->player.y - 1] == '1')
		return ;
	data->cub3d_map->map[data->cub3d_map->player.x][data->cub3d_map->player.y] = '0';
	data->cub3d_map->player.y--;
	data->cub3d_map->map[data->cub3d_map->player.x][data->cub3d_map->player.y] = 'P';
	// draw_2d_map(data);
}

void	move_right(t_data *data)
{
	if (data->cub3d_map->player.y + 1 >= data->cub3d_map->map_width
		|| data->cub3d_map->map[data->cub3d_map->player.x][data->cub3d_map->player.y + 1] == '1')
		return ;
	data->cub3d_map->map[data->cub3d_map->player.x][data->cub3d_map->player.y] = '0';
	data->cub3d_map->player.y++;
	data->cub3d_map->map[data->cub3d_map->player.x][data->cub3d_map->player.y] = 'P';
	// draw_2d_map(data);
}

void	move_player(t_data *data, int key)
{
	if (key == MLX_KEY_UP)
		move_up(data);
	if (key == MLX_KEY_DOWN)
		move_down(data);
	if (key == MLX_KEY_LEFT)
		move_left(data);
	if (key == MLX_KEY_RIGHT)
		move_right(data);
}