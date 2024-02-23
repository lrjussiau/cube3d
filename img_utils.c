/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvuadens <vvuadens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:21:24 by vvuadens          #+#    #+#             */
/*   Updated: 2024/02/23 09:29:01 by vvuadens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	//printf("pixel\n");
	dst = img->addr + (y * img->l_l + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

static void	clear(t_img *img)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while ( i < SCREEN_Y)
	{
		j = 0;
		while (j < SCREEN_X)
		{
			pixel_put(img,j ,i ,0);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img_ptr, 0, 0);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	draw_column(t_img *img, t_col *column)
{
	int	y;

	y = column->start;
	//printf("height: %d ->color: %d\n", column->height, column->color);
	while (y <= column->end)
	{
		//printf("y: %d y_end: %d\n", y, column->end);
		pixel_put(img, column->corX, y, column->color);
		y++;
	}
}

int	w_hook(t_player *player)
{
	double	moveSpeed;

	moveSpeed = 1.0;

	mlx_clear_window (player->img->mlx, player->img->mlx_win);
	printf("go up\n");
	printf("cor x: %f\n", player->corX );
	printf("cor y: %f\n",player->corY);
	printf("en x: %f\n", player->posX );
	printf("en y: %f\n",player->posY);
	if (player->map[(int)player->posY][(int)(player->posX + player->corX * moveSpeed)] == '0' || player->map[(int)player->posY][(int)(player->posX + player->corX * moveSpeed)] == 78)
		player->posX += player->corX * moveSpeed;
	if (player->map[(int)(player->posY + player->corY * moveSpeed)][(int)player->posX] == '0' || player->map[(int)(player->posY + player->corY * moveSpeed)][(int)player->posX] == 78)
		player->posY += player->corY * moveSpeed;
	clear(player->img);
	new_image(player, player->ray, player->column);
	printf("after en x: %f\n", player->posX);
	printf("after en y: %f\n", player->posY);
	return (0);
}

int	d_hook(t_player *player)
{
	double	moveSpeed;

	moveSpeed = 1;
	printf("go left\n");
	printf("en x: %f\n", player->posX );
	printf("en y: %f\n",player->posY);
	if (player->map[(int)player->posY][(int)(player->posX + player->corY * moveSpeed)] == '0' || player->map[(int)player->posY][(int)(player->posX + player->corY * moveSpeed)] == 78)
		player->posX -= player->corY * moveSpeed;
	if (player->map[(int)(player->posY + player->corX * moveSpeed)][(int)player->posX] == '0' || player->map[(int)(player->posY + player->corX * moveSpeed)][(int)player->posX] == 78)
		player->posY -= player->corX * moveSpeed;
	/*if (player->corX == 0)
	{
		if (player->map[(int)player->posY][(int)(player->posX - 1 * moveSpeed)] == '0' || player->map[(int)player->posY][(int)(player->posX - 1 * moveSpeed)] == 78)
		{
			player->posX -= 1 * moveSpeed;
		}
	}
	else
	{
		if (player->map[(int)(player->posY - 1 * moveSpeed)][(int)player->posX] == '0' || player->map[(int)(player->posY - 1 * moveSpeed)][(int)player->posX] == 78)
			player->posY -= 1 * moveSpeed;
	}*/
	clear(player->img);
	mlx_clear_window (player->img->mlx, player->img->mlx_win);
	//usleep(10000000);
	new_image(player, player->ray, player->column);
	printf("after en x: %f\n", player->posX);
	printf("after en y: %f\n", player->posY);
	return (0);
}
// == 0 or N -> 78
int	s_hook(t_player *player)
{
	double	moveSpeed;

	mlx_clear_window (player->img->mlx, player->img->mlx_win);
	moveSpeed = 1.0;
	printf("go down\n");
	printf("en x: %f\n", player->posX );
	printf("en y: %f\n",player->posY);
	if (player->map[(int)player->posY][(int)(player->posX - player->corX * moveSpeed)] == '0' || player->map[(int)player->posY][(int)(player->posX - player->corX * moveSpeed)] == 78)
		player->posX -= player->corX * moveSpeed;
	printf("what is there : %d\n", player->map[(int)(player->posY - player->corY * moveSpeed)][(int)player->posX]);
	if (player->map[(int)(player->posY - player->corY * moveSpeed)][(int)player->posX] == '0' || player->map[(int)(player->posY - player->corY * moveSpeed)][(int)player->posX] == 78)
		player->posY -= player->corY * moveSpeed;
	clear(player->img);
	mlx_clear_window (player->img->mlx, player->img->mlx_win);
	new_image(player, player->ray, player->column);
	printf("after en x: %f\n", player->posX);
	printf("after en y: %f\n", player->posY);
	return (0);
}
//probleme clear window lorsque retour sur precedente case ?
int	a_hook(t_player *player)
{
	double	moveSpeed;

	moveSpeed = 1;
	printf("go right\n");
	printf("en x: %f\n", player->posX );
	printf("en y: %f\n",player->posY);
	if (player->map[(int)player->posY][(int)(player->posX + player->corY * moveSpeed)] == '0' || player->map[(int)player->posY][(int)(player->posX + player->corY * moveSpeed)] == 78)
		player->posX += player->corY * moveSpeed;
	if (player->map[(int)(player->posY + player->corX * moveSpeed)][(int)player->posX] == '0' || player->map[(int)(player->posY + player->corX * moveSpeed)][(int)player->posX] == 78)
		player->posY += player->corX * moveSpeed;
	//printf("what is there : %d\n", player->map[(int)player->posY][(int)(player->posX - 1 * moveSpeed)]);
	/*if (player->corX == 0)
	{
		if (player->map[(int)player->posY][(int)(player->posX + 1 * moveSpeed)] == '0' || player->map[(int)player->posY][(int)(player->posX + 1 * moveSpeed)] == 78)
		{
			player->posX += 1 * moveSpeed;
		}
	}
	else
	{
		if (player->map[(int)(player->posY + 1 * moveSpeed)][(int)player->posX] == '0' || player->map[(int)(player->posY + 1 * moveSpeed)][(int)player->posX] == 78)
			player->posY += 1 * moveSpeed;
	}*/
	//printf("what is there : %d\n", player->map[(int)(player->posY - player->corY * moveSpeed)][(int)player->posX]);
	//if (player->map[(int)(player->posY + player->corY * moveSpeed)][(int)player->posX] == '0' || player->map[(int)(player->posY + player->corY * moveSpeed)][(int)player->posX] == 78)
	//	player->posY += player->corY * moveSpeed;
	mlx_clear_window (player->img->mlx, player->img->mlx_win);
	clear(player->img);
	new_image(player, player->ray, player->column);
	printf("after en x: %f\n", player->posX);
	printf("after en y: %f\n", player->posY);
	return (0);
}

