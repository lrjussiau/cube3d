/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 08:16:20 by ljussiau          #+#    #+#             */
/*   Updated: 2024/03/01 10:32:47 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	error(char *str)
{
	printf("Error : %s\n", str);
	exit (EXIT_FAILURE);
}

void	*safe_malloc(unsigned int bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
		error("malloc failed");
	return (ret);
}

double	ft_abs(double num)
{
	if (num < 0)
		return (-num);
	return (num);
}

void	cleaner(t_map *map)
{
	ft_free_tab(map->file);
	ft_free_tab(map->map);
	free(map);
}
