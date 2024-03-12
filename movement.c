/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 08:10:23 by ljussiau          #+#    #+#             */
/*   Updated: 2024/03/12 09:39:13 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	move_forward(t_player *player)
{
	if (player->map[(int)(player->pos_y)]
		[(int)(player->pos_x + player->cor_x * MOVESPEED)] != '1')
		player->pos_x += player->cor_x * MOVESPEED;
	if (player->map[(int)(player->pos_y + player->cor_y * MOVESPEED)]
		[(int)(player->pos_x)] != '1')
		player->pos_y += player->cor_y * MOVESPEED;
	return (0);
}

int	move_left(t_player *player)
{
	int	trigger;

	trigger = 1;
	if (player->drunk_mode == 0)
		trigger = -1;
	if (player->map[(int)(player->pos_y)]
		[(int)(player->pos_x - player->cor_y * MOVESPEED * trigger)] != '1')
		player->pos_x -= player->cor_y * MOVESPEED * trigger;
	if (player->map[(int)(player->pos_y + player->cor_x * MOVESPEED * trigger)]
		[(int)(player->pos_x)] != '1')
		player->pos_y += player->cor_x * MOVESPEED * trigger;
	return (0);
}

int	move_back(t_player *player)
{
	if (player->map[(int)(player->pos_y)]
		[(int)(player->pos_x - player->cor_x * MOVESPEED)] != '1')
		player->pos_x -= player->cor_x * MOVESPEED;
	if (player->map[(int)(player->pos_y - player->cor_y * MOVESPEED)]
		[(int)(player->pos_x)] != '1')
		player->pos_y -= player->cor_y * MOVESPEED;
	return (0);
}

int	move_right(t_player *player)
{
	int	trigger;

	trigger = 1;
	if (player->drunk_mode == 0)
		trigger = -1;
	if (player->map[(int)(player->pos_y)]
		[(int)(player->pos_x + player->cor_y * MOVESPEED * trigger)] != '1')
		player->pos_x += player->cor_y * MOVESPEED * trigger;
	if (player->map[(int)(player->pos_y - player->cor_x * MOVESPEED * trigger)]
		[(int)(player->pos_x)] != '1')
		player->pos_y -= player->cor_x * MOVESPEED * trigger;
	return (0);
}

int	mouse_move(int x, int y, t_player *player)
{
	if (x > (player->mouse_x + 10))
		right_arrow_hook(player, ROT * 1.5);
	else if (x < (player->mouse_x - 10))
		left_arrow_hook(player, -ROT * 1.5);
	player->mouse_x = x;
	return (0);
}
