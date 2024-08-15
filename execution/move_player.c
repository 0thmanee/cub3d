/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 19:27:05 by obouchta          #+#    #+#             */
/*   Updated: 2024/08/15 09:55:36 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	move_player_utils(t_data *data, t_player_moves *move)
{
	if (data->player.s_direction == 0)
	{
		move->new_x += (data->player.walk_direction
				* data->player.move_speed * cos(data->player.rotation_angle));
		move->new_x_size += (data->player.walk_direction
				* data->player.move_speed * cos(data->player.rotation_angle));
		move->new_y += (data->player.walk_direction
				* data->player.move_speed * sin(data->player.rotation_angle));
		move->new_y_size += (data->player.walk_direction
				* data->player.move_speed * sin(data->player.rotation_angle));
	}
	else
	{
		move->new_x += (data->player.s_direction * data->player.move_speed
				* cos(data->player.rotation_angle + (M_PI / 2)));
		move->new_x_size += (data->player.s_direction * data->player.move_speed
				* cos(data->player.rotation_angle + (M_PI / 2)));
		move->new_y += (data->player.s_direction * data->player.move_speed
				* sin(data->player.rotation_angle + (M_PI / 2)));
		move->new_y_size += (data->player.s_direction * data->player.move_speed
				* sin(data->player.rotation_angle + (M_PI / 2)));
	}
}

static void	move_player_init(t_data *data, t_player_moves *move)
{
	move->new_x = data->player.x;
	move->new_y = data->player.y;
	move->new_x_size = data->player.x + data->player.player_size;
	move->new_y_size = data->player.y + data->player.player_size;
	data->player.rotation_angle += (data->player.turn_direction
			* data->player.rotation_speed);
}

void	move_player(t_data *data, int key)
{
	t_player_moves	move;

	(void)key;
	move_player_init(data, &move);
	move_player_utils(data, &move);
	if (!wall_hitted(data, move.new_x, move.new_y)
		&& !wall_hitted(data, move.new_x_size, move.new_y_size))
	{
		data->player.x = move.new_x;
		data->player.y = move.new_y;
	}
}
