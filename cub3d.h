/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:29:45 by obouchta          #+#    #+#             */
/*   Updated: 2024/05/05 19:27:56 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "MLX42/include/MLX42/MLX42.h"

typedef struct s_player
{
	int	x;
	int	y;
	int	angle;
	int	direction;
}	t_player;

typedef struct s_map
{
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	int			floor_color[3];
	int			ceiling_color[3];
	char		**map;
	int			map_height;
	int			map_width;
	int			tile_val;
	t_player	player;
}	t_map;


typedef enum s_directs
{
	NORTH,
	SOUTH,
	WEST,
	EAST
}	t_directs;


typedef struct s_mlx
{
	mlx_t		*mlx;
	void		*win;
	int			win_height;
	int			win_width;
	mlx_image_t	*img;
}	t_mlx;

typedef struct	s_data
{
	t_mlx	*mlx_data;
	t_map	*cub3d_map;
}	t_data;

typedef struct s_free
{
	void			*ptr;
	struct s_free	*next;
}	t_free;

// libft
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strjoin(char *s1, char *s2, t_free **ptrs);
int		ft_strlen(char *s);
int		ft_strlcat(char *dest, char *src, int dstsize);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, int start, int len, t_free **ptrs);
char	*ft_strdup(char *str, t_free **ptrs);
int		is_whitespace(char c);
void	*ft_malloc(t_free **list_aloc, size_t size);
void	ft_free_ptr(t_free **list_aloc, void *ptr);
void	ft_free_all(t_free **list_aloc);
int		ft_isdigit(int c);
int		ft_strchr(char *str, char c);
void	ft_putstr_fd(char *s, int fd);
void	*ft_malloc(t_free **list_aloc, size_t size);
void	ft_free_all(t_free **list_aloc);
int		is_player(char c);
void	*ft_memset(void *ptr, int value, size_t num);
int		get_rgb(int r, int g, int b);
void 	handle_key_hooks(mlx_key_data_t keydata, void* param);

// parsing
t_map	parsing(t_free **ptrs);

// raycasting
void	mlx_init_data(t_mlx *mlx_data, t_map cub3d_map, t_free **ptrs);
void	ray_casting(t_data *data, t_free **ptrs);
void	draw_square(t_data *data, int x, int y, int color);
void	draw_2d_map(t_data *data);
void	move_player(t_data *data, int key);

#endif
