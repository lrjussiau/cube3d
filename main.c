/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:20:58 by vvuadens          #+#    #+#             */
/*   Updated: 2024/03/15 10:20:13 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	main(int ac, char **av)
{
	t_player	*player;
	t_img		img;
	t_map		*map;

	map = map_init(map);
	if (ac != 2)
		error("Wrong input, insert the map.cub path.");
	parsing_map(av[1], map);
	checker(map, av[1]);
	img.mlx = mlx_init();
	if (!img.mlx)
		return (1);
	init_player_s(&player, map, &img);
	if (BONUS == 1)
		start(player);
	else
		start_game(player);
	exit(0);
}
