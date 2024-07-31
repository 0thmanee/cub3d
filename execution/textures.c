/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasser03 <yasser03@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 09:34:44 by yasser03          #+#    #+#             */
/*   Updated: 2024/07/31 11:13:28 by yasser03         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"




uint32_t	*textures(t_data *data)
{
	uint32_t	*wall_texture;
	int			i;
	int			j;

	wall_texture = ft_malloc(data->ptrs, sizeof(uint32_t) * TEX_HEIGHT * TEX_WIDTH);
	j = -1;
	while (++j < TEX_HEIGHT)
	{
		i = -1;
		while (++i < TEX_WIDTH)
		{
			if  (i % 8 && j % 8)
				wall_texture[(TEX_WIDTH * i) + j] = 0xFF0000FF;
			else
				wall_texture[(TEX_WIDTH * i) + j] = 0xFF000000;
			
		}
	}
	return (wall_texture);
}