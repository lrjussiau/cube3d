/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:20:58 by vvuadens          #+#    #+#             */
/*   Updated: 2024/03/06 10:40:09 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	render(void *param)
{
	t_player	*player;

	player = (t_player *)param;
	if (player->home_screen != 3)
		put_home_screen(player);
	minimap_update(player);
	new_image(player, player->ray, player->column);
	if (player->home_screen == 3)
		listen_hook(player);
	return (0);
}

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
	start(player);
}
