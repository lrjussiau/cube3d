/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:36:34 by ljussiau          #+#    #+#             */
/*   Updated: 2024/02/21 12:47:50 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	ft_print_map(char **tab)
{
	int	i;
	int	j;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		j = -1;
		while (tab[i][++j])
			write(1, &tab[i][j], 1);
		write(1, "\n", 1);
		i++;
	}
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
	printf("PLAYER ORIENTATION : '%c'\n", map->player_orientation);
	printf("PLAYER POS : (x:%f ; y:%f)\n", map->player_pos_x, map->player_pos_y);
	printf("MAP SIZE : (x:%d ; y:%d)\n", map->x_max, map->y_max);
	printf("FINAL_MAP :\n");
	ft_print_map(map->map);
}
