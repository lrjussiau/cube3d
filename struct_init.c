/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:55:38 by vvuadens          #+#    #+#             */
/*   Updated: 2024/02/29 16:14:04 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	init_orientation(t_player **player, char orientation)
{
	if (orientation == 'N' || orientation == 'S')
	{
		if (orientation == 'N')
			(*player)->cor_y = -1;
		else
			(*player)->cor_y = 1;
		(*player)->plane_x = 0.66;
		(*player)->plane_y = 0;
		(*player)->cor_x = 0;
		(*player)->plane_x = 0.66;
		(*player)->plane_y = 0;
	}
	if (orientation == 'E' || orientation == 'W')
	{
		if (orientation == 'E')
			(*player)->cor_x = -1;
		else
			(*player)->cor_x = 1;
		(*player)->cor_y = 0;
		(*player)->plane_x = 0;
		(*player)->plane_y = 0.66;
	}
	return ;
}

int	init_player_s(t_player **player, t_map *map, t_img *img)
{
	printf("hello_player\n");
	(*player) = malloc(sizeof(t_player));
	if (!(*player))
		return (1);
	(*player)->pos_x = map->player_pos_x + 0.5;
	(*player)->pos_y = map->player_pos_y + 0.5;
	(*player)->time = 0;
	(*player)->old_time = 0;
	(*player)->map = map->map;
	init_orientation(player, map->player_orientation);
	(*player)->ray = init_ray_s(map->map);
	(*player)->column = init_col_s(*player, map);
	(*player)->img = init_img(img);
	(*player)->minimap = minimap_init(*player, map);
	(*player)->map_s = map;
	(*player)->mouse_x = 0;
	(*player)->mouse_y = 0;
	return (0);
}

t_ray	*init_ray_s(char **map)
{
	t_ray	*ray;

	ray = (t_ray *)safe_malloc(sizeof(t_ray));
	ray->map_x = 0;
	ray->map_y = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->hit = 0;
	ray->side = 0;
	ray->camera_x = 0.0;
	ray->cor_x = 0.0;
	ray->cor_y = 0.0;
	ray->dist_x = 0.0;
	ray->dist_y = 0.0;
	ray->deltadist_x = 0.0;
	ray->deltadist_y = 0.0;
	ray->wall_dist = 0.0;
	ray->map = map;
	return (ray);
}

t_col	*init_col_s(t_player *player, t_map *map)
{
	t_col	*column;

	column = (t_col *)malloc(sizeof(t_col));
	column->color = 0;
	column->height = 0;
	column->start = 0;
	column->end = 0;
	column->x = 0;
	column->is_right = 0;
	column->ground_color = transform_color(map->floor_color);
	column->sky_color = transform_color(map->cell_color);
	column->cor_x = player->cor_x;
	column->cor_y = player->cor_y;
	column->pitch = 0;
	return (column);
}

t_img *init_img(t_img *img)
{
	img->mlx_win = mlx_new_window(img->mlx, SCREEN_X, SCREEN_Y, "CUBE3D");
	img->img_ptr = mlx_new_image(img->mlx, SCREEN_X, SCREEN_Y);
	if (!img->img_ptr)
		return (0);
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->l_l, &img->en);
	return (img);
}