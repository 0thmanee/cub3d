/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:31:13 by obouchta          #+#    #+#             */
/*   Updated: 2024/05/08 01:19:41 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main()
{
	t_map	cub3d_map;
	t_mlx	mlx_data;
	t_data	data;
	t_free	*ptrs;

	ptrs = NULL;
	cub3d_map = parsing(&ptrs);
	mlx_init_data(&mlx_data, cub3d_map, &ptrs);
	data.mlx_data = &mlx_data;
	data.cub3d_map = &cub3d_map;
	// ray_casting(&data, &ptrs);
	mlx_key_hook(mlx_data.mlx, &handle_key_hooks, &data);
	mlx_loop_hook(mlx_data.mlx, loop_hook_func, &data);
	mlx_loop(mlx_data.mlx);
	mlx_terminate(mlx_data.mlx);
}