/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:20:58 by vvuadens          #+#    #+#             */
/*   Updated: 2024/02/29 08:31:00 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"


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
	print_struct_map(map);
	img.mlx = mlx_init();
	if (!img.mlx)
		return (1);
	//ft_print_map(map->map);
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
	new_image(player, player->ray, player->column);
	mlx_hook(img.mlx_win, 2, 1L << 0, keys_hook, player);
	mlx_hook(img.mlx_win, 6, 1l << 0, mouse_move, player);
	mlx_loop(img.mlx);
}