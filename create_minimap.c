/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 08:56:44 by vvuadens          #+#    #+#             */
/*   Updated: 2024/03/12 08:32:51 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static char	pick_char(double x, double y, t_player *p)
{
	double	a;
	double	b;

	a = round(p->pos_x * 10) / 10;
	b = round(p->pos_y * 10) / 10;
	if ((ft_abs(x - a) < 0.3) && (ft_abs(y - b) < 0.3))
		return ('P');
	else
		return ('0');
}

static void	print_player(char **new_map, int i, int j, t_player *p)
{
	int		k;
	int		m;
	int		l;
	double	x;
	double	y;

	k = 0;
	y = (int)p->pos_y;
	while (k < (M_S / 10))
	{
		m = 0;
		l = j;
		x = (int)p->pos_x;
		while (m < (M_S / 10))
		{
			new_map[i][l++] = pick_char(x, y, p);
			m++;
			x += (1.0 / (M_S / 10.0));
		}
		y += (1.0 / (M_S / 10.0));
		i++;
		k++;
	}
}

static void	print_b(char **new_map, int i, int j, char c)
{
	int	k;
	int	p;
	int	l;

	k = 0;
	while (k < M_S / 10)
	{
		p = 0;
		l = j;
		while (p < M_S / 10)
		{
			new_map[i][l++] = c;
			p++;
		}
		i++;
		k++;
	}
}

char	**m_alloc(int size)
{
	char	**new_map;
	int		i;

	i = 0;
	new_map = malloc(sizeof(char *) * size);
	while (i < size)
	{
		new_map[i] = malloc(sizeof(char) * size);
		i++;
	}
	return (new_map);
}

void	**extract_minimap(char **n, t_player *p, int i, int j)
{
	int		y;
	int		x;

	x = (p->pos_x - 5);
	y = (p->pos_y - 5);
	while (++i < 10)
	{
		j = -1;
		while (++j < 10)
		{
			if ((y <= p->map_s->y_max && y > -1) && (x <= p->map_s->x_max
					&& x > -1) && (x == (int)p->pos_x && y == (int)p->pos_y))
				print_player(n, i * (M_S / 10), j * (M_S / 10), p);
			else if ((y <= p->map_s->y_max && y > -1) && (x <= p->map_s->x_max
					&& x > -1))
				print_b(n, i * (M_S / 10), j * (M_S / 10), p->map[y][x]);
			else
				print_b(n, i * (M_S / 10), j * (M_S / 10), 'T');
			x++;
		}
		x -= 10;
		y++;
	}
}

/*void	fill_minimap(char **n, t_player *p, t_map *m, int s)
{
	int		i;
	int		j;
	int		y;
	int		x;

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
					print_player(n, i * (s / 10), j * (s / 10), p);
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
}*/
