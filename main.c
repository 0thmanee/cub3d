/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:31:13 by obouchta          #+#    #+#             */
/*   Updated: 2024/05/12 04:03:43 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main()
{
	t_data		data;
	t_free		*ptrs;

	ptrs = NULL;
	data = map_init(&ptrs);
	mlx_init_data(&data.mlx_data, data.cub3d_map, &ptrs);
	data.ptrs = &ptrs;
	mlx_key_hook(data.mlx_data.mlx, &handle_key_hooks, &data);
	mlx_loop_hook(data.mlx_data.mlx, loop_hook_func, &data);
	mlx_loop(data.mlx_data.mlx);
	mlx_terminate(data.mlx_data.mlx);
}