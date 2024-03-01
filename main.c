/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:20:58 by vvuadens          #+#    #+#             */
/*   Updated: 2024/03/01 10:15:52 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	render(void *param)
{
	t_player	*player;

	player = (t_player *)param;
	player->minimap = minimap_init(player, player->map_s);
	new_image(player, player->ray, player->column);
	listen_hook(player);
	return (0);
}

// todo : textures, mini-map, cercle de collision, animations
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
	/*printf("my_minimap: \n");
	int i = 0;
	int j = 0;
	hile (i < 100)
	{
		j = 0;
		while (j < 100)
		{
			printf("%c",minimap[i][j]);
			j++;
		}
		i++;
		printf("\n");
	}*/
	mlx_hook(img.mlx_win, 2, 1L << 0, keys_pressed, player);
	mlx_hook(img.mlx_win, 3, 1L << 1, keys_release, player);
	mlx_hook(img.mlx_win, 6, 1l << 0, mouse_move, player);
	mlx_loop_hook(img.mlx, render, player);
	mlx_loop(img.mlx);
}