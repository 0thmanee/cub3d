/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 09:34:44 by yasser03          #+#    #+#             */
/*   Updated: 2024/08/04 01:01:43 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cub3d.h"

mlx_texture_t	*textures(t_data *data)
{
	mlx_texture_t	*textures_img;

	textures_img = mlx_load_png("./textures/wall.png");
	if (!textures_img)
		(mlx_terminate(data->mlx_data.mlx), ft_error("mlx error\n", data->collector), exit(1));
	return (textures_img);
}
void	textures_init(t_data *data, t_wall *wall)
{
	//todo  add free_textures
	wall->N_texture = mlx_load_png(data->cub3d_map.no_texture);
	if (!wall->N_texture)
		(mlx_terminate(data->mlx_data.mlx), ft_error("mlx error\n", data->collector), exit(1));
	wall->S_texture = mlx_load_png(data->cub3d_map.so_texture);
	if (!wall->S_texture)
		(mlx_terminate(data->mlx_data.mlx), ft_error("mlx error\n", data->collector), exit(1));
	wall->E_texture = mlx_load_png(data->cub3d_map.ea_texture);
	if (!wall->E_texture)
		(mlx_terminate(data->mlx_data.mlx), ft_error("mlx error\n", data->collector), exit(1));
	wall->W_texture = mlx_load_png(data->cub3d_map.we_texture);
	if (!wall->W_texture)
		(mlx_terminate(data->mlx_data.mlx), ft_error("mlx error\n", data->collector), exit(1));
	
}

void	free_textures(t_wall *wall)
{
	if (wall->N_texture)
		mlx_delete_texture(wall->N_texture);
	if (wall->S_texture)
		mlx_delete_texture(wall->S_texture);
	if (wall->E_texture)
		mlx_delete_texture(wall->E_texture);
	if (wall->W_texture)
		mlx_delete_texture(wall->W_texture);
}