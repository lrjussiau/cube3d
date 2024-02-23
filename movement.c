/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljussiau <ljussiau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 08:10:23 by ljussiau          #+#    #+#             */
/*   Updated: 2024/02/23 09:27:06 by ljussiau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// int	w_hook(t_player *player)
// {
// 	double	movement;

// 	movement = player->corX * MOVESPEED;
// 	if (move_possible(player, 'x', 'w', movement) == 0)
// 		player->posX += movement;
// 	movement = player->corY * MOVESPEED;
// 	if (move_possible(player, 'y', 'w', movement) == 0)
// 		player->posY += movement;
// 	clear(player->img);
// 	new_image(player, player->ray, player->column);
// 	return (0);
// }

// int	s_hook(t_player *player)
// {
// 	double	movement;

// 	movement = player->corX * MOVESPEED;
// 	if (move_possible(player, 'x', 's', movement) == 0)
// 		player->posX -= movement;
// 	movement = player->corY * MOVESPEED;
// 	if (move_possible(player, 'y', 's', movement) == 0)
// 		player->posY -= movement;
// 	clear(player->img);
// 	new_image(player, player->ray, player->column);
// 	return (0);
// }

// int	a_hook(t_player *player)
// {
// 	double	movement;

// 	movement = 1 * MOVESPEED;
// 	if (move_possible(player, 'x', 'a', movement) == 0)
// 		player->posX += movement;
// 	// movement = player->corY * MOVESPEED;
// 	if (move_possible(player, 'y', 'a', movement) == 0)
// 		player->posY += movement;
// 	clear(player->img);
// 	new_image(player, player->ray, player->column);
// 	return (0);
// }

// int	d_hook(t_player *player)
// {
// 	double	movement;

// 	movement = 1 * MOVESPEED;
// 	if (move_possible(player, 'x', 'd', movement) == 0)
// 		player->posX -= movement;
// 	// movement = player->corY * MOVESPEED;
// 	if (move_possible(player, 'y', 'd', movement) == 0)
// 		player->posY -= movement;
// 	clear(player->img);
// 	new_image(player, player->ray, player->column);
// 	return (0);
// }

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
	if (player->corX == 0)
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
	}
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
// probleme clear window lorsque retour sur precedente case ?
int	a_hook(t_player *player)
{
	double	moveSpeed;

	moveSpeed = 1;
	printf("go right\n");
	printf("en x: %f\n", player->posX );
	printf("en y: %f\n",player->posY);
	//printf("what is there : %d\n", player->map[(int)player->posY][(int)(player->posX - 1 * moveSpeed)]);
	if (player->corX == 0)
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
	}
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
	
	return (0);
}

int	right_arrow_hook(t_player *player)
{
	
	return (0);
}

int	close_hook(t_img *img)
{
	mlx_destroy_window (img->mlx, img->mlx_win);
	exit(0);
}

int	keys_hook(int keycode, t_player *player)
{
	if (keycode == W)
		w_hook(player);
	if (keycode == A)
		a_hook(player);
	if (keycode == S)
		s_hook(player);
	if (keycode == D)
		d_hook(player);
	if (keycode == L_ARROW)
		left_arrow_hook(player);
	if (keycode == R_ARROW)
		right_arrow_hook(player);
	if (keycode == ESC)
	{
		mlx_destroy_window (player->img->mlx, player->img->mlx_win);
		exit(0);
	}
	print_mini_map(player);
	return (0);
}