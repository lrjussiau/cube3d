/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 08:17:04 by ljussiau          #+#    #+#             */
/*   Updated: 2024/03/15 10:21:43 by ljussiau         ###   ########.fr       */
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
	int	move_left;
	int	move_right;
	int	rotate_left;
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
	t_tex	*so_tex_d;
	t_tex	*no_tex_d;
	t_tex	*ea_tex_d;
	t_tex	*we_tex_d;
	t_tex	*title;
	t_tex	*sub;
	t_tex	*drink;
	t_tex	*full;
	t_tex	*emp;
}			t_img;

typedef struct s_ray
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

typedef struct s_column
{
	int		height;
	int		start;
	int		end;
	int		is_right;
	int		side_y;
	int		x;
	int		side_wall;
	int		ground_color;
	int		sky_color;
	double	cor_x;
	double	cor_y;
	double	wall_x;
}			t_col;

typedef struct s_minimap
{
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

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		cor_x;
	double		cor_y;
	double		plane_x;
	double		plane_y;
	char		**map;
	char		orientation;
	int			mouse_x;
	int			drunk_mode;
	int			home_screen;
	int			start_game;
	t_mov		*movement;
	t_map		*map_s;
	t_ray		*ray;
	t_col		*column;
	t_img		*img;
	t_minimap	*minimap;
}				t_player;

typedef struct s_line
{
	int		x;
	int		y;
	int		y0;
	int		y1;
	int		tex_x;
	int		tex_y;
}				t_line;

# ifndef BONUS
#  define BONUS 0
# endif

# define SCREEN_X	1920
# define SCREEN_Y	1080
# define M_S 200
# define W 13
# define A 0
# define S 1
# define D 2
# define B 11
# define L_ARROW 123
# define R_ARROW 124
# define ESC 53
# define ENTER 36
# define DESTROY_NOTIFY	17

# define MOVESPEED 0.08
# define ROT 0.03927

# define NORTH 1
# define WEST 2
# define EAST 3
# define SOUTH 4

//utils
void		error(char *str);
void		*safe_malloc(unsigned int bytes);
double		ft_abs(double num);
void		cleaner(t_map *map);

//map_parsing
void		parsing_map(char *path, t_map *map);

//checker
void		check_path(t_map *map, char *path);
void		check_player(t_map *map);
void		check_wall(t_map *map);
void		check_wall_vertical(t_map *map);
void		check_inside(t_map *map);
void		checker(t_map *map, char *path);

//map_parsing_utils
void		process_wall_vertical(char **map, int col);
char		*clear_path(char *str);
char		*clear_color(char *str);
void		get_size(t_map *map);
void		process_wall(char *str);

//debug
void		print_struct_map(t_map *map);
void		ft_print_map(char **tab);

//Launch texture
void		get_wall_texture(t_img *img, t_map *map);
void		get_beer_texture(t_img *img);

//Movement
int			move_forward(t_player *player);
int			move_back(t_player *player);
int			move_left(t_player *player);
int			move_right(t_player *player);
int			left_arrow_hook(t_player *player, double t);
int			right_arrow_hook(t_player *player, double t);

//Movement utils
void		listen_hook(t_player *player);
int			keys_pressed(int keycode, t_player *player);
int			keys_release(int keycode, t_player *player);

//Minimap
void		print_mini_map(t_player *player);

//struct_init
int			init_player_s(t_player **player, t_map *map, t_img *img);
t_ray		*init_ray_s(char **map);
t_img		*init_img(t_img *img, t_map *map);
t_line		*set_t_line(t_line *line, int x, t_col *col, t_tex *tex);
t_map		*map_init(t_map *map);

//struct_init_utils
void		init_orientation(t_player **player, char orientation);
t_mov		*init_mov(t_player *player);
t_tex		*load_texture(t_img *root, t_tex *tex, char *path);
t_col		*init_col_s(t_player *player, t_map *map);

//struct_update
int			update_ray_s(t_ray *ray, int x, t_player *player);
void		update_column(t_col *column, t_ray *ray, int x, t_player *player);
void		get_wall_orientation(t_col *column, t_ray *ray);

//image_utils
int			keys_pressed(int keycode, t_player *player);
int			mouse_move(int x, int y, t_player *player);
void		pixel_put(t_img *img, int x, int y, int color);
int			transform_color(char *rgb_color);
int			create_trgb(int t, int r, int g, int b);

//draw_image
void		draw_sky(t_img *img, t_col *column, t_player *player);
void		draw_ground(t_img *img, t_col *column, t_player *player);
void		new_image(t_player *player, t_ray *ray, t_col *column);
void		draw_texture(t_player *player, t_col *column, int x);

//static home_screen
void		put_home_screen(t_player *player);

//starting screen
void		start(t_player *player);

//Lunch game
void		start_game(t_player *player);
int			close_game(t_player *player);

//create_minimap
void		extract_minimap(char **map, t_player *p, int i, int j);
char		**m_alloc(int size);

//minimap_utils
t_minimap	*minimap_init(t_player *player);
void		minimap_update(t_player *player);
void		clear_minimap(t_img *img, t_minimap *map);
void		draw_minimap(t_minimap *map, t_player *player);

#endif 