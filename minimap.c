/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:15:47 by ljussiau          #+#    #+#             */
/*   Updated: 2024/02/26 06:58:55 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	print_mini_map(t_player *player)
{
	int		i;
	int		j;
	char	**tab;

	printf("\n\n");
	tab = player->map;
	tab[(int)player->pos_y][(int)player->pos_x] = 'P';
	i = 0;
	while (tab[i])
	{
		j = -1;
		while (tab[i][++j])
		{
			if (tab[i][j] == '0')
				write(1, " ", 1);
			else
				write(1, &tab[i][j], 1);
		}
		write(1, "\n", 1);
		i++;
	}
	tab[(int)player->pos_y][(int)player->pos_x] = '0';
}
