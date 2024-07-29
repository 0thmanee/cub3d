/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_projection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasser03 <yasser03@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:27:46 by yboutsli          #+#    #+#             */
/*   Updated: 2024/07/29 17:20:50 by yasser03         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void    wall_projection(t_data *data)
{
    double   distanceProjPlane;
    double   wallStripHeiht;

    distanceProjPlane = (WINDOW_WIDTH / 2) / tan(data->fov.fov_angle);
    wallStripHeiht = (data->cub3d_map.tile_size / data->rays[0]) * distanceProjPlane;
}