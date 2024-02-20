/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 08:16:20 by ljussiau          #+#    #+#             */
/*   Updated: 2024/02/20 11:19:10 by ljussiau         ###   ########.fr       */
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
