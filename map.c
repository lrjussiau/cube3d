/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 06:00:50 by vvuadens          #+#    #+#             */
/*   Updated: 2024/02/29 08:38:19 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

//au 10 eme
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
	else if (minimap_char > '0')
		return (16777215);
	else
		return (0);
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
	mlx_put_image_to_window(p->img->mlx, p->img->mlx_win, p->img->img_ptr, 0, 0);
}

double	ft_abs(double num)
{
	if (num < 0)
		return (-num);
	return (num);
}

//position = positionx + N * corx
int	print_orientation(double x, double y, t_player *player)
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

static char	pick_char(double x, double y, t_player *p)
{
	double	a = round(p->pos_x * 10) / 10;
	double 	b = round(p->pos_y * 10) / 10;

	if ((ft_abs(x - a) < 0.1) && (ft_abs(y - b) < 0.1))
	{
		return ('P');
	}
	else if (print_orientation(x, y, p))
		return ('D');
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
	while (k < 10)
	{
		m = 0;
		l = j;
		x = (int)p->pos_x;
		while (m < 10)
		{
			new_map[i][l++] = pick_char(x, y, p);
			m++;
			x += 0.1;
		}
		y += 0.1;
		i++;
		k++;
	}
}

void print_block(char **new_map, int i, int j, char c)
{
	int	k;
	int	p;
	int	l;

	k = 0;
	while (k < 10)
	{
		p = 0;
		l = j;
		while (p < 10)
		{
			new_map[i][l++] = c;
			p++;
		}
		i++;
		k++;
	}
}

/*	i = 0;
	j = 0;
	while (i < 100)
	{
		j = 0;
		while (j < 100)
		{
			printf("%c",new_map[i][j]);
			j++;
		}
		i++;
		printf("\n");
	}*/

char	**extract_minimap(t_player *player, t_map *map)
{
	char	**new_map;
	int		i;
	int		j;
	int		start_y;
	int		start_x;

	i = 0;
	new_map = malloc(sizeof(char *) * 100);
	while (i < 100)
	{
		new_map[i] = malloc(sizeof(char) * 100);
		i++;
	}
	start_x = (player->pos_x - 5);
	start_y = (player->pos_y - 5);
	i = 0;
	while (i < 10)
	{
		//printf("I: %d\n", i);
		j = 0;
		while (j < 10)
		{
			if ((start_y < map->y_max && start_y > -1) && (start_x <= map->x_max && start_x > -1))
			{
				if (start_x == (int)player->pos_x && start_y == (int)player->pos_y)
				{
					//printf("in\n");
					print_player(new_map, i * 10, j * 10, player);
					//printf("out\n");
				}
				else
					print_block(new_map, i * 10, j * 10, map->map[start_y][start_x]);
			}
			else
				print_block(new_map, i * 10, j * 10, 'T');
			start_x++;
			j++;
		}
		start_x -= 10;
		start_y++;
		i++;
	}
	//printf("extract done\n");
	return (new_map);
}

t_minimap *minimap_init(t_player *player, t_map *map)
{
	t_minimap	*minimap;

	minimap = malloc(sizeof(t_minimap));
	minimap->size = 100;
	minimap->x_start = SCREEN_X / 20;
	minimap->y_start = SCREEN_Y / 20;
	minimap->round_x = round(player->pos_x * 10) / 10;
	minimap->round_y = round(player->pos_y * 10) / 10;
	minimap->pos_x = player->pos_x;
	minimap->pos_y = player->pos_y;
	minimap->cor_x = player->cor_x;
	minimap->cor_y = player->cor_y;
	//printf("before extract\n");
	minimap->map = extract_minimap(player, map);
	//printf("after extract\n");
	return (minimap);
}