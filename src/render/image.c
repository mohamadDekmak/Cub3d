#include "cub3d.h"

int	get_rgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel_addr;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	pixel_addr = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)pixel_addr = color;
}

int	get_tex_pixel(t_img *tex, int x, int y)
{
	char	*pixel_addr;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	pixel_addr = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)pixel_addr);
}
