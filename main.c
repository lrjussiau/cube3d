/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:20:58 by vvuadens          #+#    #+#             */
/*   Updated: 2024/03/07 08:30:24 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"


int main(int ac, char **av)
{
	t_player	*player;
	t_img		img;
	t_map		*map;

	map = map_init(map);
	if (ac != 2)
		error("Wrong input, insert the map.cub path.");
	parsing_map(av[1], map);
	checker(map);
	img.mlx = mlx_init();
	if (!img.mlx)
		return (1);
	init_player_s(&player, map, &img);
	if (BONUS == 1)
		printf("lol\n");
	start(player);
}
