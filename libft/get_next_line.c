/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 20:29:43 by obouchta          #+#    #+#             */
/*   Updated: 2024/08/17 18:14:23 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*read_file(char *total_str, int fd)
{
	char	*buffer;
	ssize_t	bytes;

	buffer = malloc(2);
	if (!buffer)
		return (free_total(&total_str), NULL);
	bytes = 1;
	while (bytes)
	{
		bytes = read(fd, buffer, 1);
		if (bytes < 0)
			return (free_total(&total_str), free(buffer), NULL);
		buffer[bytes] = '\0';
		if (bytes)
		{
			total_str = ft_strjoin_line(total_str, buffer);
			if (!total_str)
				return (free(buffer), NULL);
			if (ft_strchr(buffer, '\n'))
				break ;
		}
	}
	free(buffer);
	return (total_str);
}

char	*extract_line(char *total_str)
{
	char	*line;
	int		len;
	int		i;

	if (!total_str || !total_str[0])
		return (NULL);
	len = 0;
	while (total_str[len] && total_str[len] != '\n')
		len++;
	if (total_str[len] == '\n')
		len++;
	line = malloc((len + 1) * sizeof(char));
	if (!line)
		return (free_total(&total_str), NULL);
	i = 0;
	while (total_str[i] && i < len)
	{
		line[i] = total_str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*new_total(t_next_line *total_data)
{
	char	*new_t;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (total_data->total_str[i] && total_data->total_str[i] != '\n')
		i++;
	while (total_data->total_str[i++])
		len++;
	if (len)
	{
		new_t = malloc(len * sizeof(char));
		if (!new_t)
			return (free_total(&total_data->total_str), NULL);
		ft_strcpy(new_t, total_data->total_str + i - len);
		free_total(&total_data->total_str);
		return (new_t);
	}
	else
	{
		total_data->end_file = 1;
		return (total_data->total_str);
	}
}

void	free_total(char **total_str)
{
	if (*total_str)
	{
		free(*total_str);
		*total_str = NULL;
	}
}

char	*get_next_line(int fd)
{
	static t_next_line	total_data;
	char				*line;

	if (total_data.end_file != 1)
	{
		total_data.total_str = read_file(total_data.total_str, fd);
		if (!total_data.total_str)
			return (NULL);
		line = extract_line(total_data.total_str);
		if (!line)
			return (free_total(&total_data.total_str), NULL);
		total_data.total_str = new_total(&total_data);
		if (!total_data.total_str)
			return (free(line), NULL);
		return (line);
	}
	else
		return (free_total(&total_data.total_str), NULL);
}
