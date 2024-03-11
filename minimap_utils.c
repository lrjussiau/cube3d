/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 06:00:50 by vvuadens          #+#    #+#             */
/*   Updated: 2024/03/07 10:18:04 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	clear_minimap(t_img *img, t_minimap *map)
{
	int	start_y;
	int	start_x;

	start_y = map->y_start;
	while (start_y < (map->y_start + M_S))
	{
		start_x = map->x_start;
		while (start_x < (map->x_start + M_S))
		{
			pixel_put(img, start_x, start_y, 0);
			start_x++;
		}
		start_y++;
	}
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img_ptr, 0, 0);
}

static int	pick_color(char minimap_char)
{
	if (minimap_char == 'P')
		return (16716947);
	else if (minimap_char == 'T')
		return (create_trgb(150, 220, 220, 220));
	else if (minimap_char > '0')
		return (16777215);
	else
		return (create_trgb(200, 220, 220, 220));
}

void	draw_minimap(t_minimap *map, t_player *p)
{
	int	start_y;
	int	start_x;
	int	x;
	int	y;

	y = 0;
	start_y = map->y_start;
	while (start_y < (map->y_start + M_S))
	{
		x = 0;
		start_x = map->x_start;
		while (start_x < (map->x_start + M_S))
		{
			pixel_put(p->img, start_x, start_y, pick_color(map->map[y][x]));
			x++;
			start_x++;
		}
		y++;
		start_y++;
	}
	if (p->drunk_mode == 0)
		mlx_put_image_to_window(p->img->mlx, p->img->mlx_win,
			p->img->img_ptr, 0, 0);
}

t_minimap	*minimap_init(t_player *player)
{
	t_minimap	*minimap;

	minimap = malloc(sizeof(t_minimap));
	if (!minimap)
		return (0);
	minimap->x_start = SCREEN_X / 20;
	minimap->y_start = SCREEN_Y / 20;
	minimap->round_x = round(player->pos_x * 10) / 10;
	minimap->round_y = round(player->pos_y * 10) / 10;
	minimap->pos_x = player->pos_x;
	minimap->pos_y = player->pos_y;
	minimap->cor_x = player->cor_x;
	minimap->cor_y = player->cor_y;
	minimap->map = extract_minimap(m_alloc(M_S), player, -1, 0);
	return (minimap);
}

void	minimap_update(t_player *player)
{
	t_minimap	*minimap;

	minimap = player->minimap;
	minimap->round_x = round(player->pos_x * 10) / 10;
	minimap->round_y = round(player->pos_y * 10) / 10;
	minimap->pos_x = player->pos_x;
	minimap->pos_y = player->pos_y;
	minimap->cor_x = player->cor_x;
	minimap->cor_y = player->cor_y;
	minimap->map = extract_minimap(m_alloc(M_S), player, -1, 0);
}

/*int	i = 0;
	int	j = 0;
	while (i < player->minimap_size)
	{
		j = 0;
		while (j < player->minimap_size)
		{
			printf("%c",minimap->map[i][j]);
			j++;
		}
		i++;
		printf("\n");
	}*/