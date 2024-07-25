/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:51:20 by obouchta          #+#    #+#             */
/*   Updated: 2024/05/10 05:16:28 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_map(int ac, char *file, t_free **ptrs)
{
	int	map_fd;

	if (ac != 2)
		ft_error("invalid number of arguments\n", ptrs);
	if (ft_strlen(file) < 4 || \
		ft_strcmp(ft_substr(file, ft_strlen(file) - 4, 4, ptrs), ".cub"))
		ft_error("invalid file extension\n", ptrs);
	map_fd = open(file, O_RDONLY);
	if (map_fd == -1)
		ft_error("error opening the file\n", ptrs);
	
}
