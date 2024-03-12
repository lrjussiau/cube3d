/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:59:31 by vvuadens          #+#    #+#             */
/*   Updated: 2024/03/12 08:40:23 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

//color = create_trgb(190, 51, 0, 153);
void	draw_sky(t_img *img, t_col *column, t_player *player)
{
	int	y;
	int	color;

	y = 0;
	if (player->drunk_mode == 0)
		color = column->sky_color;
	else
		color = create_trgb(190, 124, 10, 240);
	while (y < column->start)
	{
		pixel_put(img, column->x, y, color);
		y++;
	}
}

//color = create_trgb(190, 51, 26, 0);
void	draw_ground(t_img *img, t_col *column, t_player *player)
{
	int	y;
	int	color;

	y = column->end + 1;
	if (player->drunk_mode == 0)
		color = column->ground_color;
	else
		color = create_trgb(190, 155, 42, 145);
	while (y < SCREEN_Y)
	{
		pixel_put(img, column->x, y, color);
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

static void	print_hud(t_player *player, t_img *img)
{
	if (player->home_screen == 3 && player->drunk_mode == 0)
	{
		draw_minimap(player->minimap, player);
		mlx_put_image_to_window(img->mlx, img->mlx_win,
			img->full->img_ptr, 300, 479);
		mlx_put_image_to_window(img->mlx, img->mlx_win,
			img->drink->img_ptr, 1500, 900);
	}
	if (player->drunk_mode == 1)
		mlx_put_image_to_window(img->mlx, img->mlx_win,
			img->emp->img_ptr, 300, 479);
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
		draw_sky(player->img, column, player);
		draw_texture(player, column, x);
		draw_ground(player->img, column, player);
		x++;
	}
	mlx_put_image_to_window(img.mlx, img.mlx_win, img.img_ptr, 0, 0);
	if (BONUS == 1)
		print_hud(player, &img);
	else
		mlx_put_image_to_window(img.mlx, img.mlx_win, img.img_ptr, 0, 0);
}
