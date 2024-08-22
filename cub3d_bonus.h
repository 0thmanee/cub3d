/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:27:58 by yboutsli          #+#    #+#             */
/*   Updated: 2024/08/22 18:07:20 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H

# define CUB3D_BONUS_H

# include "cub3d.h"

# define M_MAP_WIDTH 200
# define M_MAP_HEIGHT 200
# define PLAYER_SIZE 4

typedef struct s_mini_map
{
	float	center_x;
	float	center_y;
	int		map_x;
	int		map_y;
	int		x;
	int		y;
	int		diffx;
	int		diffy;
}	t_mini_map;

void	cursor_func(double xpos, double ypos, void *param);
void	draw_mini_map(t_data *data);

#endif