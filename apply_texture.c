/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 07:40:44 by ljussiau          #+#    #+#             */
/*   Updated: 2024/03/11 08:12:55 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	texture_on_img(t_img *img, t_col *col, t_line *line, t_tex *tex)
{
	int	scale;

	scale = line->y * tex->line_length - (double)SCREEN_Y * tex->line_length
		/ 2 + col->height * tex->line_length / 2;
	line->tex_y = ((scale * tex->height) / col->height) / tex->line_length;
	img->addr[line->y * img->l_l + line->x * img->bpp / 8] = tex->data
	[line->tex_y * tex->line_length + line->tex_x
		* (tex->bits_per_pixel / 8)];
	img->addr[line->y * img->l_l + line->x * (img->bpp / 8) + 1] = tex->data
	[line->tex_y * tex->line_length + line->tex_x
		* (tex->bits_per_pixel / 8) + 1];
	img->addr[line->y * img->l_l + line->x * (img->bpp / 8) + 2] = tex->data
	[line->tex_y * tex->line_length + line->tex_x
		* (tex->bits_per_pixel / 8) + 2];
}

void	print_texture(t_img *img, t_col *col, t_line *line, t_tex *tex)
{
	int	y_max;

	if (line->y0 < line->y1)
	{
		line->y = line->y0;
		y_max = line->y1;
	}
	else
	{
		line->y = line->y1;
		y_max = line->y0;
	}
	if (line->y >= 0)
	{
		line->y--;
		while (++line->y < y_max)
			texture_on_img(img, col, line, tex);
	}
}

static t_tex	*choose_texture(t_player *player, t_col *column)
{
	if (player->drunk_mode == 0)
	{
		if (column->side_wall == WEST)
			return (player->img->we_tex);
		if (column->side_wall == EAST)
			return (player->img->ea_tex);
		if (column->side_wall == NORTH)
			return (player->img->no_tex);
		if (column->side_wall == SOUTH)
			return (player->img->so_tex);
	}
	else
	{
		if (column->side_wall == WEST)
			return (player->img->we_tex_d);
		if (column->side_wall == EAST)
			return (player->img->ea_tex_d);
		if (column->side_wall == NORTH)
			return (player->img->no_tex_d);
		if (column->side_wall == SOUTH)
			return (player->img->so_tex_d);
	}
	return (0);
}

void	draw_texture(t_player *player, t_col *column, int x)
{
	int		y;
	t_line	*line;
	t_tex	*tex;
	t_img	*root;

	root = player->img;
	tex = choose_texture(player, column);
	line = set_t_line(line, x, column, tex);
	y = line->y0;
	line->tex_x = (int)(column->wall_x * (double)tex->width);
	if ((column->side_wall == WEST || column->side_wall == EAST)
		&& player->ray->cor_x > 0)
		line->tex_x = tex->width - line->tex_x - 1;
	else if ((column->side_wall == SOUTH || column->side_wall == NORTH)
		&& player->ray->cor_y > 0)
		line->tex_x = tex->width - line->tex_x - 1;
	print_texture(root, column, line, tex);
	free(line);
}
