/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 08:20:36 by ljussiau          #+#    #+#             */
/*   Updated: 2024/02/21 10:54:45 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_map	*map_init(t_map *map)
{
	map = (t_map *)malloc(sizeof(t_map));
	map->file = NULL;
	map->map = NULL;
	map->no_path = NULL;
	map->so_path = NULL;
	map->ea_path = NULL;
	map->we_path = NULL;
	map->cell_color = NULL;
	map->floor_color = NULL;
	map->player_pos_x = 0;
	map->player_pos_y = 0;
	map->y_max = 0;
	map->x_max = 0;
	return (map);
}

/*int	main(int ac, char **av)
{
	t_map	*map;

	map = map_init(map);
	if (ac != 2)
		error("Wrong input, insert the map.cub path.");
	parsing_map(av[1], map);
	checker(map);
	print_struct_map(map); //debug_mode
	
	cleaner(map);
}*/
