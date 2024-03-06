/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_screen_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:16:43 by ljussiau          #+#    #+#             */
/*   Updated: 2024/03/06 10:01:15 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	pressed_enter(int keycode, t_player *player)
{
	printf("okok\n");
	if (keycode == 36)
		player->enter = 1;
	printf("euh\n");
	return (0);
}

int	animate(void *param)
{
	t_player	*player = param;
	static int	g_counter = 0;
	int			time_to_update;

	printf("test2\n");
	time_to_update = 50;
	g_counter++;
	if (player->enter == 1)
	{
		start_game(player);
		return (0);
	}
	if (g_counter >= time_to_update * 2)
		g_counter = 0;
	else if (g_counter >= time_to_update)
	{
		mlx_clear_window(player->img->mlx, player->img->mlx_win);
		mlx_put_image_to_window(player->img->mlx, player->img->mlx_win, player->img->beer_empty->img_ptr, 100, 400);
	}
	else
	{
		mlx_clear_window(player->img->mlx, player->img->mlx_win);
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
