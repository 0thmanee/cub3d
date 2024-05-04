/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:49:57 by obouchta          #+#    #+#             */
/*   Updated: 2024/05/04 22:53:09 by obouchta         ###   ########.fr       */
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

void	draw_walls(t_mlx *mlx_data, t_map cub3d_map, int x, int y)
{
	int		i;
	int		x_side;
	int		y_side;
	int		color;

	(1) && (x_side = y * 32, y_side = x * 32, i = y_side);
	while (i < y_side + 32)
	{
		if (cub3d_map.map[x][y] == 'P')
			color = 0xFF000000;
		else if (cub3d_map.map[x][y] == '1')
			color = 0x00000000;
		else
			color = 0xFFFFFFFF;
		if (i >= 0 && i < mlx_data->win_height)
			ft_memset(mlx_data->pxls + i , color, 32);
		i++;
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
		printf("%s\n", cub3d_map.map[i]);
		j = 0;
		while (j < ft_strlen(cub3d_map.map[i]))
		{
			draw_walls(mlx_data, cub3d_map, i, j);
			j++;
		}
		i++;
	}
}
