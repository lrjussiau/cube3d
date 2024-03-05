/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:20:58 by vvuadens          #+#    #+#             */
/*   Updated: 2024/03/01 12:06:47 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	render(void *param)
{
	t_player	*player;

	player = (t_player *)param;
	minimap_update(player);
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
	//print_struct_map(map);
	img.mlx = mlx_init();
	if (!img.mlx)
		return (1);
	init_player_s(&player, map, &img);
	printf("my_minimap: \n");
	/*int i = 0;
	int j = 0;
	while (i < player->minimap_size)
	{
		j = 0;
		while (j < player->minimap_size)
		{
			printf("%c",player->minimap->map[i][j]);
			j++;
		}
		i++;
		printf("\n");
	}*/
	mlx_hook(img.mlx_win, 2, 1L << 0, keys_pressed, player);
	mlx_hook(img.mlx_win, 3, 1L << 1, keys_release, player);
	//mlx_hook(img.mlx_win, 6, 1l << 0, mouse_move, player);
	mlx_loop_hook(img.mlx, render, player);
	mlx_loop(img.mlx);
}