/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_projection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:27:46 by yboutsli          #+#    #+#             */
/*   Updated: 2024/07/26 21:24:32 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void    wall_projection(t_data *data)
{
    double   distanceProjPlane;
    double   wallStripHeiht;

    distanceProjPlane = (WINDOW_WIDTH / 2) / tan(data->fov.fov_angle);
    // wallStripHeiht = (data->cub3d_map.tile_size / data->ray[i])
}