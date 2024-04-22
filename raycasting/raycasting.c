/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:49:57 by obouchta          #+#    #+#             */
/*   Updated: 2024/04/22 11:59:49 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_casting(t_map cub3d_map, t_free **ptrs)
{
	int	i;
	(void)ptrs;

	i = 0;
	while (i < cub3d_map.map_height)
	{
		printf("%s\n", cub3d_map.map[i]);
		i++;
	}
}