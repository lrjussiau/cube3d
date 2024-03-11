/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_home_screen.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:39:14 by vvuadens          #+#    #+#             */
/*   Updated: 2024/03/07 10:35:29 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	enter_key(int keycode, t_player *player)
{
	if (keycode == 36 && player->home_screen == 1)
	{
		mlx_clear_window(player->img->mlx, player->img->mlx_win);
		player->home_screen = 3;
	}
	return (0);
}

void	put_home_screen(t_player *player)
{
	t_img		*i;

	i = player->img;
	mlx_put_image_to_window(i->mlx, i->mlx_win, i->title->img_ptr, 300, 250);
	new_image(player, player->ray, player->column);
	mlx_put_image_to_window(i->mlx, i->mlx_win, i->title->img_ptr, 300, 150);
	new_image(player, player->ray, player->column);
	mlx_put_image_to_window(i->mlx, i->mlx_win, i->title->img_ptr, 300, 50);
	mlx_put_image_to_window(i->mlx, i->mlx_win, i->sub->img_ptr, 600, 800);
	new_image(player, player->ray, player->column);
	mlx_key_hook (player->img->mlx_win, enter_key, player);
	return ;
}

// int	render(void *param)
// {
// 	t_player	*player;

// 	player = (t_player *)param;
// 	if (player->home_screen != 3)
// 		put_home_screen(player);
// 	minimap_update(player);
// 	new_image(player, player->ray, player->column);
// 	if (player->home_screen == 3)
// 		listen_hook(player);
// 	return (0);
// }