/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_home_screen.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:39:14 by vvuadens          #+#    #+#             */
/*   Updated: 2024/03/06 10:15:00 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	enter_key(int keycode, t_player *player)
{
	//printf("keycode : %d\n", keycode);
	if (keycode == 36 && player->home_screen == 1)
	{
		mlx_clear_window(player->img->mlx, player->img->mlx_win);
		player->home_screen = 3;
		//player takes beer out
	}
	return (0);
}

void	put_home_screen(t_player *player)
{
	t_img		*img;

	int	i = 0;
	//printf("hello\n");
	img = player->img;
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->title->img_ptr, 300, 250);
	new_image(player, player->ray, player->column);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->title->img_ptr, 300, 150);
	new_image(player, player->ray, player->column);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->title->img_ptr, 300, 50);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->sub_title->img_ptr, 600, 800);
	new_image(player, player->ray, player->column);
	mlx_key_hook (player->img->mlx_win, enter_key, player);
	return ;
}
