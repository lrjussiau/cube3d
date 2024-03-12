/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:39:57 by ljussiau          #+#    #+#             */
/*   Updated: 2024/03/12 09:41:20 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_tex	*load_texture(t_img *root, t_tex *tex, char *path)
{
	int	width;
	int	height;

	tex->img_ptr = mlx_xpm_file_to_image(root->mlx, path, &width, &height);
	if (!tex->img_ptr)
		error("mlx_xpm_file_to_image() failure\n");
	tex->width = width;
	tex->height = height;
	tex->data = mlx_get_data_addr(tex->img_ptr, &tex->bits_per_pixel,
			&tex->line_length, &tex->endian);
	return (tex);
}

t_mov	*init_mov(t_player *player)
{
	t_mov	*movement;

	movement = safe_malloc(sizeof(t_mov));
	movement->move_back = 0;
	movement->move_forward = 0;
	movement->move_left = 0;
	movement->move_right = 0;
	movement->rotate_left = 0;
	movement->rotate_right = 0;
	return (movement);
}

void	init_orientation(t_player **player, char orientation)
{
	(*player)->cor_x = 0;
	(*player)->cor_y = 0;
	(*player)->plane_x = 0;
	(*player)->plane_y = 0;
	if (orientation == 'N')
	{
		(*player)->cor_y = -1;
		(*player)->plane_x = 0.66;
	}
	else if (orientation == 'S')
	{
		(*player)->cor_y = 1;
		(*player)->plane_x = -0.66;
	}
	else if (orientation == 'E')
	{
		(*player)->cor_x = 1;
		(*player)->plane_y = 0.66;
	}
	else if (orientation == 'W')
	{
		(*player)->cor_x = -1;
		(*player)->plane_y = -0.66;
	}
}

t_col	*init_col_s(t_player *player, t_map *map)
{
	t_col	*column;

	column = (t_col *)malloc(sizeof(t_col));
	column->height = 0;
	column->start = 0;
	column->end = 0;
	column->x = 0;
	column->is_right = 0;
	column->ground_color = transform_color(map->floor_color);
	column->sky_color = transform_color(map->cell_color);
	column->cor_x = player->cor_x;
	column->cor_y = player->cor_y;
	return (column);
}
