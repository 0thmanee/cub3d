/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 19:27:05 by obouchta          #+#    #+#             */
/*   Updated: 2024/08/17 18:34:05 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	move_player_utils(t_data *data, t_player_moves *move)
{
	data->player.rotation_angle = fmod(data->player.rotation_angle, 2.0 * M_PI);
	if (data->player.rotation_angle < 0)
		data->player.rotation_angle += M_PI * 2;
	if (data->player.s_direction == 0)
	{
		move->new_x += (data->player.walk_direction
				* data->player.move_speed * cos(data->player.rotation_angle));
		move->new_y += (data->player.walk_direction
				* data->player.move_speed * sin(data->player.rotation_angle));
	}
	else
	{
		move->new_x += (data->player.s_direction * data->player.move_speed
				* cos(data->player.rotation_angle + (M_PI / 2)));
		move->new_y += (data->player.s_direction * data->player.move_speed
				* sin(data->player.rotation_angle + (M_PI / 2)));
	}
}

static void	move_player_init(t_data *data, t_player_moves *move)
{
	move->new_x = data->player.x;
	move->new_y = data->player.y;
	data->player.rotation_angle += (data->player.turn_direction
			* data->player.rotation_speed);
}

void	move_player(t_data *data, int key)
{
	t_player_moves	move;

	(void)key;
	move_player_init(data, &move);
	move_player_utils(data, &move);
	if (!wall_hitted2(data, move.new_x, move.new_y))
	{
		data->player.x = move.new_x;
		data->player.y = move.new_y;
	}
}
