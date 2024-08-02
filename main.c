/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:31:13 by obouchta          #+#    #+#             */
/*   Updated: 2024/08/02 18:35:11 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	ft_error(char *error_msg, t_free **ptrs)
{
	int	i;

	write (2, "cub3d: ", 7);
	i = 0;
	while (error_msg[i])
		write (2, &error_msg[i++], 1);
	ft_free_all(ptrs);
	exit(1);
}

int main(int ac, char **av)
{
	t_data		data;
	t_free		*ptrs;
	t_ray	

	(void)ac;
	(void)av;
	ptrs = NULL;
	// parse_map(ac, av[1], &ptrs);
	data = map_init(&ptrs);
	mlx_init_data(&data.mlx_data, data.cub3d_map, &ptrs);
	data.ptrs = &ptrs;
	mlx_key_hook(data.mlx_data.mlx, &handle_key_hooks, &data);
	mlx_loop_hook(data.mlx_data.mlx, loop_hook_func, &data);
	mlx_loop(data.mlx_data.mlx);
	mlx_terminate(data.mlx_data.mlx);
}