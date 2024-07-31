/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 12:09:11 by obouchta          #+#    #+#             */
/*   Updated: 2024/07/30 17:51:39 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_rgb(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8 | 0xFF);
}

int	get_rgb_opacity(int r, int g, int b, int opacity)
{
	return (r << 24 | g << 16 | b << 8 | opacity);	
}