/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:49:57 by obouchta          #+#    #+#             */
/*   Updated: 2024/05/05 14:51:47 by obouchta         ###   ########.fr       */
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

void	mlx_init_data(t_mlx *mlx_data, t_map cub3d_map, t_free **ptrs)
{
	mlx_data->win_height = cub3d_map.map_height * 32;
	mlx_data->win_width = cub3d_map.map_width * 32;
	mlx_data->mlx = mlx_init(mlx_data->win_width, mlx_data->win_height,
					"CUB3D", false);
	if (!mlx_data->mlx)
		ft_error(mlx_data, ptrs);
	mlx_data->img = mlx_new_image(mlx_data->mlx, mlx_data->win_width,
					mlx_data->win_height);
	if (!mlx_data->img || (mlx_image_to_window(mlx_data->mlx,
		mlx_data->img, 0, 0) < 0))
		ft_error(mlx_data, ptrs);
}

void	draw_2d_wall(t_mlx *mlx_data, t_map cub3d_map, int i, int j)
{
	int		k;
	int		l;
	int		i_side;
	int		j_side;
	int		color;

	(1) && (i_side = i * 32, j_side = j * 32, k = i_side);
	if (cub3d_map.map[i][j] == 'P')
		color = get_rgb(255, 151, 51);
	else if (cub3d_map.map[i][j] == '1')
		color = get_rgb(0, 0, 0);
	else
		color = get_rgb(255, 255, 255);
	while (k < i_side + 32)
	{
		l = j_side;
		while (l < j_side + 32)
		{
			if (k >= 0 && k < mlx_data->win_height && l >= 0 && l < mlx_data->win_width)
				mlx_put_pixel(mlx_data->img, l, k, color);
			l++;
		}
		k++;
	}
}

void	ray_casting(t_map cub3d_map, t_mlx *mlx_data, t_free **ptrs)
{
	int		i;
	int		j;

	mlx_init_data(mlx_data, cub3d_map, ptrs);
	i = 0;
	while (i < cub3d_map.map_height)
	{
		j = 0;
		while (j < cub3d_map.map_width)
		{
			draw_2d_wall(mlx_data, cub3d_map, i, j);
			j++;
		}
		i++;
	}
}
