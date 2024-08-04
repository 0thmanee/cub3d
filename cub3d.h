/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:29:45 by obouchta          #+#    #+#             */
/*   Updated: 2024/08/04 01:02:27 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <limits.h>
# include "MLX42/include/MLX42/MLX42.h"

#define TILE_SIZE 64
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define MINI_MAP_SCALE 0.3

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
	int	player_direction;
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
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	int			floor_color[3];
	int			ceiling_color[3];
	char		**map;
	int			map_height;
	int			map_width;
	int 		infos_presence[10];
}	t_map;

typedef struct s_wall
{
	mlx_texture_t *N_texture;
	mlx_texture_t *S_texture;
	mlx_texture_t *E_texture;
	mlx_texture_t *W_texture;
	float distanceProjPlane;
	float wallStripHeiht;
	float corrected_wall_distance;
	int BOTTOM_wall_pixel;
	int TOP_wall_pixel;
	float x_offset;
	float y_offset;
	float x_factor;
	float y_factor;
	uint32_t *buffer;
} t_wall;


typedef enum s_directs
{
	EAST = 0,
	NORTH = 270,
	WEST = 180,
	SOUTH = 90,
}	t_directs;

typedef enum s_map_infos
{
	NO,
	SO,
	WE,
	EA,
	FL,
	CE,
	MAP_FOUND,
	TOP_CLOSED,
	BOTTOM_CLOSED,
	PLAYER
}	t_map_infos;


typedef struct s_mlx
{
	mlx_t		*mlx;
	void		*win;
	int			win_height;
	int			win_width;
	mlx_image_t	*img;
}	t_mlx;

typedef struct s_free
{
	void			*ptr;
	struct s_free	*next;
}	t_free;

typedef struct s_data
{
	t_mlx mlx_data;
	t_map cub3d_map;
	t_player player;
	t_fov fov;
	t_ray *rays;
	t_free **collector;
	t_wall wall;
} t_data;

typedef struct	s_line
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;
}	t_line;

typedef struct s_next_line
{
	char	*total_str;
	int		end_file;
}	t_next_line;

# define ARGS_ERR "invalid number of arguments.\n"
# define EXTN_ERR "invalid file extension.\n"
# define FILE_ERR "error opening the file.\n"
# define PATH_ERR "invalid texture path.\n"
# define TEXTURE_EXT_ERR "invalid texture extension.\n"
# define TEXTURE_ERR "texture missing.\n"
# define COLOR_ERR "invalid color.\n"
# define REPETED_ERR "repeated map info.\n"
# define MISSING_NO_TEXT_ERR "missing NO texture path.\n"
# define MISSING_SO_TEXT_ERR "missing SO texture path.\n"
# define MISSING_WE_TEXT_ERR "missing WE texture path.\n"
# define MISSING_EA_TEXT_ERR "missing EA texture path.\n"
# define MISSING_F_COLOR_ERR "missing floor color.\n"
# define MISSING_C_COLOR_ERR "missing ceiling color.\n"
# define ORDER_ERR "invalid order or missing informations.\n"
# define INVALID_ERR "remove that unclear information from the map.\n"
# define REP_PLAYER_ERR "Repeated player position.\n"
# define PLAYER_ERR "missing player.\n"
# define MAP_ERR "map error.\n"
# define MISSING_MAP_ERR "missing map.\n"
#define UNCLOSED_ERR "map is not closed.\n"

// libft
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strjoin(char *s1, char *s2, t_free **collector);
int		ft_strlen(char *s);
int		ft_strlcat(char *dest, char *src, int dstsize);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, int start, int len, t_free **collector);
char	*ft_strdup(char *str, t_free **collector);
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
char	*ft_strtrim(char *input, t_free **collector);
long	ft_atoi(const char *str);
size_t	words_counts(char const *s, char c);
char	**ft_split(char const *s, char c, t_free **collector);
void	*ft_memcpy(void *dest, const void *src, size_t n);

//get_next_line

char	*get_next_line(int fd);
char	*new_total(t_next_line *total_data);
char	*extract_line(char *total_str);
char	*read_file(char *total_str, int fd);
char	*ft_strjoin_line(char *total_str, char *buffer);
void	free_total(char **total_str);


// parsing
void		ft_error(char *error_msg, t_free **collector);
void		display_infos(t_map cub3d_map);
void		set_texture_path(t_data *data, int direction, char *texture_path);
void		parse_texture(char *line, t_data *data, int direction, t_free **collector);
void		set_grb(t_data *data, int direction, char **splited, t_free **collector);
void 		parse_color(char *line, t_data *data, int direction, t_free **collector);
int 		invalid_order(int infos_presence[]);
int 		full_wall(char *line);
t_directs	get_player_pos(char c);
void		set_player(t_data *data, char direc, int i, int j);
int			not_closed(t_data *data, int i, int j);
char		*ft_realloc_line(char *line, int len, t_free **collector);
void		fill_lines_end(t_data *data, t_free **collector);
void		parse_map_line(char *line, int i, t_data *data, t_free **collector);
int			empty_line(char *line);
void		parse_map(t_data *data, t_free **collector);
char		**ft_realloc_map(t_data *data, char *line, t_free **collector);
int			all_spaces(char *line);
void		add_map_line(t_data *data, char *line, t_free **collector);
int			check_info(char *line, int i, t_data *data, t_free **collector);
void		ead_data(int map_fd, t_data *data, t_free **collector);
void		check_infos_avalable(int *infos_presence, int bef, t_free **collector);
void		parse_data(int ac, char *file, t_data *data, t_free **collector);
void 		read_data(int map_fd, t_data *data, t_free **collector);

// raycasting
void	mlx_init_data(t_mlx *mlx_data, t_map cub3d_map, t_free **collector);
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

// mlx_texture_t *textures(t_data *data);
void			walls_rendering(t_data *data, t_wall *wall);
void			textures_img(t_data *data, t_mlx *mlx_data, uint32_t *textures);
void	free_textures(t_wall *wall);
void	textures_init(t_data *data, t_wall *wall);


#endif
