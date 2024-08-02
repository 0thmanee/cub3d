/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 09:34:44 by yasser03          #+#    #+#             */
/*   Updated: 2024/08/02 10:31:15 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

// width = height = 128
mlx_texture_t	*textures(t_data *data)
{
	uint32_t	*pixels;
	mlx_texture_t	*textures_img;

	textures_img = mlx_load_png("./textures/wall.png");
	// printf("width = %d | height = %d\n", textures_img->width, textures_img->height);
	if (!textures_img)
		(mlx_terminate(data->mlx_data.mlx), ft_error("mlx error\n", data->ptrs));
	return (textures_img);
}

// void	textures_img(t_data *data, t_mlx *mlx_data , uint32_t *textures)
// {
// 	int			x;
// 	int			y;
// 	uint32_t	color;
// 	mlx_data->textures_img = mlx_new_image(mlx_data->mlx, TEX_WIDTH, TEX_HEIGHT);
// 	if (!mlx_data->img || (mlx_image_to_window(mlx_data->mlx,
// 				mlx_data->textures_img, 0, 0) < 0))
// 		(mlx_terminate(mlx_data->mlx), ft_error("mlx error\n", data->ptrs));
// 	x = -1;
// 	while (++x < TEX_WIDTH)
// 	{
// 		y = -1;
// 		while (++y < TEX_HEIGHT)
// 		{
// 			color = textures[(TEX_WIDTH * y) + x];
// 			mlx_put_pixel(mlx_data->textures_img, x, y, color);
// 		}
// 	}	
// }