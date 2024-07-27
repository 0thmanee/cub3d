/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 05:10:23 by obouchta          #+#    #+#             */
/*   Updated: 2024/05/04 22:16:30 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_putstr_fd(char *s, int fd)
{
	int		i;
	char	c;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		c = s[i];
		write(fd, &c, 1);
		i++;
	}
}

void	*ft_memset(void *ptr, int value, size_t num)
{
	size_t			i;
	unsigned char	*ptr2;

	ptr2 = (unsigned char *)ptr;
	i = 0;
	while (i < num)
	{
		ptr2[i] = (unsigned char)value;
		i++;
	}
	return (ptr);
}

char	*ft_strjoin_line(char *total_str, char *buffer)
{
	char	*s3;
	size_t	total_len;

	if (!total_str)
	{
		total_str = (char *)malloc(1);
		if (!total_str)
			return (free(buffer), NULL);
		total_str[0] = '\0';
	}
	total_len = ft_strlen(total_str) + ft_strlen(buffer);
	s3 = (char *)malloc(total_len + 1);
	if (!s3)
		return (free_total(&total_str), free(buffer), NULL);
	ft_strcpy(s3, total_str);
	ft_strcpy(s3 + ft_strlen(total_str), buffer);
	free_total(&total_str);
	return (s3);
}

char	*ft_strtrim(char *s, t_free **collector)
{
	int		j;
	char	*new_line;

	if (!s || !s[0])
		return (NULL);
	j = ft_strlen(s) - 1;
	while (j >= 0 && (s[j] == ' ' || s[j] == '\n'))
		j--;
	if (j < 0)
		return (NULL);
	new_line = ft_substr(s, 0, j + 1, collector);
	return (new_line);
}