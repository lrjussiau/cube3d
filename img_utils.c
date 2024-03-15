/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:21:24 by vvuadens          #+#    #+#             */
/*   Updated: 2024/03/15 10:09:54 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	isnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_color(char *c)
{
	int	color;

	color = ft_atoi(c);
	if (color < 0 || color > 254)
		return (1);
	return (0);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	transform_color(char *rgb_color)
{
	char	**rgb;
	int		color;

	color = 0;
	rgb = ft_split(rgb_color, ',');
	if (rgb[0] == NULL || rgb[1] == NULL || rgb[2] == NULL)
		error("Color Not valid.");
	if (isnum(rgb[0]) || isnum(rgb[1]) || isnum(rgb[2]))
		error("Color Not valid, not a int.");
	if (check_color(rgb[0]) || check_color(rgb[1]) || check_color(rgb[2]))
		error("Color Not valid, value must be beetween 0 and 254.");
	color = create_trgb(100, ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	ft_free_tab(rgb);
	return (color);
}

void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->l_l + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}
