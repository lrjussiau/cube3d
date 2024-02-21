#include "cube3d.h"
  
   #define mapWidth 20
   #define mapHeight 20
   #define screenWidth 640
   #define screenHeight 480
  
   int gameMap[mapHeight][mapWidth]
   {
      {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 11     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
 12     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
 13     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
 14     {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,1},
 15     {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,1},
 16     {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,1},
 17     {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,1},
 18     {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,1},
 19     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
 20     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
 21     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
 22     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
 23     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
 24     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
 25     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
 26     {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,1},
 27     {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,1},
 28     {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,1},
 29     {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,1},
 30 };
 31
 32 typedef struct player_structure{
 33     double  posX;
 34     double  posY;
 35     double  corX;
 36     double  corY;
 37     double  planeX;
 38     double  planeY;
 39     double  time;
 40     double  oldTime;
 41     int     mapHeight;
 42     int     mapWidth;
 43     int     screeHeight;
 44     int     screenWidth;
 45 }                   player_s;
 46
 47 typedef struct  ray_structure{
 48     int     mapX;
 49     int     mapY;
 50     int     stepX;
 51     int     stepY;
 52     int     hit;
 53     int     side;
 54     double  cameraX;
 55     double  corX;
 56     double  corY;
 57     double  distX;
 58     double  distY;
 59     double  deltaDistX;
 60     double  deltaDistY;
 61     double  wallDist;
 62     char    **map;
 63
 64 }                   ray_s;
 65
 66 typedef struct  column_structure{
 67     int height;
 68     int start;
 69     int end;
 70     int color;
		int	corX;
 71 }           col_s;

 typedef struct s_image{
	void	*mlx;
	void	*mlx_win;
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		l_l;
	int		en;
 }				t_img;

 72
 73 int init_player_s(player_s **player)
 74 {
 75     (*player) = malloc(sizeof(player_s));
 76     if (!(*player))
 77         return (1);
 78     (*player)->posX = 10;
 79     (*player)->posY = 10;
 80     (*player)->corX = -1;
 81     (*player)->corY = 0;
 82     (*player)->planeX = 0;
 83     (*player)->planeY = 0.66;
 84     (*player)->time = 0;
 85     (*player)->oldTime = 0;
 86     (*player)->screenWidth = 640;
 87     (*player)->screenHeight = 480;
 88     return (0);
 89 }
 90
 91 int init_ray_s(ray_s **ray, player_s *player, char **map)
 92 {
 93     (*ray) = malloc(sizeof(ray_s));
 94     if (!(*ray))
 95         return (1);
 96     (*ray)->mapX = 0;
 97     (*ray)->mapY = 0;
 98     (*ray)->stepX = 0;
 99     (*ray)->stepY = 0;
100     (*ray)->hit = 0;
101     (*ray)->side = 0;
102     (*ray)->cameraX = 0;
103     (*ray)->corX = 0;
104     (*ray)->corY = 0;
105     (*ray)->distX = 0;
106     (*ray)->distY = 0;
107     (*ray)->deltaDistX = 0;
108     (*ray)->deltaDistY = 0;
109     (*ray)->wallDist = 0;
110     (*ray)->map = map;
111     return (0);
112 }
113
114 int init_col_s(col_s **column)
115 {
116     (*column) = malloc(sizeof(col_s));
117     if (!(*column))
118         return (1);
119     (*column)->color = 0;
120     (*column)->height = 0;
121     (*column)->start = 0;
122     (*column)->end = 0;
123     return (0);
124 }

int	init_img_s(t_img **img)
{
	img->mlx_win = mlx_new_window(img->mlx, SCREEN_X_SIZE, SCREEN_Y_SIZE, "CUBE3D");
	img->img_ptr = mlx_new_image(img->mlx, SCREEN_X_SIZE, SCREEN_Y_SIZE );
	if (!img->img_ptr)
		return (0);
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->l_l, &img->en);
	return (1);
}
125
126 int update_column(col_s **col, ray_s **ray, int screenHeight)
127 {
128     col_s   *column;
129
130     column = *col;
131     column->color = 16711680;
132     if ((*ray)->side ==  0)
133         (*ray)->wallDist = (*ray)->sideDistX - (*ray)->delatDistX;
134     else
135     {
136         (*ray)->wallDist = (*ray)->sideDistY - (*ray)->deltaDistY;
137         column->color = column->color / 2;
138     }
139     column->height = screenHeight / wallDist;
140     column->start = (-column->height) / 2 + screenHeight / 2;
141    if (column->start < 0)
142        column->start = 0;
143    column->end = column->height / 2 + screenHeight / 2;
144    if (column->end >= screenHeight)
145        column->end = screenHeight - 1;
146    return (0);
}
129
130
131 unsigned int    abs(int num)
132 {
133     if (num < 0)
134         return (-num);
135     return (num);
136 }
137
138 int update_ray_step(ray_s **ray, player_s *player)
139 {
140     if ((*ray)->corX < 0)
141     {
142         (*ray)->stepX = -1;
143         (*ray)->sideDistX = (player->posX - (*ray)->mapX) * (*ray)->deltaDistX;
144     }
145     else
146     {
147         (*ray)->stepX = 1;
148         (*ray)->sideDistX = ((*ray)->mapX + 1.0 - player->posX) * (*ray)->deltaDistX;
149     }
150     if ((*ray)->corY < 0)
151     {
152         (*ray)->stepY = -1;
153         (*ray)->sideDistY = (player->posY - (*ray)->mapY) * (*ray)->deltaDistY;
154     }
155     else
156     {
157         (*ray)->stepY = 1;
158         (*ray)->sideDistX = ((*ray)->mapY + 1.0 - player->posY) * (*ray)->deltaDistY;
159     }
160     return (0);
161 };
162
163
164 int update_ray_s(ray_s **ray, int x, player_s *player)
165 {
166     (*ray)->mapX = player->posX;
167     (*ray)->mapY = player->posY;
168     (*ray)->cameraX = (2 * x / player->screenWidth) - 1;
169     (*ray)->corX = player->corX + player->planeX * cameraX;
170     (*ray)->corY =  player->corY + player->planeY * cameraX;
171     (*ray)->deltaDistX = 0;
		if ((*ray)->corX == 0)
194         (*ray)->deltaDistX = le30;
195     else
196         (*ray)->deltaDistX = (abs(1 / corX);
		if ((*ray)->corY == 0)
194         (*ray)->deltaDistY = le30;
195     else
196         (*ray)->deltaDistY = (abs(1 / corX);
110     (*ray)->map = map;
		update_ray_step(ray, player);
111     return (0);
112 }
113
114 int init_col_s(col_s **column)
115 {
116     (*column) = malloc(sizeof(col_s));
117     if (!(*column))
118         return (1);
119     (*column)->color = 0;
120     (*column)->height = 0;
121     (*column)->start = 0;
122     (*column)->end = 0;
123     return (0);
124 }
125
126 int update_column(col_s **col, ray_s **ray, int screenHeight, int x)
127 {
128     col_s   *column;
129
130     column = *col;
131     column->color = 16711680;
132     if ((*ray)->side ==  0)
133         (*ray)->wallDist = (*ray)->sideDistX - (*ray)->delatDistX;
134     else
135     {
136         (*ray)->wallDist = (*ray)->sideDistY - (*ray)->deltaDistY;
137         column->color = column->color / 2;
138     }
139     column->height = screenHeight / wallDist;
140     column->start = (-column->height) / 2 + screenHeight / 2;
141    if (column->start < 0)
142        column->start = 0;
143    column->end = column->height / 2 + screenHeight / 2;
144    if (column->end >= screenHeight)
145        column->end = screenHeight - 1;
		column->corX = x;
146    return (0);
147 }
148
149
150
151 unsigned int    abs(int num)
152 {
153     if (num < 0)
154         return (-num);
155     return (num);
156 }
157
158 int update_ray_step(ray_s **ray, player_s *player)
159 {
160     if ((*ray)->corX < 0)
161     {
162         (*ray)->stepX = -1;
163         (*ray)->sideDistX = (player->posX - (*ray)->mapX) * (*ray)->deltaDistX;
164     }
165     else
166     {
167         (*ray)->stepX = 1;
168         (*ray)->sideDistX = ((*ray)->mapX + 1.0 - player->posX) * (*ray)->deltaDistX;
169     }
170     if ((*ray)->corY < 0)
171     {
172         (*ray)->stepY = -1;
173         (*ray)->sideDistY = (player->posY - (*ray)->mapY) * (*ray)->deltaDistY;
174     }
175     else
176     {
177         (*ray)->stepY = 1;
178         (*ray)->sideDistX = ((*ray)->mapY + 1.0 - player->posY) * (*ray)->deltaDistY;
179     }
180     return (0);
181 };
182
183
184 int update_ray_s(ray_s **ray, int x, player_s *player)
185 {
186     (*ray)->mapX = player->posX;
187     (*ray)->mapY = player->posY;
188     (*ray)->cameraX = (2 * x / player->screenWidth) - 1;
189     (*ray)->corX = player->corX + player->planeX * cameraX;
190     (*ray)->corY =  player->corY + player->planeY * cameraX;
191     (*ray)->deltaDistX = 0;
192     (*ray)->deltaDistY = 0;
193     if ((*ray)->corX == 0)
194         (*ray)->deltaDistX = le30;
		else
152         (*ray)->deltaDistX = (abs(1 / corX);
153     if ((*ray)->corY == 0)
154         (*ray)->deltaDistY = le30;
155     else
156         (*ray)->deltaDistY = (abs(1 / corY);
157     return (update_ray_step(ray, player);
	}

int dda(ray_s **rayon)
{
	ray_s   *ray;

	ray = *rayon;
	while (ray->hit == 0)
	{
			if (ray->sideDistX < ray->sideDistY)
		{
				ray->sideDistX += ray->deltaDistX;
			ray->mapX += stepX;
			ray->side = 0;
		}
		else
		{
				ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		if (ray->map[ray->mapX][ray->mapY] > 0)
			ray->hit = 1;
	}
	return (0);
}

int main()
{
	player_s    *player;
	ray_s       *ray;
	t_col		*column;
	t_img		img;
	int         x;

	x = 0;
	img.mlx = mlx_init();
	if (!img.mlx)
		return (1);
	if (init_player_s(&player)
		return (1);
	if (init_ray_s(&ray, player)
		return (1);
	if (init_col_s(&column))
		return (1);
	if (!init_img(&img))
		return (1);
	while (x < player->screenWidth)
	{
		update_ray_s(&ray, player);
		dda(&ray);
		update_column(&column, ray, player->screenHeight, int x);
		draw_column(&img, column);
	x++;   
	}
	mlx_key_hook (img.mlx_win, esc_hook, &img);
	mlx_hook(img.mlx_win, 17, 1L << 17, close_hook, &img);
	mlx_loop(img.mlx);
}