/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 08:17:04 by ljussiau          #+#    #+#             */
/*   Updated: 2024/02/27 12:25:54 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <math.h>
# include "libft/libft.h"
# include "mlx/mlx.h"

typedef struct s_map
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	*floor_color;
	char	*cell_color;
	double	player_pos_x;
	double	player_pos_y;
	int		y_max;
	int		x_max;
	char	player_orientation;
	char	**map;
	char	**file;
}		t_map;

typedef struct s_tex
{
	void	*img_ptr;
	char	*data;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_tex;

typedef struct s_image
{
	void	*mlx;
	void	*mlx_win;
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		l_l;
	int		en;
	t_tex	*so_tex;
	t_tex	*no_tex;
	t_tex	*ea_tex;
	t_tex	*we_tex;
}			t_img;

typedef struct	s_ray
{
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	side_dist_x;
	double	side_dist_y;
	double	camera_x;
	double	cor_x;
	double	cor_y;
	double	dist_x;
	double	dist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	wall_dist;
	char	**map;
}				t_ray;

typedef struct	s_column
{
	int	height;
	int	start;
	int	end;
	int	color;
	int	is_right;
	int	side_y;
	int	x;
	int	ground_color;
	int	sky_color;
	double	cor_x;
	double	cor_y;
	double	wall_x;
}			t_col;

typedef struct	s_player
{
	double	pos_x;
	double	pos_y;
	double	cor_x;
	double	cor_y;
	double	plane_x;
	double	plane_y;
	double	time;
	double	old_time;
	t_ray	*ray;
	t_col	*column;
	t_img	*img;
	char	**map;
}				t_player;

typedef struct	s_line
{
	int		x;
	int		y;
	int		y0;
	int		y1;
	int		tex_x;
	int		tex_y;
}				t_line;

# define SCREEN_X	1000
# define SCREEN_Y	500
# define W 13
# define A 0
# define S 1
# define D 2
# define L_ARROW 123
# define R_ARROW 124
# define ESC 53

# define MOVESPEED 1.0
# define ROTSPEED 1.5708/15

# define CUBE_COLOR_N 65280
# define CUBE_COLOR_S 16711680
# define CUBE_COLOR_E 255
# define CUBE_COLOR_W 56575

//utils
void	error(char *str);
void	*safe_malloc(unsigned int bytes);

//map_parsing
void	parsing_map(char *path, t_map *map);

//map_parsing_utils
char	*str_append(char *str1, char *str2);
char	*clear_path(char *str);
char	*clear_color(char *str);
void	get_size(t_map *map);
void	process_wall(char *str);

//debug
void	print_struct_map(t_map *map);
void	ft_print_map(char **tab);

//cleaner
void	cleaner(t_map *map);

//checker
void	checker(t_map *map);


t_map	*map_init(t_map *map);

//Movement
int		w_hook(t_player *player);
int		a_hook(t_player *player);
int		s_hook(t_player *player);
int		d_hook(t_player *player);
int		keys_hook(int keycode, t_player *player);

//Movement Utils
int		move_possible(t_player *player, char direc, char touch, double movement);
void	clear(t_img *img);

//Minimap
void	print_mini_map(t_player *player);

//struct_init
int		init_player_s(t_player **player, t_map *map, t_img *img);
t_ray	*init_ray_s(char **map);
t_col	*init_col_s(t_player *player, t_map *map);
t_img	*init_img(t_img *img, t_map *map);
t_line	*set_t_line(t_line *line, int x, t_col *col, t_tex *tex);
t_tex	*load_texture(t_img *root, t_tex *tex, char *path);

//struct_update
int		update_ray_s(t_ray *ray, int x, t_player *player);
int		update_column(t_col **col, t_ray *ray, int x, t_player *player);

//image_utils
int		keys_hook(int keycode, t_player *player);
void	pixel_put(t_img *img, int x, int y, int color);
void	clear_window(t_img *img);
int		transform_color(char *rgb_color);

//draw_image
void	draw_column(t_img *img, t_col *column);
void	draw_sky(t_img *img, t_col *column);
void	draw_ground(t_img *img, t_col *column);
void	new_image(t_player *player, t_ray *ray, t_col *column);
void	draw_texture(t_player *player, t_col *column, int x);

#endif