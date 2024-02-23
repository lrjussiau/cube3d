/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 08:17:04 by ljussiau          #+#    #+#             */
/*   Updated: 2024/02/23 11:24:33 by vvuadens         ###   ########.fr       */
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

typedef struct s_image
{
	void	*mlx;
	void	*mlx_win;
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		l_l;
	int		en;
}			t_img;

typedef struct	s_ray
{
	int		mapX;
	int		mapY;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
	double	sideDistX;
	double	sideDistY;
	double	cameraX;
	double	corX;
	double	corY;
	double	distX;
	double	distY;
	double	deltaDistX;
	double	deltaDistY;
	double	wallDist;
	char	**map;
}				t_ray;

typedef struct	s_column
{
	int	height;
	int	start;
	int	end;
	int	color;
	int	corX;
	double	cor_x;
	double	cor_y;
}			t_col;

typedef struct	s_player
{
	double	posX;
	double	posY;
	double	corX;
	double	corY;
	double	planeX;
	double	planeY;
	double	time;
	double	oldTime;
	t_ray	*ray;
	t_col	*column;
	t_img	*img;
	char	**map;
}				t_player;


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

//img_utils
int		close_hook(t_img *img);
int		esc_hook(int keycode, t_img *img);
void	draw_column(t_img *img, t_col *column);
int		keys_hook(int keycode, t_player *player);

//execution
void	new_image(t_player *player, t_ray *ray, t_col *column);

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

#endif