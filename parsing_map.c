/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 08:47:14 by ljussiau          #+#    #+#             */
/*   Updated: 2024/02/20 09:07:14 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	parsing_map(char *path, t_map *map)
{
	char	**file;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		error("Fail to open file.");
	while (1)
	{
		if (!parse_line(fd, map))
			break; 
	}
	close(fd);
	// get_texture(file, map);
	// get_color(file, map);
	// get_map(file, map);
}
