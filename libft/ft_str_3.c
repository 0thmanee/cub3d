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

#include "cub3d.h"

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
