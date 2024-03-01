/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 08:14:59 by ljussiau          #+#    #+#             */
/*   Updated: 2024/03/01 08:24:47 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	listen_hook(t_player *player)
{
	t_mov	*movement;

	movement = player->movement;
	if (movement->move_forward == 1)
		move_forward(player);
	if (movement->move_left == 1)
		move_left(player);
	if (movement->move_back == 1)
		move_back(player);
	if (movement->move_right == 1)
		move_right(player);
	if (movement->rotate_left == 1)
		left_arrow_hook(player);
	if (movement->rotate_right == 1)
		right_arrow_hook(player);
}

int	keys_pressed(int keycode, t_player *player)
{
	t_mov	*movement;

	movement = player->movement;
	if (keycode == W)
		movement->move_forward = 1;
	if (keycode == A)
		movement->move_left = 1;
	if (keycode == S)
		movement->move_back = 1;
	if (keycode == D)
		movement->move_right = 1;
	if (keycode == L_ARROW)
		movement->rotate_left = 1;
	if (keycode == R_ARROW)
		movement->rotate_right = 1;
	if (keycode == ESC)
	{
		mlx_destroy_window (player->img->mlx, player->img->mlx_win);
		exit(0);
	}
	return (0);
}

int	keys_release(int keycode, t_player *player)
{
	t_mov	*movement;

	movement = player->movement;
	if (keycode == W)
		movement->move_forward = 0;
	if (keycode == A)
		movement->move_left = 0;
	if (keycode == S)
		movement->move_back = 0;
	if (keycode == D)
		movement->move_right = 0;
	if (keycode == L_ARROW)
		movement->rotate_left = 0;
	if (keycode == R_ARROW)
		movement->rotate_right = 0;
	return (0);
}


