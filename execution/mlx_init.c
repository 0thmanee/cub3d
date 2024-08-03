/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:45:05 by obouchta          #+#    #+#             */
/*   Updated: 2024/08/02 21:31:04 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// const char* mlx_strerror(mlx_errno_t val);

void	mlx_init_data(t_mlx *mlx_data, t_map cub3d_map, t_free **collector)
{
	mlx_data->win_height = cub3d_map.map_height * cub3d_map.tile_size;
	mlx_data->win_width = cub3d_map.map_width * cub3d_map.tile_size;
	mlx_data->mlx = mlx_init(mlx_data->win_width, mlx_data->win_height,
			"CUB3D", false);
	if (!mlx_data->mlx)
		(mlx_terminate(mlx_data->mlx), ft_error("mlx error\n", collector));
	mlx_data->img = mlx_new_image(mlx_data->mlx, mlx_data->win_width,
			mlx_data->win_height);
	if (!mlx_data->img || (mlx_image_to_window(mlx_data->mlx,
				mlx_data->img, 0, 0) < 0))
		(mlx_terminate(mlx_data->mlx), ft_error("mlx error\n", collector));
}
