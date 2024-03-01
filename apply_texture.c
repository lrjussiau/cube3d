/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 07:40:44 by ljussiau          #+#    #+#             */
/*   Updated: 2024/03/01 08:23:20 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	texture_on_img(t_img *img, t_col *col, t_line *line, t_tex *tex)
{
	int	scale;

	// printf("...\n");
	// printf("1. tex->data : %s\n", tex->data);
	// printf("1.1 tex->data len : %d\n", ft_strlen(tex->data));
	// printf("2. line->tex_y : %d\n", line->tex_y);
	// printf("3. tex->length : %d\n", tex->line_length);
	// printf("4. line->tex_x : %d\n", line->tex_x);
	// printf("5. tex->bits_per_pixel : %d\n", tex->bits_per_pixel);
	// printf("6. Calcul : %d\n", line->tex_y * tex->line_length + line->tex_x * (tex->bits_per_pixel / 8));
	// printf("7. '%c'\n", tex->data[0]);
	scale = line->y * tex->line_length - (double)SCREEN_Y * tex->line_length
		/ 2 + col->height * tex->line_length / 2;
	line->tex_y = ((scale * tex->height) / col->height) / tex->line_length;
	img->addr[line->y * img->l_l + line->x * img->bpp / 8] = tex->data[line->tex_y * tex->line_length + line->tex_x * (tex->bits_per_pixel / 8)];
	img->addr[line->y * img->l_l + line->x * (img->bpp / 8) + 1] = tex->data[line->tex_y * tex->line_length + line->tex_x * (tex->bits_per_pixel / 8) + 1];
	img->addr[line->y * img->l_l + line->x * (img->bpp / 8) + 2] = tex->data[line->tex_y * tex->line_length + line->tex_x * (tex->bits_per_pixel / 8) + 2];
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
		{
			// printf("line Y : %d, y max : %d\n", line->y, y_max);
			texture_on_img(img, col, line, tex);
		}
	}
}

void	draw_texture(t_player *player, t_col *column, int x)
{
	char	*texture;
	int		y;
	t_line	*line;
	t_tex	*tex;
	t_img	*root;

	root = player->img;
	if (column->color != 1)
	{
		if (column->is_right)
			tex = player->img->we_tex;
		else
			tex = player->img->ea_tex;
	}
	else
	{
		if (column->side_y == 1)
			tex = player->img->so_tex;
		else
			tex = player->img->no_tex;
	}
	line = set_t_line(line, x, column, tex);
	y = line->y0;
	line->tex_x = (int)(column->wall_x * (double)tex->width);
	if ((column->side_wall == WEST || column->side_wall == EAST) && player->ray->cor_x > 0)
		line->tex_x = tex->width - line->tex_x - 1;
	else if ((column->side_wall == SOUTH || column->side_wall == NORTH) && player->ray->cor_y > 0)
		line->tex_x = tex->width - line->tex_x - 1;
	print_texture(root, column, line, tex);
}