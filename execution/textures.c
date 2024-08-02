/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 09:34:44 by yasser03          #+#    #+#             */
/*   Updated: 2024/08/02 17:32:14 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

mlx_texture_t	*textures(t_data *data)
{
	mlx_texture_t	*textures_img;

	textures_img = mlx_load_png("./textures/wall.png");
	if (!textures_img)
		(mlx_terminate(data->mlx_data.mlx), ft_error("mlx error\n", data->ptrs), exit(1));
	return (textures_img);
}
