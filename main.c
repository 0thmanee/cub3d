/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:31:13 by obouchta          #+#    #+#             */
/*   Updated: 2024/08/23 20:52:03 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	loop_hook_func(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	cast_rays(data);
	walls_rendering(data, &data->wall);
}

void	ft_error(char *error_msg, t_free **collector)
{
	int	i;

	write (2, "cub3d: ", 7);
	i = 0;
	while (error_msg[i])
		write (2, &error_msg[i++], 1);
	ft_free_all(collector);
	exit(1);
}

void	parse_data(int ac, char *file, t_data *data, t_free **collector)
{
	int	map_fd;
	int	i;

	ft_memset(data->cub3d_map.infos_presence,
		0, sizeof(data->cub3d_map.infos_presence));
	if (ac != 2)
		ft_error(ARGS_ERR, collector);
	if (ft_strlen(file) < 4 || \
		ft_strcmp(ft_substr(file, ft_strlen(file) - 4, 4, collector), ".cub"))
		ft_error(EXTN_ERR, collector);
	map_fd = open(file, O_RDONLY);
	if (map_fd == -1)
		ft_error(FILE_ERR, collector);
	read_data(map_fd, data, collector);
	i = 0;
	check_infos_avalable(data->cub3d_map.infos_presence, 1, collector);
	fill_lines_end(data, collector);
	check_splited_map(data, collector);
	parse_map(data, collector);
	check_infos_avalable(data->cub3d_map.infos_presence, 0, collector);
}

int	main(int ac, char **av)
{
	t_data		data;
	t_free		*collector;
	t_ray		rays[WINDOW_WIDTH];

	if (WINDOW_HEIGHT <= 0 || WINDOW_WIDTH <= 0
		|| WINDOW_WIDTH > 2560 || WINDOW_HEIGHT > 1395)
	{
		write(2, WINDOW_ERROR, 26);
		exit(1);
	}
	collector = NULL;
	data.collector = &collector;
	parse_data(ac, av[1], &data, &collector);
	data.rays = rays;
	mlx_init_data(&data.mlx_data, data.cub3d_map, &collector);
	textures_init(&data, &data.wall);
	mlx_key_hook(data.mlx_data.mlx, &handle_key_hooks, &data);
	mlx_close_hook(data.mlx_data.mlx, &ft_close, &data);
	mlx_loop_hook(data.mlx_data.mlx, loop_hook_func, &data);
	mlx_loop(data.mlx_data.mlx);
	free_textures(&data.wall);
	mlx_terminate(data.mlx_data.mlx);
}
