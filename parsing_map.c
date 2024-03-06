/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 08:47:14 by ljussiau          #+#    #+#             */
/*   Updated: 2024/03/05 09:53:00 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	get_color(t_map *map)
{
	int	i;

	i = 0;
	while (map->file[i])
	{
		if (ft_strnstr(map->file[i], "F ", ft_strlen("F ")))
			map->floor_color = clear_color(map->file[i]);
		if (ft_strnstr(map->file[i], "C ", ft_strlen("C ")))
			map->cell_color = clear_color(map->file[i]);
		i++;
	}
}

static void	get_map(t_map *map)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while (map->file[i])
	{
		if (ft_strnstr(map->file[i], " ", 1)
			|| ft_strnstr(map->file[i], "1", 1)
			|| ft_strnstr(map->file[i], "0", 1))
		{
			str = str_append(str, map->file[i]);
			str = str_append(str, "\n");
		}
		i++;
	}
	map->map = ft_split(str, '\n');
	free(str);
}

static void	get_texture(t_map *map)
{
	int	i;

	i = 0;
	while (map->file[i])
	{
		if (ft_strnstr(map->file[i], "NO ", ft_strlen("NO ")))
			map->no_path = clear_path(map->file[i]);
		if (ft_strnstr(map->file[i], "SO ", ft_strlen("SO ")))
			map->so_path = clear_path(map->file[i]);
		if (ft_strnstr(map->file[i], "WE ", ft_strlen("WE ")))
			map->we_path = clear_path(map->file[i]);
		if (ft_strnstr(map->file[i], "EA ", ft_strlen("EA ")))
			map->ea_path = clear_path(map->file[i]);
		i++;
	}
}

static void	get_file(int fd, t_map *map)
{
	char	*tmp_file;
	char	*line;

	tmp_file = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		tmp_file = str_append(tmp_file, line);
		free(line);
	}
	tmp_file = str_append(tmp_file, "\0");
	map->file = ft_split(tmp_file, '\n');
	free(tmp_file);
}

void	parsing_map(char *path, t_map *map)
{
	char	**file;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		error("Fail to open file.");
	get_file(fd, map);
	close(fd);
	get_texture(map);
	get_color(map);
	get_map(map);
}
