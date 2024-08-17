/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 09:34:44 by yasser03          #+#    #+#             */
/*   Updated: 2024/08/17 18:54:06 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	mlx_err(t_data *data)
{
	mlx_terminate(data->mlx_data.mlx);
	ft_error("mlx error\n", data->collector);
	exit (1);
}

mlx_texture_t	*textures(t_data *data)
{
	mlx_texture_t	*textures_img;

	textures_img = mlx_load_png("./textures/wall.png");
	if (!textures_img)
		mlx_err(data);
	return (textures_img);
}

void	textures_init(t_data *data, t_wall *wall)
{
	wall->n_texture = mlx_load_png(data->cub3d_map.no_texture);
	if (!wall->n_texture)
		mlx_err(data);
	wall->s_texture = mlx_load_png(data->cub3d_map.so_texture);
	if (!wall->s_texture)
		mlx_err(data);
	wall->e_texture = mlx_load_png(data->cub3d_map.ea_texture);
	if (!wall->e_texture)
		mlx_err(data);
	wall->w_texture = mlx_load_png(data->cub3d_map.we_texture);
	if (!wall->w_texture)
		mlx_err(data);
}

void	free_textures(t_wall *wall)
{
	if (wall->n_texture)
		mlx_delete_texture(wall->n_texture);
	if (wall->s_texture)
		mlx_delete_texture(wall->s_texture);
	if (wall->e_texture)
		mlx_delete_texture(wall->e_texture);
	if (wall->w_texture)
		mlx_delete_texture(wall->w_texture);
}
