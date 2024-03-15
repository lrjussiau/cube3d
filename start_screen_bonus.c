/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_screen_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:16:43 by ljussiau          #+#    #+#             */
/*   Updated: 2024/03/14 08:35:24 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	print_start_screen(t_player *player, char beer)
{
	t_img		*i;

	i = player->img;
	mlx_clear_window(player->img->mlx, player->img->mlx_win);
	mlx_put_image_to_window(i->mlx, i->mlx_win, i->title->img_ptr, 300, 250);
	new_image(player, player->ray, player->column);
	mlx_put_image_to_window(i->mlx, i->mlx_win, i->title->img_ptr, 300, 150);
	new_image(player, player->ray, player->column);
	mlx_put_image_to_window(i->mlx, i->mlx_win, i->title->img_ptr, 300, 50);
	mlx_put_image_to_window(i->mlx, i->mlx_win, i->sub->img_ptr, 600, 800);
	if (beer == 'E')
		mlx_put_image_to_window(i->mlx, i->mlx_win, i->emp->img_ptr, 100, 400);
	else
		mlx_put_image_to_window(i->mlx, i->mlx_win, i->full->img_ptr, 100, 400);
}

int	pressed_enter(int keycode, t_player *player)
{
	if (keycode == ENTER)
		player->start_game = 1;
	if (keycode == ESC)
	{
		mlx_destroy_window(player->img->mlx, player->img->mlx_win);
		exit(0);
	}
	return (0);
}

int	animate(void *param)
{
	t_player	*player;
	int			time_to_update;
	static int	g_counter = 0;

	player = param;
	time_to_update = 10;
	g_counter++;
	if (player->start_game == 1)
		start_game(player);
	if (g_counter >= time_to_update * 2)
		g_counter = 0;
	else if (g_counter >= time_to_update)
		print_start_screen(player, 'E');
	else
		print_start_screen(player, 'F');
	return (0);
}

void	start(t_player *player)
{
	mlx_hook(player->img->mlx_win, 2, 1L << 0, pressed_enter, player);
	mlx_hook(player->img->mlx_win, DESTROY_NOTIFY, 0, close_game, player);
	mlx_loop_hook(player->img->mlx, animate, player);
	mlx_loop(player->img->mlx);
}
