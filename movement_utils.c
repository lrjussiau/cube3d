/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 08:14:59 by ljussiau          #+#    #+#             */
/*   Updated: 2024/02/26 06:58:31 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*int	move_possible(t_player *player, char direc, char touch, double movement)
{
	if (direc == 'x')
	{
		if (touch == 'w' || touch == 'a')
		{
			if (player->map[(int)player->posY][(int)(player->posX + movement)] == '0')
				return (0);
		}
		else if (touch == 's' || touch == 'd')
		{
			if (player->map[(int)player->posY][(int)(player->posX - movement)] == '0')
				return (0);
		}
	}
	else if (direc == 'y')
	{
		if (touch == 'w' || touch == 'a')
		{
			if (player->map[(int)(player->posY + movement)][(int)player->posX] == '0')
				return (0);
		}
		else if (touch == 's' || touch == 'd')
		{
			if (player->map[(int)(player->posY - movement)][(int)player->posX] == '0')
				return (0);
		}
	}
	return (1);
}*/
