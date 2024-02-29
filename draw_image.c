/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:59:31 by vvuadens          #+#    #+#             */
/*   Updated: 2024/02/29 09:26:28 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_column(t_img *img, t_col *column)
{
	int	y;

	y = column->start;
	if (column->color != 1)
	{
		if (column->is_right)
			column->color = CUBE_COLOR_W;
		else
			column->color = CUBE_COLOR_E;
	}
	else
	{
		if (column->side_y == 1)
			column->color = CUBE_COLOR_S;
		else
			column->color = CUBE_COLOR_N;
	}
	while (y <= column->end)
	{
		pixel_put(img, column->x, y, column->color);
		y++;
	}
}

void	draw_sky(t_img *img, t_col *column)
{
	int	y;

	y = 0;
	while (y < column->start)
	{
		pixel_put(img, column->x, y, column->sky_color);
		y++;
	}
}

void	draw_ground(t_img *img, t_col *column)
{
	int	y;

	y = column->end + 1;
	while (y < SCREEN_Y)
	{
		pixel_put(img, column->x, y, column->ground_color);
		y++;
	}
}

static void	dda(t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map[ray->map_y][ray->map_x] > '0' && ray->map[ray->map_y][ray->map_x] != 78)
		{
			if (ray->map[ray->map_y][ray->map_x] == '2')
				ray->hit = 2;
			else
				ray->hit = 1;
		}
	}
}

void	new_image(t_player *player, t_ray *ray, t_col *column)
{
	int			x;
	t_img		img;

	x = 0;
	img = *(player->img);
	while (x < SCREEN_X)
	{
		update_ray_s(ray, x, player);
		//printf("ray_cor_x: %f ray_cor_y: %f\n", ray->cor_x, ray->cor_y);
		dda(ray);
		update_column(&column, ray, x, player);
		draw_sky(player->img, column);
		draw_texture(player, column, x);
		// draw_column(player->img, column);
		draw_ground(player->img, column);
		x++;
	}
	//printf("cor_x: %f, cor_y: %f\n", player->cor_x, player->cor_y);
	mlx_put_image_to_window(img.mlx, img.mlx_win, img.img_ptr, 0, 0);
}
