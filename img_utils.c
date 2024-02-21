#include "cube3d.h"

void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->l_l + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_column(t_img *img, t_col *column)
{
	
}

int	esc_hook(int keycode, t_data *img)
{
	if (keycode == 53)
	{
		mlx_destroy_window (img->mlx, img->mlx_win);
		exit(0);
	}
	return (0);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	close_hook(t_data *img)
{
	mlx_destroy_window (img->mlx, img->mlx_win);
	exit(0);
}
