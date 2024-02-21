/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:43:01 by ljussiau          #+#    #+#             */
/*   Updated: 2024/02/21 12:48:54 by ljussiau         ###   ########.fr       */
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
			if (map->map[i][j] == 'N' || map->map[i][j] == 'E'
				|| map->map[i][j] == 'S' || map->map[i][j] == 'W')
			{
				map->player_orientation = map->map[i][j];
				map->player_pos_x = (double)j;
				map->player_pos_y = (double)i;
				return ;
			}
			j++;
		}
		i++;
	}
	error("No player inside the map");
}

void	check_wall(t_map *map)
{
	int	row;
	int	col;

	row = 0;
	get_size(map);
	while (map->map[row])
	{
		col = 0;
		while (map->map[row][col])
		{
			if (row == 0 && (map->map[row][col] != ' '
				&& map->map[row][col] != '1'))
				error("map not correctly walled.");
			else if (row == map->y_max && (map->map[row][col] != ' '
				&& map->map[row][col] != '1'))
				error("map not correctly walled.");
			else
				process_wall(map->map[row]);
			col++;
		}
		row++;
	}
}

void	check_inside(t_map *map)
{
	if (map->player_pos_x == 0 || map->player_pos_y == 0)
		error("no player inside the map.");
	if (map->player_orientation == '\0')
		error("not good orientation for the player.");
}

void	checker(t_map *map)
{
	// check_path(map);
	check_player(map);
	check_wall(map);
	check_inside(map);
}
