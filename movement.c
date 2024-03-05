/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 08:10:23 by ljussiau          #+#    #+#             */
/*   Updated: 2024/03/01 10:27:27 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	move_forward(t_player *player)
{
	if (player->map[(int)player->pos_y]
		[(int)(player->pos_x + player->cor_x * MOVESPEED)] == '0')
		player->pos_x += player->cor_x * MOVESPEED;
	if (player->map[(int)(player->pos_y + player->cor_y * MOVESPEED)]
		[(int)player->pos_x] == '0')
		player->pos_y += player->cor_y * MOVESPEED;
	return (0);
}

int	move_left(t_player *player)
{
	if (player->map[(int)player->pos_y]
		[(int)(player->pos_x - player->cor_y * MOVESPEED)] == '0')
		player->pos_x -= player->cor_y * MOVESPEED;
	if (player->map[(int)(player->pos_y + player->cor_x * MOVESPEED)]
		[(int)player->pos_x] == '0')
		player->pos_y += player->cor_x * MOVESPEED;
	return (0);
}

int	move_back(t_player *player)
{
	if (player->map[(int)player->pos_y]
		[(int)(player->pos_x - player->cor_x * MOVESPEED)] == '0')
		player->pos_x -= player->cor_x * MOVESPEED;
	if (player->map[(int)(player->pos_y - player->cor_y * MOVESPEED)]
		[(int)player->pos_x] == '0')
		player->pos_y -= player->cor_y * MOVESPEED;
	return (0);
}

int	move_right(t_player *player)
{
	if (player->map[(int)player->pos_y]
		[(int)(player->pos_x + player->cor_y * MOVESPEED)] == '0')
		player->pos_x += player->cor_y * MOVESPEED;
	if (player->map[(int)(player->pos_y - player->cor_x * MOVESPEED)]
		[(int)player->pos_x] == '0')
		player->pos_y -= player->cor_x * MOVESPEED;
	return (0);
}

int	mouse_move(int x, int y, t_player *player)
{
	if (x > (player->mouse_x + 10))
		right_arrow_hook(player);
	else if (x < (player->mouse_x - 10))
		left_arrow_hook(player);
	player->mouse_x = x;
	return (0);
}
