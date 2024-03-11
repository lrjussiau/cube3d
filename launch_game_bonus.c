/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_game_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:25:02 by ljussiau          #+#    #+#             */
/*   Updated: 2024/03/11 08:20:38 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	render(void *param)
{
	t_player	*player;

	player = (t_player *)param;
	if (BONUS == 1)
		minimap_update(player);
	new_image(player, player->ray, player->column);
	listen_hook(player);
	return (0);
}

void	start_game(t_player *player)
{
	t_img	*img;

	img = player->img;
	player->home_screen = 3;
	mlx_hook(img->mlx_win, 2, 1L << 0, keys_pressed, player);
	mlx_hook(img->mlx_win, 3, 1L << 1, keys_release, player);
	mlx_hook(img->mlx_win, 6, 1l << 0, mouse_move, player);
	mlx_loop_hook(img->mlx, render, player);
	mlx_loop(img->mlx);
}
