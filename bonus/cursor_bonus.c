/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:52:34 by yboutsli          #+#    #+#             */
/*   Updated: 2024/08/23 20:52:44 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	cursor_func(double xpos, double ypos, void *param)
{
	static double	last_xpos;
	static int		is_first_call = 1;
	double			diff;
	t_data			*data;

	(void)ypos;
	if (is_first_call)
	{
		last_xpos = xpos;
		is_first_call = 0;
	}
	diff = xpos - last_xpos;
	data = (t_data *)param;
	if (xpos > last_xpos && diff > MOUSE_TURN)
		data->player.rotation_angle += (diff / MOUSE_TURN) * (M_PI / 180);
	else if (xpos < last_xpos && diff < -MOUSE_TURN)
		data->player.rotation_angle += (diff / MOUSE_TURN) * (M_PI / 180);
	last_xpos = xpos;
	move_player(data, 0);
	data->player.turn_direction = 0;
}
