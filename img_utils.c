/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:21:24 by vvuadens          #+#    #+#             */
/*   Updated: 2024/02/23 08:51:32 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	//printf("pixel\n");
	dst = img->addr + (y * img->l_l + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	clear(t_img *img)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while ( i < SCREEN_Y)
	{
		j = 0;
		while (j < SCREEN_X)
		{
			pixel_put(img,j ,i ,0);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img_ptr, 0, 0);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	draw_column(t_img *img, t_col *column)
{
	int	y;

	y = column->start;
	//printf("height: %d ->color: %d\n", column->height, column->color);
	while (y <= column->end)
	{
		//printf("y: %d y_end: %d\n", y, column->end);
		pixel_put(img, column->corX, y, column->color);
		y++;
	}
}



