/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:21:24 by vvuadens          #+#    #+#             */
/*   Updated: 2024/03/01 10:13:20 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	transform_color(char *rgb_color)
{
	char	**rgb;
	int		color;

	color = 0;
	rgb = ft_split(rgb_color, ',');
	color = create_trgb(100,ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	//printf("rgb: %d, %d, %d\n", ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	//free_tab(rgb);
	return (color);
}

void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->l_l + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	clear_window(t_img *img)
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
			pixel_put (img, j, i, 0);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img_ptr, 0, 0);
}



int	right_arrow_hook(t_player *player)
{
	double	oldcor_x;
	double	oldplane_x;

	oldcor_x = player->cor_x;
	oldplane_x = player->plane_x;
	player->cor_x = player->cor_x * cos(ROTSPEED) - player->cor_y * sin(ROTSPEED);
	player->cor_y = oldcor_x * sin(ROTSPEED) + player->cor_y * cos(ROTSPEED);
	player->plane_x = player->plane_x * cos(ROTSPEED) - player->plane_y * sin(ROTSPEED);
	player->plane_y = oldplane_x * sin(ROTSPEED) + player->plane_y * cos(ROTSPEED);
	return (0);
}

int	left_arrow_hook(t_player *player)
{
	double	oldcor_x;
	double	oldplane_x;

	oldcor_x = player->cor_x;
	oldplane_x = player->plane_x;
	player->cor_x = player->cor_x * cos(-ROTSPEED) - player->cor_y * sin(-ROTSPEED);
	player->cor_y = oldcor_x * sin(-ROTSPEED) + player->cor_y * cos(-ROTSPEED);
	player->plane_x = player->plane_x * cos(-ROTSPEED) - player->plane_y * sin(-ROTSPEED);
	player->plane_y = oldplane_x * sin(-ROTSPEED) + player->plane_y * cos(-ROTSPEED);
	return (0);
}

int	close_hook(t_img *img)
{
	mlx_destroy_window (img->mlx, img->mlx_win);
	exit(0);
}

int	mouse_move(int x, int y, t_player *player)
{
	if (x > (player->mouse_x + 10))
		right_arrow_hook(player);
	else if (x < (player->mouse_x - 10))
		left_arrow_hook(player);
	return (0);
}

