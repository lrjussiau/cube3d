/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 06:00:50 by vvuadens          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/03/05 08:54:45 by vvuadens         ###   ########.fr       */
=======
/*   Updated: 2024/03/05 09:12:55 by ljussiau         ###   ########.fr       */
>>>>>>> 17a39c7e0203729f062c10d43061eaee3a28e347
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	clear_minimap(t_img *img, t_minimap *map)
{
	int	start_y;
	int	start_x;

	start_y = map->y_start;
	while (start_y < (map->y_start + map->size))
	{
		start_x = map->x_start;
		while (start_x < (map->x_start + map->size))
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
	//printf("draw\n");
	//clear_minimap(player->img, map);
	start_y = map->y_start;
	while (start_y < (map->y_start + map->size))
	{
		x = 0;
		start_x = map->x_start;
		while (start_x < (map->x_start + map->size))
		{
			pixel_put(p->img, start_x, start_y, pick_color(map->map[y][x]));
			x++;
			start_x++;
		}
		y++;
		start_y++;
	}
	if (p->drunk_mode == 0)
		mlx_put_image_to_window(p->img->mlx, p->img->mlx_win, p->img->img_ptr, 0, 0);
}

//position = positionx + N * corx
/*int	print_orientation(double x, double y, t_player *player)
{
	double	a = round(player->pos_x * 10) / 10;
	double 	b = round(player->pos_y * 10) / 10;
	double	corx = round(player->cor_x * 10) / 10;
	double	cory = round(player->cor_y * 10) / 10;;
	//x = round(x * 10) / 10;
	//y = round(y * 10) / 10;

	if ( corx == 0)
	{
		//printf("x: %f, y: %f, pos_x: %f, pos_y: %f, corx: %f, cory: %f\n", x, y,a, b, corx, cory );
		corx = 1.0;
		if (cory < 0)
		{
			if ((ft_abs(x - a) < 0.1 ) && (y / cory < 0) && y < b)
				return (1);
			return (0);
		}
		else
		{
			if ((ft_abs(x - a) < 0.1) && (y / cory > 0) && y > b)
				return (1);
			return (0);
		}
	}
	else if (cory == 0)
	{
		cory = 1.0;
		if (corx < 0)
		{
			if ((ft_abs(y - b) < 0.1) && (y / (corx < 0))&& x < a)
				return (1);
			return (0);
		}
		else
		{
			if ((ft_abs(y - b) < 0.1) && (y / corx > 0) && x > a)
				return (1);
			return (0);
		}
	}
	else
	{
		// ajouter les trois autres cas 
		if (ft_abs(((x - a) / corx)-((y - b) / cory)) < 0.3)
		{
			if (corx < 0 && cory < 0 && ft_abs(a) > ft_abs(x) && ft_abs(b) > ft_abs(y))
				return (1);
			if (corx > 0 && cory > 0 && ft_abs(a) < ft_abs(x) && ft_abs(b) < ft_abs(y))
				return (1);
			if (corx < 0 && cory > 0 && ft_abs(a) > ft_abs(x) && ft_abs(b) < ft_abs(y))
				return (1);
			if (corx > 0 && cory < 0 && ft_abs(a) < ft_abs(x) && ft_abs(b) > ft_abs(y))
				return (1);
		}
		return (0);
	} 
}
*/
static char	pick_char(double x, double y, t_player *p)
{
	double	a = round(p->pos_x * 10) / 10;
	double 	b = round(p->pos_y * 10) / 10;

	if ((ft_abs(x - a) < 0.3) && (ft_abs(y - b) < 0.3))
	{
		return ('P');
	}
	//else if (print_orientation(x, y, p))
	//	return ('D');
	else
		return ('0');
}

void print_player(char **new_map, int i, int j, t_player *p)
{
	int		k;
	int		m;
	int		l;
	double	x;
	double	y;

	k = 0;
	y = (int)p->pos_y;
	while (k < (p->minimap_size / 10))
	{
		m = 0;
		l = j;
		x = (int)p->pos_x;
		while (m < (p->minimap_size / 10))
		{
			new_map[i][l++] = pick_char(x, y, p);
			m++;
			x += (1.0 / (p->minimap_size / 10.0));
		}
		y += (1.0 / (p->minimap_size / 10.0));
		i++;
		k++;
	}
}

void print_block(char **new_map, int i, int j, char c, t_player *player)
{
	int	k;
	int	p;
	int	l;

	k = 0;
	while (k < player->minimap_size / 10)
	{
		p = 0;
		l = j;
			printf("k : %d, / %d\n", k, player->minimap_size /10);
		while (p < player->minimap_size / 10)
		{
			// printf("\tp : %d, / %d\n", p, player->minimap_size /10);
			// printf("\ti : %d, l: %d\n", i, l);
			new_map[i][l++] = c;
			// printf("\ttest\n");
			p++;
		}
		i++;
		k++;
	}
}

/*void print_minimap(t_player *p, char **map, int s_x, int s_y)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 10)
	{
		j = 0;
		while (j < 10)
		{
			if ((s_y <= p->map_s->y_max && s_y > -1) && (s_x <= p->map_s->x_max && s_x > -1))
			{
				if (s_x == (int)p->pos_x && s_y == (int)p->pos_y)
					print_player(map, i * (size / 10), j * (size / 10), p);
				else
					print_block(map, i * (size / 10), j * (size / 10), p->map_s->map[s_y][s_x], p);
			}
			else
				print_block(new_map, i * (size / 10), j *(size / 10), 'T' , p);
			start_x++;
			j++;
		}
		start_x -= 10;
		start_y++;
	}
	return (map);
}*/

char	**extract_minimap(t_player *p, t_map *m, int s)
{
	char	**n;
	int		i;
	int		j;
	int		y;
	int		x;

	i = 0;
	n = malloc(sizeof(char *) * s);
	printf("s : %d\n", s);
	while (i < s)
	{
		n[i] = malloc(sizeof(char) * s);
		i++;
	}
	x = (p->pos_x - 5);
	y = (p->pos_y - 5);
	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			if ((y <= m->y_max && y > -1) && (x <= m->x_max && x > -1))
			{
				if (x == (int)p->pos_x && y == (int)p->pos_y)
				{
					printf("my_minimap: \n");
					print_player(n, i * (s / 10), j * (s / 10), p);
				}
				else
					print_block(n, i * (s / 10), j * (s / 10), m->map[y][x], p);
			}
			else
				print_block(n, i * (s / 10), j * (s / 10), 'T', p);
			x++;
			j++;
		}
		x -= 10;
		y++;
		i++;
	}
	return (n);
}

t_minimap *minimap_init(t_player *player)
{
	t_minimap	*minimap;

	minimap = malloc(sizeof(t_minimap));
	if (!minimap)
		return (0);
	minimap->size = player->minimap_size;
	minimap->x_start = SCREEN_X / 20;
	minimap->y_start = SCREEN_Y / 20;
	minimap->round_x = round(player->pos_x * 10) / 10;
	minimap->round_y = round(player->pos_y * 10) / 10;
	minimap->pos_x = player->pos_x;
	minimap->pos_y = player->pos_y;
	minimap->cor_x = player->cor_x;
	minimap->cor_y = player->cor_y;
	minimap->map = extract_minimap(player, player->map_s, player->minimap_size);
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
	//free(minimap->map);
	minimap->map = extract_minimap(player, player->map_s, minimap->size);
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
}
