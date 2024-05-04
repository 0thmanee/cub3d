/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:49:57 by obouchta          #+#    #+#             */
/*   Updated: 2024/05/04 18:12:54 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(t_mlx *mlx_data, t_free **ptrs)
{
	printf("Error Occured\n");
	if (mlx_data->mlx)
		mlx_terminate(mlx_data->mlx);
	ft_free_all(ptrs);
	exit(1);
}

void	mlx_init_data(t_mlx *mlx_data, t_free **ptrs)
{
	mlx_data->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", false);
	if (!mlx_data->mlx)
		ft_error(mlx_data, ptrs);
	mlx_data->img = mlx_new_image(mlx_data->mlx, WIDTH, HEIGHT);
	if (!mlx_data->img || (mlx_image_to_window(mlx_data->mlx,
		mlx_data->img, 0, 0) < 0))
		ft_error(mlx_data, ptrs);
}

void	ray_casting(t_map cub3d_map, t_mlx *mlx_data, t_free **ptrs)
{
	int		i;
	int		j;

	mlx_init_data(mlx_data, ptrs);
	i = 0;
	while (i < cub3d_map.map_height)
	{
		j = 0;
		while (j < ft_strlen(cub3d_map.map[i]))
		{
			if (cub3d_map.map[i][j] == 1)
				// mlx_put_pixel(mlx_data->img, i, j, 0xfff);
			else
				// mlx_put_pixel(mlx_data->img, i, j, 0xfff);
			j++;
		}
		i++;
	}
}