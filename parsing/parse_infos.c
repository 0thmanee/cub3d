/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_infos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 21:18:23 by obouchta          #+#    #+#             */
/*   Updated: 2024/08/17 18:54:00 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	parse_texture(char *line, t_data *data,
			int direction, t_free **collector)
{
	int		i;
	int		fd;
	char	*texture_path;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (data->cub3d_map.infos_presence[direction])
		ft_error(REPETED_ERR, collector);
	if (line[i])
	{
		texture_path = ft_strdup(line + i, collector);
		fd = open(texture_path, O_RDONLY);
		if (fd == -1)
			ft_error(TEXTURE_ERR, collector);
		close(fd);
		set_texture_path(data, direction, texture_path);
		data->cub3d_map.infos_presence[direction] = 1;
	}
}

static int	pars_color_utils(char *line, int *i,
			t_free **collector, char last_char)
{
	while (line[*i] && line[*i] == ' ')
		(*i)++;
	if (!ft_isdigit(line[*i]) && line[*i] != ',')
		ft_error(COLOR_ERR, collector);
	if (line[*i] == ',')
	{
		if (last_char == ',')
			ft_error(COLOR_ERR, collector);
		return (1);
	}
	return (0);
}

void	parse_color(char *line, t_data *data, int direction, t_free **collector)
{
	int		i;
	int		count;
	char	**splited;
	char	last_char;

	if (data->cub3d_map.infos_presence[direction])
		ft_error(REPETED_ERR, collector);
	i = -1;
	count = 0;
	while (line[++i])
	{
		count += pars_color_utils(line, &i, collector, last_char);
		last_char = line[i];
	}
	if (count != 2)
		ft_error(COLOR_ERR, collector);
	splited = ft_split(line, ',', collector);
	if (!splited || words_counts(line, ',') != 3)
		ft_error(COLOR_ERR, collector);
	set_grb(data, direction, splited, collector);
}
