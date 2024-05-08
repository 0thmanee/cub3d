/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:49:57 by obouchta          #+#    #+#             */
/*   Updated: 2024/05/08 03:34:23 by obouchta         ###   ########.fr       */
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
	mlx_data->win_height = cub3d_map.map_height * cub3d_map.tile_val;
	mlx_data->win_width = cub3d_map.map_width * cub3d_map.tile_val;
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

void	draw_player(t_data *data)
{
	int		i;
	int		j;
	int		color;

	color = get_rgb(255, 151, 51);
	i = data->cub3d_map->player.y;
	while (i < data->cub3d_map->player.y + data->cub3d_map->tile_val / 4)
	{
		j = data->cub3d_map->player.x;
		while (j < data->cub3d_map->player.x + data->cub3d_map->tile_val / 4)
		{
			if (i >= 0 && i < data->mlx_data->win_height
				&& j >= 0 && j < data->mlx_data->win_width)
				mlx_put_pixel(data->mlx_data->img, j, i, color);
			j++;
		}
		i++;
	}
}

void	draw_square(t_data *data, int x, int y, int color)
{
	int		i;
	int		j;
	int		i_side;
	int		j_side;

	(1) && (i_side = x * data->cub3d_map->tile_val,
		j_side = y * data->cub3d_map->tile_val,	i = i_side - 1);
	while (++i < i_side + data->cub3d_map->tile_val)
	{
		j = j_side;
		while (j < j_side + data->cub3d_map->tile_val)
			if (i >= 0 && i < data->mlx_data->win_height
				&& j >= 0 && j < data->mlx_data->win_width)
				mlx_put_pixel(data->mlx_data->img, j++, i, color);
	}
}

void	draw_2d_map(t_data *data)
{
	int		i;
	int		j;
	i = 0;
	while (i < data->cub3d_map->map_height)
	{
		j = 0;
		while (j < data->cub3d_map->map_width)
		{
			if (data->cub3d_map->map[i][j] == '1')
				draw_square(data, i, j, get_rgb(0, 0, 0));
			else
				draw_square(data, i, j, get_rgb(255, 255, 255));
			j++;
		}
		i++;
	}
}

void	ray_casting(t_data *data, t_free **ptrs)
{
	(void)ptrs;
	(void)data;
}
