/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_processing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 21:21:39 by obouchta          #+#    #+#             */
/*   Updated: 2024/08/04 00:49:19 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_realloc_line(char *line, int len, t_free **collector)
{
	char	*new_line;
	int		i;

	new_line = ft_malloc(collector, len + 1);
	ft_memcpy(new_line, line, ft_strlen(line));
	new_line[len] = '\0';
	i = ft_strlen(line);
	while (i < len)
	{
		new_line[i] = ' ';
		i++;
	}
	return (new_line);
}

void	fill_lines_end(t_data *data, t_free **collector)
{
	int		i;

	i = 0;
	while (data->cub3d_map.map[i])
	{
		if (ft_strlen(data->cub3d_map.map[i]) < data->cub3d_map.map_width)
			data->cub3d_map.map[i] = ft_realloc_line(data->cub3d_map.map[i],
			data->cub3d_map.map_width, collector);
		i++;
	}
}

void	parse_map_line(char *line, int i, t_data *data, t_free **collector)
{
	int	j;

	data->cub3d_map.infos_presence[BOTTOM_CLOSED] = full_wall(line);
	j = 0;
	while (line[j])
	{
		if (line[j] == 'N' || line[j] == 'S' || line[j] == 'W' || line[j] == 'E')
		{
			if (data->cub3d_map.infos_presence[PLAYER])
				ft_error(REP_PLAYER_ERR, collector);
			set_player(data, line[j], i, j);
			if (not_closed(data, i, j))
			{
				printf("%c\n", line[j]);
				ft_error(MAP_ERR, collector);
			}
		}
		else if (line[j] == '0' && not_closed(data, i, j))
				ft_error(MAP_ERR, collector);
		else if (line[j] != '0' && line[j] != '1' && line[j] != ' ')
			ft_error(INVALID_ERR, collector);
		j++;
	}
}

void	parse_map(t_data *data, t_free **collector)
{
	int	i;

	if (!full_wall(data->cub3d_map.map[0]))
		ft_error(UNCLOSED_ERR, collector);
	data->cub3d_map.infos_presence[TOP_CLOSED] = 1;
	i = 1;
	while (data->cub3d_map.map[i])
	{
		if (empty_line(data->cub3d_map.map[i]))
		{
			data->cub3d_map.map[i++] = NULL;
			while (data->cub3d_map.map[i])
			{
				if (!empty_line(data->cub3d_map.map[i]))
					ft_error(MAP_ERR, collector);
				i++;
			}
			break ;
		}
		parse_map_line(data->cub3d_map.map[i], i, data, collector);
		i++;
	}
}

char	**ft_realloc_map(t_data *data, char *line, t_free **collector)
{
	size_t	old_size;
	char	**new_map;
	int		len;
	
	if (!data->cub3d_map.map)
	{
		new_map = ft_malloc(collector, 2 * sizeof(char *));
		new_map[0] = line;
		new_map[1] = NULL;
		return (new_map);
	}
	old_size = 0;
	while (data->cub3d_map.map[old_size])
		old_size++;
	new_map = ft_malloc(collector, (old_size + 2) * sizeof(char *));
	ft_memcpy(new_map, data->cub3d_map.map, old_size * sizeof(char *));
	new_map[old_size] = line;
	new_map[old_size + 1] = NULL;
	len = ft_strlen(line);
	if (len > data->cub3d_map.map_width)
		data->cub3d_map.map_width = len;
	data->cub3d_map.map_height++;
	return (new_map);
}