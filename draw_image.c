/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:59:31 by vvuadens          #+#    #+#             */
/*   Updated: 2024/03/06 10:39:24 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
		if (ray->map[ray->map_y][ray->map_x] > '0')
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
		dda(ray);
		get_wall_orientation(column, ray);
		update_column(column, ray, x, player);
		draw_sky(player->img, column);
		draw_texture(player, column, x);
		draw_ground(player->img, column);
		x++;
	}
	mlx_put_image_to_window(img.mlx, img.mlx_win, img.img_ptr, 0, 0);
	// clear_minimap(&img, player->minimap);
	if (player->home_screen == 3 && player->drunk_mode == 0)
	{
		draw_minimap(player->minimap, player);
		mlx_put_image_to_window(img.mlx, img.mlx_win, img.drink_info->img_ptr, 1500, 900);
	}
	if (player->drunk_mode == 1)
		mlx_put_image_to_window(img.mlx, img.mlx_win, img.img_ptr, 0, 0);
	if (player->drunk_mode == 0)
		mlx_put_image_to_window(img.mlx, img.mlx_win,
		img.beer_full->img_ptr, 300, 479);
	else
		mlx_put_image_to_window(img.mlx, img.mlx_win,
		img.beer_empty->img_ptr, 300, 479);
}
