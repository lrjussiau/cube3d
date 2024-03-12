/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map__utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:01:21 by ljussiau          #+#    #+#             */
/*   Updated: 2024/03/12 09:13:28 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char	*clear_path(char *str)
{
	int	i;

	i = 3;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (&str[i]);
}

char	*clear_color(char *str)
{
	int	i;

	i = 2;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (&str[i]);
}

void	get_size(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
			j++;
		if (map->x_max < j)
			map->x_max = j - 1;
		i++;
	}
	map->y_max = i - 1;
}

void	process_wall(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
		{
			if (str[i] != '1')
				error("map not correctly walled.");
			while (str[i])
			{
				if (str[i] == ' ')
					break ;
				i++;
			}
			i--;
			if (str[i] != '1')
				error("map not correctly walled.");
		}
		i++;
	}
}

void	process_wall_vertical(char **map, int col)
{
	int	row;

	row = 0;
	while (map[row])
	{
		if (map[row][col] == '0' || map[row][col] == '1')
		{
			if (map[row][col] != '1')
			{
				error("map not correctly walled.");
			}
			while (map[row])
			{
				if (map[row][col] == ' ')
					break ;
				row++;
			}
			row--;
			if (map[row][col] != '1')
			{
				error("map not correctly walled.");
			}
		}
		row++;
	}
}
