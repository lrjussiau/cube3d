/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:20:58 by vvuadens          #+#    #+#             */
/*   Updated: 2024/02/21 11:58:20 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

//update_player when add hook for movement
int	init_player_s(t_player **player, t_map *map)
{
	(*player) = malloc(sizeof(t_player));
	if (!(*player))
		return (1);
	(*player)->posX = map->player_pos_x;
	(*player)->posY = map->player_pos_y;
	(*player)->corX = -1;
	(*player)->corY = 0;
	(*player)->planeX = 0;
	(*player)->planeY = 0.66;
	(*player)->time = 0;
	(*player)->oldTime = 0;
	return (0);
}

int	init_ray_s(t_ray **ray, char **map)
{
	(*ray) = malloc(sizeof(t_ray));
	if (!(*ray))
		return (1);
	(*ray)->mapX = 0;
	(*ray)->mapY = 0;
	(*ray)->stepX = 0;
	(*ray)->stepY = 0;
	(*ray)->hit = 0;
	(*ray)->side = 0;
	(*ray)->cameraX = 0;
	(*ray)->corX = 0;
	(*ray)->corY = 0;
	(*ray)->distX = 0;
	(*ray)->distY = 0;
	(*ray)->deltaDistX = 0;
	(*ray)->deltaDistY = 0;
	(*ray)->wallDist = 0;
	(*ray)->map = map;
	return (0);
}

int	init_col_s(t_col **column)
{
	(*column) = malloc(sizeof(t_col));
	if (!(*column))
		return (1);
	(*column)->color = 0;
	(*column)->height = 0;
	(*column)->start = 0;
	(*column)->end = 0;
	(*column)->corX = 0;
	return (0);
}

int	init_img(t_img *img)
{
	img->mlx_win = mlx_new_window(img->mlx, SCREEN_X, SCREEN_Y, "CUBE3D");
	img->img_ptr = mlx_new_image(img->mlx, SCREEN_X, SCREEN_Y);
	if (!img->img_ptr)
		return (0);
	//printf("lol\n");
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->l_l, &img->en);
	return (1);
}

unsigned int	ft_abs(int num)
{
	if (num < 0)
		return (-num);
	return (num);
}

int	update_ray_step(t_ray **ray, t_player *player)
{
	if ((*ray)->corX < 0)
	{
		(*ray)->stepX = -1;
		(*ray)->sideDistX = (player->posX - (*ray)->mapX) * (*ray)->deltaDistX;
	}
	else
	{
		(*ray)->stepX = 1;
		(*ray)->sideDistX = ((*ray)->mapX + 1.0 - player->posX) * (*ray)->deltaDistX;
	}
	if ((*ray)->corY < 0)
	{
		(*ray)->stepY = -1;
		(*ray)->sideDistY = (player->posY - (*ray)->mapY) * (*ray)->deltaDistY;
	}
	else
	{
		(*ray)->stepY = 1;
		(*ray)->sideDistX = ((*ray)->mapY + 1.0 - player->posY) * (*ray)->deltaDistY;
	}
	return (0);
}

int	update_ray_s(t_ray **ray, int x, t_player *player)
{
	(*ray)->mapX = player->posX;
	(*ray)->mapY = player->posY;
	(*ray)->cameraX = (2 * x / SCREEN_X) - 1;
	(*ray)->corX = player->corX + player->planeX * (*ray)->cameraX;
	(*ray)->corY =  player->corY + player->planeY * (*ray)->cameraX;
	if ((*ray)->corX == 0)
		(*ray)->deltaDistX = 1e30;
	else
		(*ray)->deltaDistX = (ft_abs(1 / (*ray)->corX));
	if ((*ray)->corY == 0)
		(*ray)->deltaDistY = 1e30;
	else
		(*ray)->deltaDistY = (ft_abs(1 / (*ray)->corX));
	update_ray_step(ray, player);
	return (0);
}

int	update_column(t_col **col, t_ray **ray, int x)
{
	t_col	*column;

	column = *col;
	column->color = 16711680;
	if ((*ray)->side ==  0)
		(*ray)->wallDist = (*ray)->sideDistX - (*ray)->deltaDistX;
	else
	{
		(*ray)->wallDist = (*ray)->sideDistY - (*ray)->deltaDistY;
		column->color = column->color / 2;
	}
	printf("distance du mur: %f\n",(*ray)->wallDist);
	column->height = SCREEN_Y / (*ray)->wallDist;
	column->start = ((-column->height) / 2) + (SCREEN_Y / 2);
	if (column->start < 0)
		column->start = 0;
	column->end = (column->height / 2) + (SCREEN_Y / 2);
	if (column->end >= SCREEN_Y)
		column->end = SCREEN_Y - 1;
	column->corX = x;
	return (0);
}

int dda(t_ray **ray)
{
	//printf("rayon: %d\n", ray->sideDistX);
	while ((*ray)->hit == 0)
	{
		printf("hello1\2");
		if ((*ray)->sideDistX < (*ray)->sideDistY)
		{
			(*ray)->sideDistX += (*ray)->deltaDistX;
			(*ray)->mapX += (*ray)->stepX;
			(*ray)->side = 0;
		}
		else
		{
			(*ray)->sideDistY += (*ray)->deltaDistY;
			(*ray)->mapY += (*ray)->stepY;
			(*ray)->side = 1;
		}
		printf("hello\2");
		if ((*ray)->map[(*ray)->mapX][(*ray)->mapY] > 0)
			(*ray)->hit = 1;
	}
	return (0);
}

int main(int ac, char **av)
{

	t_player    *player;
	t_ray       *ray;
	t_col		*column;
	t_img		img;
	int         x;
	t_map	*map;

	map = map_init(map);
	if (ac != 2)
		error("Wrong input, insert the map.cub path.");
	parsing_map(av[1], map);
	checker(map);
	print_struct_map(map);
	x = 0;
	img.mlx = mlx_init();
	if (!img.mlx)
		return (1);
	if (init_player_s(&player, map))
		return (1);
	if (init_ray_s(&ray, map->map))
		return (1);
	if (init_col_s(&column))
		return (1);
	if (!init_img(&img))
		return (1);
	while (x < SCREEN_X)
	{
		update_ray_s(&ray, x, player);
		printf("okok1\n");
		dda(&ray);
		printf("okok2\n");
		update_column(&column, &ray, x);
		printf("hauteur du mur: %d\n",column->height);
		printf("okok3\n");
		draw_column(&img, column);
		printf("okok4\n");
		x++;
	}
	mlx_key_hook (img.mlx_win, esc_hook, &img);
	mlx_hook(img.mlx_win, 17, 1L << 17, close_hook, &img);
	mlx_loop(img.mlx);
}