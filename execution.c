#include "cube3d.h"

#define mapWidth 20
#define mapHeight 20
#define screenWidth 640
#define screenHeight 480

typedef struct player_structure
{
	double	posX;
	double	posY;
	double	corX;
	double	corY;
	double	planeX;
	double	planeY;
	double	time;
	double	oldTime;
	int		mapHeight;
	int		mapWidth;
	int		screeHeight;
	int		screenWidth;
}		player_s;

typedef struct	ray_structure
{
	int		mapX;
	int		mapY;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
	double	cameraX;
	double	corX;
	double	corY;
	double	distX;
	double	distY;
	double	deltaDistX;
	double	deltaDistY;
	double	wallDist;
	char	**map;
}		ray_s;

typedef struct  column_structure
{
	int height;
	int start;
	int end;
	int color;
}		col_s;

int	init_player_s(player_s **player)
{
	(*player) = malloc(sizeof(player_s));
	if (!(*player))
		return (1);
	(*player)->posX = 10;
	(*player)->posY = 10;
	(*player)->corX = -1;
	(*player)->corY = 0;
	(*player)->planeX = 0;
	(*player)->planeY = 0.66;
	(*player)->time = 0;
	(*player)->oldTime = 0;
	(*player)->screenWidth = 640;
	(*player)->screenHeight = 480;
	return (0);
}

int	init_ray_s(ray_s **ray, player_s *player, char **map)
{
	(*ray) = malloc(sizeof(ray_s));
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

int	init_col_s(col_s **column)
{
	(*column) = malloc(sizeof(col_s));
	if (!(*column))
		return (1);
	(*column)->color = 0;
	(*column)->height = 0;
	(*column)->start = 0;
	(*column)->end = 0;
	return (0);
}

int	update_column(col_s **column, int wallDist)
{
	(*column)->height =

}

unsigned int    abs(int num)
{
	if (num < 0)
		return (-num);
	return (num);
}

int	update_ray_step(ray_s **ray, player_s *player)
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

int	update_ray_s(ray_s **ray, int x, player_s *player)
{
	(*ray)->mapX = player->posX;
	(*ray)->mapY = player->posY;
	(*ray)->cameraX = (2 * x / player->screenWidth) - 1;
	(*ray)->corX = player->corX + player->planeX * cameraX;
	(*ray)->corY =  player->corY + player->planeY * cameraX;
	(*ray)->deltaDistX = 0;
	(*ray)->deltaDistY = 0;
	if ((*ray)->corX == 0)
		(*ray)->wallDist = 0;
	(*ray)->map = map;
	return (0);
}

int	init_col_s(col_s **column)
{
	(*column) = malloc(sizeof(col_s));
	if (!(*column))
		return (1);
	(*column)->color = 0;
	(*column)->height = 0;
	(*column)->start = 0;
	(*column)->end = 0;
	return (0);
}

int	update_column(col_s **col, ray_s **ray, int screenHeight)
{
	col_s	*column;

	column = *col;
	column->color = 16711680;
	if ((*ray)->side ==  0)
		(*ray)->wallDist = (*ray)->sideDistX - (*ray)->delatDistX;
	else
	{
		(*ray)->wallDist = (*ray)->sideDistY - (*ray)->deltaDistY;
		column->color = column->color / 2;
	}
	column->height = screenHeight / wallDist;
	column->start = (-column->height) / 2 + screenHeight / 2;
	if (column->start < 0)
		column->start = 0;
	column->end = column->height / 2 + screenHeight / 2;
	if (column->end >= screenHeight)
		column->end = screenHeight - 1;
	return (0);
}

unsigned int	abs(int num)
{
	if (num < 0)
		return (-num);
	return (num);
}

int	update_ray_step(ray_s **ray, player_s *player)
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