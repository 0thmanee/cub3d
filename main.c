/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:31:13 by obouchta          #+#    #+#             */
/*   Updated: 2024/05/04 18:07:45 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main()
{
	t_map	cub3d_map;
	t_mlx	mlx_data;
	t_free	*ptrs;

	cub3d_map = parsing(&ptrs);
	ptrs = NULL;
	ray_casting(cub3d_map, &mlx_data, &ptrs);
	mlx_loop(mlx_data.mlx);
	mlx_terminate(mlx_data.mlx);
}