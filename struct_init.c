/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:55:38 by vvuadens          #+#    #+#             */
/*   Updated: 2024/03/05 09:19:07 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_map	*map_init(t_map *map)
{
	map = (t_map *)malloc(sizeof(t_map));
	map->file = NULL;
	map->map = NULL;
	map->no_path = NULL;
	map->so_path = NULL;
	map->ea_path = NULL;
	map->we_path = NULL;
	map->cell_color = NULL;
	map->floor_color = NULL;
	map->player_pos_x = 0;
	map->player_pos_y = 0;
	map->y_max = 0;
	map->x_max = 0;
	return (map);
}

int	init_player_s(t_player **player, t_map *map, t_img *img)
{
	(*player) = malloc(sizeof(t_player));
	if (!(*player))
		return (1);
	(*player)->pos_x = map->player_pos_x + 0.5;
	(*player)->pos_y = map->player_pos_y + 0.5;
	(*player)->minimap_size = MINIMAP_SIZE;
	(*player)->time = 0;
	(*player)->old_time = 0;
	(*player)->map = map->map;
	(*player)->drunk_mode = 1;
	init_orientation(player, map->player_orientation);
	(*player)->ray = init_ray_s(map->map);
	(*player)->column = init_col_s(*player, map);
	(*player)->img = init_img(img, map);
	(*player)->map_s = map;
	(*player)->minimap = minimap_init(*player);
	(*player)->movement = init_mov(*player);
	(*player)->mouse_x = 0;
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

t_img	*init_img(t_img *img, t_map *map)
{
	img->addr = malloc(sizeof(char *));
	img->so_tex = malloc(sizeof(t_tex));
	img->no_tex = malloc(sizeof(t_tex));
	img->ea_tex = malloc(sizeof(t_tex));
	img->we_tex = malloc(sizeof(t_tex));
	if (!img->so_tex || !img->no_tex || !img->ea_tex || !img->we_tex)
		return (0);
	img->mlx_win = mlx_new_window(img->mlx, SCREEN_X, SCREEN_Y, "CUBE3D");
	img->img_ptr = mlx_new_image(img->mlx, SCREEN_X, SCREEN_Y);
	if (!img->img_ptr)
		return (0);
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->l_l, &img->en);
	img->so_tex = load_texture(img, img->so_tex, map->so_path);
	img->no_tex = load_texture(img, img->no_tex, map->no_path);
	img->ea_tex = load_texture(img, img->ea_tex, map->ea_path);
	img->we_tex = load_texture(img, img->we_tex, map->we_path);
	return (img);
}

t_line	*set_t_line(t_line *line, int x, t_col *col, t_tex *tex)
{
	line = safe_malloc(sizeof (t_line));
	line->x = x;
	line->y = 0;
	line->y0 = col->start;
	line->y1 = col->end;
	line->tex_y = 0;
	line->tex_x = 0;
	return (line);
}
