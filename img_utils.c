/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:21:24 by vvuadens          #+#    #+#             */
/*   Updated: 2024/02/26 10:27:16 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	transform_color(char *rgb_color)
{
	char	**rgb;
	int		color;

	color = 0;
	rgb = ft_split(rgb_color, ',');
	color = create_trgb(100,ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	//printf("rgb: %d, %d, %d\n", ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	//free_tab(rgb);
	return (color);
}

void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->l_l + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	clear_window(t_img *img)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while ( i < SCREEN_Y)
	{
		j = 0;
		while (j < SCREEN_X)
		{
			pixel_put (img, j, i, 0);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img_ptr, 0, 0);
}

int	w_hook(t_player *player)
{
	if (player->map[(int)player->pos_y][(int)(player->pos_x + player->cor_x * MOVESPEED)] == '0' || player->map[(int)player->pos_y][(int)(player->pos_x + player->cor_x * MOVESPEED)] == 78)
		player->pos_x += player->cor_x * MOVESPEED;
	if (player->map[(int)(player->pos_y + player->cor_y * MOVESPEED)][(int)player->pos_x] == '0' || player->map[(int)(player->pos_y + player->cor_y * MOVESPEED)][(int)player->pos_x] == 78)
		player->pos_y += player->cor_y * MOVESPEED;
	clear_window(player->img);
	new_image(player, player->ray, player->column);
	return (0);
}

int	d_hook(t_player *player)
{
	if (player->map[(int)player->pos_y][(int)(player->pos_x - player->cor_y * MOVESPEED)] == '0' || player->map[(int)player->pos_y][(int)(player->pos_x - player->cor_y * MOVESPEED)] == 78)
		player->pos_x -= player->cor_y * MOVESPEED;
	if (player->map[(int)(player->pos_y + player->cor_x * MOVESPEED)][(int)player->pos_x] == '0' || player->map[(int)(player->pos_y + player->cor_x * MOVESPEED)][(int)player->pos_x] == 78)
		player->pos_y += player->cor_x * MOVESPEED;
	clear_window(player->img);
	new_image(player, player->ray, player->column);

	return (0);
}

int	s_hook(t_player *player)
{
	if (player->map[(int)player->pos_y][(int)(player->pos_x - player->cor_x * MOVESPEED)] == '0' || player->map[(int)player->pos_y][(int)(player->pos_x - player->cor_x * MOVESPEED)] == 78)
		player->pos_x -= player->cor_x * MOVESPEED;
	if (player->map[(int)(player->pos_y - player->cor_y * MOVESPEED)][(int)player->pos_x] == '0' || player->map[(int)(player->pos_y - player->cor_y * MOVESPEED)][(int)player->pos_x] == 78)
		player->pos_y -= player->cor_y * MOVESPEED;
	clear_window(player->img);
	new_image(player, player->ray, player->column);
	return (0);
}

int	a_hook(t_player *player)
{
	if (player->map[(int)player->pos_y][(int)(player->pos_x + player->cor_y * MOVESPEED)] == '0' || player->map[(int)player->pos_y][(int)(player->pos_x + player->cor_y * MOVESPEED)] == 78)
		player->pos_x += player->cor_y * MOVESPEED;
	if (player->map[(int)(player->pos_y - player->cor_x * MOVESPEED)][(int)player->pos_x] == '0' || player->map[(int)(player->pos_y - player->cor_x * MOVESPEED)][(int)player->pos_x] == 78)
		player->pos_y -= player->cor_x * MOVESPEED;
	clear_window(player->img);
	new_image(player, player->ray, player->column);
	return (0);
}

int	right_arrow_hook(t_player *player)
{
	double	oldcor_x;
	double	oldplane_x;

	oldcor_x = player->cor_x;
	oldplane_x = player->plane_x;
	player->cor_x = player->cor_x * cos(ROTSPEED) - player->cor_y * sin(ROTSPEED);
	player->cor_y = oldcor_x * sin(ROTSPEED) + player->cor_y * cos(ROTSPEED);
	player->plane_x = player->plane_x * cos(ROTSPEED) - player->plane_y * sin(ROTSPEED);
	player->plane_y = oldplane_x * sin(ROTSPEED) + player->plane_y * cos(ROTSPEED);
	clear_window(player->img);
	new_image(player, player->ray, player->column);
	return (0);
}

int	left_arrow_hook(t_player *player)
{
	double	oldcor_x;
	double	oldplane_x;

	oldcor_x = player->cor_x;
	oldplane_x = player->plane_x;
	player->cor_x = player->cor_x * cos(-ROTSPEED) - player->cor_y * sin(-ROTSPEED);
	player->cor_y = oldcor_x * sin(-ROTSPEED) + player->cor_y * cos(-ROTSPEED);
	player->plane_x = player->plane_x * cos(-ROTSPEED) - player->plane_y * sin(-ROTSPEED);
	player->plane_y = oldplane_x * sin(-ROTSPEED) + player->plane_y * cos(-ROTSPEED);
	clear_window(player->img);
	new_image(player, player->ray, player->column);
	return (0);
}

int	close_hook(t_img *img)
{
	mlx_destroy_window (img->mlx, img->mlx_win);
	exit(0);
}

int	keys_hook(int keycode, t_player *player)
{
	if (keycode == 13)
		w_hook(player);
	if (keycode == 0)
		a_hook(player);
	if (keycode == 1)
		s_hook(player);
	if (keycode == 2)
		d_hook(player);
	if (keycode == 123)
		left_arrow_hook(player);
	if (keycode == 124)
		right_arrow_hook(player);
	if (keycode == 53)
	{
		mlx_destroy_window (player->img->mlx, player->img->mlx_win);
		exit(0);
	}
	print_mini_map(player);
	return (0);
}

