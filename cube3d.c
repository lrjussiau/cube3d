/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 08:20:36 by ljussiau          #+#    #+#             */
/*   Updated: 2024/02/20 11:19:51 by ljussiau         ###   ########.fr       */
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
	return (map);
}

void	print_struct_map(t_map *map)
{
	printf("FILE :\n");
	ft_print_map(map->file);
	printf("NORTH PATH : '%s'\n", map->no_path);
	printf("SOUTH PATH : '%s'\n", map->so_path);
	printf("WEST PATH : '%s'\n", map->we_path);
	printf("EAST PATH : '%s'\n", map->ea_path);
	printf("FLOOR COLOR : '%s'\n", map->floor_color);
	printf("CELLING COLOR : '%s'\n", map->cell_color);
	printf("FINAL_MAP :\n");
	ft_print_map(map->map);
}

int	main(int ac, char **av)
{
	t_map	*map;

	map = map_init(map);
	if (ac != 2)
		error("Wrong input, insert the map.cub path.");
	parsing_map(av[1], map);
	print_struct_map(map);
}
