/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 09:34:44 by yasser03          #+#    #+#             */
/*   Updated: 2024/07/31 21:05:01 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"


uint32_t	*textures(t_data *data)
{
	uint32_t	*wall_texture;
	int			x;
	int			y;

	wall_texture = ft_malloc(data->ptrs, sizeof(uint32_t) * TEX_HEIGHT * TEX_WIDTH);
	x = -1;
	while (++x < TEX_WIDTH)
	{
		y = -1;
		while (++y < TEX_HEIGHT)
		{
			if  (x % 4 && y % 4)
				wall_texture[(TEX_WIDTH * y) + x] = 0xFF00FF;
			else
				wall_texture[(TEX_WIDTH * y) + x] = 0x000000;
		}
	}
	return (wall_texture);
}

void	textures_img(t_data *data, t_mlx *mlx_data , uint32_t *textures)
{
	int			x;
	int			y;
	uint32_t	color;
	mlx_data->textures_img = mlx_new_image(mlx_data->mlx, TEX_WIDTH, TEX_HEIGHT);
	if (!mlx_data->img || (mlx_image_to_window(mlx_data->mlx,
				mlx_data->textures_img, 0, 0) < 0))
		(mlx_terminate(mlx_data->mlx), ft_error("mlx error\n", data->ptrs));
	x = -1;
	while (++x < TEX_WIDTH)
	{
		y = -1;
		while (++y < TEX_HEIGHT)
		{
			color = textures[(TEX_WIDTH * y) + x];
			mlx_put_pixel(mlx_data->textures_img, x, y, color);
		}
	}	
}