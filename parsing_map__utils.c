/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map__utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:01:21 by ljussiau          #+#    #+#             */
/*   Updated: 2024/02/21 08:06:38 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char	*str_append(char *str1, char *str2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (str1 == NULL)
		len1 = 0;
	else
		len1 = ft_strlen(str1);
	if (str2 == NULL)
		len2 = 0;
	else
		len2 = ft_strlen(str2);
	result = safe_malloc(len1 + len2 + 1);
	*result = '\0';
	if (str1)
		ft_strlcat(result, str1, len1 + 1);
	if (str2[0] != '\0')
		ft_strlcat(result, str2, len1 + len2 + 1);
	free(str1);
	return (result);
}

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
