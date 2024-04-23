/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:49:57 by obouchta          #+#    #+#             */
/*   Updated: 2024/04/22 21:11:49 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mlx_init_data(t_mlx *mlx_data, t_free **ptrs)
{
	mlx_data->mlx_ptr = mlx_init(WIDTH, HEIGHT, "CUB3D", false);
	if (!mlx_data->mlx_ptr)
		(ft_free_all(ptrs), exit(1));
	mlx_data->img_ptr = mlx_new_image(mlx_data->mlx_ptr, WIDTH, HEIGHT);
	if (!mlx_data->img_ptr || (mlx_image_to_window(mlx_data->mlx_ptr,
		mlx_data->img_ptr, 0, 0) < 0))
		(ft_free_all(ptrs), exit(1));
}

void	ray_casting(t_map cub3d_map, t_mlx *mlx_data, t_free **ptrs)
{
	int		i;

	mlx_init_data(mlx_data, ptrs);
	i = 0;
	while (i < cub3d_map.map_height)
	{
		printf("%s\n", cub3d_map.map[i]);
		i++;
	}
}