int	left_arrow_hook(t_player *player)
{
	double	oldCorX;
	double	rotSpeed;
	double	oldPlaneX;
	
	rotSpeed = 1.5708/2;
	oldCorX = player->corX;
	oldPlaneX = player->planeX;
	//printf(" corx avant: %f\n", player->corX);
	//printf(" cory avant: %f\n", player->corY);
	player->corX = player->corX * cos(rotSpeed) - player->corY * sin(rotSpeed);
	player->corY = oldCorX * sin(rotSpeed) + player->corY * cos(rotSpeed);
	player->planeX = player->planeX * cos(rotSpeed) - player->planeY * sin(rotSpeed);
	player->planeY = oldPlaneX * sin(rotSpeed) + player->planeY * cos(rotSpeed);
	//printf(" corx apres: %f\n", player->corX);
	//printf(" cory apres: %f\n", player->corY);
	clear(player->img);
	new_image(player, player->ray, player->column);
	return (0);
}

int	right_arrow_hook(t_player *player)
{
	double	oldCorX;
	double	rotSpeed;
	double	oldPlaneX;

	rotSpeed = 1.5708/2;
	//printf(" corx avant: %f\n", player->corX);
	//printf(" cory avant: %f\n", player->corY);
	oldCorX = player->corX;
	oldPlaneX = player->planeX;
	player->corX = player->corX * cos(-rotSpeed) - player->corY * sin(-rotSpeed);
	player->corY = oldCorX * sin(-rotSpeed) + player->corY * cos(-rotSpeed);
	player->planeX = player->planeX * cos(-rotSpeed) - player->planeY * sin(-rotSpeed);
	player->planeY = oldPlaneX * sin(-rotSpeed) + player->planeY * cos(-rotSpeed);
	//printf(" corx apres: %f\n", player->corX);
	//printf(" cory apres: %f\n", player->corY);
	clear(player->img);
	new_image(player, player->ray, player->column);
	return (0);
}

int	close_hook(t_img *img)
{
	mlx_destroy_window (img->mlx, img->mlx_win);
	exit(0);
}

int	keys_hook(int keycode, t_player *player)
{
	if (keycode == 13)
		w_hook(player);
	if (keycode == 0)
		a_hook(player);
	if (keycode == 1)
		s_hook(player);
	if (keycode == 2)
		d_hook(player);
	if (keycode == 123)
		left_arrow_hook(player);
	if (keycode == 124)
		right_arrow_hook(player);
	if (keycode == 53)
	{
		mlx_destroy_window (player->img->mlx, player->img->mlx_win);
		exit(0);
	}
	return (0);
}

