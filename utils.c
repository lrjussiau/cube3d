/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 08:16:20 by ljussiau          #+#    #+#             */
/*   Updated: 2024/02/20 14:37:08 by ljussiau         ###   ########.fr       */
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
