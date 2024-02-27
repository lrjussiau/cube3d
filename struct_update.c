/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:04:56 by vvuadens          #+#    #+#             */
/*   Updated: 2024/02/27 11:15:13 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static double	ft_abs(double num)
{
	if (num < 0)
		return (-num);
	return (num);
}

static int	update_ray_step(t_ray *ray, t_player *player)
{
	if (ray->cor_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x) * ray->deltadist_x;
	}
	if (ray->cor_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y) * ray->deltadist_y;
	}
	return (0);
}

int	update_ray_s(t_ray *ray, int x, t_player *player)
{
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	ray->camera_x = 2 * x / (double)SCREEN_X - 1;
	ray->cor_x = player->cor_x + player->plane_x * ray->camera_x;
	ray->cor_y =  player->cor_y + player->plane_y * ray->camera_x;
	if (ray->cor_x == 0)
	{
		printf("raycor_x == 0\n");
		ray->deltadist_x = 1e30;
	}
	else
		ray->deltadist_x = (ft_abs(1.0 / ray->cor_x));
	if (ray->cor_y == 0)
		ray->deltadist_y = 1e30;
	else
		ray->deltadist_y = (ft_abs(1.0 / ray->cor_y));
	update_ray_step(ray, player);
	ray->hit = 0;
	return (0);
}

int	update_column(t_col **col, t_ray *ray, int x, t_player *player)
{
	t_col	*column;

	column = *col;
	column->is_right = 0;
	column->side_y = 0;
	if (ray->hit == 2)
		column->color = 16711680;
	else
		column->color = 65280;
	if (ray->side ==  0)
		ray->wall_dist = ray->side_dist_x - ray->deltadist_x;
	else
	{
		ray->wall_dist = ray->side_dist_y - ray->deltadist_y;
		column->color = 1;
	}
	if (ray->cor_y < 0)
		column->side_y = 1;
	if (ray->cor_x < 0)	
		column->is_right = 1;
	column->height = (double)SCREEN_Y / ray->wall_dist;
	column->start = ((-column->height) / 2) + (SCREEN_Y / 2);
	if (column->start < 0)
		column->start = 0;
	column->end = (column->height / 2) + (SCREEN_Y / 2);
	if (column->end >= SCREEN_Y)
		column->end = SCREEN_Y - 1;
	column->x = x;
	column->cor_x = player->cor_x;
	column->cor_y = player->cor_y;
	if (column->side_y == 0)
		column->wall_x = player->pos_y + ray->wall_dist * ray->cor_y;
	else
		column->wall_x = player->pos_x + ray->wall_dist * ray->cor_x;
	return (0);
}
