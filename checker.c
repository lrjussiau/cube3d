/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:43:01 by ljussiau          #+#    #+#             */
/*   Updated: 2024/02/20 16:05:12 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	check_path(t_map *map)
{
	int	fd;

	fd = open(map->no_path, O_RDONLY);
	if (fd < 0)
		error("Failed to open NORTH texture.");
	close(fd);
	fd = open(map->so_path, O_RDONLY);
	if (fd < 0)
		error("Failed to open SOUTH texture.");
	close(fd);
	fd = open(map->we_path, O_RDONLY);
	if (fd < 0)
		error("Failed to open WEST texture.");
	close(fd);
	fd = open(map->ea_path, O_RDONLY);
	if (fd < 0)
		error("Failed to open EAST texture.");
	close(fd);
}

void	check_player(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == 'N' || map->map[i][j] == 'N'
				|| map->map[i][j] == 'N' || map->map[i][j] == 'N')
			{
				map->player_orientation = map->map[i][j];
				map->player_pos_x = j;
				map->player_pos_y = i;
				return ;
			}
			j++;
		}
		i++;
	}
	error("No player inside the map");
}

void	checker(t_map *map)
{
	// check_path(map);
	check_player(map);
	// check_wall(map);
	// check_inside(map);
}
