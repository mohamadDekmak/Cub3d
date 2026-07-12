#include "cub3d.h"

int	get_rgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}
