/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:29:45 by obouchta          #+#    #+#             */
/*   Updated: 2024/07/31 21:04:02 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include "MLX42/include/MLX42/MLX42.h"

#define TEX_WIDTH 64
#define TEX_HEIGHT 64
# define TILE_SIZE 64

# define WINDOW_WIDTH 2560
# define WINDOW_HEIGHT 1390

# define MINI_MAP_SCALE 0.3
typedef struct s_player
{
	int		x;
	int		y;
	int		line_len;
	int		body_color;
	int		line_color;
	int		turn_direction; // -1 for left, 1 for right and 0 for no turn
	int		walk_direction; // -1 for back, 1 for front and 0 for no walk
	double	rotation_angle; // in degrees
	int		move_speed; // in pixels per frame
	double	rotation_speed; // in degrees per frame, the speed of the rotation

	int	player_size;
	int	player_head;
}	t_player;

typedef	struct s_fov
{
	double	fov_angle;
	int		wall_width;
	int		nbr_rays;
}	t_fov;

typedef struct	s_ray
{
	float		ray_angle;
	float		h_x_interc;
	float		h_y_interc;
	float		h_x_step;
	float		h_y_step;
	float		h_wall_hit_x;
	float		h_wall_hit_y;
	float		h_distance;
	float		v_x_interc;
	float		v_y_interc;
	float		v_x_step;
	float		v_y_step;
	float		v_wall_hit_x;
	float		v_wall_hit_y;
	float		v_distance;
	int			faces[4];
	float		wall_hit_x;
	float		wall_hit_y;
	float		distance;
	float		hit_vertical;
}	t_ray;

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
	int			tile_size;
}	t_map;


typedef enum s_directs
{
	EAST = 0,
	NORTH = 270,
	WEST = 180,
	SOUTH = 90,
}	t_directs;


typedef struct s_mlx
{
	mlx_t		*mlx;
	void		*win;
	int			win_height;
	int			win_width;
	mlx_image_t	*img;
	mlx_image_t	*textures_img;
}	t_mlx;

typedef struct s_free
{
	void			*ptr;
	struct s_free	*next;
}	t_free;

typedef struct	s_data
{
	t_mlx		mlx_data;
	t_map		cub3d_map;
	t_player	player;
	t_fov		fov;
	t_ray		*rays;
	t_free		**ptrs;
}	t_data;

typedef struct	s_line
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;
}	t_line;


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
int	get_rgb_opacity(int r, int g, int b, int opacity);

// parsing
void	parse_map(int ac, char *file, t_free **ptrs);
void	ft_error(char *error_msg, t_free **ptrs);
t_data	map_init(t_free **ptrs);

// raycasting
void	mlx_init_data(t_mlx *mlx_data, t_map cub3d_map, t_free **ptrs);
void	draw_square(t_data *data, int x, int y, int color);
void	draw_2d_map(t_data *data);
void	draw_player(t_data *data);
void	draw_angle(t_data *data);
void	move_player(t_data *data, int key);
void 	handle_key_hooks(mlx_key_data_t keydata, void* param);
void	loop_hook_func(void *param);
void	cast_rays(t_data *data);
void	draw_line(t_data *data, t_line line, int color);
void	cast_ray(t_data *data, t_ray *ray);
int		wall_hitted(t_data *data, int x, int y);

// walls ** textures
uint32_t	*textures(t_data *data);
void	walls_rendering(t_data *data);
void	textures_img(t_data *data, t_mlx *mlx_data , uint32_t *textures);
#endif
