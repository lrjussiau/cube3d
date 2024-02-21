/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:21:24 by vvuadens          #+#    #+#             */
/*   Updated: 2024/02/21 14:27:48 by ljussiau         ###   ########.fr       */
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

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	draw_column(t_img *img, t_col *column)
{
	int	y;

	y = column->start;
	while (y <= column->end)
	{
		//printf("y: %d y_end: %d\n", y, column->end);
		pixel_put(img, column->corX, y, column->color);
		y++;
	}
}

int	esc_hook(int keycode, t_img *img)
{
	if (keycode == 53)
	{
		mlx_destroy_window (img->mlx, img->mlx_win);
		exit(0);
	}
	return (0);
}

int	close_hook(t_img *img)
{
	mlx_destroy_window (img->mlx, img->mlx_win);
	exit(0);
}
