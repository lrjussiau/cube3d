/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:20:58 by vvuadens          #+#    #+#             */
/*   Updated: 2024/03/06 09:26:00 by vvuadens         ###   ########.fr       */
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
	//print_struct_map(map);
	img.mlx = mlx_init();
	if (!img.mlx)
		return (1);
	init_player_s(&player, map, &img);
	mlx_hook(img.mlx_win, 2, 1L << 0, keys_pressed, player);
	mlx_hook(img.mlx_win, 3, 1L << 1, keys_release, player);
	//mlx_hook(img.mlx_win, 6, 1l << 0, mouse_move, player);
	mlx_loop_hook(img.mlx, render, player);
	mlx_loop(img.mlx);
}