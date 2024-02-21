/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:20:58 by vvuadens          #+#    #+#             */
/*   Updated: 2024/02/21 15:01:31 by ljussiau         ###   ########.fr       */
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
	(*player)->corY = 1;
	(*player)->planeX = 0;
	(*player)->planeY = 1.8;
	(*player)->time = 0;
	(*player)->oldTime = 0;
	return (0);
}

t_ray	*init_ray_s(t_ray *ray, char **map)
{
	ray = (t_ray *)safe_malloc(sizeof(t_ray));
	ray->mapX = 0;
	ray->mapY = 0;
	ray->stepX = 0;
	ray->stepY = 0;
	ray->hit = 0;
	ray->side = 0;
	ray->cameraX = 0.0;
	ray->corX = 0.0;
	ray->corY = 0.0;
	ray->distX = 0.0;
	ray->distY = 0.0;
	ray->deltaDistX = 0.0;
	ray->deltaDistY = 0.0;
	ray->wallDist = 0.0;
	ray->map = map;
	return (ray);
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

double	ft_abs(double num)
{
	if (num < 0)
		return (-num);
	return (num);
}

int	update_ray_step(t_ray *ray, t_player *player)
{
	if (ray->corX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (player->posX - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - player->posX) * ray->deltaDistX;
	}
	if (ray->corY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (player->posY - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - player->posY) * ray->deltaDistY;
	}
	return (0);
}

int	update_ray_s(t_ray *ray, int x, t_player *player)
{
	printf("ray : %d player : \n", (int)player->posX );
	ray->mapX = (int)player->posX;
	ray->mapY = (int)player->posY;
	printf("okok\n");
	ray->cameraX = 2 * x / (double)SCREEN_X - 1;
	printf("cmaera: %f\n", ray->cameraX);
	ray->corX = player->corX + player->planeX * ray->cameraX;
	ray->corY =  player->corY + player->planeY * ray->cameraX;
	printf("CorX : %f, Cor Y:%f\n", ray->corX, ray->corY);
	if (ray->corX == 0)
		ray->deltaDistX = 1e30;
	else
		ray->deltaDistX = (ft_abs(1.0 / ray->corX));
	if (ray->corY == 0)
		ray->deltaDistY = 1e30;
	else
		ray->deltaDistY = (ft_abs(1.0 / ray->corY));
	update_ray_step(ray, player);
	ray->hit = 0;
	return (0);
}

int	update_column(t_col **col, t_ray *ray, int x)
{
	t_col	*column;

	column = *col;
	if (ray->hit == 2)
		column->color = 16711680;
	else
		column->color = 65280;
	//printf("side DIST : %f, delta : %f\n", ray->sideDistY, ray->deltaDistY);
	if (ray->side ==  0)
		ray->wallDist = ray->sideDistX - ray->deltaDistX;
	else
	{
		printf("GO Y\n");
		ray->wallDist = ray->sideDistY - ray->deltaDistY;
		column->color = column->color / 2;
	}
	printf("distance du mur: %f\n",ray->wallDist);
	column->height = (double)SCREEN_Y / ray->wallDist;
	column->start = ((-column->height) / 2) + (SCREEN_Y / 2);
	if (column->start < 0)
		column->start = 0;
	column->end = (column->height / 2) + (SCREEN_Y / 2);
	if (column->end >= SCREEN_Y)
		column->end = SCREEN_Y - 1;
	column->corX = x;
	return (0);
}

void dda(t_ray *ray)
{
	//printf("side_dist avant: %f\n", ray->sideDistX)
	while (ray->hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		if (ray->map[ray->mapY][ray->mapX] > '0')
		{
			if (ray->map[ray->mapY][ray->mapX] == '2')
				ray->hit = 2;
			else
				ray->hit = 1;
		}
	}
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
	ray = init_ray_s(ray, map->map);
	printf("\n\n\n\n\n");
	ft_print_map(ray->map);
	if (init_col_s(&column))
		return (1);
	if (!init_img(&img))
		return (1);
	
	while (x < SCREEN_X)
	{
		printf("def\n");
		update_ray_s(ray, x, player);
		printf("1. %d\n", ray->mapX);
		dda(ray);
		printf("2. %d\n", ray->mapX);
		update_column(&column, ray, x);
		printf("hauteur du mur: %d\n",column->height);
		printf("okok3\n");
		draw_column(&img, column);
		printf("okok4\n");
		x++;
	}
	mlx_put_image_to_window(img.mlx, img.mlx_win, img.img_ptr, 0, 0);
	mlx_key_hook (img.mlx_win, esc_hook, &img);
	mlx_hook(img.mlx_win, 17, 1L << 17, close_hook, &img);
	mlx_loop(img.mlx);
}