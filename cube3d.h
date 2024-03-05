/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 08:17:04 by ljussiau          #+#    #+#             */
/*   Updated: 2024/03/01 12:06:34 by vvuadens         ###   ########.fr       */
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

typedef struct s_mov
{
	int	move_forward;
	int	move_back;
	int move_left;
	int	move_right;
	int rotate_left;
	int	rotate_right;
}				t_mov;

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

typedef struct s_sprite {
	char	*name;
	char	**paths;
	int	width;
	int	height;
}		t_sprite;

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
	int side_wall;
	int	ground_color;
	int	sky_color;
	int	pitch;
	double	cor_x;
	double	cor_y;
	double	wall_x;
}			t_col;

typedef struct	s_minimap
{
	int		size;
	int		y_start;
	int		x_start;
	char	**map;
	double	pos_x;
	double	pos_y;
	double	round_x;
	double	round_y;
	double	cor_x;
	double	cor_y;
	double	orientation;
}			t_minimap;

/*typedef struct s_sprite
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;
	double	transform_x;
	double	transform_y;
	int		sprite_screen_x;
	int		sprite_height;
	int		sprite_width;
	int		draw_start_y;
	int		draw_end_y;
	int		draw_start_x;
	int		draw_end_x;
	int		tex_x;
	int		tex_y;
	int		d;
	int		color;
}				t_sprite;*/

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
	char	**map;
	int		mouse_x;
	int		minimap_size;
	t_mov	*movement;
	t_map	*map_s;
	t_ray	*ray;
	t_col	*column;
	t_img	*img;
	t_minimap	*minimap;
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

# define SCREEN_X	2000
# define SCREEN_Y	1000
# define MINIMAP_SIZE SCREEN_Y / 5
# define W 13
# define A 0
# define S 1
# define D 2
# define L_ARROW 123
# define R_ARROW 124
# define ESC 53

# define MOVESPEED 0.08
# define ROTSPEED 1.5708/40

# define NORTH 1
# define WEST 2
# define EAST 3
# define SOUTH 4

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

//Movement
int		move_forward(t_player *player);
int		move_back(t_player *player);
int		move_left(t_player *player);
int		move_right(t_player *player);

int		left_arrow_hook(t_player *player);
int		right_arrow_hook(t_player *player);

//Movement utils
void	listen_hook(t_player *player);
int		keys_pressed(int keycode, t_player *player);
int		keys_release(int keycode, t_player *player);

//Minimap
void	print_mini_map(t_player *player);

//struct_init
int		init_player_s(t_player **player, t_map *map, t_img *img);
t_ray	*init_ray_s(char **map);
t_col	*init_col_s(t_player *player, t_map *map);
t_img	*init_img(t_img *img, t_map *map);
t_line	*set_t_line(t_line *line, int x, t_col *col, t_tex *tex);
t_tex	*load_texture(t_img *root, t_tex *tex, char *path);
t_map	*map_init(t_map *map);

//struct_update
int		update_ray_s(t_ray *ray, int x, t_player *player);
int		update_column(t_col **col, t_ray *ray, int x, t_player *player);

//image_utils
int		keys_pressed(int keycode, t_player *player);
int		mouse_move(int x, int y, t_player *player);
void	pixel_put(t_img *img, int x, int y, int color);
void	clear_window(t_img *img);
int		transform_color(char *rgb_color);
int		create_trgb(int t, int r, int g, int b);

//draw_image
void	draw_column(t_img *img, t_col *column);
void	draw_sky(t_img *img, t_col *column);
void	draw_ground(t_img *img, t_col *column);
void	new_image(t_player *player, t_ray *ray, t_col *column);
void	draw_texture(t_player *player, t_col *column, int x);

//map
char	**extract_minimap(t_player *player, t_map *map, int size);
void	clear_minimap(t_img *img, t_minimap *map);
void	minimap_update(t_player *player);
t_minimap *minimap_init(t_player *player);
void 	draw_minimap(t_minimap *map, t_player *player);

#endif