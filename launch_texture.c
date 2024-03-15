/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:37:21 by ljussiau          #+#    #+#             */
/*   Updated: 2024/03/14 08:33:15 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	get_wall_texture(t_img *img, t_map *map)
{
	img->so_tex = malloc(sizeof(t_tex));
	img->no_tex = malloc(sizeof(t_tex));
	img->ea_tex = malloc(sizeof(t_tex));
	img->we_tex = malloc(sizeof(t_tex));
	img->so_tex = load_texture(img, img->so_tex, map->so_path);
	img->no_tex = load_texture(img, img->no_tex, map->no_path);
	img->ea_tex = load_texture(img, img->ea_tex, map->ea_path);
	img->we_tex = load_texture(img, img->we_tex, map->we_path);
	img->so_tex_d = malloc(sizeof(t_tex));
	img->no_tex_d = malloc(sizeof(t_tex));
	img->ea_tex_d = malloc(sizeof(t_tex));
	img->we_tex_d = malloc(sizeof(t_tex));
	img->so_tex_d = load_texture(img, img->so_tex_d, "texture/drunk/land.xpm");
	img->no_tex_d = load_texture(img, img->no_tex_d, "texture/drunk/land2.xpm");
	img->ea_tex_d = load_texture(img, img->ea_tex_d, "texture/drunk/gal.xpm");
	img->we_tex_d = load_texture(img, img->we_tex_d, "texture/drunk/amon.xpm");
}

void	get_beer_texture(t_img *img)
{
	char	*full;
	char	*empty;

	full = ft_strdup("./texture/beer/full.xpm");
	empty = ft_strdup("./texture/beer/empty.xpm");
	img->emp = safe_malloc(sizeof(t_tex));
	img->full = safe_malloc(sizeof(t_tex));
	img->emp = load_texture(img, img->emp, empty);
	img->full = load_texture(img, img->full, full);
	free(full);
	free(empty);
}
