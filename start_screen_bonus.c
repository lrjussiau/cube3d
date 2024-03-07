/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_screen_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:16:43 by ljussiau          #+#    #+#             */
/*   Updated: 2024/03/07 08:44:27 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	pressed_enter(int keycode, t_player *player)
{
	if (keycode == ENTER)
		player->start_game = 1;
	if (keycode == ESC)
	{
		mlx_destroy_window (player->img->mlx, player->img->mlx_win);
		exit(0);
	}
	return (0);
}

int	animate(void *param)
{
	t_player	*player = param;
	static int	g_counter = 0;
	int			time_to_update;
	t_img		*img;

	img = player->img;
	time_to_update = 10;
	g_counter++;
	if (player->start_game == 1)
	{
		player->home_screen = 3;
		start_game(player);
		return (0);
	}
	if (g_counter >= time_to_update * 2)
		g_counter = 0;
	else if (g_counter >= time_to_update)
	{
		mlx_clear_window(player->img->mlx, player->img->mlx_win);
		mlx_put_image_to_window(img->mlx, img->mlx_win, img->title->img_ptr, 300, 250);
		new_image(player, player->ray, player->column);
		mlx_put_image_to_window(img->mlx, img->mlx_win, img->title->img_ptr, 300, 150);
		new_image(player, player->ray, player->column);
		mlx_put_image_to_window(img->mlx, img->mlx_win, img->title->img_ptr, 300, 50);
		mlx_put_image_to_window(img->mlx, img->mlx_win, img->sub_title->img_ptr, 600, 800);
		mlx_put_image_to_window(player->img->mlx, player->img->mlx_win, player->img->beer_empty->img_ptr, 100, 400);
	}
	else
	{
		mlx_clear_window(player->img->mlx, player->img->mlx_win);
		mlx_put_image_to_window(img->mlx, img->mlx_win, img->title->img_ptr, 300, 250);
		new_image(player, player->ray, player->column);
		mlx_put_image_to_window(img->mlx, img->mlx_win, img->title->img_ptr, 300, 150);
		new_image(player, player->ray, player->column);
		mlx_put_image_to_window(img->mlx, img->mlx_win, img->title->img_ptr, 300, 50);
		mlx_put_image_to_window(img->mlx, img->mlx_win, img->sub_title->img_ptr, 600, 800);
		mlx_put_image_to_window(player->img->mlx, player->img->mlx_win, player->img->beer_full->img_ptr, 100, 400);
	}
	return (0);
}

void	start(t_player *player)
{
	mlx_hook(player->img->mlx_win, 2, 1L << 0, pressed_enter, player);
	mlx_loop_hook(player->img->mlx, animate, player);
	mlx_loop(player->img->mlx);
}
