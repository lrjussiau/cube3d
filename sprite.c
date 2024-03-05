/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:04:02 by vvuadens          #+#    #+#             */
/*   Updated: 2024/03/01 06:50:50 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_frame(t_img *img) {
	int	i;
	int	j;

	i = 0;
	while(i < SCREEN_Y) {
		j = 0;
		while(j < slice->height) {
//			put_pixel_img(*frame, slice.width - j, i, get_pixel_img(s.sprite_img, slice.x + j, slice.y + i));
			put_pixel_img(img, j, i, get_pixel_img(s->sprite_img, slice->x + j, slice->y + i));
			j++;
		}
		i++;
	}
	mlx_put_image_to_window()
}

void new_frame(char * path, t_img *img) {
	t_img image;

	img->img_ptr = mlx_xpm_file_to_image(img->mlx, path, SCREEN_X, SCREEN_Y);
	if (!img->img_ptr)
		write(2, "File could not be read\n", 23);
	else
		img->addr = mlx_get_data_addr(img->img_ptr, image->bpp, image->l_l, img->en);
	draw_frame(img);
}

t_sprite	*new_girl_sprite(t_sprite *sprite){

		
	
}

void	put_pixel_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < SCREEN_X && y < SCREEN_Y) {
		dst = img->addr + (y * img->l_l + x * (img->bpp / 8));
		*(unsigned int *) dst = color;
	}
}

unsigned int	get_pixel_xml(t_img *img, int x, int y)
{
	return (*(unsigned int *)((img->addr
			+ (y * img->l_l) + (x * img->bpp / 8))));
}

